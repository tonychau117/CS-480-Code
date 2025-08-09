#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

#define MEMORY_SIZE 128  // 256KB / 2KB = 128 units

typedef struct Block {
    int process_id; // -1 if free
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
    Block *start = memory, *curr = memory;
    int count = 0, traversed = 0;

    while (curr) {
        traversed++;
        if (curr->process_id == -1) {
            Block* temp = curr;
            count = 0;
            while (temp && temp->process_id == -1 && count < num_units) {
                count++;
                temp = temp->next;
            }
            if (count == num_units) {
                for (int i = 0; i < num_units; ++i) {
                    curr->process_id = process_id;
                    curr = curr->next;
                }
                return traversed;
            }
        }
        curr = curr->next;
    }
    return -1;
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
    int frag = 0;

    while (curr) {
        if (curr->process_id == -1) {
            frag = 0;
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
