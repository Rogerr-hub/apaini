//TODO: tambahin buat ngapus register spesifik
// #include "jcre.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h> // For memcpy

#define MAX_AID_LEN 20
#define MAX_AID_APPLET_LEN (MAX_AID_LEN + 2)
#define MAX_CAP 1000
#define MAX_CHANNEL 20
#define MAX_REGISTER 10
#define MAX_APPLET 5
#define MAX_INSTRUCTION 100 //instruction = method


typedef struct Applet_Function Applet_Function;
typedef struct Pakcage_Function Package_Function;
typedef struct Package Package;
typedef struct REGISTERED_PACKAGE REGISTERED_PACKAGE;
typedef struct CHANNELS CHANNELS;

// fungsi-fungsi yang terdapat di dalam 1 package dalam bentuk linked list
struct Applet_Function {
    uint8_t AID_Function[MAX_AID_APPLET_LEN];  // AID Pakcage + Function Indentifier (pengenal/nama dari fungsi)
    int aid_len;

    uint8_t method[MAX_INSTRUCTION];        // instruksi dari fungsi ini

    Applet_Function *next_applet_function;  // linked list ke fungsi selanjutnya. jangan lupa kalau ngga ada dibikin null. urutan bebas
};

// instruksi di luar applet (jika ternyata ada) yang langsung diinstruksi ketika Package di Select
struct Package_Function {
    uint8_t Global_Instruction[MAX_INSTRUCTION];    // instruksi apapun yang berada di luar fungsi Applet tapi termasuk di dalam package
    int Global_Instruction_len;     // panjang instruksi nya kalau ada

    Applet_Function Applet_Function;
};

// struck utama dari Applet keseluruhan
struct Package {
    uint8_t AID[MAX_AID_LEN];       // basically AID dari Package
    int AID_len;
    bool success;       // apakah applet sukses/berhasil di inisiasi (diinstall)
    bool selected;

    uint8_t data_cap[MAX_CAP];  // data full cap disimpen disini semua mwahahahha
    int cap_len;        // panjang file cap

    struct Package_Function function;  // hasil compile nanti ketika di select dan siap di run
};

// linked list sebuah register besar berisi semua applet yang tersedia
// dan yang nantinya ketika applet dipilih dan di run tetap menggunakan register ini
// gimana cara biar data disini ngga ilang :') i mean bedain mana volatile sama non volatile memory... paling pake pointer ke file aslinya...?
struct REGISTERED_PACKAGE {
    struct Package package;
    bool registered;
    int self_index; // counting up
    // REGISTERED_PACKAGE *self;
    // REGISTERED_PACKAGE *next;
};

struct CHANNELS {
    struct Package *package;
    bool registered;
    int self_index; // counting up
};

REGISTERED_PACKAGE MAIN_REGISTER[MAX_REGISTER];
int MAIN_REGISTER_LEN = 0;
CHANNELS CHANNEL[MAX_CHANNEL];

void install(const uint8_t *cap, int cap_len);
bool registerr(Package *package);
bool find_aid(Package *package);

// bool is_AID_already_registered (uint8_t *AID, int AID_len);
bool select(int channel, uint8_t *AID, int AID_len);
bool deselect(int channel);

bool compare_arrays(const uint8_t *array_1, const uint8_t *array_2, size_t len);
bool compile(Package *package); // implementasi dari firdaus
void print_uint8_array(const uint8_t *array, size_t length);

// fungsi untuk mencari AID dari Package
bool find_aid(Package *package) {
    // // Sanity check: ensure input is valid
    // if (!package || !package->data_cap || package->cap_len <= 0) {
    //     package->success = false;
    //     return 0;
    // }

    // uint8_t AID[MAX_AID_LEN] = {0};
    // int AID_len = MAX_AID_LEN;
    // mencari AID dari CAP. bisa pake kode firdaus buat parsing spesifik aid aja?
    int AID_len = 1;
    uint8_t AID[AID_len];
    AID[0] = package->data_cap[0];
    printf("\nAID Target: 0x%02X ", package->data_cap[0]);
    printf("\nAID Tersimpan: 0x%02X ", AID[0]);
    printf("\n");
    // memcpy(AID[AID_len], package->data_cap[0], sizeof(uint8_t));
    
    memcpy(package->AID, AID, AID_len);
    package->AID_len = AID_len;
    return true;
}

// Register a new package
bool registerr(Package *package) {
    int index = 0;
    while (MAIN_REGISTER[index].self_index < (MAX_REGISTER - 1)) { // iterasi cek dari awal sampe akhir ada yang kosong ngga
        if (!MAIN_REGISTER[index].registered) {
            memcpy(&MAIN_REGISTER[index].package, package, sizeof(Package));
            MAIN_REGISTER[index].registered = true;
            MAIN_REGISTER_LEN++; // Increment the length of the register
            return true;
        }
        index++;
    }
    printf("penuh register utama nya");
    return false;
}

// Install a package
void install(const uint8_t *cap, int cap_len) {
    Package package;

    memcpy(package.data_cap, cap, cap_len);
    package.cap_len = cap_len;
    find_aid(&package);

    if (!registerr(&package)) {
        package.success = true;
    } else {
        package.success = false;
    }
}

void print_uint8_array(const uint8_t *array, size_t length) {
    printf("Array contents: ");
    for (size_t i = 0; i < length; i++) {
        printf("0x%02X ", array[i]); // Print in hexadecimal format
    }
    printf("\n");
}




// bool is_AID_already_registered (uint8_t *AID, int AID_len) {
//     REGISTERED_PACKAGE *now = MAIN_REGISTER;

//     while (now != NULL || now->self == now) { // singkatnya loop buat sampe paling akhir
//         if (compare_arrays(AID, now->package->AID, AID_len)) {
//             return true;
//         }

//         now = now->next;
//     }

//     return false;
// };

bool compare_arrays(const uint8_t *array_1, const uint8_t *array_2, size_t len) {
    // printf("\nWant to compare:\n");
    // print_uint8_array(array_1, len);
    // print_uint8_array(array_2, len);

    for (size_t i = 0; i < len; i++) {
        if (array_1[i] != array_2[i]) {
            return false; // Arrays are not equal
        }
    }
    return true; // Arrays are equal
}

bool select(int channel, uint8_t *AID, int AID_len) {
    bool found = false;

    // // cek dlu pernah ngeregister atau engga
    // if (MAIN_REGISTER == NULL || MAIN_REGISTER != MAIN_REGISTER->self) {
    //     printf("ini 0\n");
    //     return false;
    // }

    // cek ada di register atau engga TODO: pengecekan udh pernah keselect atau belum blm ada
    int index = 0;
    while (MAIN_REGISTER[index].self_index < (MAX_REGISTER - 1)) {
        // printf("test1\n");
        if (compare_arrays(AID, MAIN_REGISTER[index].package.AID, AID_len)) {
            found = true;
            printf("\nketemu!\n");
            break;
        }

        index++;
    }

    // printf("ini 1\n");
    if (found) {
        // printf("ini 2\n");
        if (!CHANNEL[channel].registered) {
            deselect(channel);
        }
        if(compile(&MAIN_REGISTER[index].package)) {
                CHANNEL[channel].package = &MAIN_REGISTER[index].package;
                CHANNEL[channel].registered = true;
                printf("yei berhasil milih\n");
                return true;

                // berhasil ketemu AID dan berhasil compile kedua
        }
    }
    return false; // gagal karna ngga ketemu AID atau gagal compile (bisa karna file corupt)
}

bool deselect(int channel) {
    CHANNEL[channel].registered = false;
    return true;
}

bool compile(Package *package) {
    // masi kosong
    // printf(" ttttes ");
    return true;
}

// // Main function for testing
// int main() {
//     const uint8_t cap_data1[] = {0x01, 0x02, 0x03};
//     const uint8_t cap_data2[] = {0xAA, 0xBB, 0xCC};

//     // Install first package
//     install(cap_data1, sizeof(cap_data1));
//     if (MAIN_REGISTER && MAIN_REGISTER->package) {
//         printf("First package installed: AID length = %d\n", MAIN_REGISTER->package->AID_len);
//     }

//     // Install second package
//     install(cap_data2, sizeof(cap_data2));
//     if (MAIN_REGISTER && MAIN_REGISTER->next && MAIN_REGISTER->next->package) {
//         printf("Second package installed: AID length = %d\n", MAIN_REGISTER->next->package->AID_len);
//     }

//     return 0;
// }

