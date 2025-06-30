/*
 * traffic.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Sebastian
 */

#include <intersection.h>

void intersection() {
	IntersectionController intersectionState;
	initIntersectionState(&intersectionState);
	while (1) {
		pedestrianLogic(&intersectionState.pedestrianStateVertical);
		task1CarSignalLogic(&intersectionState.carSignalState);
	}
}

void task2Intersection() {
	while (1) {
		task2CarSignalLogic();
	}
}

void initIntersectionState(IntersectionController *intersectionState) {
	memset(intersectionState->data, 0, sizeof(intersectionState->data));
	intersectionState->sizeOfData = sizeof(intersectionState->data);
	intersectionState->requestPedestrianButtonVertical = 0;
	intersectionState->currentTime = HAL_GetTick();

	initPedestrianState(&intersectionState->pedestrianStateVertical, intersectionState->data, intersectionState->sizeOfData, &intersectionState->currentTime,
	&intersectionState->requestPedestrianButtonVertical, 1);
	initPedestrianState(&intersectionState->pedestrianStateHorizontal, intersectionState->data, intersectionState->sizeOfData, &intersectionState->currentTime,
	&intersectionState->requestPedestrianButtonHorizontal, 2);
	initTaskCarSignalState(&intersectionState->carSignalState, intersectionState->data, intersectionState->sizeOfData, &intersectionState->currentTime, &intersectionState->requestPedestrianButtonVertical, &intersectionState->requestPedestrianButtonHorizontal);
	
	intersectionState->pedestrianStateVertical.carSignalState = &intersectionState->carSignalState.currentState;
	intersectionState->pedestrianStateHorizontal.carSignalState = &intersectionState->carSignalState.currentState;
	intersectionState->carSignalState.pedestrianStateVertical = &intersectionState->pedestrianStateVertical.currentState;
	intersectionState->carSignalState.pedestrianStateHorizontal = &intersectionState->pedestrianStateHorizontal.currentState;
}
