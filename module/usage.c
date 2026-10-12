#include "gradientMaker.h"
#include <string.h>
#include <stdio.h>

/*  Gradient Maker library (C)
 *
 *  FUNCTIONS USAGE:
 *
 *  char NumvaltoHEX(int val); - Converts number to hex letter
 *  Arguments: int val - Number from 10 to 15
 *  Return: 'A'-'F' if number between 10 to 15, else 1
 *
 *  int HEXvaltoNum(char hex); - Converts hex letter to number
 *  Arguments: char val - letter 'A'-'F'
 *  Return: 10-15 if letter in range 'A'-'F', else 1
 *
 *  int checkHEX(char *hex); - Checks hex code for validation
 *  Arguments: char *hex - hex code
 *  Return: 0 if hex code is valid, else 1
 *
 *  int checkRGB(int rgb[3]); - Checks RGB color for validation
 *  Arguments: int rgb[3] - RGB color
 *  Return: 0 if rgb color is valid, else 1
 *
 *  int HEXtoRGB(char *hex, int *rgb); - Converts HEX code to RGB values
 *  Arguments: char *hex - HEX code
 *             int *rgb - container for rgb values (empty)
 *  Return: 0 if executed with no errors, else 1
 *
 *  int RGBtoHEX(int *rgb, char *hex); - Converts RGB color to HEX code
 *  Arguments: int *rgb - RGB color
 *             char *hex - string for hex code (empty)
 *  Return: 0 if executed with no errors, else 1
 *
 *  int interpolate(int colors[][3], char *text); - Creates in-between colors for text
 *  Arguments: int colors[][3] - container for colors
 *             char *text - text
 *  Return: 0 if executed with no errors, else 1
 *  NOTE: colors array should contain first and last colors in the start and the end of array, else unexpected behavior
 *
 *  int render(int colors[][3], char *text); - Output colored text with printf
 *  Arguments: int colors[][3] - container for colors to each character
 *             char *text - text
 *  Return: 0 if executed with no errors, else 1
 *  NOTE: colors length and text length should be equal, else unexpected behavior
 *
 *  int make(char **interpolated, int colors[][3], char *text); - Apply gradient to text
 *  Arguments: char **interpolated - string for final text
 *             int colors[][3] - container for colors to each character
 *             char *text - text
 *  Return: 0 if executed with no errors, else 1
 *  NOTE: colors length and text length should be equal, else unexpected behavior
 */

int main() {
    // FIRST EXAMPLE
    char *firstHex = "21fabd";
    char *secondHex = "da1021";
    char *text = "Hello, world!";
    int colors[strlen(text)][3];
    int firstRGB[3] = {0, 0, 0};
    if (HEXtoRGB(firstHex, firstRGB)) {
        printf("Failed to convert HEX code to RGB values!\n");
        return 1;
    }
    int secondRGB[3] = {0, 0, 0};
    if (HEXtoRGB(secondHex, secondRGB)) {
        printf("Failed to convert HEX code to RGB values!\n");
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        colors[0][i] = firstRGB[i];
        colors[strlen(text)-1][i] = secondRGB[i];
    }

    if (interpolate(colors, text)) {
        printf("Couldn't create colors in-between!\n");
        return 1;
    };
    /*if (render(colors, text)) {
        printf("Couldn't output text!\n");
        return 1;
    };*/

    // SECOND EXAMPLE
    firstHex = "123bad";
    secondHex = "fab872";
    memset(firstRGB, 0, sizeof(firstRGB));
    memset(secondRGB, 0, sizeof(secondRGB));
    if (HEXtoRGB(firstHex, firstRGB)) {
        printf("Failed to convert HEX code to RGB values!\n");
        return 1;
    }
    if (HEXtoRGB(secondHex, secondRGB)) {
        printf("Failed to convert HEX code to RGB values!\n");
        return 1;
    }

    char *secondText = "Library written by TheEwonh!";
    int secondColors[strlen(secondText)][3] = {};
    for (int i = 0; i < 3; i++) {
        secondColors[0][i] = firstRGB[i];
        secondColors[strlen(secondText)-1][i] = secondRGB[i];
    }
    if (interpolate(secondColors, secondText)) {
        printf("Couldn't create colors in-between!\n");
        return 1;
    }

    char *finalResult;
    if (make(&finalResult, secondColors, secondText)) {
        printf("Couldn't apply gradient to text!\n");
        return 1;
    }
    printf("%s\n", finalResult);
    return 0;
}
