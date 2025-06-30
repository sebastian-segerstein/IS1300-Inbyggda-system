/*
 * pedestrianLogic.c
 *
 *  Created on: Dec 3, 2024
 *      Author: Sebastian
 */

#include "../../Inc/Logic/pedestrianLogic.h"
#include "../../Inc/Light/pedestrianLights.h"
#include <string.h>
#include "trafficTypes.h"
#include "FreeRTOS.h"
#include "task.h"

void initPedestrianState(PedestrianState *pedState, uint8_t *data, uint8_t sizeOfData, uint8_t id) {
	pedState->data = data;
	pedState->sizeOfData = sizeOfData;
	pedState->currentState = RED;
	pedState->nextState = RED;
	pedState->carSignalState = NULL;
	pedState->stateStartTime = 0;
	pedState->lastToggleTime = pedState->stateStartTime;
	pedState->id = id;
}

int crossWalkButtonPressed(uint8_t id) {
	switch (id) {
		case 1:
			for (int x = 10000; x > 0; x--) {
				if (HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == GPIO_PIN_RESET) {
					return 1;
				}
			}
			break;
		case 2:
			for (int x = 10000; x > 0; x--) {
				if (HAL_GPIO_ReadPin(PL1_Switch_GPIO_Port, PL1_Switch_Pin) == GPIO_PIN_RESET) {
					return 2;
				}
			}
			break;
	}
	return 0;
}

void processPedestrianState(PedestrianState *pedState, carLightState carState) {
	TickType_t currentTime = xTaskGetTickCount();
	TickType_t elapsedTime = currentTime - pedState->stateStartTime;

	switch (pedState->currentState) {
		case GREEN:
			if (elapsedTime >= pdMS_TO_TICKS(walkingDelay)) {
				pedState->nextState = RED;
				pedState->stateStartTime = currentTime;
			}
			break;
		case RED_WITH_INDICATOR:
			if ((currentTime - pedState->lastToggleTime) >= pdMS_TO_TICKS(toggleFreq)) {
				toggleIndicatorLight(pedState);
				pedState->lastToggleTime = currentTime;
			}
			if (elapsedTime >= pdMS_TO_TICKS(pedestrianDelay)) {
				if (pedState->id == 1) {
					if (carState == VERTICAL_RED) {
						pedState->nextState = GREEN;
						pedState->stateStartTime = currentTime;
					}
				} else if (pedState->id == 2) {
					if (carState == VERTICAL_GREEN) {
						pedState->nextState = GREEN;
						pedState->stateStartTime = currentTime;
					}
				}
			}
			break;
		case RED:
			if (crossWalkButtonPressed(pedState->id) && *pedState->carSignalState != YELLOW) {
				pedState->nextState = RED_WITH_INDICATOR;
				pedState->stateStartTime = currentTime;
				pedState->lastToggleTime = currentTime;
			} else
				pedState->nextState = RED;
			break;
		default:
			pedState->nextState = RED;
			pedState->stateStartTime = currentTime;
			break;
	}
	updatePedestrianState(pedState);
	pedState->currentState = pedState->nextState;
}

void pedestrianLogic(PedestrianState *pedestrianStateVertical, PedestrianState *pedestrianStateHorizontal, carLightState *carState) {
	processPedestrianState(pedestrianStateVertical, *carState);
	processPedestrianState(pedestrianStateHorizontal, *carState);
}
