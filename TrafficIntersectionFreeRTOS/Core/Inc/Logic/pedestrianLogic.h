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
#include "trafficTypes.h"

void initPedestrianState(PedestrianState *pedState, uint8_t *data, uint8_t sizeOfData, uint8_t id);
int crossWalkButtonPressed(uint8_t id);
void processPedestrianState(PedestrianState *pedState, carLightState carState);
void pedestrianLogic(PedestrianState *pedestrianStateVertical, PedestrianState *pedestrianStateHorizontal, carLightState *carState);


#endif /* INC_LOGIC_PEDESTRIANLOGIC_H_ */
