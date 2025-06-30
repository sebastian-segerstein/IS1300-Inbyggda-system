/*
 * pedestrianLogic.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Sebastian
 */

#ifndef TRAFFIC_TYPES_H
#define TRAFFIC_TYPES_H

#include <stdint.h>

#define toggleFreq 350
#define pedestrianDelay 6000
#define walkingDelay 8000
#define yellowDelay 3000
#define greenDelay 10000
#define redDelayMax 5000

typedef enum {
	GREEN,
	RED_WITH_INDICATOR,
	RED
} pedestrianLightState;

typedef enum {
	VERTICAL_GREEN,
	YELLOW,
	VERTICAL_RED
} carLightState;

typedef struct {
	uint8_t *data;
	uint8_t sizeOfData;
	pedestrianLightState currentState;
	pedestrianLightState nextState;
	carLightState *carSignalState;
	uint32_t stateStartTime;
	uint32_t lastToggleTime;
	uint8_t *requestPedestrianButton;
	uint8_t id;
} PedestrianState;

typedef struct {
	uint8_t *data;
	uint8_t sizeOfData;
	carLightState currentState;
	carLightState nextState;
	carLightState previousState;
	uint32_t stateStartTime;
	uint32_t pedestrianRequestTime;
	uint32_t carInertLaneArriveTime;
	uint32_t noCarsTime;
} CarSignalState;

typedef struct {
	uint8_t sizeOfData;
	uint8_t data[3];
	PedestrianState pedestrianStateVertical;
	PedestrianState pedestrianStateHorizontal;
	CarSignalState carSignalState;
} IntersectionController;

#endif /* TRAFFIC_TYPES_H */
