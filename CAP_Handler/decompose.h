#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include "decompose.c"

void header_structure(uint8_t *buffer, size_t length, header *hdr);
void applet_structure_versi_2_1(uint8_t *buffer, size_t length, applet *aplt);
void directory_structure_versi_2_1(uint8_t *buffer, size_t length, directory *drt);
void import_structure_versi_2_1(uint8_t *buffer, size_t length, import *imp);
void cp_structure_versi_2_1(uint8_t* buffer, size_t length, constantpool* cp);
void sf_structure_versi_2_1(uint8_t* buffer, size_t length, static_field* sf);
void reflo_structure_versi_2_1(uint8_t* buffer, size_t length, RefLocation* rf);
