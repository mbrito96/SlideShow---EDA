#include <stdio.h>
#include <string.h>
#include "listControl.h"

bool_t insertElement(listType lista, unsigned int pos, void * elemento) {
	int i;
	bool_t returnVal = FALSE;
	nodeType * primerNodo = getFirstNode(lista);

	if (pos <= listSize(lista)) {
		nodeType * newNode = malloc(sizeof(nodeType));

		if (newNode != NULL)
		{
			newNode->elemento = malloc(sizeof(getElementSize(lista)));
			if (newNode->elemento != NULL)
			{
				memcpy(newNode->elemento, elemento, getElementSize(lista));
				if (pos == 0)
				{
					newNode->proximo = primerNodo;
					setFirstNode(lista, newNode);
				}
				else
				{
					nodeType * tempNode = primerNodo;
					for (i = 1; i < pos; i++)
						tempNode = tempNode->proximo;
					newNode->proximo = tempNode->proximo;
					tempNode->proximo = newNode;
				}
				lista->elementCount += 1;
				returnVal = TRUE;
			}
			else
				free(newNode->elemento);
		}
		else
			free(newNode);
	}
	return returnVal;
}




listType createList(unsigned elementSize) // If list was not created a NULL * is returned
{
	listType newList = (listType)malloc(sizeof(headerType));
	if (newList != NULL) {
		newList->elementSize = elementSize;
		newList->firstElement = NULL;
		newList->elementCount = 0;
	}
	return newList;
}


bool_t getElement(listType list, unsigned position, void * element)
{
	unsigned i;
	bool_t retVal = FALSE;
	nodeType * tempNode;
	if (position < list->elementCount)
	{
		tempNode = list->firstElement;
		for (i = 0; i < position; i++)
			tempNode = tempNode->proximo;
		memcpy(element, tempNode->elemento, list->elementSize);
		retVal = TRUE;
	}
	return retVal;
}

bool_t removeElement(listType list, unsigned position, void * element)
{
	bool_t retVal = FALSE;
	unsigned i;
	nodeType * node2Delete;
	nodeType * prevNode2Delete;
	if (position < list->elementCount)
	{
		node2Delete = list->firstElement;
		if (position == 0)
		{
			list->firstElement = node2Delete->proximo;
			free(node2Delete->elemento);
			free(node2Delete);
		}
		else
		{
			for (i = 1; i < position; i++)
				prevNode2Delete = prevNode2Delete->proximo;
			node2Delete = prevNode2Delete->proximo;
			prevNode2Delete->proximo = node2Delete->proximo;
			free(node2Delete->elemento);
			free(node2Delete);

		}
		retVal = TRUE;
		list->elementCount -= 1;
	}
	return retVal;
}

void destroyList(listType * list)
{
	while (removeElement(list, 0));
	free(*list);
	list = NULL;
}


unsigned listSize(listType * list)
{
	return sizeof(nodeType)*list->elementCount;
}