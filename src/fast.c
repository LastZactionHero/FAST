#include <stdio.h>

#define INPUT_FILE "./output.gray"
#define DIMENSION_WIDTH 320
#define DIMENSION_HEIGHT 240
#define BORDER 4

#define PIXEL_COUNT DIMENSION_WIDTH * DIMENSION_HEIGHT
#define THRESHOLD 0x40

unsigned char image[PIXEL_COUNT];

unsigned char getPixel(int x, int y);
int fast(int x, int y, unsigned char *pixel);

int main() {
  printf("FAST\n");

  FILE *fp = fopen(INPUT_FILE, "rb");
  fread(image, PIXEL_COUNT, 1, fp);

  // Reverse endianness, fread loads this in backwards
  // for(int i = 0; i < PIXEL_COUNT / 2; i++) {
  //   unsigned char tmp = image[i * 2];
  //   image[i * 2] = image[i * 2 + 1];
  //   image[i * 2 + 1] = tmp;
  // }


  for(int x = BORDER; x < DIMENSION_WIDTH - 2 * BORDER; x++) {
    for(int y = BORDER; y < DIMENSION_HEIGHT - 2 * BORDER; y++) {
      if(fast(x, y, image)) {
        printf("Found corner: (%d, %d)\n", x, y);
      }
    }
  }


  fclose(fp);
}

unsigned char getPixel(int x, int y) {
  return image[y * DIMENSION_WIDTH + x];
}

int fast(int x, int y, unsigned char *image) {
  unsigned char pixel = getPixel(x, y);

  // Pixel is within THRESHOLD of min or max, impossible to a corner
  if(pixel <= THRESHOLD || pixel >= 0xFF - THRESHOLD) {
    return 0;
  }

  unsigned char neighbors[16];
  neighbors[0] = getPixel(x, y - 3);
  neighbors[1] = getPixel(x + 1, y - 3);
  neighbors[2] = getPixel(x + 2, y - 2);
  neighbors[3] = getPixel(x + 3, y - 1);
  neighbors[4] = getPixel(x + 3, y);
  neighbors[5] = getPixel(x + 3, y + 1);
  neighbors[6] = getPixel(x + 2, y + 2);
  neighbors[7] = getPixel(x + 1, y + 3);
  neighbors[8] = getPixel(x, y + 3);
  neighbors[9] = getPixel(x - 1, y + 3);
  neighbors[10] = getPixel(x - 2, y + 2);
  neighbors[11] = getPixel(x - 3, y + 1);
  neighbors[12] = getPixel(x - 3, y);
  neighbors[13] = getPixel(x - 3, y - 1);
  neighbors[14] = getPixel(x - 2, y - 2);
  neighbors[15] = getPixel(x - 1, y - 3);

  for(int i = 0; i < 16; i++) {
    int direction = 0;
    for(int j = 0; j < 12; j++) {
      int possibleMatch = 1;
      int neighborIdx = (i + j) % 12;
      unsigned char neighborPixel = neighbors[neighborIdx];

      // Is the first pixel lighter, darker, or the same as the center pixel?
      if(j == 0) {
        if(neighborPixel > pixel) {
          // Lighter
          direction = 1;
        } else if(neighborPixel < pixel) {
          // Darker
          direction = -1;
        } else {
          break; // Pixels are equal, nothing to do here.
        }
      }

      if(direction == 1) {
        // Make sure all surrounding pixels are at least THRESHOLD lighter
        if(neighborPixel <= (pixel + THRESHOLD)) {
          possibleMatch = 0;
        }
      } else {
        // Make sure all surrounding pixels are at least THRESHOLD darker
        if(neighborPixel >= pixel - THRESHOLD) {
          possibleMatch = 0;
        }
      }

      if(!possibleMatch) {
        break;
      }
      if(j == 11 && possibleMatch) {
        return 1;
      }
    }
  }

  return 0;
}