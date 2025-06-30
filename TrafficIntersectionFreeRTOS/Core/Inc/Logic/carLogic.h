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

void initTaskCarSignalState(CarSignalState *carSignalState, uint8_t *data, uint8_t sizeOfData);
uint8_t noCars(carLightState state);
uint8_t carInActiveLane(carLightState state);
uint8_t carInInertLane(carLightState state);
void taskCarSignalLogic(CarSignalState *s, pedestrianLightState pedestrianStateVertical, pedestrianLightState pedestrianStateHorizontal);

#endif /* INC_LOGIC_CARSIGNALLOGIC_H_ */
