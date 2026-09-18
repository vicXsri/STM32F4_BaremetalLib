/*
 * bootloader.c
 *
 *  Created on: Sep 17, 2026
 *      Author: Vichu
 */

#include "bootloader.h"


uint8_t bl_rx_buffer[bl_rx_buffer_length];

char buff[500];

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

uint8_t supported_commands[] = {
								BL_GET_VER,
								BL_GET_HELP,
								BL_GET_CID,
								BL_GET_RDP_STATUS,
								BL_GO_TO_ADDR,
								BL_FLASH_ERASE,
								BL_MEM_WRITE,
								BL_READ_SECTOR_STATUS,
								};

void bootloader_jump_to_user_app(void){

	// just a function pointer to hold the address of the reset handler of this user app.
	void (*app_reset_handler)(void);
	debug_tx("BL_DEBUG_MSG: bootloader_jump_to_user_app\r\n");

	// Configure the MSP by reading the value from the base address of the sector 2
	uint32_t msp_value = *(volatile uint32_t*) FLASH_SECTOR2_BASE_ADD;
	uint32_t resethandler_address = *(volatile uint32_t*) (FLASH_SECTOR2_BASE_ADD + 0x04);
	app_reset_handler = (void*) resethandler_address;

	sprintf(buff, "BL_DEBUG_MSG: MSP_VALUE : 0x%lx\r\n", msp_value);
	debug_tx(buff);

	sprintf(buff, "BL_DEBUG_MSG: app_reset_handler addr : %p\r\n\r\n", (void *)app_reset_handler);
	debug_tx(buff);

	//This function is supposed to comes from CMSIS
	__set_MSP(msp_value);
	app_reset_handler();

}

void bootloader_uart_read_data(void){

	uint8_t rcv_length = 0;

	while(1){

		memset(bl_rx_buffer, 0, 200);

		UART_Receive(&huart2, bl_rx_buffer, 1, MAX_DELAY);

		rcv_length = bl_rx_buffer[0];

		UART_Receive(&huart2, &bl_rx_buffer[1], rcv_length, MAX_DELAY);
		sprintf(buff, "buf[0] -> %u\r\nbuf[1] -> %u\r\nbuf[2] -> %u\r\nbuf[3] -> %u\r\nbuf[4] -> %u\r\nbuf[5] -> %u\r\n\r\n", bl_rx_buffer[0], bl_rx_buffer[1], bl_rx_buffer[2], bl_rx_buffer[3], bl_rx_buffer[4],bl_rx_buffer[5]);
		debug_tx(buff);
		switch (bl_rx_buffer[1]) {
			case BL_GET_VER:
				bootloader_handle_getver_cmd(bl_rx_buffer);
				break;
			case BL_GET_HELP:
				bootloader_handle_gethelp_cmd(bl_rx_buffer);
				break;
			case BL_GET_CID:
				bootloader_handle_getcid_cmd(bl_rx_buffer);
				break;
			case BL_GET_RDP_STATUS:
				bootloader_handle_getrdp_cmd(bl_rx_buffer);
				break;
			case BL_GO_TO_ADDR:
				bootloader_handle_go_cmd(bl_rx_buffer);
				break;
			case BL_FLASH_ERASE:
				bootloader_handle_flash_erase_cmd(bl_rx_buffer);
				break;
			case BL_MEM_WRITE:
				bootloader_handle_mem_write_cmd(bl_rx_buffer);
				break;
			case BL_EN_R_W_PROTECT:
				bootloader_handle_en_rw_protect(bl_rx_buffer);
				break;
			case BL_MEM_READ:
				bootloader_handle_mem_read(bl_rx_buffer);
				break;
			case BL_READ_SECTOR_STATUS:
				bootloader_handle_read_sector_status(bl_rx_buffer);
				break;
			case BL_OTP_READ:
				bootloader_handle_read_otp(bl_rx_buffer);
				break;
			case BL_DIS_R_W_PROTECT:
				bootloader_handle_dis_rw_protect(bl_rx_buffer);
				break;
			default:
				debug_tx("BL_DEBUG_MSG: Invalid command code received from host !\r\n");
				break;
		}

	}

}

uint8_t bootloader_verify_crc(uint8_t* pdata, uint32_t len, uint32_t crc_host){

	uint32_t uwCRCValue = 0xff;

	CRC->CR = (0x01UL << 0U);

	for(uint32_t i = 0; i < len; i++){

		uint32_t i_data = pdata[i];

		uwCRCValue = CRC_Accumulate(CRC, &i_data, 1);
	}

//	sprintf(buff, "the crc, found was : 0x%X\r\n\r\n", uwCRCValue);
//	debug_tx(buff);

	if(uwCRCValue == crc_host){
		return VERIFY_CRC_SUCCESS;
	}

	return VERIFY_CRC_FAIL;

}

void bootloader_handle_getver_cmd(uint8_t* bl_rx_buffer){

	uint8_t bl_version;

	debug_tx("BL_DEBUG_MSG: bootloader_handle_getver_cmd\r\n");

	uint32_t command_packet_len = bl_rx_buffer[0] + 1;
	uint32_t host_crc = *((uint32_t*) (bl_rx_buffer + command_packet_len - 4));


	if(!bootloader_verify_crc(&bl_rx_buffer[0], command_packet_len - 4, host_crc)){

		debug_tx("BL_DEBUG_MSG: Checksum Success !!\r\n");
		//Checksum is correct
		bootloader_send_ack(bl_rx_buffer[0], 1);
		bl_version = get_bootloader_version();

		sprintf(buff, "BL_DEBUG_MSG: BL_VER: %d\r\n", bl_version);
		debug_tx(buff);
		bootloader_uart_write_data(&bl_version, 1);

	}else{
		debug_tx("BL_DEBUG_MSG: Checksum Fail !!\r\n");
		bootloader_send_nack();
	}

}
void bootloader_handle_gethelp_cmd(uint8_t* bl_rx_buffer){

//	uint8_t bl_version;

	debug_tx("BL_DEBUG_MSG: bootloader_handle_gethelp_cmd\r\n");

	uint32_t command_packet_len = bl_rx_buffer[0] + 1;
	uint32_t host_crc = *((uint32_t*) (bl_rx_buffer + command_packet_len - 4));


	if(!bootloader_verify_crc(&bl_rx_buffer[0], command_packet_len - 4, host_crc)){

		debug_tx("BL_DEBUG_MSG: Checksum Success !!\r\n");
		//Checksum is correct
		bootloader_send_ack(bl_rx_buffer[0], sizeof(supported_commands));
//		bl_version = get_bootloader_version();
		bootloader_uart_write_data(supported_commands, sizeof(supported_commands));

	}else{
		debug_tx("BL_DEBUG_MSG: Checksum Fail !!\r\n");
		bootloader_send_nack();
	}

}
void bootloader_handle_getcid_cmd(uint8_t* bl_rx_buffer){

	uint16_t did_num;

	debug_tx("BL_DEBUG_MSG: bootloader_handle_getcid_cmd\r\n");

	uint32_t command_packet_len = bl_rx_buffer[0] + 1;
	uint32_t host_crc = *((uint32_t*) (bl_rx_buffer + command_packet_len - 4));


	if(!bootloader_verify_crc(&bl_rx_buffer[0], command_packet_len - 4, host_crc)){

		debug_tx("BL_DEBUG_MSG: Checksum Success !!\r\n");
		//Checksum is correct
		bootloader_send_ack(bl_rx_buffer[0], 2);

		did_num = get_device_identifier();
		bootloader_uart_write_data((uint8_t*)&did_num, sizeof(did_num));

	}else{
		debug_tx("BL_DEBUG_MSG: Checksum Fail !!\r\n");
		bootloader_send_nack();
	}

}
//void bootloader_handle_getcid_cmd(uint8_t* bl_rx_buffer){
//
//	uint8_t cid_num[12];
//
//	debug_tx("BL_DEBUG_MSG: bootloader_handle_getcid_cmd\r\n");
//
//	uint32_t command_packet_len = bl_rx_buffer[0] + 1;
//	uint32_t host_crc = *((uint32_t*) (bl_rx_buffer + command_packet_len - 4));
//
//
//	if(!bootloader_verify_crc(&bl_rx_buffer[0], command_packet_len - 4, host_crc)){
//
//		debug_tx("BL_DEBUG_MSG: Checksum Success !!\r\n");
//		//Checksum is correct
//		bootloader_send_ack(bl_rx_buffer[0], sizeof(cid_num));
//		get_uid_num(cid_num);
//		bootloader_uart_write_data(cid_num, sizeof(cid_num));
//
//	}else{
//		debug_tx("BL_DEBUG_MSG: Checksum Fail !!\r\n");
//		bootloader_send_nack();
//	}
//
//}

void bootloader_handle_getrdp_cmd(uint8_t* bl_rx_buffer){

}
void bootloader_handle_go_cmd(uint8_t* bl_rx_buffer){

}
void bootloader_handle_flash_erase_cmd(uint8_t* bl_rx_buffer){

}
void bootloader_handle_mem_write_cmd(uint8_t* bl_rx_buffer){

}
void bootloader_handle_en_rw_protect(uint8_t* bl_rx_buffer){

}
void bootloader_handle_mem_read(uint8_t* bl_rx_buffer){

}
void bootloader_handle_read_sector_status(uint8_t* bl_rx_buffer){

}
void bootloader_handle_read_otp(uint8_t* bl_rx_buffer){

}

void bootloader_handle_dis_rw_protect(uint8_t* bl_rx_buffer){

}

void bootloader_send_ack(uint8_t command_code, uint8_t follow_len){

	uint8_t ack_buff[2];

	ack_buff[0] = BL_ACK;
	ack_buff[1] = follow_len;

	UART_Transmit(&huart2, ack_buff, 2, MAX_DELAY);

}

void bootloader_send_nack(void){

	uint8_t nack;

	nack = BL_NACK;

	UART_Transmit(&huart2, &nack, 1, MAX_DELAY);

}


uint8_t get_bootloader_version(){

	return (uint8_t)BL_VERSION;

}

void bootloader_uart_write_data(uint8_t* pBuffer, uint32_t len){
	UART_Transmit(&huart2, pBuffer, len, MAX_DELAY);
}


uint16_t get_device_identifier(void){

	volatile uint32_t* DBGMCU_IDCODE = (volatile uint32_t*)0xE0042000;

	return (uint16_t)(*DBGMCU_IDCODE & (0xFFF));

}
