/*
 * uid.h
 *
 *  Created on: Sep 18, 2026
 *      Author: Vichu
 */

#ifndef UID_H_
#define UID_H_

#include "main.h"

typedef struct{
	__IO uint32_t uid0;
	__IO uint32_t uid1;
	__IO uint32_t uid2;
}UID_Typedef;

#define UID		((UID_Typedef*) UID_Base)


void get_uid_num(uint8_t* id);

#endif /* UID_H_ */
