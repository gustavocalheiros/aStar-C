#include <stdio.h>
#include <string.h>

#include "Map.h"
#include "List.h"
#include "AStar.h"
#include "path_assert.h"

///////////////////////////
//Reverses the list for printing in the correct order.
////////////////////////////
static City* reverseList(City* head) {
	City* new_root = NULL;
	while (head)
	{
		City* next = head->back_pointer;
		head->back_pointer = new_root;
		new_root = head;
		head = next;
	}

	return new_root;
}

static void printResult(City* n)
{
	n = reverseList(n);

	do{
		printf("%s: %d\n", n->name, n->g);
		n = n->back_pointer;
	}while(n);
}

status runAStar()
{
	//step 1
	s = addList(openCities, start);
	ASSERT_OK(s);
	start->g = 0;

	//step 2
	while(lengthList(openCities) != 0)
	{
		City *n = NULL;
		int i;

		//step 3
		s = remFromListAt(openCities, 0, (void**)&n);
		ASSERT_OK(s);

		s = addList(closedCities, n);
		ASSERT_OK(s);

		//step 4
		if(strcmp(n->name, goal->name) == 0)
		{
			printResult(n);
			return OK;
		}

		//step 5
		for(i=0; i < n->neighbors->nelts; i++)
		{
			Neighbor *neigh = NULL;

			if(nthInList(n->neighbors, i, (void**)&neigh) == OK)
			{
				City *successor = NULL;
				City* aux = NULL;
				int temp;
				ASSERT_NOT_NULL(neigh);

				// step 5.1
				temp = n->g + neigh->distance;
				successor = findCity(neigh->name);
				ASSERT_NOT_NULL(successor);

				// step 5.2
				if((isInList(openCities, successor) || isInList(closedCities, successor)) &&
					(temp  > successor->g))
				{
					continue;
				}

				//step 5.3
				s = remFromListGetElement(openCities, successor,(void**) &aux);
				ASSERT_REMOVE(s);
				if(s == OK)
					successor = aux;

				s = remFromListGetElement(closedCities, successor, (void**) &aux);
				ASSERT_REMOVE(s);
				if(s == OK)
					successor = aux;

				//step 5.4
				successor->g = temp;
				successor->f = temp + successor->h;
				successor->back_pointer = n;

				s = addList(openCities, successor);
				ASSERT_OK(s);
			}
		}
	}// while

	return ERRUNKNOWN;
}
