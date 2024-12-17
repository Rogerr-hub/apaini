#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "decompose.h"
#include <stdbool.h>

// int main(int argc, char *argv[]) {
//     if (argc != 2) {
//         fprintf(stderr, "Usage: %s <cap_file>\n", argv[0]);
//         return EXIT_FAILURE;
//     }

//     const char *filename = argv[1];
//     uint8_t __inside[256];
//     size_t length = 0;
//     uint8_t buff[256];
//     read_isi_partisi(filename, "Header.cap", buff, &length);

//     //print_array(buff,length);
//     translate_bytecode(buff,length);

// }
int main(int argc, char* argv[]){
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <cap_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    uint8_t data_header[256];
    uint8_t data_drt[256];
    uint8_t data_aplt[256];
    
    size_t length_header = 0;
    size_t length_drt = 0;
    size_t length_aplt = 0;
    
    read_isi_partisi(filename, "Header.cap", data_header, &length_header);
    read_isi_partisi(filename, "Directory.cap", data_drt, &length_drt);
    read_isi_partisi(filename, "Applet.cap", data_aplt, &length_aplt);

    applet aplt;
    directory drt;
    header hdr;

    
    header_structure(data_header, length_header, &hdr);
    directory_structure_versi_2_1(data_drt, length_drt, &drt);
    applet_structure_versi_2_1(data_aplt, length_aplt, &aplt);

    printf("HEADER.................................\n");
    printf("Tag: %02x\n", hdr.tag);
    printf("Size: %04x\n", hdr.size);
    printf("Magic: %08x\n", hdr.magic);
    printf("Minor: %02x, Major: %02x, Flags: %02x\n", hdr.minor, hdr.major, hdr.flags);

    printf("Package Info:\n");
    printf("  Minor: %02x, Major: %02x\n", hdr.package.minor, hdr.package.major);
    printf("  AID Length: %02x\n", hdr.package.AID_length);
    printf("  AID: ");
    for (int i = 0; i < hdr.package.AID_length; i++) {
        printf("%02x ", hdr.package.AID[i]);
    }
    printf("\n");

    printf("\n");

    printf("Directory..............................\n");
     printf("Tag : %02x\n", drt.tag);
    printf("Size : %04x\n", drt.size);

    printf("Component Sizes:\n");
    for (int i = 0; i < 11; i++) {
        printf("  Component[%d] : %04x\n", i, drt.component_sizes1[i]);
    }

    printf("Static Field Size:\n");
    printf("  Image Size        : %04x\n", drt.static_field_size.image_size);
    printf("  Array Init Count  : %04x\n", drt.static_field_size.array_init_count);
    printf("  Array Init Size   : %04x\n", drt.static_field_size.array_init_size);

    printf("Import Count : %02x\n", drt.import_count);
    printf("Applet Count : %02x\n", drt.applet_count);
    printf("Custom Count : %02x\n", drt.custom_count);
    printf("\n\n");

    printf("APPLET................\n");
     printf("Tag: %d\n", aplt.tag);
    printf("Size: %d\n", aplt.size);
    printf("Count: %d\n", aplt.count);

    for (int i = 0; i < aplt.count; i++) {
        printf("Applet %d:\n", i + 1);
        printf("  AID_length: %d\n", aplt.applets[i].AID_length);
        printf("  AID: ");
        for (int j = 0; j < aplt.applets[i].AID_length; j++) {
            printf("%02X ", aplt.applets[i].AID[j]);
        }
        printf("\n");
        printf("  Install_method_offset: 0x%04X\n", aplt.applets[i].install_method_offset);
    }
    printf("\n");

   
}
