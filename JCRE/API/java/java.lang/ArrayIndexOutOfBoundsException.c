#include <stdio.h>

/**
 * Structure to represent an ArrayIndexOutOfBoundsException.
 * In C, this structure holds an error message to indicate that an array index is out of bounds.
 */
typedef struct ArrayIndexOutOfBoundsException {
    char message[100];
} ArrayIndexOutOfBoundsException;

/**
 * Constructs an ArrayIndexOutOfBoundsException with a default message.
 */
ArrayIndexOutOfBoundsException createArrayIndexOutOfBoundsException() {
    ArrayIndexOutOfBoundsException ex;
    snprintf(ex.message, sizeof(ex.message), "Array index out of bounds");
    return ex;
}

/**
 * Simulates accessing an array and throws an ArrayIndexOutOfBoundsException if the index is illegal.
 *
 * @param array The array to access.
 * @param size The size of the array.
 * @param index The index to access.
 * @return The value at the index if valid; otherwise, prints an error.
 */
int accessArray(int *array, int size, int index) {
    if (index < 0 || index >= size) {
        ArrayIndexOutOfBoundsException ex = createArrayIndexOutOfBoundsException();
        printf("%s: Index %d is out of bounds. Valid range is 0 to %d.\n", ex.message, index, size - 1);
        return -1; // Return an error value (could be handled differently)
    }
    return array[index];  // Return the value at the given index if valid
}
/*
int main() {
    int array[5] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);

    // Example of valid access
    int value = accessArray(array, size, 2);
    if (value != -1) {
        printf("Value at index 2: %d\n", value);
    }

    // Example of invalid access (out of bounds)
    accessArray(array, size, 10);  // Will trigger the exception

    return 0;
}
*/
