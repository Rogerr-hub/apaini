#include <stdio.h>

/**
 * Structure representing a RuntimeException in C.
 */
typedef struct RuntimeException {
    char message[100];  // To store the exception message
} RuntimeException;

/**
 * Structure representing a SecurityException in C, which extends RuntimeException.
 */
typedef struct SecurityException {
    RuntimeException base; // Inherit from RuntimeException
} SecurityException;

/**
 * Constructs a SecurityException with a default message.
 */
SecurityException createSecurityException() {
    SecurityException ex;
    snprintf(ex.base.message, sizeof(ex.base.message), "SecurityException: A security violation has occurred.");
    return ex;
}

/**
 * Function to simulate a security-sensitive operation.
 * 
 * @param allowed A boolean indicating if the operation is allowed.
 * @return 0 on success, -1 if a SecurityException would be thrown.
 */
int performSensitiveOperation(int allowed) {
    if (!allowed) {
        SecurityException ex = createSecurityException();
        printf("%s\n", ex.base.message);
        return -1; // Indicate failure due to security exception
    }

    // Simulate successful operation
    printf("Sensitive operation performed successfully.\n");
    return 0; // Success
}
/*
int main() {
    // Simulate an unauthorized access
    performSensitiveOperation(0); // This should trigger the SecurityException simulation

    // Simulate an authorized access
    performSensitiveOperation(1); // This should succeed

    return 0;
}
*/
