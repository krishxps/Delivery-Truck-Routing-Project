#define _CRT_SECURE_NO_WARNINGS
#include "shipment.h"
#include <stdio.h>
#include <string.h>

void printHeader()
{
	printf("================= \n Seneca College Deliveries\n=================\n");
}


// -1 -- Exit
// 0 Wrong data
// 4 correct data
void getShipment(struct Truck* trucks, int numTrucks, struct Map* map)
{
	int flag = 0;
    int divert = 0;
    char truckID = 'X';
    struct Shipment currentClient = { 0 };
    struct Route newRoute = { 0 };
    struct Point startPoint = { 0 };
	do {
		printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
		flag = validateShip(&currentClient);
        if (flag == 1) {
            truckID = findTruck(&currentClient, trucks, numTrucks, &divert, &startPoint);
            if (truckID != 'X') {
                printBusline(truckID);
                if (divert) {
                    printf("divert:");
                    newRoute = shortestPath(map, startPoint, currentClient.destination);
                    if (newRoute.numPoints > 0) {
                        printDiversion(&startPoint, &newRoute, &currentClient.destination);
                    }
                    else {
                        printf("Error: No valid route found.\n");
                    }
                } else {
                    printf("no diversion\n");
                };
            }
            fillTruck(&currentClient, truckID, trucks);
        }
	} while (flag !=-1);
	

}

int validateShip(struct Shipment* currentClient)
{
    float weight = 0, size = 0;
    char col = 'X';
    int row = 0;
    int result = 0;
    printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
    result = scanf("%f %f %d%c", &weight, &size, &row, &col);
    if (result == 4) {
        result = validateWeight(weight);
        if (result) {
            currentClient->weight = weight;
            result = validateSize(size);
            if (result) {
                currentClient->size = size;
                result = validatePoint(row, col);
                if (result) {
                    currentClient->destination.col = toCol(col);
                    currentClient->destination.row = row - 1;
                }
            } 
        }
    }
    else if(result == 2){
        result = validateExit(weight, size);
    }
    else {
        printf("Invalid Data\n");
        clearInputBuffer();
        result = 0;
    }
    return result;
}

int validateWeight(float weight) {
    int result = 1;
    if (weight <= 0 || weight > MAX_WEIGHT) {
        printf("Invalid weight (must be 1-%d Kg.)\n", MAX_WEIGHT);
        result = 0;
    } 
    return result;
}

int validateSize(float size) {
    int result = 1;
    if (!(size == 0.5 || size == 1 || size == 5)) {
        printf("Invalid size\n");
        result = 0;
    }
    return result;
}

int validatePoint(double row, char col) {
    int result = 1;
    if (row < 1 || row > 25 || col < 'A' || col > 'Y') {
        printf("Invalid destination\n");
        result = 0;
    }
    return result;
}

int validateExit(float weight, float size) {
    int result = -1;
    char nextChar = getchar();
    if (weight == 0 && size == 0 && nextChar == 'x') {
        printf("Thanks for shipping with Seneca!\n");
    }
    else {
        clearInputBuffer();
        result = 0;
    }
    return result;
}

void clearInputBuffer(void)
{
    printf("Invalid Data\n");
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

int toCol(char col) {
    int result = col - 'A';
    return result;
}

void printBusline(char truckID) {
    switch (truckID) {
    case 'B':
        printf("Ship on BLUE LINE, ");
        break;
    case 'Y':
        printf("Ship on YELLOW LINE, ");
        break;
    case 'G':
        printf("Ship on GREEN LINE, ");
        break;
    default:
        printf("Error truckID");
    }
}

void fillTruck(struct Shipment* currentClient, char truckID, struct Truck* trucks) {
    switch (truckID)
    {
    case 'B':
        trucks[0].weight += currentClient->weight;
        trucks[0].volume += currentClient->size;
        break;
    case 'Y':
        trucks[1].weight += currentClient->weight;
        trucks[1].volume += currentClient->size;
        break;
    default:
        trucks[2].weight += currentClient->weight;
        trucks[2].volume += currentClient->size;
    }
}

void printDiversion(struct Point* startPoint, struct Route* route, struct Point* destination) {
    printf(" %d%c,",startPoint->row+1,startPoint->col + 'A');
    for (int i = 0; i < route->numPoints; i++) {
        printf(" %d%c,", route->points[i].row + 1, route->points[i].col + 'A');
    }
    printf(" %d%c\n", destination->row + 1, destination->col + 'A');
}

//////// Functions to test acceptance tests with scanf functions
void getShipmentAT(struct Truck* trucks, int numTrucks, struct Map* map, const float weight, const float size, const int row, const char col, char* output)
{
    int flag = 0;
    int divert = 0;
    char truckID = 'X';
    struct Shipment currentClient = { 0 };
    struct Route newRoute = { 0 };
    struct Point startPoint = { 0 };
        flag = validateShipAT(&currentClient,weight,size,row,col,output);
        if (flag == 1) {
            truckID = findTruck(&currentClient, trucks, numTrucks, &divert, &startPoint);
            if (truckID != 'X') {
                printBuslineAT(truckID,output);
                if (divert) {
                    strcat(output, "divert:");
                    newRoute = shortestPath(map, startPoint, currentClient.destination);
                    if (newRoute.numPoints > 0) {
                        printDiversionAT(&startPoint, &newRoute, &currentClient.destination,output);
                    }
                    else {
                        strcat(output,"Error: No valid route found.");
                    }
                }
                else {
                    strcat(output, "no diversion");
                };
            }
            fillTruck(&currentClient, truckID, trucks);
        }
}

int validateShipAT(struct Shipment* currentClient, const float weight, const float size, const int row, const char col, char* output)
{
    int result = 0;
    if (!(col == 'x' && weight == 0 && size == 0)) {
        result = validateWeightAT(weight,output);
        if (result) {
            currentClient->weight = weight;
            result = validateSizeAT(size,output);
            if (result) {
                currentClient->size = size;
                result = validatePointAT(row,col,output);
                if (result) {
                    currentClient->destination.col = toCol(col);
                    currentClient->destination.row = row - 1;
                }
            }
        }
    }
    else {
        result = validateExitAT(weight,size,col,output);
    }
    return result;
}

int validateSizeAT(float size, char* output) {
    int result = 1;
    if (!(size == 0.5 || size == 1 || size == 5)) {
        strcpy(output, "Invalid size");
        result = 0;
    }
    return result;
}

int validateWeightAT(float weight, char* output) {
    int result = 1;
    if (weight <= 0 || weight > MAX_WEIGHT) {
        strcpy(output,"Invalid weight (must be 1-1200 Kg.)");
        result = 0;
    }
    return result;
}

int validatePointAT(double row, char col, char* output) {
    int result = 1;
    if (row < 1 || row > 25 || col < 'A' || col > 'Y') {
        strcpy(output,"Invalid destination");
        result = 0;
    }
    return result;
}

int validateExitAT(float weight, float size, char col, char* output) {
    int result = -1;
    if (weight == 0 && size == 0 && col == 'x') {
        strcpy(output,"Thanks for shipping with Seneca!");
    }
    else {
        result = 0;
    }
    return result;
}

void printBuslineAT(char truckID, char* output) {
    switch (truckID) {
    case 'B':
        strcpy(output,"Ship on BLUE LINE, ");
        break;
    case 'Y':
        strcpy(output,"Ship on YELLOW LINE, ");
        break;
    case 'G':
        strcpy(output,"Ship on GREEN LINE, ");
        break;
    default:
        strcpy(output, "Error truckID");
    }
}

void printDiversionAT(struct Point* startPoint, struct Route* route, struct Point* destination,char* output) {
    char temp[20];
    sprintf(temp, " %d%c,", startPoint->row + 1, startPoint->col + 'A');
    strcat(output, temp);
    for (int i = 0; i < route->numPoints; i++) {
        sprintf(temp, " %d%c,", route->points[i].row + 1, route->points[i].col + 'A');
        strcat(output, temp);
    }
    sprintf(temp, " %d%c", destination->row + 1, destination->col + 'A');
    strcat(output, temp);
}