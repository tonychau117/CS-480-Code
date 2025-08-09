#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memory.h"

int generate_request_type();
int generate_process_id();
int generate_units();
void print_statistics(int, int, long long, int);

int main() {
    srand(time(NULL));
    initialize_memory();

    int total_requests = 10000;
    int denied = 0;
    long long traversal_sum = 0;

    for (int i = 0; i < total_requests; ++i) {
        int type = rand() % 2;
        int pid = generate_process_id();

        if (type == 0) {
            int units = generate_units();
            int result = allocate_mem(pid, units);
            if (result == -1) denied++;
            else traversal_sum += result;
        } else {
            deallocate_mem(pid);
        }
    }

    int fragments = fragment_count();
    print_statistics(total_requests, denied, traversal_sum, fragments);

    return 0;
}
