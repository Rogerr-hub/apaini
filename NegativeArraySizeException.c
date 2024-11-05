#include <stdio.h>

/**
 * Structure representing a NegativeArraySizeException in C.
 */
typedef struct NegativeArraySizeException {
    char message[100];  // To store the exception message
} NegativeArraySizeException;

/**
 * Constructs a NegativeArraySizeException with a default message.
 */
NegativeArraySizeException createNegativeArraySizeException() {
    NegativeArraySizeException ex;
    snprintf(ex.message, sizeof(ex.message), "NegativeArraySizeException: Array size cannot be negative.");
    return ex;
}

/**
 * Simulates creating an array with bounds checking for negative size.
 *
 * @param size The size of the array.
 * @param arr A pointer to the static array where elements will be stored.
 * @return 0 on success, -1 if size is negative.
 */
int createArray(int size, int arr[], int maxSize) {
    if (size < 0) {
        NegativeArraySizeException ex = createNegativeArraySizeException();
        printf("%s: Invalid size %d\n", ex.message, size);
        return -1; // Indicate failure to create array
    }

    if (size > maxSize) {
        printf("Size exceeds maximum allowed size of %d\n", maxSize);
        return -1; // Indicate failure to create array
    }

    // Initialize the array elements to zero (or any other value as needed)
    for (int i = 0; i < size; i++) {
        arr[i] = 0; // Just an example, could initialize with other values
    }

    return 0; // Success
}
/*
int main() {
    // Define a static array with a maximum size
    const int MAX_SIZE = 10;
    int arr[MAX_SIZE];
    
    // Attempt to create an array with a negative size
    int size = -5;
    if (createArray(size, arr, MAX_SIZE) == 0) {
        // The array was created successfully; you can work with it here
    }

    // Attempt to create an array with a valid size
    size = 5;
    if (createArray(size, arr, MAX_SIZE) == 0) {
        printf("Array created successfully with size %d.\n", size);
        // Do something with arr
    }

    return 0;
}
*/
