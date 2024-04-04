#include "functional.h"
#include "tasks.h"
#include "tests.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void reverse_elem(void *element)
{
	int *temp = malloc(sizeof(int));
	memcpy(temp,(int *)element,sizeof(int));
	memcpy((int *)element,(int *)(element)+sizeof(int),sizeof(int));
	memcpy((int *)(element)+sizeof(int),temp,sizeof(int));
	free(temp);
	
}


array_t reverse(array_t list) {
	for_each(reverse_elem,list);
	return list;
}


void functie_2(void *element , void **componente)
{
	number_t *num = (number_t *)element;
	num->integer_part = *(int*)componente[0];
	num->fractional_part = *(int *)componente[1];
	num->string = malloc(100);
	sprintf(num->string,"%d.%d",num->integer_part,num->fractional_part);
}

void destructor(void *p)
{
	number_t *elem = (number_t *)p;
	if(elem->string!=NULL)
	{
		free(elem->string);
		elem->string=NULL;
	}
}
array_t create_number_array(array_t integer_part, array_t fractional_part) {
	array_t new_list = map_multiple(functie_2,sizeof(number_t),destructor,2,integer_part,fractional_part);
	return new_list;
}

boolean functie_3(void *p)
{
	student_t stud = *(student_t *)p;
	return stud.grade > 5.0;
}

array_t get_passing_students_names(array_t list) {
	array_t new_list = filter(functie_3 , list);
	return new_list;
}


void functie_4(void *acc , void *lista_valori)
{
	int suma = 0;
	for(int i=0;i<(*(array_t *)lista_valori).len;i++)
		suma+=*(int *)((*(array_t *)lista_valori).data+i*(*(array_t *)lista_valori).elem_size);
	memcpy(acc,&suma,sizeof(int));
}

void verificare(void *element_lista_noua,void **lista_valori)
{
	boolean *value = (boolean *)element_lista_noua;
	int elem_sume = *(int *)lista_valori[0];
	int elem_control = *(int *)lista_valori[1];
	if(elem_sume >= elem_control)
		*value = true;
	else 
		*value = false;
}

array_t check_bigger_sum(array_t list_list, array_t int_list) {
	
	
	array_t new_list_sums = map(functie_4 , sizeof(int) , int_list.destructor , list_list);
	array_t new_list = map_multiple(verificare,sizeof(boolean),NULL,2,new_list_sums,int_list);
	return new_list;
}

array_t get_even_indexed_strings(array_t list) {
	(void)list;
	return (array_t){0};
}

void aloc(void *p)
{
	(void)p;
	//int *value = (int *)p;
	printf("NU\n");
}


void inc_elem(void *elem)
{
	char *i = (char *)elem;
	(*i)++;
}

array_t generate_square_matrix(int n) {
	array_t Array;
	Array.len = n;
	Array.elem_size = sizeof(char);
	Array.destructor = NULL;
	Array.data = malloc(Array.elem_size*Array.len);
	//for_each(decrement,Array);
	for_each(inc_elem,Array);
	//for_each(division,Array);
	for(int i=0;i<Array.len;i++)
		printf("%d ", *(int *)Array.data+i*Array.elem_size);
	//array_t new_array = map(functie_5,sizeof(array_t),NULL,)
	return (array_t){0};
}
