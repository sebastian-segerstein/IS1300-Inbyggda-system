/*
 * carSignalLogic.c
 *
 *  Created on: Dec 8, 2024
 *      Author: Sebastian
 */

#include "../../Inc/Logic/carSignalLogic.h"
#include "../../Inc/Lights/carSignalLights.h"
#include "constants.h"
#include "trafficTypes.h"

uint8_t noCars(LightState state);
uint8_t carInActiveLane(LightState state);
uint8_t carInInertLane(LightState state);

void initTaskCarSignalState(CarSignalState *carSignalState, uint8_t *data, uint8_t sizeOfData, uint32_t *currentTime, uint8_t *requestPedestrianButtonVerical, uint8_t *requestPedestrianButtonHorizontal) {
	carSignalState->data = data;
	carSignalState->sizeOfData = sizeOfData;
	carSignalState->currentState = VERTICAL_GREEN;
	carSignalState->nextState = VERTICAL_GREEN;
	carSignalState->previousState = VERTICAL_GREEN;
	carSignalState->pedestrianStateVertical = NULL;
	carSignalState->pedestrianStateHorizontal = NULL;
	carSignalState->currentTime = currentTime;
	carSignalState->stateStartTime = carSignalState->currentTime;
	carSignalState->requestPedestrianButtonVertical = requestPedestrianButtonVerical;
	carSignalState->requestPedestrianButtonHorizontal = requestPedestrianButtonHorizontal;
	carSignalState->pedestrianRequestTime = 0;
	carSignalState->carInertLaneArriveTime = 0;
	carSignalState->noCarsTime = 0;
}

uint8_t noCars(LightState state) {
	return !carInActiveLane(state) && !carInInertLane(state);
}

uint8_t carInActiveLane(LightState state) {
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

uint8_t carInInertLane(LightState state) {
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

			//	if (*s->requestPedestrianButtonVertical == 1 && !(*s->pedestrianStateHorizontal == GREEN || *s->pedestrianStateHorizontal == RED_WITH_INDICATOR)) {
			//		if (s->pedestrianRequestTime == 0)
			//			s->pedestrianRequestTime = *s->currentTime;
			//		else if (*s->currentTime - s->pedestrianRequestTime >= pedestrianDelay - yellowDelay) {
			//			s->pedestrianRequestTime = 0;
			//			*s->requestPedestrianButtonVertical = 0;
			//			s->nextState = YELLOW;
			//			s->previousState = VERTICAL_GREEN;
			//			s->stateStartTime = *s->currentTime;
			//		}
			//	}

void taskCarSignalLogic(CarSignalState *s) {
	uint32_t elapsedTime = *s->currentTime - s->stateStartTime;

	switch (s->currentState) {
		case VERTICAL_GREEN:
			if (*s->pedestrianStateHorizontal == GREEN || *s->pedestrianStateHorizontal == RED_WITH_INDICATOR)
				break;
			else if (*s->requestPedestrianButtonVertical == 1) {
				if (s->pedestrianRequestTime == 0)
					s->pedestrianRequestTime = *s->currentTime;
				if (*s->currentTime - s->pedestrianRequestTime < pedestrianDelay - yellowDelay)
					break;
				s->requestPedestrianButtonVertical = 0;
				s->pedestrianRequestTime = 0;
			}
			// R2.4
			else if (noCars(s->currentState)) {
				s->carInertLaneArriveTime = 0;
				if (s->noCarsTime == 0)
					s->noCarsTime = *s->currentTime;
				if (*s->currentTime - s->noCarsTime < greenDelay)
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
					s->carInertLaneArriveTime = *s->currentTime;
				if (*s->currentTime - s->carInertLaneArriveTime < redDelayMax)
					break;
				int x = 1 + 1;
			} // IMPLICIT R2.7

			s->previousState = VERTICAL_GREEN;
			s->nextState = YELLOW;
			s->carInertLaneArriveTime = 0;
			s->noCarsTime = 0;
			s->stateStartTime = *s->currentTime;
		break;

		case YELLOW:
			if (elapsedTime >= yellowDelay) {
				if (s->previousState == VERTICAL_GREEN)
					s->nextState = VERTICAL_RED;
				else
					s->nextState = VERTICAL_GREEN;
				s->previousState = YELLOW;
				s->stateStartTime = *s->currentTime;
			} else
				s->nextState = YELLOW;
			break;
			
		case VERTICAL_RED:
			if (*s->pedestrianStateVertical == GREEN || *s->pedestrianStateVertical == RED_WITH_INDICATOR)
				break;
			else if (*s->requestPedestrianButtonHorizontal == 1) {
				if (s->pedestrianRequestTime == 0)
					s->pedestrianRequestTime = *s->currentTime;
				if (*s->currentTime - s->pedestrianRequestTime < pedestrianDelay - yellowDelay)
					break;
				s->requestPedestrianButtonHorizontal = 0;
				s->pedestrianRequestTime = 0;
			}
			// R2.4
			else if (noCars(s->currentState)) {
				s->carInertLaneArriveTime = 0;
				if (s->noCarsTime == 0)
					s->noCarsTime = *s->currentTime;
				if (*s->currentTime - s->noCarsTime < greenDelay)
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
					s->carInertLaneArriveTime = *s->currentTime;
				if (*s->currentTime - s->carInertLaneArriveTime < redDelayMax)
					break;
				int x = 1 + 1;
			} // IMPLICIT R2.7

			s->previousState = VERTICAL_RED;
			s->nextState = YELLOW;
			s->carInertLaneArriveTime = 0;
			s->noCarsTime = 0;
			s->stateStartTime = *s->currentTime;
		break;
	}
	task2UpdateCarSignalState(s);
	s->currentState = s->nextState;
}