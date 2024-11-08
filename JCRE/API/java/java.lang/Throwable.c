#include <stdio.h>
#include "Object.c" //implement throwable extend object (masukin di typdef)

//kalau mau inherit equals dari Object.c tinggal panggil aja equals(&obj1, &obj2) ngga perlu inherit2 ribet karna udh di "include" BOOM! (ada penjelasan di object.c ini ngga salah tapi kurang tepat aja guys)
/**
 * Structure representing a Throwable in C.
 */
typedef struct Throwable Throwable;
struct Throwable {
    Object Object; // formalitas...?
    Throwable (*createThrowable) (const char *msg);
    void (*printThrowable) (const Throwable *throwable);
    
    char message[100];  // To store the exception message
};

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

// int main() {
//     // Create and print a Throwable instance
//     Throwable t1 = createThrowable("An error has occurred.");
//     printThrowable(&t1);

//     // Create and print a default Throwable instance
//     Throwable t2 = createThrowable(NULL);
//     printThrowable(&t2);

//     Object o1;
//     Object o2;
//     // Compare obj1 and obj2
//     if (equals(&o1, &o2)) {
//         printf("Objects are equal.\n");
//     } else {
//         printf("Objects are not equal.\n");
//     }

//     //misal cara pake inheritance:
//     Object o3;
//     o3.equals = equals;
//     if (o3.equals(&o1, &o2)) {              // -> di bagian ini, o3 punya pengecekan equals yg terpisah dari equals fungsi langsung (meskipun sama tapi beda gitu deh wkwkk)
//         printf("Objects are equal.\n");
//     } else {
//         printf("Objects are not equal.\n");
//     }


//     return 0;
// }

