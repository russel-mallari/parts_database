#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string_func.h"
#include "typedef.h"

// string write:
// writes character to a string.
// Parameter: size of string, characters to write, string to be written to
// Returns: 0 if successful, 1 if not.


static char *filename;

void string_write(const char *source, char *destination, unsigned int length)
{
    unsigned int char_counter = 0;

    while(char_counter < (length - 1))
    {
        *destination = *source;
        ++destination;
        ++source;
        ++char_counter;
    } 
    *destination = '\0';    

}


void string_get(char *destination, unsigned int length)
{
    unsigned int char_counter = 0;
    bool exceed_length = false;
    char c;

    while((c = getchar()) != '\n')      //keep reading the buffer to discard newline.
    {
        if(exceed_length == false)
        {
            *destination = c;
            ++destination;
            ++char_counter;
        }

        if(char_counter >= (length - 1))
        {
            exceed_length = true;
        }
    }
    *destination = '\0';

}


bool string_compare(const char *str1, const char *str2)
{
    bool is_match = true;

        while(((*str1 != '\0') || (*str2 != '\0')) && (is_match == true))
        {
            if(*str1 == *str2)
            {
                ++str1;
                ++str2;
                is_match = true;
            }
            else
            {
                is_match = false;
            }
        }

    return is_match;
}


char* part_type_select(void)
{

    char *filename_copy;

    printf("\n");
    printf("Listed below are the part type.\n");
    printf("1 : Microcontrollers    2 : Diodes     3 : Resistors\n");
    printf("Enter the number on the left of your chosen part type: ");

    unsigned int part_type_selector;
    scanf("%d", &part_type_selector);
    getchar();      // remove the newline from the buffer. 

    
    switch (part_type_selector)
    {
    case 1:
        string_write("Microcontrollers", elec_part.part_type, PART_TYPE_SIZE);
        filename = "microcontrollers.txt";
        break;
    case 2:
        string_write("Diodes", elec_part.part_type, PART_TYPE_SIZE);
        filename = "diodes.txt";
        break;
    case 3:
        string_write("Resistors", elec_part.part_type, PART_TYPE_SIZE);
        filename = "resistors.txt";
        break;
    default:
        break;

    }

    filename_copy = filename;

    return filename_copy;
}


char* filename_return(void)
{
    char* filename_copy;
    filename_copy = filename;

    return filename_copy;
}

unsigned int get_mode(void)
{
    unsigned int mode;

    printf("\n");
    printf("*****************************************\n");
    printf("Listed below are the modes.\n");
    printf("1 : add record      2 : search record\n");
    printf("3 : edit record     4 : delete record     5 : exit\n");
    printf("Enter the number on the left of your chosen mode: ");
    scanf("%d", &mode);
    getchar();      // discard newline to avoid error on next read
    

    return mode;
}