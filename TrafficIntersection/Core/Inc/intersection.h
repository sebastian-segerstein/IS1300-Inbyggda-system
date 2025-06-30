/*
 * pedestrianLogic.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Sebastian
 */

#include "Logic/pedestrianLogic.h"
#include "Logic/carSignalLogic.h"
#include <string.h>

typedef struct {
	uint8_t sizeOfData;
	uint8_t data[3];
	uint32_t currentTime;
	uint8_t requestPedestrianButtonVertical;
	uint8_t requestPedestrianButtonHorizontal;
	PedestrianState pedestrianStateVertical;
	PedestrianState pedestrianStateHorizontal;
	CarSignalState carSignalState;
} IntersectionController;