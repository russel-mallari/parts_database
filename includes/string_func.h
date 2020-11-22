#ifndef STRING_FUNC_H
#define STRIN_FUNC_H

#include <stdbool.h>

void string_write(const char *source, char *destination, unsigned int length);
void string_get(char *destination, unsigned int length);
bool string_compare(const char *str1, const char *str2);
char* part_type_select(void);
char* filename_return(void);
unsigned int get_mode(void);



#endif