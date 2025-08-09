#ifndef MEMORY_H
#define MEMORY_H

int allocate_mem(int process_id, int num_units);
int deallocate_mem(int process_id);
int fragment_count();
void initialize_memory();
void reset_memory();

#endif
