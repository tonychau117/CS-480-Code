#include <stdio.h>

void print_statistics(int total, int denied, long long traversal_sum, int fragments) {
    printf("Total Requests: %d\n", total);
    printf("Denied Allocations: %d (%.2f%%)\n", denied, (100.0 * denied / total));
    printf("Avg Nodes Traversed: %.2f\n", (double)traversal_sum / (total - denied));
    printf("Final Fragment Count: %d\n", fragments);
}
