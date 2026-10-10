#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

struct RGB {
    int red;
    int green;
    int blue;
};

int checkHEX(char *hex); // Check HEX code for validation, return 1 if valid hex code
void HEXtoRGB(char *hex, struct RGB *color); // Convert HEX code to RGB
void RGBtoHEX(struct RGB *color, char *hex); // Convert RGB code to HEX
void interpolate(struct RGB *colors, char *text); // Create in-between colors
void render(struct RGB *colors, char *text); // Output text with gradient

int main() {
    // Request data to work with
    char firstHEX[7] = "000000\0";
    int c;
    do {
        if (c == EOF) {
            return 1;
        }
        printf("Enter first hex code: #");
        scanf("%6s", firstHEX);

        // Clear input buffer
        if ((c = getchar()) != '\n') {
            printf("Invalid hex code was given! Example: FF12AB; 127bae\n");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        if (!checkHEX(firstHEX)) {
            printf("Invalid hex code was given! Example: FF12AB; 127bae\n");
            continue;
        }
        break;
    } while (1);
    c = 0;

    char secondHEX[7] = "000000\0";
    do {
        if (c == EOF) {
            return 1;
        }
        printf("Enter second hex code: #");
        scanf("%6s", secondHEX);

        // Clear input buffer
        int c;
        if ((c = getchar()) != '\n') {
            printf("Invalid hex code was given! Example: FF12AB; 127bae\n");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        if (!checkHEX(secondHEX)) {
            printf("Invalid hex code was given! Example: FF12AB; 127bae\n");
            continue;
        }
        break;
    } while (1);
    // Convert HEX to RGB
    struct RGB firstRGB = {0, 0, 0};
    HEXtoRGB(firstHEX, &firstRGB);

    struct RGB secondRGB = {0, 0, 0};
    HEXtoRGB(secondHEX, &secondRGB);

    // Request text
    c = 0;
    char text[2049] = {'0'};
    printf("Enter text (2048 characters maximum): ");
    fgets(text, 2049, stdin);
    if (text[strlen(text)-1] != '\0') {
        if (text[strlen(text)-1] != '\n') {
            printf("Text is too large, only up to 2048!\n");
            return 1;
        }
        text[strlen(text)-1] = '\0';
    }
    int textLength = strlen(text);

    // Create list of colors to interpolate
    struct RGB *colors = malloc(textLength);
    colors[0] = firstRGB;
    colors[textLength-1] = secondRGB;
    interpolate(colors, text);

    // Render text with applied gradient
    render(colors, text);

    return 0;
}

int checkHEX(char *hex) {
    char hexValues[] = "0123456789abcdef";
    if (strlen(hex) != 6) {
        return 0;
    }
    for (int num = 0; num < strlen(hex); num++) {
        int broke = 0;
        for (int val = 0; val < strlen(hexValues); val++) {
            if (tolower(hex[num]) == hexValues[val]) {
                broke = 1;
            }
        }
        if (!broke) {
            return 0;
        }
    }

    return 1;
}
void HEXtoRGB(char *hex, struct RGB *color) {
    for (int i = 0; i < 5; i+=2) {
        if (i == 0) {
            if (isdigit(hex[i])) {
                color->red += 16*(hex[i] - '0');
            } else {
                color->red += 16*((toupper(hex[i]) == 'A') ? 10 :
                                  (toupper(hex[i]) == 'B') ? 11 :
                                  (toupper(hex[i]) == 'C') ? 12 :
                                  (toupper(hex[i]) == 'D') ? 13 :
                                  (toupper(hex[i]) == 'E') ? 14 : 15);
            }

            if (isdigit(hex[i+1])) {
                color->red += hex[i+1] - '0';
            } else {
                color->red += (toupper(hex[i+1]) == 'A') ? 10 :
                              (toupper(hex[i+1]) == 'B') ? 11 :
                              (toupper(hex[i+1]) == 'C') ? 12 :
                              (toupper(hex[i+1]) == 'D') ? 13 :
                              (toupper(hex[i+1]) == 'E') ? 14 : 15;
            }
            continue;
        } else if (i == 2) {
            if (isdigit(hex[i])) {
                color->green += 16*(hex[i] - '0');
            } else {
                color->green += 16*((toupper(hex[i]) == 'A') ? 10 :
                                    (toupper(hex[i]) == 'B') ? 11 :
                                    (toupper(hex[i]) == 'C') ? 12 :
                                    (toupper(hex[i]) == 'D') ? 13 :
                                    (toupper(hex[i]) == 'E') ? 14 : 15);
            }

            if (isdigit(hex[i+1])) {
                color->green += hex[i+1] - '0';
            } else {
                color->green += (toupper(hex[i+1]) == 'A') ? 10 :
                                (toupper(hex[i+1]) == 'B') ? 11 :
                                (toupper(hex[i+1]) == 'C') ? 12 :
                                (toupper(hex[i+1]) == 'D') ? 13 :
                                (toupper(hex[i+1]) == 'E') ? 14 : 15;
            }
            continue;
        } else if (i == 4) {
            if (isdigit(hex[i])) {
                color->blue += 16*(hex[i] - '0');
            } else {
                color->blue += 16*((toupper(hex[i]) == 'A') ? 10 :
                                   (toupper(hex[i]) == 'B') ? 11 :
                                   (toupper(hex[i]) == 'C') ? 12 :
                                   (toupper(hex[i]) == 'D') ? 13 :
                                   (toupper(hex[i]) == 'E') ? 14 : 15);
            }

            if (isdigit(hex[i+1])) {
                color->blue += hex[i+1] - '0';
            } else {
                color->blue += (toupper(hex[i+1]) == 'A') ? 10 :
                               (toupper(hex[i+1]) == 'B') ? 11 :
                               (toupper(hex[i+1]) == 'C') ? 12 :
                               (toupper(hex[i+1]) == 'D') ? 13 :
                               (toupper(hex[i+1]) == 'E') ? 14 : 15;
            }
        }
    }
}
void RGBtoHEX(struct RGB *color, char *hex) {
    int red = color->red / 16;
    int green = color->green / 16;
    int blue = color->blue / 16;
    if (red >= 10) {
        hex[0] = (red == 10) ? 'A' :
                 (red == 11) ? 'B' :
                 (red == 12) ? 'C' :
                 (red == 13) ? 'D' :
                 (red == 14) ? 'E' : 'F';
    } else {
        hex[0] = red + '0';
    }
    red = color->red - (16 * red);
    if (red >= 10) {
        hex[1] = (red == 10) ? 'A' :
                 (red == 11) ? 'B' :
                 (red == 12) ? 'C' :
                 (red == 13) ? 'D' :
                 (red == 14) ? 'E' : 'F';
    } else {
        hex[1] = red + '0';
    }

    if (green >= 10) {
        hex[2] = (green == 10) ? 'A' :
                 (green == 11) ? 'B' :
                 (green == 12) ? 'C' :
                 (green == 13) ? 'D' :
                 (green == 14) ? 'E' : 'F';
    } else {
        hex[2] = green + '0';
    }
    green = color->green - (16 * green);
    if (green >= 10) {
        hex[3] = (green == 10) ? 'A' :
                 (green == 11) ? 'B' :
                 (green == 12) ? 'C' :
                 (green == 13) ? 'D' :
                 (green == 14) ? 'E' : 'F';
    } else {
        hex[3] = green + '0';
    }

    if (blue >= 10) {
        hex[4] = (blue == 10) ? 'A' :
                 (blue == 11) ? 'B' :
                 (blue == 12) ? 'C' :
                 (blue == 13) ? 'D' :
                 (blue == 14) ? 'E' : 'F';
    } else {
        hex[4] = blue + '0';
    }
    blue = color->blue - (16 * blue);
    if (blue >= 10) {
        hex[5] = (blue == 10) ? 'A' :
                 (blue == 11) ? 'B' :
                 (blue == 12) ? 'C' :
                 (blue == 13) ? 'D' :
                 (blue == 14) ? 'E' : 'F';
    } else {
        hex[5] = blue + '0';
    }
    hex[6] = '\0';
}
void interpolate(struct RGB *colors, char *text) {
    int textLength = strlen(text);
    double firstAmp = 1;
    double secondAmp = 0;
    for (int i = 1; i < textLength-1; i++) {
        firstAmp -= 1.0 / (textLength - 1);
        secondAmp += 1.0 / (textLength - 1);
        // Interpolation formula: ((color1 * firstAmp) + (color2 * secondAmp))
        int red = round((((double)colors[0].red * firstAmp) + ((double)colors[textLength-1].red * secondAmp)));
        int green = round((((double)colors[0].green * firstAmp) + ((double)colors[textLength-1].green * secondAmp)));
        int blue = round((((double)colors[0].blue * firstAmp) + ((double)colors[textLength-1].blue * secondAmp)));
        colors[i] = (struct RGB){red, green, blue};
    }
}
void render(struct RGB *colors, char *text) {
    for (int i = 0; i < strlen(text); i++) {
        printf("\033[38;2;%d;%d;%dm%c", colors[i].red, colors[i].green, colors[i].blue, text[i]);
    }
    printf("\033[0m\n");

    for (int i = 0; i < strlen(text); i++) {
        char hex[7] = "0";
        RGBtoHEX(&colors[i], hex);
        printf("\033[38;2;%d;%d;%dm%c\033[0m -> (\033[38;2;%d;0;0m%d\033[0m, \033[38;2;0;%d;0m%d\033[0m, \033[38;2;0;0;%dm%d\033[0m) / #\033[38;2;%d;%d;%dm%s\033[0m\n",
               colors[i].red, colors[i].green, colors[i].blue, text[i], colors[i].red, colors[i].red, colors[i].green, colors[i].green, colors[i].blue, colors[i].blue, colors[i].red, colors[i].green, colors[i].blue, hex);
    }
}
