#include <stdio.h>
#include <string.h>

/**
 * Structure representing an IndexOutOfBoundsException in C.
 */
typedef struct IndexOutOfBoundsException {
    char message[100];  // To store the exception message
} IndexOutOfBoundsException;

/**
 * Constructs an IndexOutOfBoundsException with a default message.
 */
IndexOutOfBoundsException createIndexOutOfBoundsException() {
    IndexOutOfBoundsException ex;
    snprintf(ex.message, sizeof(ex.message), "IndexOutOfBoundsException: Index is out of bounds.");
    return ex;
}

/**
 * Simulates accessing an array with bounds checking.
 *
 * @param arr The array to access.
 * @param size The size of the array.
 * @param index The index to access.
 */
void accessArray(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        IndexOutOfBoundsException ex = createIndexOutOfBoundsException();
        printf("%s: Invalid index %d (size: %d)\n", ex.message, index, size);
        return;
    }
    printf("Array element at index %d: %d\n", index, arr[index]);
}
/*
int main() {
    // Example array
    int arr[5] = {1, 2, 3, 4, 5};
    
    // Access a valid index
    accessArray(arr, 5, 2);  // Should succeed

    // Access an invalid index (out of bounds)
    accessArray(arr, 5, 10); // Should trigger IndexOutOfBoundsException

    return 0;
}
*/
