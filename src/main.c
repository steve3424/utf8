#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>

void PrintBits(void* bytes, uint64_t num_bytes) {
    printf("Bytes: ");
    for(uint64_t i = 0; i < num_bytes; ++i) {
        for(uint64_t j = 0; j < 8; ++j) {
            uint8_t on = ((uint8_t*)bytes)[i] & ((uint8_t)1 << ((uint8_t)7 - j));
            if(on) {
                printf("1");
            }
            else {
                printf("0");
            }

            if(j == 3) {
                printf(".");
            }
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    char unicode_string[10];
    uint32_t code_point = 0x11111111;

    if(code_point < 0x80) {
        // 0xxxxxxx
        unicode_string[0] = code_point & 127;
        unicode_string[1] = '\0';
        printf("Char: %s\n", unicode_string);
    }
    else if(code_point < 0x800) {
        // 110xxxxx 10xxxxxx
        unicode_string[0] = code_point >> 6 & 31 | 192;
        unicode_string[1] = code_point & 63 | 128;
        unicode_string[2] = '\0';
        printf("Char: %s\n", unicode_string);
    }
    else if(code_point < 0x10000) {
        // 1110xxxx 10xxxxxx 10xxxxxx
        unicode_string[0] = code_point >> 12 & 15 | 224;
        unicode_string[1] = code_point >>  6 & 63 | 128;
        unicode_string[2] = code_point & 63 | 128;
        unicode_string[3] = '\0';
        printf("Char: %s\n", unicode_string);
    }
    else if(code_point < 0x110000) {
        // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        unicode_string[0] = code_point >> 18 &  7 | 240;
        unicode_string[1] = code_point >> 12 & 63 | 128;
        unicode_string[2] = code_point >>  6 & 63 | 128;
        unicode_string[3] = code_point & 63 | 128;
        unicode_string[4] = '\0';
    }
    else {
        printf("I don't know what to do with this %u\n", code_point);
    }

    return 0;
}