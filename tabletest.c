/*
* tabletests - several functions to implement associative arrays in C
*
* Copyright 2006 Felix H. Dahlke <>
* License: DWTFYLWI
*/

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

/* TODO: check for duplicates? not really needed for our purposes */

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

print_table(tabl) /* prints the table beautifully */
table *tabl;
{
int x;

if (!tabl)
return;

printf("======================================\n") ;
for (x = 0; x < tabl->number_of_elements; x++)
printf("%s | %s\n======================================\n", tabl->column1[x], tabl->column2[x]);
}

int main()
{
table *L2EPID = create_table();

add_to_table(L2EPID, VBI_ID, 34214);
add_to_table(L2EPID, tunnel_ID, "AV-2312");
add_to_table(L2EPID, trust_flag, 3);
add_to_table(L2EPID, priority_source, "random");
add_to_table(L2EPID, def_priority, 21);
add_to_table(L2EPID, L2_flag, 235213);
add_to_table(L2EPID, PBB_L2EP, 919);

print_table(L2EPID);
printf("Bob likes to %s.\n", get_column(hobbies, 2, "Bob"));

delete_table(hobbies);
}

