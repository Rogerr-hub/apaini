#include <stdio.h>
#include <stdbool.h>

/**
 * Struct representing a generic object in C.
 * This is similar to Java's Object class, acting as the root of all structures.
 */
typedef struct Object Object;
struct Object {
    Object (*createObject) (); // technically ngga pernah kepake..?
    bool (*equals) (Object*, Object*); // sebagai formalitas? c bisa lgsg manggil fungsi kalo udah include

    // teorinya gini: nanti ini dipake dengan assign Object.createObject = createObject
    // terus pake nya dengan Object.createObject()
    // atau
    // Object.equals = equals;
    // Object.equals(&obj1, &obj2)

    // okeoke ternyata inheritance bisa kepake tapi masi aga lama
    // semisal ada 2 fungsi yang namanya beda tapi isinya sama, biar ngga perlu nulis 2 kali ini bisa banget dipake guys :DD ehhee awokwokwok gg


    // Fields can be added here to represent data
} ;

/**
 * Constructs an Object.
 * In C, we can just return an empty Object struct.
 */
Object createObject() {
    Object obj;
    // Initialize any fields if needed
    return obj;
}

/**
 * Compares two Object references for equality.
 * In C, we compare pointers to simulate Java's 'equals' method.
 *
 * @param obj1 The first object to compare.
 * @param obj2 The second object to compare.
 * @return true if the objects are the same; false otherwise.
 */
bool equals(Object *obj1, Object *obj2) {
    return (obj1 == obj2);  // Compare object pointers (similar to Java's `==` operator)
}

// int main() {
//     Object obj1 = createObject();  // Create first object
//     Object obj2 = createObject();  // Create second object

//     // Compare obj1 and obj2
//     if (equals(&obj1, &obj2)) {
//         printf("Objects are equal.\n");
//     } else {
//         printf("Objects are not equal.\n");
//     }

//     // Compare obj1 with itself
//     if (equals(&obj1, &obj1)) {
//         printf("Object is equal to itself.\n");
//     }

//     return 0;
// }

