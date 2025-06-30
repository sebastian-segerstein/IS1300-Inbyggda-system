/*
 * carSignalLogic.h
 *
 *  Created on: Dec 8, 2024
 *      Author: Sebastian
 */

#ifndef INC_LOGIC_CARSIGNALLOGIC_H_
#define INC_LOGIC_CARSIGNALLOGIC_H_

#include "gpio.h"
#include "trafficTypes.h"

typedef struct {
	uint8_t *data;
	uint8_t sizeOfData;
	LightState currentState;
	LightState nextState;
	LightState previousState;

	LightState *pedestrianStateVertical;
	LightState *pedestrianStateHorizontal;

	uint8_t *requestPedestrianButtonVertical;
	uint8_t *requestPedestrianButtonHorizontal;

	uint32_t *currentTime;
	uint32_t stateStartTime;
	uint32_t pedestrianRequestTime;
	uint32_t carInertLaneArriveTime;
	uint32_t noCarsTime;
} CarSignalState;

#endif /* INC_LOGIC_CARSIGNALLOGIC_H_ */
