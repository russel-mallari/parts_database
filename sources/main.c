#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "string_func.h"
#include "defines.h"
#include "typedef.h"
#include "file_operations.h"


int main(void)
{   

    
    unsigned int mode;
    mode = idle;

    while(1)
    {
        switch(mode)
        {
            case idle:
                mode = get_mode();
                break;
            case add:
                printf("Adding record....\n");
                add_record();
                mode = idle;
                break;
            case search:
                printf("Searching record....\n");
                record_search();
                mode = idle;
                break;
            case edit:
                printf("Editing record....\n");
                record_edit();
                mode = idle;
                break;
            case delete:
                printf("Deleting record....\n");
                record_delete();
                mode = idle;
                break;
            case exit_mode:
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Wrong mode. Please try again.\n");
                mode = idle;
                break;
        }
    }

    return 0;
    
}


