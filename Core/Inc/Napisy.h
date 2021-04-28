/*
 * Napisy.h
 *
 *  Created on: 25 lut 2021
 *      Author: Teodor
 */

#ifndef INC_NAPISY_H_
#define INC_NAPISY_H_

extern void change_font_color(uint8_t Color);
extern void Odczytaj_znak_S16_uc8 (uint8_t  *char_num  );
extern uint8_t* Insert_Font_in_BUF(uint8_t *char_num,uint16_t Row_num ,uint8_t *Cr_String_Buf, uint8_t Color);
extern uint8_t get_font(uint8_t *char_num);
extern uint8_t siding_font();
extern int Create_String_buffer (uint8_t *Word, uint8_t Size, uint8_t Rzad, uint8_t *Cr_String_Buf, uint8_t Color);
#endif /* INC_NAPISY_H_ */
