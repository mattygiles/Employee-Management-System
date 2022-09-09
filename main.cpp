#include "emsHeaders.h"
using namespace std;

int main() {

    // retrieve employee.txt file
    Employee::retrieveFile();

    // run loop function that contains options for user to choose
    Employee::loop();

    return 0;
}