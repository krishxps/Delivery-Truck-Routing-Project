#ifndef TRUCK_H
#define TRUCK_H
#define MAX_WEIGHT 1200
#define MAX_VOLUME 50
#include "mapping.h"

// This structure will save the data for a truck.
struct Truck {
    char truckID; // The unique identifier of the truck (Blue, Green, Yellow).
    float weight; // The amount of weight the truck is currently carrying.
    float volume; // The amount of volume the boxes are already occupying inside the truck.
    struct Route route; // The current route of the truck.
    // Here is the option to include the percentage, but because it is a calculated value and it will be used only once (at the comparison), it should not be stored for memory efficiency reasons.
};

// This structure is going to save the distance of a point and the truck owner of that point
struct DistanceWithTruck {
    double distance;
    struct Truck truck;
};

/// <summary>
/// This create the array of the 3 trucks, giving each one a route symbol (B,Y,G)
/// </summary>
/// <param name="trucks"></param>
void createTrucks(struct Truck* trucks);

/// <summary>
/// This function find the best option to take the shipment
/// </summary>
/// <param name="currentClient"></param>
/// <param name="trucks"></param>
/// <param name="numTrucks"></param>
/// <param name="divert"></param>
/// <param name="startPoint"></param>
/// <returns></returns>
char findTruck(struct Shipment* currentClient, struct Truck* trucks, int numTrucks, int* divert, struct Point* startPoint);

/// <summary>
/// This function compares between two trucks to find the emptier one, if they are in the same distance from the destination
/// </summary>
/// <param name="distances"></param>
/// <returns></returns>
int chooseTruck(struct DistanceWithTruck* distances);

/// <summary>
/// It returns the index of the truck that has more available space to store the shipment
/// </summary>
/// <param name="w1"></param>
/// <param name="s1"></param>
/// <param name="w2"></param>
/// <param name="s2"></param>
/// <returns></returns>
int emptierTruck(double w1, double s1, double w2, double s2 );

/// <summary>
/// It checks if the truck has enough space for the shipment
/// </summary>
/// <param name="currentClient"></param>
/// <param name="trucks"></param>
/// <returns></returns>
int enoughSpace(struct Shipment* currentClient, struct Truck* trucks);


/// <summary>
/// It checks if the route is already passing next to the destination
/// </summary>
/// <param name="route"></param>
/// <param name="destination"></param>
/// <returns></returns>
int hasPoint(struct Route* route, struct Point* destination);

#endif // !TRUCK_H
