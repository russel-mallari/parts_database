#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "file_operations.h"
#include "typedef.h"
#include "string_func.h"


static unsigned int line_number_match;

void file_write(const char *filename)
{
    time_t t = time(NULL);
    struct tm tm1 = *localtime(&t);

    // print the header of the database if the file does not exist
    if(file_is_existing(filename) == false)
    {
        FILE *output;
        output = fopen(filename, "a+");

        fprintf(output, "Part Number    Quantity    Name                    Date Updated    Description\n");
        fclose(output);
    }

    // write the record to database
    FILE *output;
    output = fopen(filename, "a+");

    if(output == NULL)
    {
         fprintf(stderr, "Could not open the file\n");
    }
    
    fprintf(output, "%-11s    %-8d    %-20s    %-d/%-d/%d      %-30s\n", elec_part.part_ID, elec_part.quantity, elec_part.part_name, tm1.tm_mon + 1, tm1.tm_mday, tm1.tm_year + 1900, elec_part.part_description);
    
    fclose(output);
}


bool file_is_existing(const char *filename)
{
    bool file_exist = false;

    FILE *output;
    output = fopen(filename, "r+");

    if(output == NULL)
    {
        file_exist = false;
    }
    else
    {
        file_exist = true;
    }

    fclose(output);
    
    return file_exist;
}

void add_record(void)
{
    char *filename;
    
    filename = part_type_select();

    printf("Enter the part name: ");
    string_get(elec_part.part_name, PART_NAME_SIZE);
    
    printf("Enter the part description: ");
    string_get(elec_part.part_description, PART_DESCRIPTION_SIZE);

    printf("Enter Part ID: ");
    string_get(elec_part.part_ID, PART_ID_SIZE);

    printf("Enter the quantity: ");
    scanf("%d", &elec_part.quantity);

    file_write(filename);
}

bool goto_n_line_offset(FILE *file_ptr, unsigned int line_number)
{
    bool reach_end_of_file = false;
    unsigned int line_counter = 0;
    char c;
    
    while((line_counter < line_number) && !reach_end_of_file)
    {
        while((c = fgetc(file_ptr)) != '\n')
        {
            if(c == EOF)
            {
                reach_end_of_file = true;
                break;
            }
        }
        ++line_counter;
    }

    return reach_end_of_file;
    
}

bool goto_n_line(FILE *file_ptr, unsigned int line_number)
{
    rewind(file_ptr);
    bool reach_end_of_file = false;
    unsigned int line_counter = 0;
    char c;
    
    while((line_counter < line_number) && !reach_end_of_file)
    {
        while((c = fgetc(file_ptr)) != '\n')
        {
            if(c == EOF)
            {
                reach_end_of_file = true;
                break;
            }
        }
        ++line_counter;
    }

    return reach_end_of_file;    
}


unsigned int record_count(FILE *file_ptr)
{
    rewind(file_ptr);
    char c;
    unsigned int counter = 0;
    // read charcters until not EOF
    while ((c = fgetc(file_ptr)) != EOF)
    {
        if(c == '\n')
        {
            ++counter;
        }
    }

    return counter;
}


FILE* record_search(void)
{

    char *file_name = part_type_select();
    

    FILE *ptr;
    ptr = fopen(file_name, "r+");
    

    char string_to_search[PART_NAME_SIZE];
    char string_fetched[PART_NAME_SIZE];

    printf("\n");
    printf("Please choose the field that you want to search.\n");
    printf("Press 1, if part ID. Press 2, if part name: ");

    unsigned int field_to_search;
    scanf("%d", &field_to_search);
    getchar();  // discard the newline

    printf("Please enter the record that you want to search: ");
    string_get(string_to_search, PART_NAME_SIZE);
    printf("Searched name is %s.\n", string_to_search);  
    printf("\n");  
    
    bool end_of_file = false;
    bool found_match = false;
    unsigned int line_counter = 1;
    
    line_number_match = 1;

    while(!(found_match) && !(end_of_file))
    {
        end_of_file = goto_n_line_offset(ptr, 1);
        
        if(field_to_search == 1)
        {
            fscanf(ptr, "%s", string_fetched);      // skip part ID and quantity
        }
        else if(field_to_search == 2)
        {
            fscanf(ptr, "%*s%*s%s", string_fetched);      // skip part ID and quantity
        }

        found_match = string_compare(string_to_search, string_fetched);
        if(found_match == true)
        {
            line_number_match = line_counter;
        }
        ++line_counter;
    }

    if(found_match == true)
    {
        goto_n_line(ptr, line_number_match);
        fscanf(ptr, "%s%d%s%s %[^\n]s",elec_part.part_ID, &elec_part.quantity, elec_part.part_name, elec_part.date_updated, elec_part.part_description);
        printf("Part id is %s.\n", elec_part.part_ID);
        printf("Quantity is %d.\n", elec_part.quantity);
        printf("Partname is %s.\n", elec_part.part_name);
        printf("Part was updated on %s.\n", elec_part.date_updated);
        printf("Part description is %s\n", elec_part.part_description);
    }
    else 
    {
        printf("Sorry did not found a match. Please try again.\n");
    }


    return ptr;
}


void record_edit(void)
{
    FILE *ptr;
    fpos_t pos;
    time_t t = time(NULL);
    struct tm tm1 = *localtime(&t);

    ptr = record_search();
    
    goto_n_line(ptr, line_number_match);
    fgetpos(ptr, &pos);
    fsetpos(ptr, &pos);
    
    unsigned int field_to_edit = 2;
    
    printf("\n");
    printf("Listed below are the field you can edit.\n");
    printf("1 : Part ID     2 : Quantity\n");
    printf("3 : Part Name   4 : Description\n");
    printf("Enter the number on the left of your chosen field: ");

    scanf("%d", &field_to_edit);
    getchar();  // flush newline

    switch(field_to_edit)
    {
        case 1:
            printf("What will be new part ID?\n");
            string_get(elec_part.part_ID, PART_ID_SIZE);
            break;
        case 2:
            printf("What will be new quantity?\n");
            scanf("%d", &elec_part.quantity);
            getchar();  // flush the newline
            break;
        case 3:
            printf("What will be new part name?\n");
            string_get(elec_part.part_name, PART_NAME_SIZE);
            break;
         case 4:
            printf("What will be new part description?\n");
            string_get(elec_part.part_description, PART_DESCRIPTION_SIZE);
            break;
        default:
            printf("Error\n");
    }

    fprintf(ptr, "%-11s    %-8d    %-20s    %-d/%-d/%d      %-30s\n", elec_part.part_ID, elec_part.quantity, elec_part.part_name, tm1.tm_mon + 1, tm1.tm_mday, tm1.tm_year + 1900, elec_part.part_description);

    fclose(ptr);
}


void record_delete(void)
{
    FILE *ptr_1;
    FILE *ptr_2;

    fpos_t position_temp_file;

    unsigned int line_match = 0;
    unsigned int line_limit;
    
    ptr_1 = record_search();
    ptr_2 = fopen("temp_file.txt", "w+");
    
    line_match = return_line_number();
    line_limit = record_count(ptr_1) - 1;
    
    rewind(ptr_1);
    rewind(ptr_2);

    fprintf(ptr_2, "Part Number    Quantity    Name                    Date Updated    Description\n");
    
    goto_n_line(ptr_1, 1);
    goto_n_line(ptr_1, 1);
    
    for(unsigned int i = 1; i <= line_limit; ++i)
    {
        if(line_match != i)
        {
            fscanf(ptr_1, "%s%d%s%s %[^\n]s",elec_part.part_ID, &elec_part.quantity, elec_part.part_name, elec_part.date_updated, elec_part.part_description);
            fprintf(ptr_2, "%-11s    %-8d    %-20s    %-13s   %-30s\n", elec_part.part_ID, elec_part.quantity,elec_part.part_name, elec_part.date_updated, elec_part.part_description);
        }
        else
        {
            line_match = 0;
            fscanf(ptr_1, "%s%d%s%s %[^\n]s",elec_part.part_ID, &elec_part.quantity, elec_part.part_name, elec_part.date_updated, elec_part.part_description);
        }    
    }
    
    fclose(ptr_2);
    fclose(ptr_1);

    char *file_name;
    file_name = filename_return();
    
    remove(file_name);

    if(rename("temp_file.txt", file_name) != 0)
    {
        printf("Failed deleting the record.\n");
    }
    else
    {
        printf("Success deleting the record\n");
    }
}

unsigned int return_line_number(void)
{
    return line_number_match;
}