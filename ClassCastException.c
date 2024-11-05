#include <stdio.h>
#include <string.h>

/**
 * Structure representing a ClassCastException in C.
 */
typedef struct ClassCastException {
    char message[100];  // To store the exception message
} ClassCastException;

/**
 * Constructs a ClassCastException with a default message.
 */
ClassCastException createClassCastException() {
    ClassCastException ex;
    snprintf(ex.message, sizeof(ex.message), "ClassCastException: Invalid cast attempted.");
    return ex;
}

/**
 * Simulates a type-checking system in C by using enums for object types.
 */
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} ObjectType;

/**
 * Structure representing a generic "Object" with a type and data.
 */
typedef struct {
    ObjectType type;
    union {
        int intValue;
        float floatValue;
        char *stringValue;
    } value;
} Object;

/**
 * Function to simulate casting an object to a specific type.
 *
 * @param obj The object to cast.
 * @param expectedType The expected object type to cast to.
 */
void castObject(Object obj, ObjectType expectedType) {
    if (obj.type != expectedType) {
        ClassCastException ex = createClassCastException();
        printf("%s: Cannot cast from type %d to type %d\n", ex.message, obj.type, expectedType);
        return;
    }
    printf("Cast successful: Object type is %d\n", obj.type);
}
/*
int main() {
    // Create a "String" object
    Object stringObj;
    stringObj.type = TYPE_STRING;
    stringObj.value.stringValue = "Hello, world!";

    // Create an "Int" object
    Object intObj;
    intObj.type = TYPE_INT;
    intObj.value.intValue = 42;

    // Try to cast the string object to an integer (invalid cast)
    castObject(stringObj, TYPE_INT);  // This should trigger a ClassCastException

    // Try to cast the int object to an integer (valid cast)
    castObject(intObj, TYPE_INT);     // This should succeed

    return 0;
}
*/
