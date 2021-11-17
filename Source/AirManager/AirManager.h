#include "SmartList.h"
#include <stdbool.h>
typedef struct runway runway;

typedef enum{FLYING, WAITING_LANDING, LANDING, PARKING, WAITING_TAKEOFF, TAKEOFF} planeStatus;
typedef enum{AIRLINER, BUSINESS, LIGHT} planeType;

typedef struct{
    char matriculation[7];
    planeType type;
    unsigned int passengers;
    unsigned int passengersMax;
    planeStatus status;
    runway *targetRunway;
}plane;

typedef enum{SMALL, MEDIUM, LARGE} runwayType;

typedef struct{
    char id;
    float length;
    float width;
    runwayType type;
    unsigned int maxTakeoffQueue;
    list *takeoffQueue;
    plane *planeLT;
}runway;

typedef struct{
    unsigned int parkingSize;
    list *runways;
    list *planesInRange;
    list *parkingPlanes;
    list *landingQueue;
    list *waitForRunwayQueue;
}airport;

plane* newPlane(char matriculation[7], planeType type, unsigned int passengers, unsigned int passengersMax, planeStatus status);
void loadPlainInAirport(airport* airport, plane *plane);


runway* newRunway(float length, float width, runwayType type, unsigned int maxTakeoffQueue);

//Runway Slot Manager
void addPlaneToRunway(runway *runway, plane *plane);
void planeExitRunway(runway *runway, plane *plane);
bool isRunwayFree(runway* newRunway);

//Runway Queue Manager
void grantTakeoffForRunway(runway *runway);
void addPlaneToRunwayQueue(runway *runway, plane *plane);
bool isRunwayQueueFull(runway *runway);


airport* newAirport(unsigned int parkingSize);
void buildAirport(airport* airport, int numberOfSmallRunway, int numberOfMediumRunway, int numberOfLargeRunway);

//Parking Management
void addPlaneToParking(airport* airport, plane *plane);
bool isParkingFull(airport* airport);
bool isParkingQueueFull(airport* airport);

//LandingQueue List Requests
void addPlaneToLandingQueue(airport* airport, plane *plane);
void grantPlaneInLQAccessToRunway(airport* airport, runway *runway, plane *plane);

//AskForRunwayQueue List Requests
void addPlaneToAFRQ(airport* airport, plane *plane);
void grantPlaneInAFRQAccessToRunway(airport* airport, runway *runway, plane *plane);