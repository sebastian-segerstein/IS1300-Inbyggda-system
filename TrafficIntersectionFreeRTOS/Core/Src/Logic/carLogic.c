/*
 * carSignalLogic.c
 *
 *  Created on: Dec 8, 2024
 *      Author: Sebastian
 */

#include "../../Inc/Logic/carLogic.h"
#include "../../Inc/Light/carLights.h"
#include "trafficTypes.h"
#include "FreeRTOS.h"
#include "task.h"

uint8_t noCars(carLightState state);
uint8_t carInActiveLane(carLightState state);
uint8_t carInInertLane(carLightState state);

void initTaskCarSignalState(CarSignalState *carSignalState, uint8_t *data, uint8_t sizeOfData) {
	carSignalState->data = data;
	carSignalState->sizeOfData = sizeOfData;
	carSignalState->currentState = VERTICAL_GREEN;
	carSignalState->nextState = VERTICAL_GREEN;
	carSignalState->previousState = VERTICAL_GREEN;
	carSignalState->stateStartTime = 0;
	carSignalState->pedestrianRequestTime = 0;
	carSignalState->carInertLaneArriveTime = 0;
	carSignalState->noCarsTime = 0;
}

uint8_t noCars(carLightState state) {
	return !carInActiveLane(state) && !carInInertLane(state);
}

uint8_t carInActiveLane(carLightState state) {
	switch (state) {
	case VERTICAL_GREEN:
		return (HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin) == GPIO_PIN_RESET ||
				HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin) == GPIO_PIN_RESET);
	case VERTICAL_RED:
		return (HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin) == GPIO_PIN_RESET ||
				HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin) == GPIO_PIN_RESET);
	default:
		return 0;
	}
}

uint8_t carInInertLane(carLightState state) {
	switch (state) {
	case VERTICAL_GREEN:
		return (HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin) == GPIO_PIN_RESET ||
				HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin) == GPIO_PIN_RESET);
	case VERTICAL_RED:
		return (HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin) == GPIO_PIN_RESET ||
				HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin) == GPIO_PIN_RESET);
	default:
		return 0;
	}
}

void taskCarSignalLogic(CarSignalState *s, pedestrianLightState pedestrianStateVertical, pedestrianLightState pedestrianStateHorizontal) {
	TickType_t currentTime = xTaskGetTickCount();
	TickType_t elapsedTime = currentTime - s->stateStartTime;

	switch (s->currentState) {
		case VERTICAL_GREEN:
			if (pedestrianStateHorizontal == GREEN || pedestrianStateHorizontal == RED_WITH_INDICATOR)
				break;
			else if (pedestrianStateVertical == RED_WITH_INDICATOR) {
				if (s->pedestrianRequestTime == 0)
					s->pedestrianRequestTime = currentTime;
				if (currentTime - s->pedestrianRequestTime < pdMS_TO_TICKS(pedestrianDelay) - pdMS_TO_TICKS(yellowDelay))
					break;
				s->pedestrianRequestTime = 0;
			}
			// R2.4
			else if (noCars(s->currentState)) {
				s->carInertLaneArriveTime = 0;
				if (s->noCarsTime == 0)
					s->noCarsTime = currentTime;
				if (currentTime - s->noCarsTime < pdMS_TO_TICKS(greenDelay))
					break;
			// R2.5
			} else if (carInActiveLane(s->currentState) && !carInInertLane(s->currentState)) {
				s->carInertLaneArriveTime = 0;
				s->noCarsTime = 0;
				break;
			// R2.6
			} else if (carInInertLane(s->currentState) && carInActiveLane(s->currentState)) {
				s->noCarsTime = 0;
				if (s->carInertLaneArriveTime == 0)
					s->carInertLaneArriveTime = currentTime;
				if (currentTime - s->carInertLaneArriveTime < pdMS_TO_TICKS(redDelayMax))
					break;
			} // IMPLICIT R2.7

			s->previousState = VERTICAL_GREEN;
			s->nextState = YELLOW;
			s->carInertLaneArriveTime = 0;
			s->noCarsTime = 0;
			s->stateStartTime = currentTime;
		break;

		case YELLOW:
			if (elapsedTime >= pdMS_TO_TICKS(yellowDelay)) {
				if (s->previousState == VERTICAL_GREEN)
					s->nextState = VERTICAL_RED;
				else
					s->nextState = VERTICAL_GREEN;
				s->previousState = YELLOW;
				s->stateStartTime = currentTime;
			} else
				s->nextState = YELLOW;
			break;

		case VERTICAL_RED:
			if (pedestrianStateVertical == GREEN || pedestrianStateVertical == RED_WITH_INDICATOR)
				break;
			else if (pedestrianStateHorizontal == RED_WITH_INDICATOR) {
				if (s->pedestrianRequestTime == 0)
					s->pedestrianRequestTime = currentTime;
				if (currentTime - s->pedestrianRequestTime < pdMS_TO_TICKS(pedestrianDelay) - pdMS_TO_TICKS(yellowDelay))
					break;
				s->pedestrianRequestTime = 0;
			}
			// R2.4
			else if (noCars(s->currentState)) {
				s->carInertLaneArriveTime = 0;
				if (s->noCarsTime == 0)
					s->noCarsTime = currentTime;
				if (currentTime - s->noCarsTime < pdMS_TO_TICKS(greenDelay))
					break;
			// R2.5
			} else if (carInActiveLane(s->currentState) && !carInInertLane(s->currentState)) {
				s->carInertLaneArriveTime = 0;
				s->noCarsTime = 0;
				break;
			// R2.6
			} else if (carInInertLane(s->currentState) && carInActiveLane(s->currentState)) {
				s->noCarsTime = 0;
				if (s->carInertLaneArriveTime == 0)
					s->carInertLaneArriveTime = currentTime;
				if (currentTime - s->carInertLaneArriveTime < pdMS_TO_TICKS(redDelayMax))
					break;
			} // IMPLICIT R2.7

			s->previousState = VERTICAL_RED;
			s->nextState = YELLOW;
			s->carInertLaneArriveTime = 0;
			s->noCarsTime = 0;
			s->stateStartTime = currentTime;
		break;
	}
	updateCarState(s);
	s->currentState = s->nextState;
}
