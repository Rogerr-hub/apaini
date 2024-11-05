#include <stdio.h>

/**
 * A C structure to represent an ArithmeticException.
 * In C, instead of exceptions, we use return codes or flags to indicate errors.
 */
typedef struct ArithmeticException {
    char message[50];  // A simple message for the exception
} ArithmeticException;

/**
 * Constructs an ArithmeticException with a default message.
 */
ArithmeticException createArithmeticException() {
    ArithmeticException ex;
    // Initialize with a default message
    snprintf(ex.message, sizeof(ex.message), "Arithmetic exception occurred");
    return ex;
}

/**
 * Constructs an ArithmeticException with a custom message.
 */
ArithmeticException createArithmeticExceptionWithMessage(const char *customMessage) {
    ArithmeticException ex;
    // Copy the custom message to the exception's message
    snprintf(ex.message, sizeof(ex.message), "%s", customMessage);
    return ex;
}

/**
 * Prints the ArithmeticException message.
 */
void printArithmeticException(ArithmeticException ex) {
    printf("ArithmeticException: %s\n", ex.message);
}

/**
 * Simulate a divide by zero error, and raise the ArithmeticException.
 */
void divide(int numerator, int denominator) {
    if (denominator == 0) {
        ArithmeticException ex = createArithmeticException();
        printArithmeticException(ex);
    } else {
        printf("Result: %d\n", numerator / denominator);
    }
}
/*
int main() {
    // Example of throwing the exception for divide by zero
    divide(10, 0);
    
    // Example of normal division
    divide(10, 2);

    return 0;
}
*/
