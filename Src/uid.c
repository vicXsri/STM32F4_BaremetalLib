/*
 * uid.c
 *
 *  Created on: Sep 18, 2026
 *      Author: Vichu
 */


#include "uid.h"


void get_uid_num(uint8_t* id){

	uint32_t uid0 = UID->uid0;
	uint32_t uid1 = UID->uid1;
	uint32_t uid2 = UID->uid2;

	id[0] =  (uint8_t) uid0;
	id[1] =  (uint8_t) (uid0 >> 8);
	id[2] =  (uint8_t) (uid0 >> 16);
	id[3] =  (uint8_t) (uid0 >> 24);

	id[4] =  (uint8_t) uid1;
	id[5] =  (uint8_t) (uid1 >> 8);
	id[6] =  (uint8_t) (uid1 >> 16);
	id[7] =  (uint8_t) (uid1 >> 24);

	id[8] =  (uint8_t) uid2;
	id[9] =  (uint8_t) (uid2 >> 8);
	id[10] = (uint8_t) (uid2 >> 16);
	id[11] = (uint8_t) (uid2 >> 24);

}
