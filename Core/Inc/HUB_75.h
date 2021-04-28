/*
 * HUB_75.h
 *
 *  Created on: 20 lut 2021
 *      Author: Teodor
 */

#ifndef INC_HUB_75_H_
#define INC_HUB_75_H_

#include "main.h"

typedef enum
{
	SCR_VIEWING_PROCESS_DONE = 0x2,
	SCR_VIEWING_PROCESS_BUSY = 0x1,
	BUFOR1= 0x0,
	BUFOR2= 0x1,

} SCR_State_Proces_TypeDef;


typedef uint8_t SCR_PROCES;
extern SCR_PROCES SCR_PROCESS;
extern SCR_PROCES SCR_BUF_PROCES;


extern uint8_t Bufor_Send_Picker;
extern uint8_t *SedingBufor_Adr;

/*
typedef struct
{
	__IO HAL_QSPI_StateTypeDef State;
}Scr_HandleTypeDef;
*/

#define White  0xF
#define White2 0x7

#define Black 0x0
#define Black2 0x3

#define Green  0xA
#define Green2 0x2
#define Green3 0x6

#define Red    0x9
#define Blue   0xC
//#define Blue2 0xE
#define Blue3 0x4

#define Yellow 0xB
//#define Yellow2 0x3
#define Azure  0xE

#define Purple 0x1
#define Purple2 0x5
#define Purple3 0xD

extern uint8_t OUT_B1[2550];
extern uint8_t OUT_B2[2550];


extern  uint32_t f_start_view;
extern uint32_t k,l;
extern uint8_t Conv_BP[10000];
extern uint8_t Prepared_String_Buf[];

extern uint32_t zT_SCROLL;
extern int LINIA;
extern uint16_t F_QSPI_Cplt;
extern uint32_t  QSPI_zT_CLT;
extern uint8_t BMP_OB[];
extern int pointer;

extern void TIM5_CallBack();
extern void PrepareFullBuffer(uint8_t *BMP,uint8_t *OUT_B);
extern void HUB_75_INIT();

extern uint8_t* Horizontal_SCROLL(uint8_t *BIT_MAP, uint16_t Hor_Pixel_Count,uint32_t Time_hold, uint32_t Czas_P);
extern uint8_t* HOR_SCROLL_PROCES(uint8_t *BIT_MAP, uint32_t Time_Pr, uint16_t Hor_Pixel_Count);
extern uint8_t* Verical_Scroll_Flow_withHOLD(uint8_t *BIT_MAP, uint8_t Row_Count, uint32_t Czas_P, uint32_t Time_hold_Start,uint32_t Time_hold_Stop, uint8_t HALF);
extern uint8_t* Vertical_Scroll_Flow(uint8_t *BIT_MAP, uint8_t Row_Count, uint32_t Czas_P, uint8_t HALF);
extern void Send_on_SCR(uint8_t *BIT_MAP );
extern uint8_t* Viewing_BitMapBy_Time(uint8_t *BIT_MAP, uint32_t Time);
extern void PrepareRowPart(uint8_t *BMP,uint8_t *OUT_B);
extern void PrepareRow(uint8_t *BMP, uint8_t *OUT_B, uint8_t ROW);

#endif /* INC_HUB_75_H_ */
