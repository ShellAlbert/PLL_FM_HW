

//file: zuart_protocol.h
//funtion: define uart protocols relevanted.
//date: Feburary 15,2022
//author: by YantaiElectrician
#ifndef __ZUART_PROTOCOL_H__
#define __ZUART_PROTOCOL_H__

//RS422 Full duplex communication.
//LDM:Laser Distance Measurement Module.
//Frame format: MCU--->>>LDM
//Byte0,Byte1,Byte2,Byte3,Byte4,Byte5
//0xb7,0xb8,Comm,DatH,DatL,Bak

/*----------Comm:Commands----------*/
//0x01: Measure distance automatically.
//		LDM will measure distance at specified interval period after get this command.
//0x02: End measure distance.
//0x03: Set the choose distance.
//		Byte3 is High Byte,Byte4 is Low Byte.
//0x04: Set Interval time.
//		Byte3 is High Byte,Byte4 is Low Byte.
//0x07: Single distance measurement.
//format command for Laser Distance Module.
typedef enum {
	ZLDM_DISTANCE_AUTO = 0, 
	ZLDM_DISTANCE_END_AUTO, 
	ZLDM_DISTANCE_SET,
	ZLDM_DISTANCE_SINGLE, 
} ZLDM_CMD_TYPES;
extern uint8_t zldm_fmt_cmd(ZLDM_CMD_TYPES cmdType,uint8_t * cmdBuffer, uint8_t cmdBufLen);

//Frame format: LDM--->>>MCU
//Byte0,Byte1,Byte2,Byte3,Byte4,Byte5
//0xb7,0xb8,Falg,DatH,DatL,St
//Falg definition.
//0x01: Report distance values to MCU. 
//		Byte3 is High Byte,Byte4 is Low Byte,Byte5 is Status Byte.
//St defination.
//0x08: No Laser output.
//0x00: With Distance value, but no front object and rear object.
//0x01: With front object.
//0x02: With rear object.
//0x03: With front object and rear object.
//0x04: Object exceeds distance.
//0x05: Distance value equals 0 with front object.

//parse commands response from Laser Distance Module. 
extern uint8_t zldm_parse_cmd(uint8_t * cmdBuffer, uint8_t cmdBufLen);
#endif //__ZUART_PROTOCOL_H__
