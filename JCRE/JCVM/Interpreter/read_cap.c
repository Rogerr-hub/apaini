#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define size_header 100
#define size_directory 100
#define size_applet 100
#define size_import 100
#define size_constantpool 100
#define size_class 100
#define size_method 100
#define size_staticfield 100
#define size_reflocation 100
#define size_descriptor 100

#define buffer_size 10

uint8_t headercap[] = {0x48, 0x65, 0x61, 0x64, 0x65, 0x72, 0x2E, 0x63, 0x61, 0x70};
uint8_t classcap[] = {0x43, 0x6C, 0x61, 0x73, 0x73, 0x2E, 0x63, 0x61, 0x70};
uint8_t methodcap[] = {0x4D, 0x65, 0x74, 0x68, 0x6F, 0x64, 0x2E, 0x63, 0x61, 0x70};

uint8_t end_of_file[] = {0x50, 0x4B};
uint8_t end_of_cap[] = {0x50, 0x4B, 0x05, 0x06};

uint8_t *file_order[] = {headercap, classcap, methodcap};

typedef struct CAP CAP;
struct CAP {
    uint8_t header[size_header];
    int header_len;
    uint8_t class[size_class];
    int class_len;
    uint8_t method[size_method];
    int method_len;
};

void shift_left(uint8_t *array, size_t size) {
    if (size == 0) return; // No shifting needed for empty array
    for (size_t i = 0; i < size - 1; i++) {
        array[i] = array[i + 1];
    }
    array[size - 1] = 0; // Fill the last position with 0 (or any default value)
}

int find_value(const uint8_t *array, size_t size, uint8_t value) {
    for (size_t i = 0; i < size; i++) {
        if (array[i] == value) {
            return i; // Return the index of the value
        }
    }
    return -1; // Not found
}

bool find_subarray(const uint8_t *array, size_t array_size, const uint8_t *subarray, size_t subarray_size) {
    if (subarray_size > array_size) {
        return false; // Subarray is larger than array
    }

    for (size_t i = 0; i <= array_size - subarray_size; i++) {
        if (memcmp(&array[i], subarray, subarray_size) == 0) {
            return true; // Subarray found
        }
    }

    return false; // Subarray not found
}

void cap_init(CAP *cap) {
    cap->header_len = 0;
    cap->class_len = 0;
    cap->method_len = 0;
}

int read_cap(CAP *cap) {
    cap_init(&cap);

    int pointer_cap = 0;
    uint8_t read = 0;
    uint8_t buffer[buffer_size] = 0;
    int buff_pointer = 0;

    int in_file_pointer = 0;

    int file_order_pointer = 0;

    bool next_masukin = false;

    while (true) {
        // read per byte
        read = get_bytes(pointer_cap);
        if (buff_pointer >= (buffer_size - 1)) {
            shift_left(buffer, buffer_size);
            buffer[buff_pointer] = read;
        }
        else {
            buffer[buff_pointer] = read;
            buff_pointer += 1;
        }

        if (find_subarray(buffer, buffer_size, end_of_cap, sizeof(end_of_cap) / sizeof(end_of_cap[0]))) {
            return 1; //file error
        }

        if (next_masukin) {
            if (file_order_pointer == 0) {
                cap->header[in_file_pointer] = read;
                cap->header_len += 1;
            }
            else if (file_order_pointer == 1) {
                cap->class[in_file_pointer] = read;
                cap->class_len += 1;
            }
            else if (file_order_pointer == 2) {
                cap->method[in_file_pointer] = read;
                cap->method_len += 1;
            }

            if (find_subarray(buffer, buffer_size, end_of_file, sizeof(end_of_file) / sizeof(end_of_file[0]))) {
                next_masukin = false;
                file_order_pointer += 1; 
                
                if (file_order_pointer == 0) {
                    cap->header_len -= 2;
                }
                else if (file_order_pointer == 1) {
                    cap->class_len -= 2;
                }
                else if (file_order_pointer == 2) {
                    cap->method_len -= 2;
                }

            }
        }

        // check apakah nama file yg diperlukan ada
        else {
            if (find_subarray(buffer, buffer_size, file_order[file_order_pointer], (sizeof(file_order[file_order_pointer]) / sizeof(file_order[file_order_pointer][0])))) {
                next_masukin = true;
            }
        }

        if (file_order_pointer == 3) {
            return 0; // berhasil berhasil horey
        }

        pointer_cap += 1;
    }
}