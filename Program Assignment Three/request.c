#include <stdlib.h>

int gen_pid() {
    return rand() % 50 + 1; // PID 1 to 50
}

int gen_units() {
    return rand() % 8 + 3; // 3 to 10
}
