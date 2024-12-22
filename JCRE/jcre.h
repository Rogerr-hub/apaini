// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <stdbool.h>
// #include <string.h> // For memcpy
#include "jcre.c"

/*
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
*/
// void install(const uint8_t *cap, int cap_len);
// bool registerr(Package *package);
// bool find_aid(Package *package);

// // bool is_AID_already_registered (uint8_t *AID, int AID_len);
// bool select(int channel, uint8_t *AID, int AID_len);
// bool deselect(int channel);

// bool compare_arrays(const uint8_t *array_1, const uint8_t *array_2, size_t len);
// bool compile(Package *package); // implementasi dari firdaus
// void print_uint8_array(const uint8_t *array, size_t length);

// extern REGISTERED_PACKAGE MAIN_REGISTER[MAX_REGISTER];
// extern int MAIN_REGISTER_LEN;
// extern CHANNELS CHANNEL[MAX_CHANNEL];

// #include "jcre.c"