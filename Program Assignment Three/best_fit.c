// Tony Chau, Enrique Rodriguez

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

#define MEMORY_SIZE 128  // memoery count

typedef struct Block {
    int process_id; // process id
    struct Block* next; // pointer 
} Block;

static Block* memory = NULL; // head pointer

void initialize_memory() {
    memory = (Block*)malloc(sizeof(Block)); // gets the first block
    memory->process_id = -1; // -1 marks it as a free one
    memory->next = NULL; // sets next pointer to null

    Block* curr = memory; // curr pointer
    for (int i = 1; i < MEMORY_SIZE; ++i) { // loops through the remaining memory size
        curr->next = (Block*)malloc(sizeof(Block)); // sets next to an allocation
        curr = curr->next; // resetse curr
        curr->process_id = -1; // marks as free
        curr->next = NULL; // sets the next pointer to null
    }
}

void reset_memory() {
    Block* curr = memory; // starts at mem
    while (curr) { // while mem exists
        curr->process_id = -1; // frees curr position
        curr = curr->next; // moves to next
    }
}

int allocate_mem(int process_id, int num_units) {
    Block *curr = memory; // traversal
    Block *best_fit_start = NULL; 
    int traversed = 0; // count for amt traversed
    int best_fit_size = MEMORY_SIZE + 1; // init size of best fit

    while (curr) { // looping through mem
        traversed++; // inc traversed section
        Block* temp = curr; // create a dummy var to find a free slot
        int size = 0; // size of seg


        while (temp && temp->process_id == -1) { // cond
            size++; // incs our size
            temp = temp->next; // constantly sets temp to the next over while cond is true
        }

        if (size >= num_units && size < best_fit_size) { // if the shoe fits
            best_fit_start = curr; // updates the following two vars
            best_fit_size = size;
        }

        // else 
        if (size > 0)
            for (int i = 0; i < size; ++i)
                curr = curr->next; // omve until cond met
        else
            curr = curr->next; // single inc
    }

    if (best_fit_start) {
        Block* ptr = best_fit_start; // creation of a ptr
        for (int i = 0; i < num_units; ++i) { // loop cond
            ptr->process_id = process_id; // sets ptr to a corresponding pid
            ptr = ptr->next; // moves to next node/block
        }
        return traversed; // returns # of traversed
    }

    return -1; // fails
}

int deallocate_mem(int process_id) {
    Block* curr = memory; // sets curr
    int found = 0; // freed
    while (curr) {
        if (curr->process_id == process_id) { 
            curr->process_id = -1; // free
            found = 1; // succ
        }
        curr = curr->next; // sets curr to next node/block
    }
    return found ? 1 : -1; // returns 1 if at  least one was free
}

int fragment_count() {
    Block* curr = memory; // origin
    int count = 0; // ctr

    while (curr) {
        if (curr->process_id == -1) { // if free
            int frag = 0; // frag ctr
            Block* temp = curr; // temp var to move throughout
            for (int i = 0; i < 2 && temp && temp->process_id == -1; ++i) {
                frag++; // incs
                temp = temp->next; // reassigns
            }
            if (frag > 0)
            {
                count++; //if frag > 0, inc
            }
            while (curr && curr->process_id == -1)
                curr = curr->next; // reassigns
        } else {
            curr = curr->next; // reassigns
        }
    }
    return count; // returns count
}
