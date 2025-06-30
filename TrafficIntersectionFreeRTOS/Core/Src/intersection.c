/*
 * traffic.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Sebastian
 */

#include "../Inc/intersection.h"
#include "../Inc/Logic/pedestrianLogic.h"
#include "../Inc/Logic/carLogic.h"
#include <string.h>

void initIntersectionState(IntersectionController *intersectionState) {
	memset(intersectionState->data, 0, sizeof(intersectionState->data));
	intersectionState->sizeOfData = sizeof(intersectionState->data);

	initPedestrianState(&intersectionState->pedestrianStateVertical, intersectionState->data, intersectionState->sizeOfData, 1);
	initPedestrianState(&intersectionState->pedestrianStateHorizontal, intersectionState->data, intersectionState->sizeOfData, 2);
	initTaskCarSignalState(&intersectionState->carSignalState, intersectionState->data, intersectionState->sizeOfData);
	intersectionState->pedestrianStateVertical.carSignalState = &intersectionState->carSignalState.currentState;
	intersectionState->pedestrianStateHorizontal.carSignalState = &intersectionState->carSignalState.currentState;
}
