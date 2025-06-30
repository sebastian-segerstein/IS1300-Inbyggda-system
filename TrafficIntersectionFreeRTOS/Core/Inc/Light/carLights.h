/*
 * carLights.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Sebastian
 */

#ifndef INC_LIGHTS_CARSIGNALLIGHTS_H_
#define INC_LIGHTS_CARSIGNALLIGHTS_H_

#include "trafficTypes.h"

void updateCarState(CarSignalState *s);
void clearHorizontalLanes(CarSignalState *s);
void clearVerticalLanes(CarSignalState *s);

#endif /* INC_LIGHTS_CARSIGNALLIGHTS_H_ */
