#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bddManager.h"

int CmpPtr(void *data1, void *data2){
    if(data1 == data2) return 0;
    else return 1;
}


void savePlaneInFile(airport *airport)
{
    chainItem *PlaneContainer = airport->planesInRange->first;
    FILE *bdd = fopen("planes.bdd", "w");

    while (PlaneContainer != NULL)
    {
        plane *planes = PlaneContainer->data;
        char type[10];
        char status[17];
        switch ((planes->type))
        {
        case AIRLINER:
            strcpy(type, "AIRLINER");
            break;
        case BUSINESS:
            strcpy(type, "BUSINESS");
            break;
        case LIGHT:
            strcpy(type, "LIGHT");
            break;
        }
        switch ((planes->status))
        {
        case FLYING:
            strcpy(status, "FLYING");
            break;
        default:
            strcpy(status, "PARKING");
            break;
        }
        fprintf(bdd, "%s - %s | %d/%d | %s\n", planes->matriculation, type, planes->passengers, planes->passengersMax, status);
        PlaneContainer = PlaneContainer->next;
    }
    fclose(bdd);
}

plane *sMakeChainData(char buffer[100])
{
    char type[30], status[30];
    //plane vierge
    plane *newData = newPlane("",AIRLINER,0,0,FLYING);
    // char masssBufffer[10];
    sscanf(buffer, "%[^ ] - %[^ ] | %u/%u | %s", newData->matriculation, type, &newData->passengers, &newData->passengersMax, status);
   


    if (strcmp("AIRLINER", type)==0)newData->type=AIRLINER;
    else if(strcmp("BUSINESS", type)==0)newData->type=BUSINESS;
    else if(strcmp("LIGHT", type)==0)newData->type=LIGHT;

    if( strcmp("FLYING", status)==0)newData->status=FLYING;
    else if( strcmp("PARKING", status)==0) newData->status=PARKING;
  
    return newData;
}

// recup type et stat need to put in string and compare value to enter right type and shit
// need to trabsforme dat in right flyin EG flyung 0 (( STRCMP ))
// CAD comme flying est un int en string  faut faire strcmp et si flying == flying alors statu == flying )

void *openChainFile(char *fileName,simulation* simulation)// list == planes in range
{
    
    list* listPlane=newList(CmpPtr);
    list* listPK=newList(CmpPtr);
    list* listAC=newList(CmpPtr);
    FILE *file = NULL;
    file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("\033[1;31mERROR : Echec de l'ouverture de %s.\033[0m", fileName);
        
    }
    char cursor = fgetc(file);
    while (fgetc(file) !=EOF)
    {
            char buffer[100];
            long startPin = ftell(file);
            long endPin = startPin;
            while (cursor != '\n')
            {
                cursor = fgetc(file);
                endPin++;
            }
            fseek(file, startPin-2, SEEK_SET);
            fgets(buffer, endPin - startPin +3, file);
            plane*plane=sMakeChainData(buffer);
            sim_planeActor *planeActor = malloc(sizeof(sim_planeActor));
            planeActor->plane = plane;
            planeActor->stateRemainTimeInMs = -1;
            appendInList(listPlane, plane);
            appendInList(listAC, planeActor);
            if(plane->status==PARKING)appendInList(listPK, plane);
        

        //out of if
        if (cursor == '\n' )
            cursor = fgetc(file);
    }
    fclose(file);
    printf("loaded\n");
    simulation->airport->planesInRange=listPlane;
    simulation->airport->parkingPlanes=listPK;
    simulation->planeActors=listAC;
    
}

// char* randomRegistration()
// {
//     char *mat = malloc(6);
//     *mat = (char)('A' + randomInt(0, 25));
//     *(mat + 1) = 'A' + (randomInt(0, 25));
//     mat[2] = '-';
//     mat[3] = 'A' + (random() % 26);
//     mat[4] = 'A' + (random() % 26);
//     mat[5] = 'A' + (random() % 26);
//     mat[6] = '\0';
//     return mat;
// }

// int randomInt(int min, int max)
// {
//     int result;
//     static int A;
//     srand(time(NULL) + A);
//     A++;
//     if (A > 100)
//         A = 0;
//     result = (rand() % (max - min)) + min;
//     return result;
// }
