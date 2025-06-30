/*
 * pedestrianLogic.c
 *
 *  Created on: Dec 3, 2024
 *      Author: Sebastian
 */

#include "../../Inc/Logic/pedestrianLogic.h"
#include "../../Inc/Lights/pedestrianLights.h"
#include <string.h>
#include "constants.h"
#include "trafficTypes.h"

void initPedestrianState(PedestrianState *pedState, uint8_t *data, uint8_t sizeOfData, uint32_t *currentTime, uint8_t *requestPedestrianButton, uint8_t id) {
	pedState->data = data;
	pedState->sizeOfData = sizeOfData;
	pedState->currentState = RED;
	pedState->nextState = RED;
	pedState->carSignalState = NULL;
	pedState->currentTime = currentTime;
	pedState->stateStartTime = pedState->currentTime;
	pedState->lastToggleTime = pedState->stateStartTime;
	pedState->requestPedestrianButton = requestPedestrianButton;
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

void checkPedButtonPressed() {
	if (crossWalkButtonPressed(1)) {
		setPedestrianLightState(RED_WITH_INDICATOR);
	}
}

void pedestrianLogic3(PedestrianState *pedState, LightState previousCarState) {
	uint32_t elapsedTime = *pedState->currentTime - pedState->stateStartTime;

	switch (pedState->currentState) {
		case GREEN:
			if (elapsedTime >= walkingDelay) {
				pedState->nextState = RED;
				pedState->stateStartTime = *pedState->currentTime;
			}
			break;
		case RED_WITH_INDICATOR:
			if ((*pedState->currentTime - pedState->lastToggleTime) >= toggleFreq) {
				toggleIndicatorLight(pedState);
				pedState->lastToggleTime = *pedState->currentTime;
			}
			if (elapsedTime >= pedestrianDelay) {
				if (pedState->id == 1) {
					if (previousCarState == VERTICAL_RED) {
						pedState->nextState = GREEN;
						pedState->stateStartTime = *pedState->currentTime;
					}
				} else if (pedState->id == 2) {
					if (previousCarState == VERTICAL_GREEN) {
						pedState->nextState = GREEN;
						pedState->stateStartTime = *pedState->currentTime;
					}
				}
			}
			break;
		case RED:
			if (crossWalkButtonPressed(pedState->id) && *pedState->carSignalState != YELLOW) {
				*pedState->requestPedestrianButton = 1;
				pedState->nextState = RED_WITH_INDICATOR;
				pedState->stateStartTime = *pedState->currentTime;
				pedState->lastToggleTime = *pedState->currentTime;
			} else
				pedState->nextState = RED;
			break;
		default:
			pedState->nextState = RED;
			pedState->stateStartTime = *pedState->currentTime;
			break;
	}
	updatePedestrianData(pedState);
	pedState->currentState = pedState->nextState;
}

void pedestrianLogic(PedestrianState *pedestrianStateVertical, PedestrianState *pedestrianStateHorizontal, LightState *other) {
	pedestrianLogic3(pedestrianStateVertical, *other);
	pedestrianLogic3(pedestrianStateHorizontal, *other);
}

//	void pedestrianLogic(PedestrianState *vPed, PedestrianState *hPed) {	// take in one large struct instead?
//		uint32_t elapsedTime = *pedState->currentTime - pedState->stateStartTime;
//		switch (vPed->currentState) {
//			case RED:
//				switch (hPed->currentState) {
//					case RED:
//						int buttonPressed = crossWalkButtonPressed();
//						if (buttonPressed == 1) {
//							*vPed->requestPedestrianButton = 1;
//							vPed->nextState = RED_WITH_INDICATOR;
//							vPed->stateStartTime = *vPed->currentTime;
//							vPed->lastToggleTime = *vPed->currentTime;
//						} else if (buttonPressed == 2) {
//							*hPed->requestPedestrianButton = 1;
//							hPed->nextState = RED_WITH_INDICATOR;
//							hPed->stateStartTime = *hPed->currentTime;
//							hPed->lastToggleTime = *hPed->currentTime;
//						}
//						break;
//					case RED_WITH_INDICATOR:
//						if ((*hPed->currentTime - hPed->lastToggleTime) >= toggleFreq) {
//							toggleIndicatorLight(hPed);
//							hPed->lastToggleTime = *hPed->currentTime;
//						}
//						if (elapsedTime >= pedestrianDelay) {
//							pedState->nextState = GREEN;
//							pedState->stateStartTime = *pedState->currentTime;
//						}
//						break;
//					case GREEN:
//						break;
//				}
//				break;
//
//			case RED_WITH_INDICATOR:
//				switch (hPed->currentState) {
//					case RED:
//						break;
//					case RED_WITH_INDICATOR:
//						break;
//					case GREEN:
//						break;
//				}
//				break;
//
//			case GREEN:
//				switch (hPed->currentState) {
//					case RED:
//						break;
//					case RED_WITH_INDICATOR:
//						break;
//				}
//				break;
//		}
//	}
