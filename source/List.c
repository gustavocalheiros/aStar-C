#include <stdio.h>
#include <string.h>

#include "List.h"
#include "Status.h"

List*	newList	(compFun f1, prFun f2)
{
	List* l = malloc(sizeof(List));

	if(l)
	{
		memset(l, 0, sizeof(List));
		l->comp = f1;
		l->pr = f2;
		l->nelts = 0;
	}

	return l;
}

void delList(List* list, int deleteVal)
{
	int i = 0;
	Node *aux = list->head;
	for(;i < list->nelts;i++)
	{
		Node* tmp = aux;
		aux = aux->next;
		if(deleteVal) free(tmp->val);
		free(tmp);
	}

	free(list);
}


status 	nthInList	(List* list,int index, void** e)
{
	int i = 0;
	Node *aux = list->head;

	if(index >= list->nelts)
		return ERRINDEX;

	for(;i < index;i++)
	{
		aux = aux->next;
	}

	*e = aux->val;

	return OK;
}

status 	remFromListAt(List* list,int index, void** out)
{
	int i = 0;
	Node *aux = list->head;
	Node *tmp = aux;

	if(index >= list->nelts)
		return ERRINDEX;

	for(;i < index;i++)
	{
		tmp = aux;
		aux = aux->next;
	}

	if(index == 0)
	{
		list->head = aux->next;
	}

	tmp->next = aux->next;
	if(out)
		*out = aux->val;

	free(aux);

	list->nelts--;

	return OK;
}

status 	remFromListGetElement	(List* list, void* e, void** out)
{
	Node *aux = list->head;
	int i=0;

	if(!list->comp)
		return ERRUNABLE;

	for(;i < list->nelts;i++)
	{
		if(list->comp(aux->val, e) == 0)
			break;

		aux = aux->next;
	}

	return remFromListAt(list, i, out);
}

status 	remFromList	(List* list,void* e)
{
	return remFromListGetElement(list, e, NULL);
}

status 	displayList(List* list)
{
	int i = 0;
	Node *aux = list->head;

	if(!list->pr)
		return ERRUNABLE;

	printf("[ ");

	for(;i < list->nelts;i++)
	{
		list->pr(aux->val);
		printf(" ");
		aux = aux->next;
	}

	printf("]\n");

	return OK;
}

void forEach(List* list,void(*f)(void* ) )
{
	int i = 0;
	Node *aux = list->head;
	for(;i < list->nelts;i++)
	{
		f(aux->val);
		aux = aux->next;
	}
}

int	lengthList(List* list)
{
	return list->nelts;
}

status	addList(List* list, void* e)
{
	Node *aux;
	aux = list->head;
	int i=0;

	if(!list->comp)
		return ERRUNABLE;

	for(;i < list->nelts;i++)
	{
		if(list->comp(aux->val, e) > 0)
		{
			break;
		}

		aux = aux->next;
	}

	return addListAt(list, i, e);
}

status addListAt(List* list,int index, void* e)
{
	Node *newNode, *aux;

	if(index > list->nelts)
		return ERRINDEX;

	newNode = malloc(sizeof(Node));
	if(!newNode)
		return ERRALLOC;

	memset(newNode, 0, sizeof(Node));

	if(index == 0)
	{
		newNode->next = list->head;
		list->head = newNode;
	}else{
		int i = 0;
		Node *tmp;
		aux = list->head;

		for(;i < index;i++)
		{
			tmp = aux;
			aux = aux->next;
		}

		tmp->next = newNode;
		newNode->next = aux;
	}

	newNode->val = e;
	list->nelts++;

	return OK;
}

Node* isInList(List* list,void* e)
{
	int i = 1;
	Node *aux = list->head;
	Node *prev = aux;

	if(!list->comp || list->nelts == 0)
		return NULL;

	if(list->comp(aux->val, e) == 0)
		return (Node*)1;

	aux = aux->next;
	for(;i < list->nelts;i++)
	{
		if(list->comp(aux->val, e) == 0)
			return prev;

		prev = aux;
		aux = aux->next;
	}

	return NULL;
}
