/*
 * carLights.c
 *
 *  Created on: Dec 2, 2024
 *      Author: Sebastian
 */

#include "spiCommunication.h"
#include "../../Inc/Logic/carSignalLogic.h"
#include "../../Inc/spiCommunication.h"
#include "trafficTypes.h"

#define RED1_BIT_MASK         0x01  // Red for lane 1 (byte 0, bit 3)
#define YELLOW1_BIT_MASK      0x02  // Yellow for lane 1 (byte 0, bit 4)
#define GREEN1_BIT_MASK       0x04  // Green for lane 1 (byte 0, bit 5)

#define RED2_BIT_MASK         0x01  // Red for lane 2 (byte 1, bit 0)
#define YELLOW2_BIT_MASK      0x02  // Yellow for lane 2 (byte 1, bit 1)
#define GREEN2_BIT_MASK       0x04  // Green for lane 2 (byte 1, bit 2)


// fix comments
#define RED3_BIT_MASK         0x01  // Red for lane 1 (byte 0, bit 3)
#define YELLOW3_BIT_MASK      0x02  // Yellow for lane 1 (byte 0, bit 4)
#define GREEN3_BIT_MASK       0x04  // Green for lane 1 (byte 0, bit 5)

#define RED4_BIT_MASK         0x08  // Red for lane 2 (byte 1, bit 0)
#define YELLOW4_BIT_MASK      0x10  // Yellow for lane 2 (byte 1, bit 1)
#define GREEN4_BIT_MASK       0x20  // Green for lane 2 (byte 1, bit 2)

void task1UpdateCarSignalData(CarSignalState *carSignalState) {
	switch (carSignalState->currentState) {
		case GREEN:
			carSignalState->data[0] &= ~(RED1_BIT_MASK | YELLOW1_BIT_MASK | GREEN1_BIT_MASK);
			carSignalState->data[1] &= ~(RED2_BIT_MASK | YELLOW2_BIT_MASK | GREEN2_BIT_MASK);
			carSignalState->data[0] |= GREEN1_BIT_MASK;
			carSignalState->data[1] |= GREEN2_BIT_MASK;
			break;

		case YELLOW:
			carSignalState->data[0] &= ~GREEN1_BIT_MASK;
			carSignalState->data[1] &= ~GREEN2_BIT_MASK;
			carSignalState->data[0] |= YELLOW1_BIT_MASK;
			carSignalState->data[1] |= YELLOW2_BIT_MASK;
			break;

		case RED:
			carSignalState->data[0] &= ~(RED1_BIT_MASK | YELLOW1_BIT_MASK | GREEN1_BIT_MASK);
			carSignalState->data[1] &= ~(RED2_BIT_MASK | YELLOW2_BIT_MASK | GREEN2_BIT_MASK);
			carSignalState->data[0] |= RED1_BIT_MASK;
			carSignalState->data[1] |= RED2_BIT_MASK;
			break;
	}
	transmitData(carSignalState->data, carSignalState->sizeOfData);
}

void task2UpdateCarSignalState(CarSignalState *s) {
	switch (s->currentState) {
		case VERTICAL_GREEN:
			clearHorizontalLanes(s);
			s->data[2] |= RED1_BIT_MASK;
			s->data[1] |= GREEN2_BIT_MASK;
			s->data[0] |= RED3_BIT_MASK;
			s->data[0] |= GREEN4_BIT_MASK;
			break;
		
		case YELLOW:
			s->data[2] &= ~GREEN1_BIT_MASK;
			s->data[1] &= ~GREEN2_BIT_MASK;
			s->data[0] &= ~GREEN3_BIT_MASK;
			s->data[0] &= ~GREEN4_BIT_MASK;

			s->data[2] |= YELLOW1_BIT_MASK;
			s->data[1] |= YELLOW2_BIT_MASK;
			s->data[0] |= YELLOW3_BIT_MASK;
			s->data[0] |= YELLOW4_BIT_MASK;
			break;

		case VERTICAL_RED:
			clearVerticalLanes(s);
			s->data[2] |= GREEN1_BIT_MASK;
			s->data[1] |= RED2_BIT_MASK;
			s->data[0] |= GREEN3_BIT_MASK;
			s->data[0] |= RED4_BIT_MASK;

			s->data[1] &= ~YELLOW2_BIT_MASK;
			s->data[0] &= ~YELLOW4_BIT_MASK;
			break;
	}
	transmitData(s->data, s->sizeOfData);
}

void clearHorizontalLanes(CarSignalState *s) {
		s->data[2] &= ~(RED1_BIT_MASK | YELLOW1_BIT_MASK | GREEN1_BIT_MASK);
		s->data[1] &= ~(RED2_BIT_MASK | YELLOW2_BIT_MASK | GREEN2_BIT_MASK);
		s->data[0] &= ~(RED3_BIT_MASK | YELLOW3_BIT_MASK | GREEN3_BIT_MASK
			| RED4_BIT_MASK | YELLOW4_BIT_MASK | GREEN4_BIT_MASK);
}

void clearVerticalLanes(CarSignalState *s) {
		s->data[2] &= ~(RED1_BIT_MASK | YELLOW1_BIT_MASK | GREEN1_BIT_MASK);
		s->data[1] &= ~(RED2_BIT_MASK | YELLOW2_BIT_MASK | GREEN2_BIT_MASK);
		s->data[0] &= ~(RED3_BIT_MASK | YELLOW3_BIT_MASK | GREEN3_BIT_MASK
			| RED4_BIT_MASK | YELLOW4_BIT_MASK | GREEN4_BIT_MASK);
}