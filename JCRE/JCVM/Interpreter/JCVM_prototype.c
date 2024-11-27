#include <stdio.h>
#include <stdint.h>

#define DEBUG

#define INS_ICONST_0    0x0A
#define INS_ICONST_1    0x0B
#define INS_ISTORE_1    0x34
#define INS_IINC        0x5A
#define INS_RETURN      0x7A

uint8_t sum_dot_cap[] = {0x0A, 0x34, 0x5A, 0x01, 0x01, 0x5A, 0x01, 0x02, 0x5A, 0x01, 0x03, 0x5A, 0x01, 0x04, 0x5A, 0x01, 0x05, 0x5A, 0x01, 0x06, 0x5A, 0x01, 0x07, 0x5A, 0x01, 0x08, 0x5A, 0x01, 0x09, 0x5A, 0x01, 0x0A, 0x7A};

void jcvm(uint8_t *addr){
    uint8_t     jcvm_instr;             // implementation of buffer for instruction
    uint32_t    jcvm_addr_offset = 0;   // implementation of buffer for address pointer
    uint32_t    debug_addr_offset;      // implementation of buffer for address pointer
    uint8_t     jcvm_index;             // implementation of buffer for index
    uint8_t     jcvm_const;             // implementation of buffer for const

    uint16_t    stack[65536];           // implementation of buffer for operand stack
    uint16_t    stack_ptr = 0;          // implementation of buffer for stack pointer

    uint16_t    local_variable[256];    // implementation of buffer for local variable

    do{
        // Read the jcvm_instruction.
        jcvm_instr = *(addr + jcvm_addr_offset);

        // Execute the Java bytecode
        switch (jcvm_instr){
        case INS_ICONST_0:
            debug_addr_offset = jcvm_addr_offset;
            // Append constant '0' into the operand stack
            stack[stack_ptr]        = 0x0000; // word 1 is MSB
            stack[stack_ptr + 1]    = 0x0000; // word 2 is LSB
            
            // Increment the stack pointer
            stack_ptr += 2;

            // Increment the address offset
            jcvm_addr_offset += 1;
            break;
        case INS_ICONST_1:
            debug_addr_offset = jcvm_addr_offset;
            // Append constant '1' into the operand stack
            stack[stack_ptr]        = 0x0000; // word 1 is MSB
            stack[stack_ptr + 1]    = 0x0001; // word 2 is LSB
            
            // Increment the stack pointer
            stack_ptr += 2;
            
            // Increment the address offset
            jcvm_addr_offset += 1;
            break;
        case INS_ISTORE_1:
            debug_addr_offset = jcvm_addr_offset;
            // Load value from operand stack into local variable '1'
            local_variable[2] = stack[stack_ptr - 2];
            local_variable[3] = stack[stack_ptr - 1];
            
            // Decrement the stack pointer (the same as 'pop' operation)
            stack_ptr -= 2;
            
            // Increment the address offset
            jcvm_addr_offset += 1;
            break;
        case INS_IINC:
            debug_addr_offset = jcvm_addr_offset;
            // Increment the address offset and read the 'index'
            jcvm_addr_offset += 1;
            jcvm_index = *(addr + jcvm_addr_offset);
            
            // Increment the address offset and read the 'const'
            jcvm_addr_offset += 1;
            jcvm_const = *(addr + jcvm_addr_offset);

            // Increment the designated local variable with 'const'
            int32_t jcvm_temp = (local_variable[2 * jcvm_index] << 16) | local_variable[2 * jcvm_index + 1];
            jcvm_temp += jcvm_const;
            local_variable[2 * jcvm_index] = (jcvm_temp >> 16) & 0x0000FFFF;
            local_variable[2 * jcvm_index + 1] = jcvm_temp & 0x0000FFFF;

            // Increment the address offset
            jcvm_addr_offset += 1;
            break;
        case INS_RETURN:
            debug_addr_offset = jcvm_addr_offset;
            // do nothing and return
            break;
        default:
            break;
        }

        #ifdef DEBUG
            #define DEBUG_INSTR_ADDR        0x01
            #define DEBUG_STACK             0x01
            #define DEBUG_LOCAL_VAR         0x01
            
            #define DEBUG_LOCAL_VAR_COUNT   4
            #define DEBUG_STACK_COUNT       4

            printf("%3d: ", debug_addr_offset);
            switch (jcvm_instr){
            case INS_ICONST_0:
                printf("ICONST_0");
                break;
            case INS_ICONST_1:
                printf("ICONST_1");
                break;
            case INS_ISTORE_1:
                printf("ISTORE_1");
                break;
            case INS_IINC:
                printf("IINC");
                break;
            case INS_RETURN:
                printf("RETURN");
                break;
            default:
                printf("NOT AVAILABLE");
                break;
            }
            printf("\n");

            if(DEBUG_INSTR_ADDR){
                if(jcvm_instr < 0x10){
                    printf("      - BYTECODE        : 0x0%x\n", jcvm_instr);
                }else{
                    printf("      - BYTECODE        : 0x%x\n", jcvm_instr);
                }
                printf("      - ADDRESS         : %d\n", debug_addr_offset);
            }

            if(DEBUG_STACK){
                printf("      - OPERAND STACK   : [");
                for(uint16_t i = 0; i < DEBUG_STACK_COUNT; i++){
                    int32_t jcvm_temp = (stack[2 * i] << 16) | stack[2 * i + 1];
                    printf("%d", jcvm_temp);
                    if(i != DEBUG_STACK_COUNT - 1){
                        printf("\t");
                    }else{
                        if(DEBUG_STACK_COUNT < 32768){
                            printf("\t...\t]\n");
                        }else{
                            printf("]\n");
                        }
                    }
                }
            }
            
            if(DEBUG_LOCAL_VAR){
                printf("      - LOCAL VARIABLES : [");
                for(uint16_t i = 0; i < DEBUG_LOCAL_VAR_COUNT; i++){
                    int32_t jcvm_temp = (local_variable[2 * i] << 16) | local_variable[2 * i + 1];
                    printf("%d", jcvm_temp);
                    if(i != DEBUG_LOCAL_VAR_COUNT - 1){
                        printf("\t");
                    }else{
                        if(DEBUG_LOCAL_VAR_COUNT < 128){
                            printf("\t...\t]\n");
                        }else{
                            printf("]\n");
                        }
                    }
                }
            }
            printf("\n");
        #endif
    } while (jcvm_instr != INS_RETURN);
    
}

int main(void){
    jcvm(&sum_dot_cap[0]);
}