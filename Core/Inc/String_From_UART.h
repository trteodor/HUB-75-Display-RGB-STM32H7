/*
 * String_From_UART.h
 *
 *  Created on: Mar 4, 2021
 *      Author: Teodor
 */

#ifndef INC_STRING_FROM_UART_H_
#define INC_STRING_FROM_UART_H_

#include "main.h"



extern int Ilosc_Lini_tesktu;
extern uint32_t Z_czasOtrzymania_tekstu;

int Conv_String_From_UART_BMP(uint8_t *Rec_String, uint16_t CountData);

extern uint8_t Created_By_UART_BMP[10000];

#endif /* INC_STRING_FROM_UART_H_ */
