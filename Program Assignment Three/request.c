#include <stdlib.h>

int generate_request_type() {
    return rand() % 2; // 0 = alloc, 1 = dealloc
}

int generate_process_id() {
    return rand() % 50 + 1; // PID 1 to 50
}

int generate_units() {
    return rand() % 8 + 3; // 3 to 10
}
