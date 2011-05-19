#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct table_struct
{
    char **column1;
    char **column2;
    int number_of_elements;
};

typedef struct table_struct table;

    table *
create_table() /* allocates space for a new structure and it's initial elements */
{
    table *tabl;

    tabl = malloc(sizeof(tabl->number_of_elements) + sizeof(tabl->column1) + sizeof(tabl->column2));

    tabl->column1 = malloc(sizeof(tabl->column1));
    tabl->column2 = malloc(sizeof(tabl->column2));
    tabl->number_of_elements = 0;

    return tabl;
}

delete_table(tabl) /* frees the size used by the table */
    table *tabl;
{
    int x;

    if (!tabl)
        return;

    for (x = 0; x < tabl->number_of_elements; x++) {
        free(tabl->column1[x]);
        free(tabl->column2[x]);
        tabl->column1[x] = tabl->column2[x] = NULL;
    }
    free(tabl->column1);
    free(tabl->column2);
    free(tabl);

    tabl->column1 = tabl->column2 = NULL;
    tabl = NULL;
}

add_to_table(tabl, col1, col2) /* adds elements (rows) to the table */
    table *tabl;
    char *col1;
    char *col2;
{ 
    int num, s1, s2;

    if (!tabl)
        return;

    num = tabl->number_of_elements++;

    tabl->column1 = realloc(tabl->column1, (num+1) * sizeof(col1));
    tabl->column2 = realloc(tabl->column2, (num+1) * sizeof(col2));

    s1 = strlen(col1);
    s2 = strlen(col2);

    tabl->column1[num] = malloc(s1+1);
    tabl->column2[num] = malloc(s2+1);

    strncpy(tabl->column1[num], col1, s1);
    strncpy(tabl->column2[num], col2, s2);

    tabl->column1[num][s1] = tabl->column2[num][s2] = '\0';
}

    char *
get_column(tabl, column, key) /* returns the element whose corresponding column matches the given key */
    table *tabl;
    short column;
    char *key;
{
    char *value, *key2;
    int x;

    if (!tabl)
        return(NULL);

for (x = 0; x < tabl->number_of_elements; x++) {
    switch (column) {
        case 1: {
                    key2 = tabl->column1[x];
                    value = tabl->column2[x];
                    break;
                }
        case 2: {
                    key2 = tabl->column2[x];
                    value = tabl->column1[x];
                    break;
                }
        default:
                return(NULL);
    }
    if (!strcmp(key, key2)) 
        return(value);
}

return(NULL);
}

print_table(tabl) 
    table *tabl;
{
    int x;

    if (!tabl)
        return;

    for (x = 0; x < tabl->number_of_elements; x++)
        printf("%s => %s\n", tabl->column1[x], tabl->column2[x]);
}

void table_populate(table *table_name)
{
    //populating each L2EPID table with 
    //random values - Just for demo purposes
    add_to_table(table_name, "VBI_ID", "34214");
    add_to_table(table_name, "tunnel_ID", "2312");
    add_to_table(table_name, "trust_flag", "3");
    add_to_table(table_name, "priority_source", "53");
    add_to_table(table_name, "def_priority", "21");
    add_to_table(table_name, "L2_flag", "235213");
    add_to_table(table_name, "PBB_L2EP", "919");
}

int main()
{
    //creates the level0 table which contains
    //the mapping for each L2EPID. This can
    //then be further used to find the values 
    //of the requested L2EPID. 
    table *level0 = create_table();
    add_to_table(level0, "L2-2353","L2EPID1");
    add_to_table(level0, "L2-1490", "L2EPID2");
    add_to_table(level0, "L2-8912", "L2EPID3");

    //creates the level1 table for each L2EPID
    //each of this table contains the mappings 
    //for the specific L2EPID.
    table *L2EPID1 = create_table();
    table *L2EPID2 = create_table();
    table *L2EPID3 = create_table();

    //populating the fields in each L2EPID
    table_populate(L2EPID1);
    table_populate(L2EPID2);
    table_populate(L2EPID3);

    char *current_table;
    current_table = get_column(level0, 1, "L2-1490");
    printf("Showing mappings for %s table :\n", current_table);

    print_table(L2EPID2);

    //delete_table(L2EPID);
    exit(0);
}

