#include "jcre.c"
#include <stdio.h>
// #define MAX_AID_LEN 20

// Main function for testing
int main() {
    memset(MAIN_REGISTER, 0, sizeof(MAIN_REGISTER));
    const uint8_t cap_data1[] = {0x01, 0x02, 0x03};
    const uint8_t cap_data2[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};

    // Install first package
    install(cap_data1, 3);
    if (MAIN_REGISTER_LEN != 0) {
        REGISTERED_PACKAGE data = MAIN_REGISTER[0];
        printf("First package installed: AID length = %d\n", data.package.AID_len);
        print_uint8_array(data.package.AID, data.package.AID_len);
        printf("First package installed: CAP length = %x\n", data.package.cap_len);
        print_uint8_array(data.package.data_cap, data.package.cap_len);
    }

    printf("\n");
    // Install second package
    install(cap_data2, 5);
    if (MAIN_REGISTER_LEN != 0) {
        REGISTERED_PACKAGE data = MAIN_REGISTER[1];
        printf("First package installed: AID length = %d\n", data.package.AID_len);
        print_uint8_array(data.package.AID, data.package.AID_len);
        printf("First package installed: CAP length = %x\n", data.package.cap_len);
        print_uint8_array(data.package.data_cap, data.package.cap_len);
    }

    printf("\n\nTes selek:\n");
    uint8_t AID1[] = {0x01};
    int channel1 = 9; // choose channel test here
    printf("AID target: 0x%02X", AID1[0]);
    if(select(channel1, AID1, 1)) {
        // printf("berhasil?");
        printf("\n");
        printf("CAP dari aid yg dipilih: \n");
        print_uint8_array(CHANNEL[channel1].package->data_cap, CHANNEL[channel1].package->cap_len);
    }
    else {
        printf("ngga ketemu :(");
    }

    printf("\n\nTes selek:\n");
    uint8_t AID2[] = {0xAA};
    int channel2 = 9; // choose channel test here
    printf("AID target: 0x%02X", AID2[0]);
    if(select(channel2, AID2, 1)) {
        // printf("berhasil?");
        printf("\n");
        printf("CAP dari aid yg dipilih: \n");
        print_uint8_array(CHANNEL[channel2].package->data_cap, CHANNEL[channel2].package->cap_len);
    }
    else {
        printf("ngga ketemu :(");
    }

    return 0;
}

// // Main function for testing
// int main() {
//     const uint8_t cap_data1[] = {0x01, 0x02, 0x03};
//     const uint8_t cap_data2[] = {0xAA, 0xBB, 0xCC};

//     // Install first package
//     install(&cap_data1, 3);
//     if (MAIN_REGISTER_LEN != 0) {
//         REGISTERED_PACKAGE data = MAIN_REGISTER[0];
//         printf("First package installed: AID length = %d\n", MAIN_REGISTER[3].package->AID_len);
//     }

//     // Install second package
//     install(cap_data2, sizeof(cap_data2));
//     if (MAIN_REGISTER && MAIN_REGISTER->next && MAIN_REGISTER->next->package) {
//         printf("Second package installed: AID length = %d\n", MAIN_REGISTER->next->package->AID_len);
//     }

//     return 0;
// }

// void main() {
//     printf("test\n");
//     uint8_t cap[] = {0x01, 0x02, 0x03};

//     int cap_len = 3;

//     install(cap, cap_len);
//     printf("bisa...?");

//     // uint8_t AID[MAX_AID_LEN] = {0};
//     // int AID_len = MAX_AID_LEN;

//     // // printf("testt");
//     // printf("\n%d", select(2, AID, AID_len));
//     return;
// }