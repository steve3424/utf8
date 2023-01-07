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

void CodePointToChar(uint32_t* code_point_array, uint32_t count, char* buffer, uint32_t buffer_size) {
    char error_message_buffer_full[] = "Buffer full. Successfully wrote %u of %u characters to buffer.\n";

    uint32_t buffer_i = 0;
    for(uint32_t i = 0; i < count; ++i) {
        uint32_t code_point = code_point_array[i];
        if(code_point < 0x80) {
            // 0xxxxxxx

            if((buffer_i + 1) >= buffer_size) {
                printf(error_message_buffer_full, i, count);
                break;
            }

            buffer[buffer_i++] = code_point & 127;
        }
        else if(code_point < 0x800) {
            // 110xxxxx 10xxxxxx

            if((buffer_i + 2) >= buffer_size) {
                printf(error_message_buffer_full, i, count);
                break;
            }

            buffer[buffer_i++] = code_point >> 6 & 31 | 192;
            buffer[buffer_i++] = code_point & 63 | 128;
        }
        else if(code_point < 0x10000) {
            // 1110xxxx 10xxxxxx 10xxxxxx

            if((buffer_i + 3) >= buffer_size) {
                printf(error_message_buffer_full, i, count);
                break;
            }

            buffer[buffer_i++] = code_point >> 12 & 15 | 224;
            buffer[buffer_i++] = code_point >>  6 & 63 | 128;
            buffer[buffer_i++] = code_point & 63 | 128;
        }
        else if(code_point < 0x110000) {
            // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

            if((buffer_i + 4) >= buffer_size) {
                printf(error_message_buffer_full, i, count);
                break;
            }

            buffer[buffer_i++] = code_point >> 18 &  7 | 240;
            buffer[buffer_i++] = code_point >> 12 & 63 | 128;
            buffer[buffer_i++] = code_point >>  6 & 63 | 128;
            buffer[buffer_i++] = code_point & 63 | 128;
        }
        else {
            printf("Code point out of range: %u. Successfully wrote %u characters to buffer.\n", code_point, i);
            break;
        }
    }

    buffer[buffer_i] = '\0';
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    char unicode_string[61];
    uint32_t code_points[20] = {
        0x2514, 0x2500, 0x2500, 0x2500, 0x2500, 
        0x2500, 0x2500, 0x2500, 0x2500, 0x2500, 
        0x2500, 0x2500, 0x2500, 0x2500, 0x2500, 
        0x2500, 0x2500, 0x2500, 0x2500, 0x2500
    };
    CodePointToChar(code_points, sizeof(code_points)/sizeof(uint32_t), unicode_string, sizeof(unicode_string)/sizeof(char));
    printf(unicode_string);

    return 0;
}