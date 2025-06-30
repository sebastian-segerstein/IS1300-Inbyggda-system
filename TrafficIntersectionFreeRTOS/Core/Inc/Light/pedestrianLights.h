/*
 * pedestrianLights.h
 *
 *  Created on: Dec 5, 2024
 *      Author: Sebastian
 */

#ifndef INC_LIGHTS_PEDESTRIANLIGHTS_H_
#define INC_LIGHTS_PEDESTRIANLIGHTS_H_

#include "../Logic/pedestrianLogic.h"
#include "trafficTypes.h"

void toggleIndicatorLight(PedestrianState *pedState);
void updatePedestrianState(PedestrianState *pedState);

#endif /* INC_LIGHTS_PEDESTRIANLIGHTS_H_ */
