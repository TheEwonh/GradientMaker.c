#include "gradientMaker.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

char NumvaltoHEX(int val) {
    if (val < 10 || val > 15) {
        printf("Invalid hex value given\n");
        return 1;
    }
    return (val == 10) ? 'A' :
           (val == 11) ? 'B' :
           (val == 12) ? 'C' :
           (val == 13) ? 'D' :
           (val == 14) ? 'E' :
           (val == 15) ? 'F' : 1;
}
int HEXvaltoNum(char val) {
    return (toupper(val) == 'A') ? 10 :
           (toupper(val) == 'B') ? 11 :
           (toupper(val) == 'C') ? 12 :
           (toupper(val) == 'D') ? 13 :
           (toupper(val) == 'E') ? 14 :
           (toupper(val) == 'F') ? 15 : 1;
}
int checkHEX(char *hex) {
    char hexValues[] = "0123456789abcdef";
    if (strlen(hex) != 6) {
        return 1;
    }
    for (int num = 0; num < strlen(hex); num++) {
        int broke = 0;
        for (int val = 0; val < strlen(hexValues); val++) {
            if (tolower(hex[num]) == hexValues[val]) {
                broke = 1;
            }
        }
        if (!broke) {
            return 1;
        }
    }

    return 0;
}
int checkRGB(int rgb[3]) {
    for (int i = 0; i < 3; i++) {
        if (rgb[i] < 0 || rgb[i] > 255) {
            return 1;
        }
    }
    return 0;
}
int HEXtoRGB(char *hex, int *rgb) {
    if (checkHEX(hex)) {
        printf("Invalid hex code was given!\n");
        return 1;
    }
    for (int i = 0; i < 5; i+=2) {
        if (isdigit(hex[i])) {
            rgb[i/2] += 16*(hex[i]-'0');
        } else {
            rgb[i/2] += 16*HEXvaltoNum(hex[i]);
        }

        if (isdigit(hex[i+1])) {
            rgb[i/2] += hex[i+1]-'0';
        } else {
            rgb[i/2] += HEXvaltoNum(hex[i+1]);
        }
    }
    return 0;
}
int RGBtoHEX(int *rgb, char *hex) {
    if (checkRGB(rgb)) {
        printf("Invalid RGB value was given!\n");
        return 1;
    }
    int red = rgb[0] / 16;
    int green = rgb[1] / 16;
    int blue = rgb[2] / 16;
    if (red >= 10) {
        hex[0] = NumvaltoHEX(red);
    } else {
        hex[0] = red + '0';
    }
    red = rgb[0] - (16 * red);
    if (red >= 10) {
        hex[1] = NumvaltoHEX(red);
    } else {
        hex[1] = red + '0';
    }

    if (green >= 10) {
        hex[2] = NumvaltoHEX(green);
    } else {
        hex[2] = green + '0';
    }
    green = rgb[1] - (16 * green);
    if (green >= 10) {
        hex[3] = NumvaltoHEX(green);
    } else {
        hex[3] = green + '0';
    }

    if (blue >= 10) {
        hex[4] = NumvaltoHEX(blue);
    } else {
        hex[4] = blue + '0';
    }
    blue = rgb[2] - (16 * blue);
    if (blue >= 10) {
        hex[5] = NumvaltoHEX(blue);
    } else {
        hex[5] = blue + '0';
    }
    hex[6] = '\0';
    return 0;
}
int interpolate(int colors[][3], char *text) {
    int textLength = strlen(text);
    double firstAmp = 1;
    double secondAmp = 0;
    for (int i = 1; i < textLength-1; i++) {
        firstAmp -= 1.0 / (textLength - 1);
        secondAmp += 1.0 / (textLength - 1);
        // Interpolation formula: ((color1 * firstAmp) + (color2 * secondAmp))
        for (int j = 0; j < 3; j++) {
            colors[i][j] = round((((double)colors[0][j] * firstAmp) + ((double)colors[textLength-1][j] * secondAmp)));
        }
    }
    return 0;
}
int make(char **interpolated, int colors[][3], char *text) {
    *interpolated = malloc(1);
    if (*interpolated == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    (*interpolated)[0] = '\0';
    size_t capacity = 1;
    for (int i = 0; i < strlen(text); i++) {
        capacity += 27;
        char *temp = realloc(*interpolated, capacity);
        if (temp == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
        *interpolated = temp;
        char toWrite[30] = "\0";
        snprintf(toWrite, sizeof(toWrite), "\033[38;2;%d;%d;%dm%c", colors[i][0], colors[i][1], colors[i][2], text[i]);
        strcat(*interpolated, toWrite);
    }
    char *temp = realloc(*interpolated, capacity+9);
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    *interpolated = temp;
    temp = NULL;
    strcat(*interpolated, "\033[0m");
    return 0;
}
int render(int colors[][3], char *text) {
    for (int i = 0; i < strlen(text); i++) {
        printf("\033[38;2;%d;%d;%dm%c", colors[i][0], colors[i][1], colors[i][2], text[i]);
    }
    printf("\033[0m\n");

    for (int i = 0; i < strlen(text); i++) {
        char hex[7] = "0";
        RGBtoHEX(colors[i], hex);
        printf("\033[38;2;%d;%d;%dm%c\033[0m -> (\033[38;2;%d;0;0m%d\033[0m, \033[38;2;0;%d;0m%d\033[0m, \033[38;2;0;0;%dm%d\033[0m) / #\033[38;2;%d;%d;%dm%s\033[0m\n",
               colors[i][0], colors[i][1], colors[i][2], text[i], colors[i][0], colors[i][0], colors[i][1], colors[i][1], colors[i][2], colors[i][2], colors[i][0], colors[i][1], colors[i][2], hex);
    }
    return 0;
}
