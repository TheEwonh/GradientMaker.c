#ifndef gradientMaker_H
#define gradientMaker_H

char NumvaltoHEX(int val); // Convert num to hex
int HEXvaltoNum(char val); // Convert hex value to number
int checkHEX(char *hex); // Check HEX code for validation, return 0 if valid hex code
int checkRGB(int rgb[3]); // Check RGB code for validation, returns 0 if valid rgb
int HEXtoRGB(char *hex, int *rgb); // Convert HEX code to RGB
int RGBtoHEX(int *rgb, char *hex); // Convert RGB code to HEX
int interpolate(int colors[][3], char *text); // Create in-between colors
int make(char **interpolated, int colors[][3], char *text); // Apply gradient to text, but not print it
int render(int colors[][3], char *text); // Output text with gradient

#endif
