// header
#ifndef MEMORY_H
#define MEMORY_H

int allocate_mem(int process_id, int num_units); // alloc
int deallocate_mem(int process_id); // dealloc
int fragment_count(); // frag count
void initialize_memory(); // init mem
void reset_memory(); //reset mem

#endif
