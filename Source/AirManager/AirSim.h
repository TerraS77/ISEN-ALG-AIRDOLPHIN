#include "AirManager.h"
#include "cmdPrint.h"
#if !defined( AIRSIM_H )
#define AIRSIM_H

typedef struct{
    unsigned int simulationSpeedInMs;
    airport *airport;
    list *planeActors;
} simulation;

typedef struct{
    plane *plane;
    int stateRemainTimeInMs; 
} sim_planeActor;

#endif