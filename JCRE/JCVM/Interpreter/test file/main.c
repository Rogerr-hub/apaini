#include "../read_cap.c"

int main() {
    // int position = 0;
    // uint8_t byte = get_byte (position);
    // printf("Byte at position %d: %x\n", position, byte);

    CAP cap;

    printf("%d\n", read_cap(&cap));

    printf("data header:\n");
    printf("%x", cap.header[0]);
    for (int i = 1; i < cap.header_len; i++) {
        printf(", ");
        printf("%x", cap.header[i]);
    }

    printf("\n\ndata class:\n");
    printf("%x", cap.class[0]);
    for (int i = 1; i < cap.class_len; i++) {
        printf(", ");
        printf("%x", cap.class[i]);
    }

    printf("\n\ndata method:\n");
    printf("%x", cap.method[0]);
    for (int i = 1; i < cap.method_len; i++) {
        printf(", ");
        printf("%x", cap.method[i]);
    }

    return 0;
}