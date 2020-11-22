#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stdbool.h>

void file_write(const char *filename);
bool file_is_existing(const char *filename);
void add_record(void);
bool goto_n_line(FILE *file_ptr, unsigned int line_number);
bool goto_n_line_offset(FILE *file_ptr, unsigned int line_number);
FILE* record_search(void);
void record_edit(void);
void record_delete(void);
unsigned int record_count(FILE *file_ptr);
unsigned int return_line_number(void);






#endif
