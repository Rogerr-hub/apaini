#include <stdio.h>
#include <string.h>
#include "Throwable.c" //implement exception extend throwable (masukin di typdef)

/**
 * Structure representing a generic Exception in C.
 * This is similar to Java's Exception class.
 */
typedef struct Exception {
    char message[100];  // To store the exception message
} Exception;

/**
 * Constructs an Exception instance with a default message.
 */
Exception createException() {
    Exception ex;
    snprintf(ex.message, sizeof(ex.message), "An exception occurred.");
    return ex;
}

/**
 * Constructs an Exception instance with a custom message.
 *
 * @param msg The custom message to set for the exception.
 */
Exception createExceptionWithMessage(const char *msg) {
    Exception ex;
    snprintf(ex.message, sizeof(ex.message), "%s", msg);
    return ex;
}

/**
 * Prints the exception message.
 *
 * @param ex The exception to print.
 */
void printException(Exception ex) {
    printf("Exception: %s\n", ex.message);
}
/*
int main() {
    // Create a default exception
    Exception ex = createException();
    printException(ex);

    // Create a custom exception with a specific message
    Exception customEx = createExceptionWithMessage("Custom exception occurred.");
    printException(customEx);

    return 0;
}
*/
