/*
 * Copyright (C) 2024, Oracle and/or its affiliates. All rights reserved.
 */

#include <stdio.h>
#include <string.h>
#include "../java.lang/Exception.c" //implement IOexception extend exception (masukin di typdef)

/**
 * A C structure to represent an I/O exception.
 * In C, we typically handle errors using return codes instead of exceptions.
 * This structure can hold error information, similar to Java's IOException.
 */
typedef struct IOException IOException;
struct IOException {
    Exception Exception;
    void (*initIOException) (IOException *exception);
    void (*initIOExceptionWithMessage) (IOException *exception, const char *customMessage);
    void (*printIOException) (IOException *exception);

    char message[256];  // Error message describing the I/O issue
};

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

// int main() {
//     IOException ioException;
//     initIOException(&ioException);  // Initialize with default message
//     printIOException(&ioException);

//     IOException customIOException;
//     initIOExceptionWithMessage(&customIOException, "Custom I/O error message");
//     printIOException(&customIOException);

//     Object o1;
//     Object o2;
//     o2.equals = equals;
//     if (o2.equals(&o1, &o1)) {
//         printf("Objects are equal.\n");
//     } else {
//         printf("Objects are not equal.\n");
//     }

//     return 0;
// }

