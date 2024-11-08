#include "java.io/package_java_io.h"

void main() {
    IOException IOExc1;
    IOException test_exception;

    IOExc1.initIOException = initIOException;
    IOExc1.printIOException = printIOException;

    IOExc1.initIOException(&test_exception);
    IOExc1.printIOException(&test_exception);

};