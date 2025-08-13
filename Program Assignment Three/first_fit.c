// Tony Chau, Enrique Rodriguez

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

#define MEMORY_SIZE 128  // mem size

typedef struct Block {
    int process_id; // -1 if free
    struct Block* next; // ptr
} Block;

static Block* memory = NULL; // set to null yb default

void initialize_memory() { 
    memory = (Block*)malloc(sizeof(Block)); // first block
    memory->process_id = -1; // free
    memory->next = NULL; // ptr null

    Block* curr = memory; // curr ptr
    for (int i = 1; i < MEMORY_SIZE; ++i) {
        curr->next = (Block*)malloc(sizeof(Block)); // find and set  block
        curr = curr->next; // move to next
        curr->process_id = -1; // set as free
        curr->next = NULL; // set ptr to null
    }
}

void reset_memory() {
    Block* curr = memory; // starts at beginngin of mem
    while (curr) {
        curr->process_id = -1; // marks free
        curr = curr->next; // moves to next
    }
}

int allocate_mem(int process_id, int num_units) {
    Block *start = memory;
    Block *curr = memory; // creates var for beginning of list and the ptr
    int count = 0; // sets to 0 for default
    int traversed = 0; // sets to 0 for default

    while (curr) {
        traversed++; // incs traversed
        if (curr->process_id == -1) {
            Block* temp = curr; // checks for free part
            count = 0; // ctr becomes 0
            while (temp && temp->process_id == -1 && count < num_units) {
                count++; // ctr for # of free blocks
                temp = temp->next; // sets dummy tepm var to next block
            }
            if (count == num_units) { // if a suitable amount are found
                for (int i = 0; i < num_units; ++i) {
                    curr->process_id = process_id; // allocates
                    curr = curr->next; // moves to next
                }
                return traversed; // returns # of traversed
            }
        }
        curr = curr->next; // moves to next if no allocation
    }
    return -1; // fails
}

int deallocate_mem(int process_id) {
    Block* curr = memory; // starts from beginning again
    int found = 0; // ctr
    while (curr) { // while not null
        if (curr->process_id == process_id) {
            curr->process_id = -1; // pids match set free
            found = 1; // denotes succ
        }
        curr = curr->next; // moves to next
    }
    return found ? 1 : -1; // returns 1 for dealloc, -1 elsewise
}

int fragment_count() {
    Block* curr = memory; // starting from beginnong again
    int count = 0; // sets to 0 for default
    int frag = 0; // sets to 0 for default

    while (curr) {
        if (curr->process_id == -1) { // if free
            frag = 0; // resets frag
            Block* temp = curr; // temp var gest curr pos
            for (int i = 0; i < 2 && temp && temp->process_id == -1; ++i) {
                frag++; // counts free blocks and inc frags if so
                temp = temp->next; // sets temp to next
            }
            if (frag > 0) 
            {
                count++; // if frag size > 0, inc count
            }
            while (curr && curr->process_id == -1)
                curr = curr->next; // skips
        } else {
            curr = curr->next; // moves to next
        }
    }
    return count; // return totla #
}
