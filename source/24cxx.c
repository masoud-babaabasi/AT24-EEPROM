/*
*	file: 24cxx.c
*	Author: Masoud Babaabasi
*	Data: January 2022
*/
#include "24cxx.h"

I2C_HandleTypeDef *i2c_at24;
uint16_t EE_TYPE;
uint8_t dev_add;
/*
*	@brief: Initialize the I2C interface
*	@param: STM32 HAL I2C_HandleTypeDef pointer(initilized before)
*	@param: Chip name: { AT24C01 ,  AT24C02 , AT24C04 , AT24C08 ,
*			AT24C16 , AT24C32 , AT24C32 , AT24C128 , AT24C256}
*	@param: chip physical address determined by A0 , A1 and A2 pins
*	@retval: NONE
*/
void AT24CXX_Init(I2C_HandleTypeDef *_i2c , uint16_t _type , uint8_t _dev_add)
{
	i2c_at24 = _i2c;
	if(_type == AT24C01 || _type == AT24C02 || _type == AT24C04 || _type == AT24C08 || \
		_type == AT24C16 || _type == AT24C32 || _type == AT24C32 || _type == AT24C128 || _type == AT24C256)
		EE_TYPE = _type;
	else 
		EE_TYPE = AT24C02;
	dev_add = (0xA0) | ( 0x07 & _dev_add);
}
/*
*	@brief: Read a data at the specified address of AT24CXX
*	@param: the address to start reading
*	@retval: the read data 
*/
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr)
{				  
	uint8_t buff[2];		  	    																  
	if( EE_TYPE > AT24C16)
	{
		buff[0] = (ReadAddr>>8);
		buff[1] = ReadAddr%256;
		HAL_I2C_Master_Transmit(i2c_at24, dev_add, buff, 2, HAL_MAX_DELAY);	   //Send write command 
	}else {
		buff[0] = ReadAddr%256;
		HAL_I2C_Master_Transmit(i2c_at24, dev_add+((ReadAddr/256)<<1), buff, 1, HAL_MAX_DELAY);	
	}		  	 	   
	HAL_I2C_Master_Receive(i2c_at24, dev_add, buff, 1, HAL_MAX_DELAY) ;   
	return buff[0];
	HAL_Delay(1);	
}
/*
*	@brief: Write a data at the specified address of AT24CXX
*	@param: the destination address for writing data
*	@param: the data to be written
*	@retval: NONE
*/
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{		
	uint8_t buff[3];	
	if( EE_TYPE > AT24C16)
	{
		buff[0] = (WriteAddr>>8);
		buff[1] = WriteAddr%256;
		buff[2] = DataToWrite;
		HAL_I2C_Master_Transmit(i2c_at24, dev_add, buff, 3, HAL_MAX_DELAY);	   //Send write command 
	}else{
		buff[0] = WriteAddr%256;
		buff[1] = DataToWrite;
		HAL_I2C_Master_Transmit(i2c_at24, dev_add+((WriteAddr/256)<<1), buff, 2, HAL_MAX_DELAY);	
	}	
	HAL_Delay(10);	
}
/*
*	@brief: Start writing data of length Len at the specified address in AT24CXX
*			This function can be used to write 16bit or 32bit data.
*	@param: the address to start writing
*	@param: the first address of the data array
*	@param: Length of data to be written 2,4
*	@retval: NONE
*/
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len)
{  	
	uint8_t t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}
/*
*	@brief: Start reading data of length Len from the specified address in AT24CXX
*			This function is used to read 16bit or 32bit data.
*	@param: the address to start reading
*	@param: Length of data to be written 2,4
*	@retval: read data
*/
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len)
{  	
	uint8_t t;
	uint32_t temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
/*
*	@brief: Start reading the specified number of data at the specified address in AT24CX
*	@param: The address to start reading
*	@param: the first address of the data array
*	@param: The number of data to be read
*	@retval: NONE
*/
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
/*
*	@brief: Start writing the specified number of data at the specified address in AT24CXX
*	@param: The address to start writing
*	@param: the first address of the data array
*	@param: The number of data to be written
*	@retval: NONE
*/
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
/****************************************END OF FILE***************************************************/
