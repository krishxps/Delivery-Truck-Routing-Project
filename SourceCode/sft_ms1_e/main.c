#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "shipment.h"

int main(void)
{
	//Create the array for the trucks available
	struct Truck trucks[3];
	int numTrucks = 3;
	//Create the map for the trucks
	struct Map baseMap = populateMap();
	//printf("This is the base map:\n");
	//printMap(&baseMap, 1, 1);
	//printf("\n");
	//add a route to each truck
	createTrucks(trucks);
	// Fill the map with all te routes
	struct Map routeMap = addRoute(&baseMap, &trucks[0].route);
	routeMap = addRoute(&routeMap, &trucks[1].route);
	routeMap = addRoute(&routeMap, &trucks[2].route);
	//printf("This is the map with the 3 routes:\n");
	//printMap(&routeMap, 1, 1);
	//printf("\n");

	//Print the header:
	printHeader();
	//Ask for the shipment
	getShipment(trucks, numTrucks, &baseMap);

	return 0;
}