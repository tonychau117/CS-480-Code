// Tony Chau, Enrique Rodriguez

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memory.h"

int gen_pid(); // gets random pid
int gen_units(); // gets units
void print_statistics(int total_requests, int alloc_requests, int denied, double denial_pct, double avg_traversed, double avg_fragments); // prints the stats

static int allocated[51] = {0};
int main() {
    srand(time(NULL)); // sets time
    initialize_memory(); // init mem

    int total_requests = 10000; // 10k loops for 10k sims
    int denied = 0; // denied alloc
    long long traversal_sum = 0; // sum of nodes
    int alloc_requests = 0; // alloc attempts
    long long sum_fragments = 0; // sum of fragment_count() after each request

    for (int i = 0; i < total_requests; ++i) {
        int type = rand() % 2; // either alloc or dealloc
        int pid = gen_pid(); // gens pid
        
        if (type == 0) { // alloc each PID only once, dealloc if allocated
            if (allocated[pid]) type = 1;
        }
        else {
            if (!allocated[pid]) type = 0; 
        }

        if (type == 0) { // if alloc
            alloc_requests++; // track alloc attemps
            int units = gen_units(); // gens units
            int result = allocate_mem(pid, units); // passes to allic func
            if (result == -1) { 
                denied++; // if unsuccessful alloc inc denied
            }
            else {
                traversal_sum += result; // else up results
                allocated[pid] = 1; // mark PID as allocated
            }
        } else {
            int d = deallocate_mem(pid); // if not 0, then 1 -> dealloc
            if (d == 1) {
                allocated[pid] = 0; // dealloc
            }
        }
        sum_fragments += fragment_count();
    }

    int alloc_success = alloc_requests - denied;
    double denial_pct = (alloc_requests > 0) ? (100.0 * denied / alloc_requests) : 0.0;
    double avg_traversed = (alloc_success > 0) ? ((double)traversal_sum / alloc_success) : 0.0;
    double avg_fragments = (double)sum_fragments / (double)total_requests;
    print_statistics(total_requests, alloc_requests, denied, denial_pct, avg_traversed, avg_fragments); // pass to stats

    return 0; // fin
}
