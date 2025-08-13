// Tony Chau, Enrique Rodriguez

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memory.h"

int gen_pid(); // gets random pid
int gen_units(); // gets units
void print_statistics(int, int, long long, int); // prints the stats

int main() {
    srand(time(NULL)); // sets time
    initialize_memory(); // init mem

    int total_requests = 10000; // 10k loops for 10k sims
    int denied = 0; // denied alloc
    long long traversal_sum = 0; // sum of nodes

    for (int i = 0; i < total_requests; ++i) {
        int type = rand() % 2; // either alloc or dealloc
        int pid = gen_pid(); // gens pid

        if (type == 0) { // if alloc
            int units = gen_units(); // gens units
            int result = allocate_mem(pid, units); // passes to allic func
            if (result == -1) { 
                denied++; // if unsuccessful alloc inc denied
            }
            else {
                traversal_sum += result; // else up results
            }
        } else {
            deallocate_mem(pid); // if not 0, then 1 -> dealloc
        }
    }

    int frags = fragment_count(); // count frags
    print_statistics(total_requests, denied, traversal_sum, frags); // pass to stats

    return 0; // fin
}
