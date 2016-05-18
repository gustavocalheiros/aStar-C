#include <stdio.h>
#include "Map.h"
#include "AStar.h"
#include "List.h"
#include "path_assert.h"

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("Please insert 2 cities (From & to)\n");
		return EXIT_FAILURE;
	}

	char *from = argv[1];
	char *to = argv[2];

	initializeVariables();

	s = populateList(from, to);
	ASSERT_OK(s);

	// Check if the city names provided are valid.
	if(!goal || !start)
	{
		printf("Please insert 2 VALID cities!!! \n");
		return EXIT_FAILURE;
	}

	s = fillMissingInfo();
	ASSERT_OK(s);

	s = runAStar();
	ASSERT_OK(s);

	deleteVariables();

	return EXIT_SUCCESS;
}
