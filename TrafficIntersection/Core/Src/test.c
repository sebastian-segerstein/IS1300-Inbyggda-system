#include <Lights/carSignalLights.h>
#include "main.h"
#include "../Inc/Lights/pedestrianLights.h"
#include "../Inc/Lights/carSignalLights.h"
#include "../Inc/Logic/carSignalLogic.h"
#include "../Inc/intersection.h"

void testLeds() {
	uint8_t data[3] = {0};
	for (uint8_t counter = 0; counter < 24; counter++) {
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;

		data[counter / 8] = 1 << (counter % 8);
		transmitData(data, sizeof(data));
		HAL_Delay(500);
	}
}

void testLightInitialization() {
	initializeLights();
}

void testPedestrianButton() {
	while (!crossWalkButtonPressed(0)) {
		continue;
	}
	uint8_t data[] = {0x00, 0x20, 0x00};
	transmitData(data, sizeof(data));
}

void testSetPedestrianLightState() {
	uint8_t data[3];
	PedestrianState pedState;
	initPedestrianState(&pedState, data, sizeof(data));
	memset(pedState.data, 0, pedState.sizeOfData);
	HAL_Delay(1000);
	// TEST RED STATE
	pedState.currentState = RED;
	updatePedestrianData(&pedState);
	HAL_Delay(3000);
	pedState.currentState = RED_WITH_INDICATOR;
	updatePedestrianData(&pedState);
	HAL_Delay(3000);
	pedState.currentState = GREEN;
	updatePedestrianData(&pedState);
}

void testToggleIndicatorLight(uint32_t toggleFreq) {
	uint32_t startTick;
	while(1) {
		toggleIndicatorLight(toggleFreq);
		startTick = HAL_GetTick();
	}
}

void testPedestrianLogic() {
	uint8_t data[3];
	PedestrianState pedState;
	initPedestrianState(&pedState, data, sizeof(data));
	memset(pedState.data, 0, pedState.sizeOfData);
	while (1) {
		pedestrianLogic(&pedState);
	}
}

void testOrangeLight() {
	carSetOrange();
}

void testInitPedestrianState() {
	PedestrianState state;
	initPedestrianState(&state);
}

void testCarSignalLightStates() {
	uint8_t data[3];
	CarSignalState carSingalState;
	initCarSignalState(&carSingalState, data, sizeof(data));
	memset(carSingalState.data, 0, carSingalState.sizeOfData);
	carSingalState.currentState = RED;
	updateCarSignalData(&carSingalState);
	HAL_Delay(1000);
	carSingalState.currentState = YELLOW;
	updateCarSignalData(&carSingalState);
	HAL_Delay(1000);
	carSingalState.currentState = GREEN;
	updateCarSignalData(&carSingalState);
	HAL_Delay(1000);
	carSingalState.currentState = YELLOW;
	updateCarSignalData(&carSingalState);
	HAL_Delay(1000);
	carSingalState.currentState = RED;
	updateCarSignalData(&carSingalState);
}

void testIntersection() {
	while (1) {
		intersection();
	}
}

void testCarSignalLogic() {
	uint8_t data[3];
	CarSignalState carSignalState;
	initCarSignalState(&carSignalState, data, sizeof(data));
	memset(carSignalState.data, 0, carSignalState.sizeOfData);
	while (1) {
		carSignalLogic(&carSignalState);
	}
}

void testCarSwitches() {
	if (HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin) == GPIO_PIN_RESET)
		HAL_GPIO_WritePin(GPIOB, LED25_Pin, 1);
	else
		HAL_GPIO_WritePin(GPIOB, LED25_Pin, 0);
	if (HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin) == GPIO_PIN_RESET)
		HAL_GPIO_WritePin(GPIOB, LED26_Pin, 1);
	else
		HAL_GPIO_WritePin(GPIOB, LED26_Pin, 0);
}

void testTask2Init() {

}


void testInActiveLane() {
	while (1) {
		if (carInActiveLane(VERTICAL_GREEN))
			HAL_GPIO_WritePin(GPIOB, LED25_Pin, 1);
		//else
		//	HAL_GPIO_WritePin(GPIOB, LED25_Pin, 0);
		if (carInInertLane(VERTICAL_GREEN))
			HAL_GPIO_WritePin(GPIOB, LED26_Pin, 1);
		//else
		//	HAL_GPIO_WritePin(GPIOB, LED26_Pin, 0);
	}
}

void testTask2() {
	CarSignalState carSignalState;
	uint8_t data[3];
	initTask2CarSignalState(&carSignalState, data, sizeof(data));
	memset(data, 0, sizeof(data));
	while (1)
		task2CarSignalLogic(&carSignalState);
}

void testTask3() {
	IntersectionController intersection;
	initIntersectionState(&intersection);
	while (1) {
		intersection.currentTime = HAL_GetTick();
		pedestrianLogic(&intersection.pedestrianStateVertical, &intersection.pedestrianStateHorizontal, &intersection.carSignalState.currentState);
		taskCarSignalLogic(&intersection.carSignalState);
	}
}

void testPedestrianData() {
	uint8_t data[3];
	PedestrianState pedState;
	initPedestrianState(&pedState, data, sizeof(data), HAL_GetTick(), 0, 2);
	memset(pedState.data, 0, pedState.sizeOfData);
	pedState.currentState = RED_WITH_INDICATOR;
	updatePedestrianData(&pedState);
}

void testProgram() {
	initializeRegisters();
	//	testLeds();
	//	testLightInitialization();
	//	testPedestrianButton();
	//	testPedestrianLightStates();
	//	testToggleIndicatorLight(500);
	//	testOrangeLight();
	//	testInitPedestrianState();
	//	testSetPedestrianLightState();
	//	testPedestrianLogic();
	//	testCarSignalLightStates();
	//	testCarSignalLogic();
	//	testIntersection();
	//	testTask2();
	//	testInActiveLane();
	//	testPedestrianData();
	testTask3();
}
