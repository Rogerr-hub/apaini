#include <stdio.h>
#include <string.h>

/**
 * Enum representing different types of objects that could be stored in the array.
 */
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR
} ObjectType;

/**
 * Structure representing a simple "Object" that stores a type and value.
 */
typedef struct {
    ObjectType type;
    union {
        int intValue;
        float floatValue;
        char charValue;
    } value;
} Object;

/**
 * Structure to represent an ArrayStoreException.
 * In C, this is used to simulate the exception when storing an invalid object in an array.
 */
typedef struct ArrayStoreException {
    char message[100];
} ArrayStoreException;

/**
 * Constructs an ArrayStoreException with a default message.
 */
ArrayStoreException createArrayStoreException() {
    ArrayStoreException ex;
    snprintf(ex.message, sizeof(ex.message), "Array store exception: Incompatible type");
    return ex;
}

/**
 * Simulates storing an object in an array.
 * Throws an ArrayStoreException if the object type is not compatible with the target type.
 *
 * @param array The array to store into.
 * @param index The index to store at.
 * @param obj The object to store.
 * @param expectedType The expected object type for the array.
 */
void storeObject(Object *array, int index, Object obj, ObjectType expectedType) {
    if (obj.type != expectedType) {
        ArrayStoreException ex = createArrayStoreException();
        printf("%s: Cannot store type %d into array of type %d at index %d\n", ex.message, obj.type, expectedType, index);
        return;
    }
    array[index] = obj;  // Store the object if the type is correct
    printf("Stored object of type %d at index %d\n", obj.type, index);
}
/*
int main() {
    // Create an array of objects (simulated array of "integers")
    Object array[5];

    // Create some objects
    Object intObject = { TYPE_INT, .value.intValue = 42 };
    Object floatObject = { TYPE_FLOAT, .value.floatValue = 3.14f };

    // Try to store an integer (valid)
    storeObject(array, 0, intObject, TYPE_INT);

    // Try to store a float (invalid)
    storeObject(array, 1, floatObject, TYPE_INT);  // Should trigger ArrayStoreException

    return 0;
}
*/
