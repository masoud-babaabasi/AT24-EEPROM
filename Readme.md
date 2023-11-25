# AT24CXX EEPROM Library
### STM32 AT24xx EEPROM C Library
This code is written for use in stm32 family projects. It uses HAL I2C read and write functions. So You need to initilize the I2C with HAL library and then use this code for communication with the EEPROM chip. This code can handle most of the chip in the AT24 family including:
- AT24C02
- AT24C04
- AT24C08
- AT24C16
- AT24C32
- AT24C64
- AT24C128
- AT24C256

I recommend to use STM32CubeMX to initilize the microcontroller. You can use the my library in the main.c file like shown below:
```C
#include "24cxx.h" 
I2C_HandleTypeDef hi2c1;
int main(void)
{
/*
* Start up code 
*/
  HAL_Init();
  SystemClock_Config();
/*
* CubeMX Initilization functions
*/
  MX_I2C1_Init();
/* USER CODE BEGIN 2 */
  /*Initilize the EEPROM chip , chip address is 0 */
  AT24CXX_Init(&hi2c1 , AT24C32 , 0);
  int address = 5;
  uint8_t data_write = 25 , data_read = 0;
  /*Write 25 at address 5*/
  T24CXX_WriteOneByte(address, data_write);
  /*Check if data is written correctly*/
  data_read = AT24CXX_ReadOneByte(address);
  if(data_read != date_write){
    /* print error message*/
    Error_Handler();
  }
/* USER CODE END 2 */
while (1)
  {

  }
}
```

