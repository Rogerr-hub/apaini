#include <stdio.h>

/**
 * Structure representing a RuntimeException in C.
 */
typedef struct RuntimeException {
    char message[100];  // To store the exception message
} RuntimeException;

/**
 * Constructs a RuntimeException with a default message.
 */
RuntimeException createRuntimeException() {
    RuntimeException ex;
    snprintf(ex.message, sizeof(ex.message), "RuntimeException: An unexpected error occurred.");
    return ex;
}

/**
 * Function to demonstrate a scenario that can throw a RuntimeException.
 * 
 * @param condition A condition that simulates an error.
 * @return 0 on success, -1 if a RuntimeException would be thrown.
 */
int performOperation(int condition) {
    if (condition < 0) {
        RuntimeException ex = createRuntimeException();
        printf("%s\n", ex.message);
        return -1; // Indicate failure due to runtime exception
    }

    // Simulate successful operation
    printf("Operation performed successfully with condition: %d\n", condition);
    return 0; // Success
}
/*
int main() {
    // Simulate an operation that fails
    performOperation(-1); // This should trigger the RuntimeException simulation

    // Simulate a successful operation
    performOperation(1); // This should succeed

    return 0;
}
*/
