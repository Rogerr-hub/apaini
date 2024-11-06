#include <stdio.h>
#include "Object.c" //implement throwable extend object (masukin di typdef)

#define equals 
/**
 * Structure representing a Throwable in C.
 */
typedef struct Throwable {
    Object Object;
    char message[100];  // To store the exception message
} Throwable;

/**
 * Constructs a new Throwable with an optional message.
 * 
 * @param msg The message to initialize the Throwable with (can be NULL).
 * @return An instance of Throwable initialized with the given message.
 */
Throwable createThrowable(const char *msg) {
    Throwable t;
    if (msg != NULL) {
        snprintf(t.message, sizeof(t.message), "%s", msg);
    } else {
        snprintf(t.message, sizeof(t.message), "Throwable occurred.");
    }
    return t;
}

/**
 * Function to print the Throwable message.
 * 
 * @param throwable The Throwable instance to print.
 */
void printThrowable(const Throwable *throwable) {
    printf("%s\n", throwable->message);
}
/*
int main() {
    // Create and print a Throwable instance
    Throwable t1 = createThrowable("An error has occurred.");
    printThrowable(&t1);

    // Create and print a default Throwable instance
    Throwable t2 = createThrowable(NULL);
    printThrowable(&t2);

    return 0;
}
*/
