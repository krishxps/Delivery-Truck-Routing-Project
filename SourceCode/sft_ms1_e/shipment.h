#ifndef SHIPMENT_H
#define SHIPMENT_H
#include "mapping.h"
#include "truck.h"


// This structure will save the data for the shipment.
struct Shipment
{
	float weight; //the weight of the box
	float size; //The volume of the box
	struct Point destination; //The destination for the box
};

/// <summary>
/// Print the header of the program
/// </summary>
void printHeader();


/// <summary>
/// Get the data for a shipment
/// </summary>
void getShipment(struct Truck* trucks,int numTrucks, struct Map* map);


/// <summary>
/// validate the information for a shipment
/// </summary>
/// <param name=""></param>
int validateShip(struct Shipment* currentClient);

/// <summary>
/// It validates if the input weiht is a valid value
/// </summary>
/// <param name="weight"></param>
/// <returns></returns>
int validateWeight(float weight);


/// <summary>
/// It validates if the input size/volume is a valid value
/// </summary>
/// <param name="size"></param>
/// <returns></returns>
int validateSize(float size);


/// <summary>
/// It validates if the input destination is a valid value
/// </summary>
/// <param name="row"></param>
/// <param name="col"></param>
/// <returns></returns>
int validatePoint(double row, char col);

/// <summary>
/// It validates if the input exit command is a valid command
/// </summary>
/// <param name="weight"></param>
/// <param name="size"></param>
/// <returns></returns>
int validateExit(float weight, float size);

/// <summary>
/// It converts the user's value for column into the correct type of value
/// </summary>
/// <param name="col"></param>
/// <returns></returns>
int toCol(char col);

// Discard all remaining char's from the standard input buffer:
void clearInputBuffer(void);

/// <summary>
/// print the line owner of the route
/// </summary>
/// <param name=""></param>
void printBusline(char truckID);

/// <summary>
/// fill the truck with the shipment
/// </summary>
/// <param name="currentClient"></param>
/// <param name="truckID"></param>
/// <param name="trucks"></param>
void fillTruck(struct Shipment* currentClient, char truckID, struct Truck* trucks);

/// <summary>
/// print the coordinates for the diversion in the route
/// </summary>
/// <param name="startPoint"></param>
/// <param name="route"></param>
/// <param name="destination"></param>
void printDiversion(struct Point* startPoint, struct Route* route, struct Point* destination);

//////// Functions to test acceptance tests with scanf functions
void getShipmentAT(struct Truck* trucks, int numTrucks, struct Map* map, const float weight, const float size, const int row, const char col, char* output);
int validateShipAT(struct Shipment* currentClient, const float weight, const float size, const int row, const char col, char* output);
int validateSizeAT(float size, char* output);
int validateWeightAT(float weight, char* output);
int validatePointAT(double row, char col, char* output);
int validateExitAT(float weight, float size, char col, char* output);
void printBuslineAT(char truckID, char* output);
void printDiversionAT(struct Point* startPoint, struct Route* route, struct Point* destination, char* output);

#endif // !SHIPMENT_H

