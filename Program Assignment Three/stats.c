// Tony Chau, Enrique Rodriguez

#include <stdio.h>

// stat func
void print_statistics(int total, int alloc_requests, int denied, double denial_pct, double avg_traversed, double avg_fragments) {
    printf("Total Requests: %d\n", total);
    printf("Allocation Requests: %d\n", alloc_requests);
    printf("Denied Allocations: %d (%.2f%%)\n", denied, denial_pct);
    printf("Avg Nodes Traversed (successful allocs): %.2f\n", avg_traversed);
    printf("Average External Fragments: %.2f\n", avg_fragments);
}
