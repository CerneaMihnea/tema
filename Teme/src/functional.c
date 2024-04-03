#include "functional.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <stdio.h>

void for_each(void (*func)(void *), array_t list)
{
	void *p=list.data;
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
	//void *np =new_list.data,*p=list.data;
	for(int i=0;i<new_list.len;i++)
		func(new_list.data+i*new_list_elem_size,list.data+i*list.elem_size);
	if(list.destructor)
		for(int i=0;i<list.len;i++)
			list.destructor(list.data+i*list.elem_size);
	free(list.data);
	return new_list;
}

array_t filter(boolean(*func)(void *), array_t list)
{
	array_t new_list;
	new_list.destructor=list.destructor;
	new_list.elem_size=list.elem_size;
	
	void *p =list.data;
	int lenght_new_list=0;
	for(int i=0;i<list.len;i++)
		if(func(p+i*list.elem_size))
			lenght_new_list++;
	new_list.len = lenght_new_list;
	new_list.data = malloc(new_list.len*new_list.elem_size);
	int index=0;
	void *np = new_list.data;
	for(int i=0;i<list.len;i++)
	{	
		
		if(func(p+i*list.elem_size))
		{
			memcpy(np+index*new_list.elem_size,p+i*list.elem_size,list.elem_size);
			//*(int *)(np+index*new_list.elem_size) = *(int *)(p+i*list.elem_size);
			index++;
		}
	}
	free(list.data);
	return new_list;
}

void *reduce(void (*func)(void *, void *), void *acc, array_t list)
{
	for(int i=0;i<list.len;i++)
	{
		func(acc,list.data+i*list.elem_size);
	}
	return NULL;
}

void for_each_multiple(void(*func)(void **), int varg_c, ...)
{
	va_list lists;
	va_start(lists,varg_c);
	int minim=-1;
	for(int i=0;i<varg_c;i++)
	{
		array_t list = va_arg(lists,array_t);
		if(minim ==-1 || list.len < minim)
			minim = list.len;
	}
	va_end(lists);
	
	for(int i=0;i<minim;i++)
	{
		void **elements = malloc(varg_c *sizeof(void *));
		va_start(lists,varg_c);
		for(int j=0;j<varg_c;j++)
		{
			array_t list = va_arg(lists, array_t);
			elements[j] = list.data+i*list.elem_size;
		}
		va_end(lists);
		func(elements);
		free(elements);
	}
}

array_t map_multiple(void (*func)(void *, void **),
					 int new_list_elem_size,
					 void (*new_list_destructor)(void *),
					 int varg_c, ...)
{
	va_list lists;
	va_start(lists,varg_c);
	int minim=-1;
	for(int i=0;i<varg_c;i++)
	{
		array_t list = va_arg(lists,array_t);
		if(minim ==-1 || list.len < minim)
			minim = list.len;
	}
	va_end(lists);
	
	array_t new_list;
	new_list.destructor=new_list_destructor;
	new_list.elem_size=new_list_elem_size;
	new_list.len = minim;
	new_list.data = malloc(new_list.len*new_list_elem_size);
	for(int i=0;i<minim;i++)
	{
		void **elements = malloc(varg_c *sizeof(void *));
		va_start(lists,varg_c);
		for(int j=0;j<varg_c;j++)
		{
			array_t list = va_arg(lists, array_t);
			elements[j] = list.data+i*list.elem_size;
		}
		va_end(lists);
		func(new_list.data+i*new_list.elem_size,elements);
		free(elements);
	}
	
	va_start(lists,varg_c);
		for(int j=0;j<varg_c;j++)
		{
			array_t list = va_arg(lists, array_t);
			if(list.destructor)
				for(int i=0;i<list.len;i++)
					list.destructor(list.data+i*list.elem_size);
			free(list.data);
		}
		va_end(lists);
	return new_list;
}

void *reduce_multiple(void(*func)(void *, void **), void *acc, int varg_c, ...)
{
	va_list lists;
	va_start(lists,varg_c);
	int minim=-1;
	for(int i=0;i<varg_c;i++)
	{
		array_t list = va_arg(lists,array_t);
		if(minim ==-1 || list.len < minim)
			minim = list.len;
	}
	va_end(lists);
	
	for(int i=0;i<minim;i++)
	{
		void **elements = malloc(varg_c *sizeof(void *));
		va_start(lists,varg_c);
		for(int j=0;j<varg_c;j++)
		{
			array_t list = va_arg(lists, array_t);
			elements[j] = list.data+i*list.elem_size;
		}
		va_end(lists);
		func(acc,elements);
		free(elements);
	}
	return NULL;
}
