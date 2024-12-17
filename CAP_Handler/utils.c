#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// Define the Opcode struct
typedef struct {
    uint8_t opcode;       // The opcode value
    const char *mnemonic; // Human-readable name
    uint8_t param_count;  // Number of parameters
    uint8_t param_sizes[3]; // Sizes of parameters (max 3 for simplicity)
} Opcode;

// Define the opcode table as an array of Opcode structs
Opcode opcode_table[] = {
    {36, "aaload", 0, {0}},
    {55, "aastore", 0, {0}},
    {1, "aconst_null", 0, {0}},
    {21, "aload", 1, {1}},
    {24, "aload_0", 0, {0}},
    {25, "aload_1", 0, {0}},
    {26, "aload_2", 0, {0}},
    {27, "aload_3", 0, {0}},
    {145, "anewarray", 2, {2}},
    {119, "areturn", 0, {0}},
    {146, "arraylength", 0, {0}},
    {40, "astore", 1, {1}},
    {43, "astore_0", 0, {0}},
    {44, "astore_1", 0, {0}},
    {45, "astore_2", 0, {0}},
    {46, "astore_3", 0, {0}},
    {147, "athrow", 0, {0}},
    {37, "baload", 0, {0}},
    {56, "bastore", 0, {0}},
    {18, "bipush", 1, {1}},
    {16, "bspush", 1, {1}},
    {148, "checkcast", 3, {1, 2, 0}},
    {61, "dup", 0, {0}},
    {63, "dup_x", 1, {1}},
    {62, "dup2", 0, {0}},
    {131, "getfield_a", 1, {1}},
    {173, "getfield_a_this", 1, {1}},
    {169, "getfield_a_w", 2, {2}},
    {132, "getfield_b", 1, {1}},
    {174, "getfield_b_this", 1, {1}},
    {170, "getfield_b_w", 2, {2}},
    {134, "getfield_i", 1, {1}},
    {176, "getfield_i_this", 1, {1}},
    {172, "getfield_i_w", 2, {2}},
    {133, "getfield_s", 1, {1}},
    {175, "getfield_s_this", 1, {1}},
    {171, "getfield_s_w", 2, {2}},
    {123, "getstatic_a", 2, {2}},
    {124, "getstatic_b", 2, {2}},
    {126, "getstatic_i", 2, {2}},
    {125, "getstatic_s", 2, {2}},
    {112, "goto", 1, {1}},
    {168, "goto_w", 2, {2}},
    {93, "i2b", 0, {0}},
    {94, "i2s", 0, {0}},
    {66, "iadd", 0, {0}},
    {39, "iaload", 0, {0}},
    {84, "iand", 0, {0}},
    {58, "iastore", 0, {0}},
    {95, "icmp", 0, {0}},
    {10, "iconst_0", 0, {0}},
    {11, "iconst_1", 0, {0}},
    {12, "iconst_2", 0, {0}},
    {13, "iconst_3", 0, {0}},
    {14, "iconst_4", 0, {0}},
    {15, "iconst_5", 0, {0}},
    {9, "iconst_m1", 0, {0}},
    {72, "idiv", 0, {0}},
    {104, "if_acmpeq", 1, {1}},
    {160, "if_acmpeq_w", 2, {2}},
    {105, "if_acmpne", 1, {1}},
    {161, "if_acmpne_w", 2, {2}},
    {106, "if_scmpeq", 1, {1}},
    {162, "if_scmpeq_w", 2, {2}},
    {109, "if_scmpge", 1, {1}},
    {165, "if_scmpge_w", 2, {2}},
    {110, "if_scmpgt", 1, {1}},
    {166, "if_scmpgt_w", 2, {2}},
    {111, "if_scmple", 1, {1}},
    {167, "if_scmple_w", 2, {2}},
    {108, "if_scmplt", 1, {1}},
    {164, "if_scmplt_w", 2, {2}},
    {107, "if_scmpne", 1, {1}},
    {163, "if_scmpne_w", 2, {2}},
    {96, "ifeq", 1, {1}},
    {152, "ifeq_w", 2, {2}},
    {99, "ifge", 1, {1}},
    {155, "ifge_w", 2, {2}},
    {100, "ifgt", 1, {1}},
    {156, "ifgt_w", 2, {2}},
    {101, "ifle", 1, {1}},
    {157, "ifle_w", 2, {2}},
    {98, "iflt", 1, {1}},
    {154, "iflt_w", 2, {2}},
    {97, "ifne", 1, {1}},
    {153, "ifne_w", 2, {2}},
    {103, "ifnonnull", 1, {1}},
    {159, "ifnonnull_w", 2, {2}},
    {102, "ifnull", 1, {1}},
    {158, "ifnull_w", 2, {2}},
    {90, "iinc", 2, {1, 1}},
    {151, "iinc_w", 3, {1, 2}},
    {20, "iipush", 4, {4}},
    {23, "iload", 1, {1}},
    {0, NULL, 0, {0}} // Terminator
};


bool is_sub_file(const char *expected_header, const uint8_t *buffer, size_t buffer_length) {
    for (size_t i = 0; i < buffer_length; i++) {
        if ((uint8_t)expected_header[i] != buffer[i]) {
            return false; 
        }
    }
    return true; // Match
}


void read_cap_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    uint8_t current_byte;
    uint8_t previous_byte = 0x50; 
    int counter = 0;
    printf("Processing CAP file:\n");
    while (fread(&current_byte, 1, 1, file)) {
        if (previous_byte == 0x50 && current_byte == 0x4B) {
            printf("\nDelimiter PK found\n");
            
        } else if(current_byte == 0x50){
            printf(" ");
        } else {
            printf("%02X ", current_byte);     
        }
        previous_byte = current_byte;
        counter++;
        if (counter == 16) {
            printf("\n");
            counter = 0;
        }
    }

    fclose(file);
    printf("\nFile reading completed.\n");
}

void print_buffer(uint8_t *buffer, int len_buffer){
    for(int i=0; i<len_buffer;i++){
        printf("%02x ", buffer[i]);
    }
    printf("\n");
}
void print_array(uint8_t* buffer, size_t length){
    int counter = 0;
    for(int i = 0; i<length ;i++){
        if(counter<4){printf("%02x ", buffer[i]); counter++;}
        else{
            printf("%02x\n",buffer[i]);
            counter=0;
        }
        //counter++;
        
    }
    printf("\n");
}



void read_isi_partisi(const char* filename, const char* sub_file, uint8_t* dalam, size_t* length){
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    //buat
    uint8_t buffer_header[256];
    char expected_header[256];
    //char sub_file[] = "Applet.cap";
    size_t length_without_last_4 = strlen(filename) > 4 ? strlen(filename) - 4 : 0;
    snprintf(expected_header, sizeof(expected_header), "%.*s/javacard/%s", (int)length_without_last_4, filename, sub_file);

    int length_header = strlen(expected_header);
    uint8_t buffer[length_header];

    uint8_t curr;
    uint8_t prev = 0x0;
    memset(buffer, 0, sizeof(buffer)); // Clear the buffer

    printf("Expected Header: %s\n", expected_header);
    printf("Processing CAP file:");

    uint8_t current_byte;
    int i = 0; // Index for filling the buffer
    while (fread(&curr, 1, 1, file)) {
        buffer[i] = curr;
        i++;
        if (i == length_header) { // Buffer is full, check for match
            if (is_sub_file(expected_header, buffer, length_header)) {
                printf("\nFound : %s\n", sub_file);
                do{ 
                    fread(&curr, 1, 1, file);
                    if(curr != 0x50){
                        //printf("%02X ", curr);
                        dalam[(*length)++] = curr;
                    }
                    prev = curr;
                } while(curr != 0x4B && prev != 0x50);
                printf("\n");
                break; // Stop reading if the header is found
            }
            // Shift buffer to the left by one byte
            memmove(buffer, buffer + 1, length_header - 1);
            i--; // Adjust index
        }
         
    }
    fclose(file);
}

void translate_bytecode(const uint8_t *bytecode, size_t length) {
    size_t i = 0;
    while (i < length) {
        uint8_t opcode = (int)bytecode[i];
        Opcode *found = NULL;

        // Search for the opcode in the opcode table
        for (int j = 0; opcode_table[j].mnemonic != NULL; j++) {
            if (opcode_table[j].opcode == opcode) {
                found = &opcode_table[j];
                break;
            }
        }

        if (found) {
            printf("%s", found->mnemonic);
            i++;
            for (int p = 0; p < found->param_count; p++) {
                printf(" 0x%02X", bytecode[i]);
                i++;
            }
            printf("\n");
        } else {
            printf("Unknown opcode: 0x%02X\n", opcode);
            i++;
        }
    }
}
