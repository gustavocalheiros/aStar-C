#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "Map.h"
#include "path_assert.h"

#define PATH_MAP "res/FRANCE.MAP"
#define FIELDS_DELIMITER "\t"

#define MAX_DISTANCE 99999

static const int CITY = 4;
static const int NEIGHBOR = 3;

/**
 * compare functions
 */
int compString (void * c1, void * c2) {
  return strcmp(((City*)c1)->name, ((City*)c2)->name);
}

int compF (void * c1, void * c2)
{
	if(((City*)c1)->f < ((City*)c2)->f)
	  return -1;

	if(((City*)c1)->f > ((City*)c2)->f)
  	  return 1;

  return 0;
}

void prString(void * s) {
  printf("%s",((City*)s)->name);
}

//
// Auxiliar functions
//
City* findCity(char *name)
{
	Node *aux = cities->head;
	City *c = NULL;

	while(aux)
	{
		c = (City*)aux->val;
		if(strcmp(c->name, name) == 0)
			break;

		aux = aux->next;
	}

	return c;
}

void initializeVariables()
{
	goal =
	start = NULL;
	cities =
	openCities =
	closedCities = NULL;

	cities = newList(compString, prString);
	ASSERT_NOT_NULL(cities);
	openCities = newList(compF, prString);
	ASSERT_NOT_NULL(openCities);
	closedCities = newList(compString, prString);
	ASSERT_NOT_NULL(closedCities);
}

void deleteVariables()
{
	int i;
	Node *aux = cities->head;

	for(i=0;i < cities->nelts;i++)
	{
		City *c = (City*)aux->val;
		aux = aux->next;
		delList(c->neighbors, true);
	}

	delList(cities, true);
	delList(openCities, false);
	delList(closedCities, false);
}

/**
 * Populates the main city list with the content of the MAP file.
 */
status populateList(const char* from, const char* to)
{
	FILE *f = fopen(PATH_MAP, "r");
	char line[100];
	City *c;

	if(!f)
		return ERROPEN;

	while (fgets(line, sizeof(line), f)) {
		int place = resolveLine(line);
		if(place == CITY)
		{
			c = malloc(sizeof(City));
			if(!c)
			{
				fclose(f);
				return ERRALLOC;
			}

			memset(c, 0, sizeof(City));

			c->neighbors = newList(compString, prString);

			char* name = strtok(line, FIELDS_DELIMITER);
			strcpy(c->name, name);

			// discover if the city is either the "goal" or the "start".
			if(!goal && strcmp(to, name) == 0)
			{
				goal = c;
			}
			if(!start && strcmp(from, name) == 0)
			{
				start = c;
			}

			c->lat = atoi(strtok(NULL, FIELDS_DELIMITER));
			c->lon = atoi(strtok(NULL, FIELDS_DELIMITER));

			s = addList(cities, c);
			ASSERT_OK(s);
		}
		else if(place == NEIGHBOR) // last found city is used to add the neighbors
		{
			Neighbor* n = malloc(sizeof(Neighbor));
			if(!n)
			{
				fclose(f);
				return ERRALLOC;
			}

			memset(n, 0, sizeof(Neighbor));

			char* name = strtok(line, FIELDS_DELIMITER);
			strcpy(n->name, name);

			n->distance = atoi(strtok(NULL, FIELDS_DELIMITER));
			s = addList(c->neighbors, n);
			ASSERT_OK(s);
		}
	}

	fclose(f);

	return OK;
}


/**
 * Fill the main City List with the missing information:
 *  H: Its value can just be calculated after discovering which of the cities is the goal.
 *  G and F: Setting high values
 */
status fillMissingInfo()
{
	Node *aux = cities->head;

	while(aux)
	{
		City *c = (City*)aux->val;
		c->h = (abs(c->lat - goal->lat) + abs(c->lon - goal->lon))/4.f + .5f; // sum 0.5 to round the number

		// Fill G and F with a huge value.
		c->g = c->f = MAX_DISTANCE;

		aux = aux->next;
	}

	return OK;
}

////////////////////
//Parses the line considering the delimiter
//////////////////
int resolveLine(char* line)
{
	int i = 0;
	char *ptr = line;

	while (ptr!=NULL)
	{
		ptr=strchr(ptr+i,FIELDS_DELIMITER[0]);
		i++;
	}

	return i;
}

