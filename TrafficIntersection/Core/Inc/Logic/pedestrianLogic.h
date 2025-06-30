/*
 * pedestrianLogic.h
 *
 *  Created on: Dec 3, 2024
 *      Author: Sebastian
 */

#ifndef INC_LOGIC_PEDESTRIANLOGIC_H_
#define INC_LOGIC_PEDESTRIANLOGIC_H_

#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "trafficTypes.h"

typedef struct {
	uint8_t *data;
	uint8_t sizeOfData;
	LightState currentState;
	LightState nextState;
	LightState *carSignalState;
	uint32_t *currentTime;
	uint32_t stateStartTime;
	uint32_t lastToggleTime;
	uint8_t *requestPedestrianButton;
	uint8_t id;
} PedestrianState;



#endif /* INC_LOGIC_PEDESTRIANLOGIC_H_ */
