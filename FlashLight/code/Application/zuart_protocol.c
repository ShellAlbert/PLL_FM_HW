

//file: zuart_protocol.c
//funtion: define uart protocols relevanted.
//date: Feburary 15,2022
//author: by YantaiElectrician
//format command for Laser Distance Module.
uint8_t zldm_fmt_cmd(ZLDM_CMD_TYPES cmdType, uint8_t * cmdBuffer, uint8_t cmdBufLen)
{
	//check parameters validation.
	if (NULL == cmdBuffer || cmdBufLen != 6) {
		return 0;
	}

	* (cmdBuffer + 0)	= 0xb7;
	* (cmdBuffer + 1)	= 0xb8;

	switch (cmdType)
	{
		case ZLDM_DISTANCE_AUTO:
			* (cmdBuffer + 2) = 0x01;
			break;

		case ZLDM_DISTANCE_END_AUTO:
			* (cmdBuffer + 2) = 0x02;
			break;

		case ZLDM_DISTANCE_SET:
			* (cmdBuffer + 2) = 0x03;
			break;

		case ZLDM_DISTANCE_SINGLE:
			* (cmdBuffer + 2) = 0x07;
			break;

		default:
			break;
	}

	* (cmdBuffer + 3)	= 0x0;
	* (cmdBuffer + 4)	= 0x0;
	* (cmdBuffer + 5)	= 0x0;
	return 1;
}


//parse commands response from Laser Distance Module. 
//Frame format: LDM--->>>MCU
//Byte0,Byte1,Byte2,Byte3,Byte4,Byte5
//0xb7,0xb8,Falg,DatH,DatL,St
uint8_t zldm_parse_cmd(uint8_t * cmdBuffer, uint8_t cmdBufLen)
{
	//check parameters validation.
	if (NULL == cmdBuffer || cmdBufLen != 6) {
		return 0;
	}

	//make sure first two header bytes matched.
	if (! (cmdBuffer[0] == 0xb7 && cmdBuffer[1] == 0xb8)) {
		return 0;
	}

	switch (cmdBuffer[2])
	{
		case 0x01:
			break;

		default:
			break;
	}

	return 0;
}



