#include "../Inc/spiCommunication.h"
#include "main.h"
#include "gpio.h"
#include "spi.h"

void initializeRegisters() {
	HAL_GPIO_WritePin(GPIOA, SPI3_RESET_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, SPI3_STCP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, SPI3_STCP_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, SPI3_ENABLE_Pin, GPIO_PIN_RESET);
}

void transmitData(uint8_t *data, size_t size) {
	HAL_SPI_Transmit(&hspi3, data, size, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, SPI3_STCP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, SPI3_STCP_Pin, GPIO_PIN_RESET);
}
