/*********************************************************************************
 *  Author:  Ehab Magdy Abdullah												 *
 *  YouTube: @EmbeddedEhab														 *
 ********************************************************************************/

#include "stdio.h"
#include "stdint.h"
#include "TFPlayer.h"
#include "usart.h"

uint16_t CheckSum;

void TF_Send_Command(uint8_t cmd, uint8_t parameter1, uint8_t parameter2)
{
	CheckSum = VERSION + CMD_LEN + cmd + FEEDBACK + parameter1 + parameter2;
	CheckSum = 0 - CheckSum;

	/* Command Packet： START  VER  Length  CMD  Feedback  parameter1  parameter2  CheckSum <2 bytes>  END  */
	uint8_t CommandPacket[10] = {START_BYTE, VERSION, CMD_LEN, cmd, FEEDBACK, parameter1, parameter2, (CheckSum >> 8) & 0xFF, (CheckSum & 0xFF), END_BYTE};

	HAL_UART_Transmit(TF_UART, CommandPacket, 10, HAL_MAX_DELAY);
}

void TF_PlayFromStart(void)
{
	TF_Send_Command(0x03,0x00,0x01);
}

void TF_Init(void)
{
	TF_Send_Command(0x3F, 0x00, SOURCE_TF_Card);
	HAL_Delay(800);
}

void TF_Set_Volume(uint8_t volume)
{
	TF_Send_Command(0x06, 0x00, volume);
}

void TF_Next(void)
{
	TF_Send_Command(0x01, 0x00, 0x00);
}

void TF_Previous(void)
{
	TF_Send_Command(0x02, 0, 0);
}

void TF_Pause(void)
{
	TF_Send_Command(0x0E, 0, 0);
}

void TF_Resume(void)
{
	TF_Send_Command(0x0D, 0, 0);
}
