#include "functional.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <stdio.h>

void for_each(void (*func)(void *), array_t list)
{
	int *p=list.data;
	for(int i=0;i<list.len;i++)
	{
		func(p+i*list.elem_size);
	}
}

array_t map(void (*func)(void *, void *),
			int new_list_elem_size,
			void (*new_list_destructor)(void *),
			array_t list)
{	
	array_t new_list;
	new_list.elem_size = new_list_elem_size;
	new_list.len = list.len;
	new_list.destructor = new_list_destructor;
	new_list.data = malloc(list.len * list.elem_size);
	int *np =new_list.data,*p=list.data;
	for(int i=0;i<new_list.len;i++)
		func(np+i*new_list_elem_size,p+i*list.elem_size);
	free(list.data);
	return new_list;
}

array_t filter(boolean(*func)(void *), array_t list)
{
	array_t new_list;
	new_list.destructor=list.destructor;
	new_list.elem_size=list.elem_size;
	
	int *p =list.data;
	int lenght_new_list=0;
	for(int i=0;i<list.len;i++)
		if(func(p+i*list.elem_size))
			lenght_new_list++;
	new_list.len = lenght_new_list;
	new_list.data = malloc(new_list.len*new_list.elem_size);
	int index=0;
	int *np = new_list.data;
	for(int i=0;i<list.len;i++)
	{	
		
		if(func(p+i*list.elem_size))
		{
			
			*(np+index*new_list.elem_size) = *(p+i*list.elem_size);
			//printf("%d\n", *(np+index*new_list.elem_size));
			index++;
		}
	}
	free(list.data);
	return new_list;
}

void *reduce(void (*func)(void *, void *), void *acc, array_t list)
{
	(void)func;
	(void)acc;
	(void)list;
	return NULL;
}

void for_each_multiple(void(*func)(void **), int varg_c, ...)
{
	(void)func;
	(void)varg_c;
}

array_t map_multiple(void (*func)(void *, void **),
					 int new_list_elem_size,
					 void (*new_list_destructor)(void *),
					 int varg_c, ...)
{
	(void)func;
	(void)new_list_elem_size;
	(void)new_list_destructor;
	(void)varg_c;
	return (array_t){0};
}

void *reduce_multiple(void(*func)(void *, void **), void *acc, int varg_c, ...)
{
	(void)func;
	(void)acc;
	(void)varg_c;
	return NULL;
}
