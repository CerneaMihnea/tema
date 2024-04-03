#include "functional.h"
#include "tasks.h"
#include "tests.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

array_t reverse(array_t list) {
	(void)list;
	return (array_t){0};
}


void functie_2(void *element , void **componente)
{
	number_t *num = (number_t *)element;
	num->integer_part = *(int*)componente[0];
	num->fractional_part = *(int *)componente[1];
	num->string = malloc(100);
	sprintf(num->string,"%d.%d",num->integer_part,num->fractional_part);
}


array_t create_number_array(array_t integer_part, array_t fractional_part) {
	array_t new_list = map_multiple(functie_2,sizeof(number_t),NULL,2,integer_part,fractional_part);
	return new_list;
}

array_t get_passing_students_names(array_t list) {
	(void)list;
	return (array_t){0};
}

array_t check_bigger_sum(array_t list_list, array_t int_list) {
	(void)list_list;
	(void)int_list;
	return (array_t){0};
}

array_t get_even_indexed_strings(array_t list) {
	(void)list;
	return (array_t){0};
}

array_t generate_square_matrix(int n) {
	(void)n;
	return (array_t){0};
}
