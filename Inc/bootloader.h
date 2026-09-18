/*
 * bootloader.h
 *
 *  Created on: Sep 17, 2026
 *      Author: Vichu
 */

#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

#include "main.h"


#define bl_rx_buffer_length	200

#define BL_GET_VER				0x51
#define BL_GET_HELP				0x52
#define BL_GET_CID				0x53
#define BL_GET_RDP_STATUS		0x54
#define BL_GO_TO_ADDR			0x55
#define BL_FLASH_ERASE			0x56
#define BL_MEM_WRITE			0x57
#define BL_EN_R_W_PROTECT		0x58
#define BL_MEM_READ				0x59
#define BL_READ_SECTOR_STATUS	0x5A
#define BL_OTP_READ				0x5B
#define BL_DIS_R_W_PROTECT		0x5C

#define BL_NACK					0x7F
#define BL_ACK					0xA5

#define BL_VERSION				0x10

#define VERIFY_CRC_SUCCESS		0x00
#define VERIFY_CRC_FAIL			0x01

void bootloader_uart_read_data(void);
void bootloader_jump_to_user_app(void);

void bootloader_handle_getver_cmd(uint8_t* bl_rx_buffer);
void bootloader_handle_gethelp_cmd(uint8_t* bl_rx_buffer);
void bootloader_handle_getcid_cmd(uint8_t* bl_rx_buffer);
void bootloader_handle_getrdp_cmd(uint8_t* bl_rx_buffer);
void bootloader_handle_go_cmd(uint8_t* bl_rx_buffer);
void bootloader_handle_flash_erase_cmd(uint8_t* bl_rx_buffer);
void bootloader_handle_mem_write_cmd(uint8_t* bl_rx_buffer);
void bootloader_handle_en_rw_protect(uint8_t* bl_rx_buffer);
void bootloader_handle_mem_read(uint8_t* bl_rx_buffer);
void bootloader_handle_read_sector_status(uint8_t* bl_rx_buffer);
void bootloader_handle_read_otp(uint8_t* bl_rx_buffer);
void bootloader_handle_dis_rw_protect(uint8_t* bl_rx_buffer);

uint8_t bootloader_verify_crc(uint8_t* pdata, uint32_t len, uint32_t crc_host);

void bootloader_send_ack(uint8_t command_code, uint8_t follow_len);
void bootloader_send_nack(void);

uint16_t get_device_identifier(void);
uint8_t get_bootloader_version();
void bootloader_uart_write_data(uint8_t* pBuffer, uint32_t len);
#endif /* BOOTLOADER_H_ */
