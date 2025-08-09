#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

#define MEMORY_SIZE 128  // 256 KB / 2 KB per unit = 128 units

typedef struct Block {
    int process_id;           // -1 means free
    struct Block* next;
} Block;

static Block* memory = NULL;

void initialize_memory() {
    memory = (Block*)malloc(sizeof(Block));
    memory->process_id = -1;
    memory->next = NULL;

    Block* curr = memory;
    for (int i = 1; i < MEMORY_SIZE; ++i) {
        curr->next = (Block*)malloc(sizeof(Block));
        curr = curr->next;
        curr->process_id = -1;
        curr->next = NULL;
    }
}

void reset_memory() {
    Block* curr = memory;
    while (curr) {
        curr->process_id = -1;
        curr = curr->next;
    }
}

int allocate_mem(int process_id, int num_units) {
    Block *curr = memory, *best_fit_start = NULL;
    int traversed = 0;
    int best_fit_size = MEMORY_SIZE + 1;

    while (curr) {
        traversed++;
        Block* temp = curr;
        int size = 0;

        // Look for free blocks
        while (temp && temp->process_id == -1) {
            size++;
            temp = temp->next;
        }

        // If this hole is big enough and better than the current best
        if (size >= num_units && size < best_fit_size) {
            best_fit_start = curr;
            best_fit_size = size;
        }

        // Skip this block (either allocated or already checked hole)
        if (size > 0)
            for (int i = 0; i < size; ++i)
                curr = curr->next;
        else
            curr = curr->next;
    }

    if (best_fit_start) {
        Block* ptr = best_fit_start;
        for (int i = 0; i < num_units; ++i) {
            ptr->process_id = process_id;
            ptr = ptr->next;
        }
        return traversed;
    }

    return -1; // No suitable block found
}

int deallocate_mem(int process_id) {
    Block* curr = memory;
    int found = 0;
    while (curr) {
        if (curr->process_id == process_id) {
            curr->process_id = -1;
            found = 1;
        }
        curr = curr->next;
    }
    return found ? 1 : -1;
}

int fragment_count() {
    Block* curr = memory;
    int count = 0;

    while (curr) {
        if (curr->process_id == -1) {
            int frag = 0;
            Block* temp = curr;
            for (int i = 0; i < 2 && temp && temp->process_id == -1; ++i) {
                frag++;
                temp = temp->next;
            }
            if (frag > 0) count++;
            while (curr && curr->process_id == -1)
                curr = curr->next;
        } else {
            curr = curr->next;
        }
    }
    return count;
}
