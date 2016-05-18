#ifndef __MAP_H__
#define __MAP_H__

#include "List.h"

#define MAX_LENGHT 100

typedef struct City
{
	char name[MAX_LENGHT];
	int lat;
	int lon;
	int g; //distance from the origin to city
	int h;// h from the origin to the goal //  ==== computed only once (city creation)
	int f;
	struct City* back_pointer;
	List* neighbors;
}City;

typedef struct Neighbor
{
	char name[MAX_LENGHT];
	int distance;
}Neighbor;

// Compare functions
int compString(void * c1, void * c2);
void prString(void*);
int compF (void * c1, void * c2);

//fields
City* goal;
City* start;
List* cities;
List* openCities;
List* closedCities;

//methods
void initializeVariables();
void deleteVariables();
City* findCity(char *name);
status populateList(const char* from, const char* to);
status fillMissingInfo();
int resolveLine(char* line);

#endif //__MAP_H__
