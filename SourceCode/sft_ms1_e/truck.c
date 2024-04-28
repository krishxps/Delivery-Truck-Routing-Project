#define _CRT_SECURE_NO_WARNINGS
#include "shipment.h"
#include <stdio.h>

void createTrucks(struct Truck* trucks) {
	// truck [0] Blue route
	trucks[0].route = getBlueRoute();
	trucks[0].truckID = 'B';
	// truck [1] Yellow route
	trucks[1].route = getYellowRoute();
	trucks[1].truckID = 'Y';
	// truck [2] Green route
	trucks[2].route = getGreenRoute();
	trucks[2].truckID = 'G';
	trucks[0].weight = trucks[1].weight = trucks[2].weight = trucks[0].volume = trucks[1].volume = trucks[2].volume = 0;
}

char findTruck(struct Shipment* currentClient, struct Truck* trucks, int numTrucks, int* divert, struct Point* startPoint) {
	int blue = 0, yellow = 0, green = 0, index = 0;
	char truckID = 'X';
	struct DistanceWithTruck distances[3] = { 0 };
	struct Point startPoints[3] = { 0 };
	struct Map map = populateMap();
	if (enoughSpace(currentClient, &trucks[0])) {
		blue = hasPoint(&trucks[0].route, &currentClient->destination);
		if (blue == -1) {
			blue = shortestRouteToDestination(&map, &trucks[0].route, currentClient->destination);
			startPoints[0] = trucks[0].route.points[blue];
		}
		else {
			truckID = 'B';
			*divert = 0;
		}
	} else {
		blue = 0;
	};
	if (enoughSpace(currentClient, &trucks[1]) && truckID != 'B') {
		yellow = hasPoint(&trucks[1].route, &currentClient->destination);
		if (yellow == -1) {
			yellow = shortestRouteToDestination(&map, &trucks[1].route, currentClient->destination);
			startPoints[1] = trucks[1].route.points[yellow];
		}
		else {
			truckID = 'Y';
			*divert = 0;
		}
	} else {
		yellow = 0;
	};
	if (enoughSpace(currentClient, &trucks[2]) && truckID != 'B' && truckID != 'Y') {
		green = hasPoint(&trucks[2].route, &currentClient->destination);
		if (green == -1) {
			green = shortestRouteToDestination(&map, &trucks[2].route, currentClient->destination);
			startPoints[2] = trucks[2].route.points[green];
		}
		else {
			truckID = 'G';
			*divert = 0;
		}
	} else {
		green = 0;
	};
	if (blue == 0 && yellow == 0 && green == 0) {
		printf("Ships tomorrow\n");
		truckID = 'X';
	} else if(truckID == 'X') {
		if (blue) {
			distances[0].distance = distance(&(currentClient->destination), &startPoints[0]);
			distances[0].truck = trucks[0];
		} else {
			distances[0].distance = 1000;
		};
		if (yellow) {
			distances[1].distance = distance(&(currentClient->destination), &startPoints[1]);
			distances[1].truck = trucks[1];
		} else {
			distances[1].distance = 1000;
		};
		if (green) {
			distances[2].distance = distance(&(currentClient->destination), &startPoints[2]);
			distances[2].truck = trucks[2];
		} else {
			distances[2].distance = 1000;
		};
		for (int i = 0; i < numTrucks - 1; i++) {
			for (int j = 0; j < numTrucks - i - 1; j++) {
				if (distances[j].distance > distances[j + 1].distance) {
					struct DistanceWithTruck temp = distances[j];
					distances[j] = distances[j + 1];
					distances[j + 1] = temp;
				}
			}
		};

		index = chooseTruck(distances);
		*divert = 1;
		truckID = distances[index].truck.truckID;
		if (truckID == 'B') {
			*startPoint = startPoints[0];
		} else if (truckID == 'Y') {
			*startPoint = startPoints[1];
		} else {
			*startPoint = startPoints[2];
		}
	}
	return truckID;
}

//bug is fixed
int chooseTruck(struct DistanceWithTruck* distances) {
	int index = -1;
	if (distances != NULL) {
		if (distances[0].distance == distances[1].distance) {
			index = emptierTruck(distances[0].truck.weight, distances[0].truck.volume, distances[1].truck.weight, distances[1].truck.volume);
		}
		else {
			index = 0;
		}
	}

	return index;
}

int emptierTruck(double w1, double s1, double w2, double s2) {
	int index = 0;
	double percentage1 = 0, percentage2 = 0;

	percentage1 = (w1 / MAX_WEIGHT *100) + (s1 / MAX_VOLUME *100);
	percentage2 = (w2 / MAX_WEIGHT * 100) + (s2 / MAX_VOLUME * 100);
	if (percentage2 < percentage1) {
		index = 1;
	}
	return index;
}

//bug is fixed
int enoughSpace(struct Shipment* currentClient, struct Truck* trucks) {
	int answer = 0;
	if (trucks != NULL) {
		if (((trucks->volume + currentClient->size) <= MAX_VOLUME) && ((trucks->weight + currentClient->weight) <= MAX_WEIGHT)) {
			answer = 1;
		}
	}
	return answer;
}

int hasPoint(struct Route* route, struct Point* destination) {
	int index = -1;
	for (int i = 0; i < route->numPoints; i++) {
		if (distance(destination, &route->points[i]) == 1.0) {
			index = i;
			i = route->numPoints;
		}
	}
	return index;
}
