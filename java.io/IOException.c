/*
 * Copyright (C) 2024, Oracle and/or its affiliates. All rights reserved.
 */

#include <stdio.h>
#include <string.h>
#include "../java.lang/object.c" //implement IOexception extend exception (masukin di typdef)

/**
 * A C structure to represent an I/O exception.
 * In C, we typically handle errors using return codes instead of exceptions.
 * This structure can hold error information, similar to Java's IOException.
 */

typedef struct IOException {
    char message[256];  // Error message describing the I/O issue
} IOException;

/**
 * Initializes an IOException with a default message.
 */
void initIOException(IOException *exception) {
    if (exception != NULL) {
        strcpy(exception->message, "I/O exception occurred");
    }
}

/**
 * Initializes an IOException with a custom message.
 */
void initIOExceptionWithMessage(IOException *exception, const char *customMessage) {
    if (exception != NULL && customMessage != NULL) {
        strncpy(exception->message, customMessage, sizeof(exception->message) - 1);
        exception->message[sizeof(exception->message) - 1] = '\0'; // Ensures null termination
    }
}

/**
 * Prints the IOException message.
 */
void printIOException(IOException *exception) {
    if (exception != NULL) {
        printf("IOException: %s\n", exception->message);
    }
}
/*
int main() {
    IOException ioException;
    initIOException(&ioException);  // Initialize with default message
    printIOException(&ioException);

    IOException customIOException;
    initIOExceptionWithMessage(&customIOException, "Custom I/O error message");
    printIOException(&customIOException);

    return 0;
}
*/
