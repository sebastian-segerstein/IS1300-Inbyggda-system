/*
 * pedestrianLights.c
 *
 *  Created on: Dec 2, 2024
 *      Author: Sebastian
 */

#include "gpio.h"
#include "../../Inc/Logic/pedestrianLogic.h"
#include "../../Inc/spiCommunication.h"



#define LIGHT_RED_BYTE_INDEX_HORIZONTAL         2
#define LIGHT_RED_BYTE_INDEX_VERTICAL         1
#define LIGHT_RED_BIT_POSITION       3

#define LIGHT_GREEN_BYTE_INDEX_HORIZONTAL       2
#define LIGHT_GREEN_BYTE_INDEX_VERTICAL       1
#define LIGHT_GREEN_BIT_POSITION     4

#define LIGHT_INDICATOR_BYTE_INDEX_HORIZONTAL   2
#define LIGHT_INDICATOR_BYTE_INDEX_VERTICAL   1
#define LIGHT_INDICATOR_BIT_POSITION 5

// Bit masks for the lights
#define LIGHT_RED_BIT_MASK           (1 << LIGHT_RED_BIT_POSITION)
#define LIGHT_GREEN_BIT_MASK         (1 << LIGHT_GREEN_BIT_POSITION)
#define LIGHT_INDICATOR_BIT_MASK     (1 << LIGHT_INDICATOR_BIT_POSITION)




void toggleIndicatorLight(PedestrianState *pedState) {
	pedState->data[pedState->id] ^= LIGHT_INDICATOR_BIT_MASK; // to be removed?
    transmitData(pedState->data, pedState->sizeOfData);
}



void updatePedestrianData(PedestrianState *pedState) {
    switch (pedState->currentState) {
        case RED:
            pedState->data[pedState->id] |= LIGHT_RED_BIT_MASK;
            pedState->data[pedState->id] &= ~LIGHT_GREEN_BIT_MASK;
            pedState->data[pedState->id] &= ~LIGHT_INDICATOR_BIT_MASK;
            break;

        case RED_WITH_INDICATOR:
            pedState->data[pedState->id] |= LIGHT_RED_BIT_MASK;
            //  pedState->data[pedState->id] |= LIGHT_INDICATOR_BIT_MASK; // comment out / remove?
            pedState->data[pedState->id] &= ~LIGHT_GREEN_BIT_MASK;
            break;

        case GREEN:
            pedState->data[pedState->id] |= LIGHT_GREEN_BIT_MASK;
            pedState->data[pedState->id] &= ~LIGHT_RED_BIT_MASK;
            pedState->data[pedState->id] &= ~LIGHT_INDICATOR_BIT_MASK;
            break;
    }
    // TODO: move transmit later
    transmitData(pedState->data, pedState->sizeOfData);
}