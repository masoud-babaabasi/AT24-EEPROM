/*
*	file: 24cxx.h
*	Author: Masoud Babaabasi
*	Data: January 2022
*/
#ifndef _24CXX_H
#define _24CXX_H
#include "main.h"

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  

//#define EE_TYPE AT24C32

void AT24CXX_Init(I2C_HandleTypeDef *_i2c , uint16_t _type, uint8_t _dev_add); //Initialize IIC					  
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr);							//Read a byte at the specified address
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);		//Write a byte to the specified address
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len);//The specified address starts to write the specified length of data
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len);					//The specified address starts to read the specified length data
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);	//Write data of the specified length from the specified address
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);   	//Read data of the specified length from the specified address

#endif
/*************************************END OF FILE**********************************************/
