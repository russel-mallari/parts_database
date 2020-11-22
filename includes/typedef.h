#ifndef TYPEDEF_H
#define TYPEDEF_H


#include "defines.h"

typedef struct
{
    char part_ID[PART_ID_SIZE];
    unsigned int quantity;
    char part_type[PART_TYPE_SIZE];
    char part_name[PART_NAME_SIZE];
    char date_updated[DATE_UPDATED_SIZE];
    char part_description[PART_DESCRIPTION_SIZE];
} record;


extern record elec_part;

enum
{
    idle,
    add,
    search,
    edit,
    delete,
    exit_mode,
};

#endif