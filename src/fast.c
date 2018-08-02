#include <stdio.h>

#define INPUT_FILE "./output.gray"
#define DIMENSION_WIDTH 320
#define DIMENSION_HEIGHT 240
#define BORDER 3

#define PIXEL_COUNT DIMENSION_WIDTH * DIMENSION_HEIGHT

unsigned char image[PIXEL_COUNT];

int fast(unsigned char *pixel);

int main() {
  printf("FAST\n");

  FILE *fp = fopen(INPUT_FILE, "rb");
  fread(image, PIXEL_COUNT, 1, fp);

  // Reverse endianness, fread loads this in backwards
  for(int i = 0; i < PIXEL_COUNT / 2; i++) {
    unsigned char tmp = image[i * 2];
    image[i * 2] = image[i * 2 + 1];
    image[i * 2 + 1] = tmp;
  }
  // dadce1e5
  // 0000000 dcda e5e1 eeea f1f0 faf6 edf9 d4dd e0d8
  int cornerCount = 0;
  for(int x = BORDER; x < DIMENSION_WIDTH - 2 * BORDER; x++) {
    for(int y = BORDER; y < DIMENSION_HEIGHT - 2 * BORDER; y++) {
      if(fast(&image[x * DIMENSION_HEIGHT + y]) == 1) {
        printf("(%d,%d)\n", x, y);
        cornerCount++;
      }
    }
  }

  printf("Corner Count: %d\n", cornerCount);


  fclose(fp);
}

int fast(unsigned char *pixel) {
  unsigned char neighbors[16];
  neighbors[0] = *(pixel - 3 * DIMENSION_WIDTH);
  neighbors[1] = *(pixel - 3 * DIMENSION_WIDTH + 1);
  neighbors[2] = *(pixel - 2 * DIMENSION_WIDTH + 2);
  neighbors[3] = *(pixel - 1 * DIMENSION_WIDTH + 3);
  neighbors[4] = *(pixel - 0 * DIMENSION_WIDTH + 3);
  neighbors[5] = *(pixel + 1 * DIMENSION_WIDTH + 3);
  neighbors[6] = *(pixel + 2 * DIMENSION_WIDTH + 2);
  neighbors[7] = *(pixel + 3 * DIMENSION_WIDTH + 1);
  neighbors[8] = *(pixel + 3 * DIMENSION_WIDTH + 0);
  neighbors[9] = *(pixel + 3 * DIMENSION_WIDTH - 1);
  neighbors[10] = *(pixel + 2 * DIMENSION_WIDTH - 2);
  neighbors[11] = *(pixel + 1 * DIMENSION_WIDTH - 3);
  neighbors[12] = *(pixel + 0 * DIMENSION_WIDTH - 3);
  neighbors[13] = *(pixel - 1 * DIMENSION_WIDTH - 3);
  neighbors[14] = *(pixel - 2 * DIMENSION_WIDTH - 2);
  neighbors[15] = *(pixel - 3 * DIMENSION_WIDTH - 1);

  // printf("-----\n");
  for(int i = 0; i < 16; i++) {
    if(*pixel < neighbors[i] && neighbors[i] - *pixel > 254) {
      neighbors[i] = neighbors[i] - *pixel;
    } else {
      neighbors[i] = *pixel;
    }
    // printf("%x\n", neighbors[i]);
  }
  // printf("-----\n");

  for(int i = 0; i < 16; i++) {
    for(int j = 0; j < 12; j++) {
      int idx = j + i % 12;
      if(neighbors[idx] == *pixel) {
        break;
      }
      printf("Pixel: %x\n", *pixel);
      for(int k = 0; k < 16; k++){
        printf("%x", neighbors[i]);
      }
      printf("\n");
      return 1;
    }
  }
  return 0;
}