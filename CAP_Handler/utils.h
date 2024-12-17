#include "utils.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

//Read cap partition and safe it in an array called "dalam"
void read_isi_partisi(const char* filename, const char* sub_file, uint8_t* dalam, size_t* length);

// translate bytecode using LUT(look up table)
void translate_bytecode(const uint8_t *bytecode, size_t length);

// to check if sub CAP is included in CAP
bool is_sub_file(const char *expected_header, const uint8_t *buffer, size_t buffer_length);

//Print functions
void print_buffer(uint8_t *buffer, int len_buffer);
void print_array(uint8_t* buffer, size_t length);