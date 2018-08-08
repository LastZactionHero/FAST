# FAST

An implementation of the FAST algorithm for corner detection.

## Usage

1. Run `./convert.sh` to convert an image into a 320x240 grayscale byte stream file
2. Compile `gcc ./src/fast.c`
3. Run `./a.out`

### Results from test image of my car

Threshold `0x40`

```
Found corner: (14, 115)
Found corner: (15, 115)
Found corner: (17, 65)
Found corner: (52, 7)
Found corner: (71, 171)
Found corner: (72, 172)
Found corner: (83, 180)
Found corner: (131, 40)
Found corner: (151, 29)
Found corner: (152, 56)
Found corner: (152, 57)
Found corner: (154, 57)
Found corner: (154, 58)
Found corner: (156, 12)
Found corner: (177, 87)
Found corner: (196, 59)
Found corner: (205, 62)
Found corner: (206, 62)
Found corner: (289, 8)
Found corner: (289, 60)
Found corner: (290, 8)
```