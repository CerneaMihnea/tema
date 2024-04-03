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
	/*for(int i=0;i<(*(array_t *)lista_valori).len;i++)
	{
		if((*(array_t *)lista_valori).data>(*(array_t *)lista_valori).data)
	}*/
	//boolean *value = (boolean *)element_lista_noua;
	(void)element_lista_noua;
	for(int i=0;i<(*((array_t *)lista_valori)).len;i++);
	printf("%d ", ((*(array_t *)lista_valori).len));
}

array_t check_bigger_sum(array_t list_list, array_t int_list) {
	
	
	array_t new_list_sums = map(functie_4 , sizeof(int) , int_list.destructor , list_list);

	/*for(int i=0;i<new_list_sums.len;i++)
		printf("%d\n" , *(int *)(new_list_sums.data+i*new_list_sums.elem_size));*/
	/*for(int i=0;i<new_list_sums.len;i++)
		printf("%d " , *((int *)new_list_sums.data+i*new_list_sums.elem_size));*/

	/*for(int i=0;i<list_list.len;i++)
	{
		array_t lista = *(array_t *)(list_list.data+i*list_list.elem_size);
		int acc=0;
		reduce(functie_4,&acc,lista);
		if(acc >= *(int *)(int_list.data+i*int_list.elem_size))
			*((boolean *)new_list.data+i*new_list.elem_size) = 1;
		else 
			*((boolean *)new_list.data+i*new_list.elem_size) = 0;
	}*/



	array_t new_list = map_multiple(verificare,sizeof(boolean),NULL,2,new_list_sums,int_list);

	/*if(int_list.destructor)
		for(int i=0;i<int_list.len;i++)
			{
				int_list.destructor(int_list.data+i*int_list.elem_size);
				new_list_sums.destructor(new_list_sums.data+i*new_list_sums.elem_size);
			}
	free(int_list.data);
	free(new_list_sums.data);*/
	return new_list;
}

array_t get_even_indexed_strings(array_t list) {
	(void)list;
	return (array_t){0};
}

array_t generate_square_matrix(int n) {
	(void)n;
	return (array_t){0};
}
