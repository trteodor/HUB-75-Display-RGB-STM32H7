/*
 * HUB_75.c
 *
 *  Created on: 20 lut 2021
 *      Author: Teodor
 */

#include "HUB_75.h"
#include "main.h"
#include "stm32h7xx_it.h"
#include "tim.h"
#include "quadspi.h"
#include "PIXEL_MAPS.h"

//@here define the brightness
#define scr_brightness 25
//min 1 max 100;

void Send_BUF_IN_SCR(uint8_t *SendBuffer);
void Select_Send_Buf(uint8_t *BITMAP);
void PrepareRowPart(uint8_t *BMP,uint8_t *OUT_B);
void wybierz_linie(uint8_t *MAP_NAME);
uint8_t* HOR_SCROLL_PROCES(uint8_t *BIT_MAP, uint32_t Time_Pr, uint16_t Hor_Pixel_Count);
int pointer=0;
//Bufory
uint8_t Conv_BP[10000]={0};
uint8_t OUT_B1[2550]={0};
uint8_t OUT_B2[2550]={0};
//uint8_t OUT_B2[550];
//Globalne zmienne pomocniczne
uint32_t k=0,l=0;
int LINIA=0;
uint32_t zT_SCROLL=0;
uint32_t zT_View=0;
uint32_t f_start_view=1;
uint32_t start_view_by_time;
//Inicjalizacjia struktury QSPI_Command
QSPI_CommandTypeDef sCommand;
//Zabawa z typedefem - estetyka
SCR_State_Proces_TypeDef My_Scr_Status;
SCR_PROCES SCR_PROCESS;
uint8_t *SedingBufor_Adr=0;
uint8_t Bufor_Send_Picker=BUFOR1;

void TIM5_CallBack()
{
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,100);
	Send_BUF_IN_SCR( SedingBufor_Adr );
}
void Send_BUF_IN_SCR(uint8_t *SendBuffer)
{

	 if(LINIA>7)
	 {
		  LINIA=-1;
	 }
	 LINIA++;

		switch(LINIA) {
					case 7: //7
						HAL_QSPI_Transmit_DMA(&hqspi, SendBuffer+(  LINIA *300  ));

						HAL_GPIO_WritePin(LINE_A_GPIO_Port, LINE_A_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LINE_B_GPIO_Port, LINE_B_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LINE_C_GPIO_Port, LINE_C_Pin, GPIO_PIN_SET);

						break;
					case 6: //6
						HAL_QSPI_Transmit_DMA(&hqspi, SendBuffer+( LINIA *300 ));

						HAL_GPIO_WritePin(LINE_A_GPIO_Port, LINE_A_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(LINE_B_GPIO_Port, LINE_B_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LINE_C_GPIO_Port, LINE_C_Pin, GPIO_PIN_SET);

						break;
					case 5: //5
						HAL_QSPI_Transmit_DMA(&hqspi, SendBuffer+( LINIA *300  ));

						HAL_GPIO_WritePin(LINE_A_GPIO_Port, LINE_A_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LINE_B_GPIO_Port, LINE_B_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(LINE_C_GPIO_Port, LINE_C_Pin, GPIO_PIN_SET);

						break;
					case 4:
						HAL_QSPI_Transmit_DMA(&hqspi, SendBuffer+( LINIA *300  ));

						HAL_GPIO_WritePin(LINE_A_GPIO_Port, LINE_A_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(LINE_B_GPIO_Port, LINE_B_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(LINE_C_GPIO_Port, LINE_C_Pin, GPIO_PIN_SET);


						break;
					case 3:
						HAL_QSPI_Transmit_DMA(&hqspi, SendBuffer+( LINIA *300  ));

						HAL_GPIO_WritePin(LINE_A_GPIO_Port, LINE_A_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LINE_B_GPIO_Port, LINE_B_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LINE_C_GPIO_Port, LINE_C_Pin, GPIO_PIN_RESET);


						break;
					case 2:
						HAL_QSPI_Transmit_DMA(&hqspi, SendBuffer+( LINIA *300  ));

						HAL_GPIO_WritePin(LINE_A_GPIO_Port, LINE_A_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(LINE_B_GPIO_Port, LINE_B_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LINE_C_GPIO_Port, LINE_C_Pin, GPIO_PIN_RESET);


						break;
					case 1:
						HAL_QSPI_Transmit_DMA(&hqspi, SendBuffer+( LINIA *300  ));

						HAL_GPIO_WritePin(LINE_A_GPIO_Port, LINE_A_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(LINE_B_GPIO_Port, LINE_B_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(LINE_C_GPIO_Port, LINE_C_Pin, GPIO_PIN_RESET);
						break;
					case 0:
						HAL_QSPI_Transmit_DMA(&hqspi, SendBuffer+( LINIA *300  ));

						HAL_GPIO_WritePin(LINE_A_GPIO_Port, LINE_A_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(LINE_B_GPIO_Port, LINE_B_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(LINE_C_GPIO_Port, LINE_C_Pin, GPIO_PIN_RESET);
						break;
					}
}
void PrepareFullBuffer(uint8_t *BMP,uint8_t *OUT_B)
{
for(int i=0; i<2500; i++)
{
	OUT_B[i]=0;
}
PrepareRow(BMP,OUT_B+(0*300),7);
PrepareRow(BMP,OUT_B+(1*300),6);
PrepareRow(BMP,OUT_B+(2*300),5);
PrepareRow(BMP,OUT_B+(3*300),4);
PrepareRow(BMP,OUT_B+(4*300),3);
PrepareRow(BMP,OUT_B+(5*300),2);
PrepareRow(BMP,OUT_B+(6*300),1);
PrepareRow(BMP,OUT_B+(7*300),0);
}
void PrepareRow(uint8_t *BMP, uint8_t *OUT_B, uint8_t ROW)
{

	PrepareRowPart ( BMP+32+ (0*64) +(ROW*64), ( OUT_B+(2*16)) );
	PrepareRowPart ( BMP+32+ (8*64) +(ROW*64), ( OUT_B+(3*16)) );

	PrepareRowPart ( BMP+32+ (16*64) +(ROW*64), ( OUT_B+(10*16)) );
	PrepareRowPart ( BMP+32+ (24*64) +(ROW*64), ( OUT_B+(11*16)) ); // srodek mlodszy

	PrepareRowPart ( BMP+16+ (0*64) +(ROW*64), ( OUT_B+(4*16)) );
	PrepareRowPart ( BMP+16+ (8*64) +(ROW*64), ( OUT_B+(5*16)) );

	PrepareRowPart ( BMP+16+ (16*64) +(ROW*64), ( OUT_B+(12*16)) );
	PrepareRowPart ( BMP+16+ (24*64) +(ROW*64), ( OUT_B+(13*16)) ); // srodek starszy


	PrepareRowPart ( BMP+48+ (0*64) +(ROW*64), ( OUT_B+(0*16)) );
	PrepareRowPart ( BMP+48+ (8*64) +(ROW*64), ( OUT_B+(1*16)) );

	PrepareRowPart ( BMP+48+ (16*64) +(ROW*64), ( OUT_B+(8*16)) );
	PrepareRowPart ( BMP+48+ (24*64) +(ROW*64), ( OUT_B+(9*16)) ); // najmlodszy


	PrepareRowPart ( BMP+ (0*64) +(ROW*64), ( OUT_B+(6*16)) );
	PrepareRowPart ( BMP+ (8*64)  +(ROW*64), ( OUT_B+(7*16)) );

	PrepareRowPart ( BMP+ (16*64) +(ROW*64), ( OUT_B+(14*16)) );
	PrepareRowPart ( BMP+ (24*64) +(ROW*64), ( OUT_B+(15*16)) );  //najstarszy
																						//kurde gdyby algorytm na to znalezc :/
}
void PrepareRowPart(uint8_t *BMP,uint8_t *OUT_B)
{
int HIGHER_BIT=0,LOWER_BIT=0;

uint8_t NR_PIXLA=0;
int adr_ink=16;

for(int i=0; i<4; i++)
{
	for(int NR_BIT=0; NR_BIT<8; NR_BIT++) //ten Numer bit sie plusuje i w tym forze wiec 2x
	{
		LOWER_BIT=0;
		HIGHER_BIT=0;
		HIGHER_BIT=(BMP[NR_PIXLA] & 0xF0)>>4;
		LOWER_BIT= (BMP[NR_PIXLA]  & 0x0F);
		NR_PIXLA++;
		adr_ink--;
		//Higer
		if(HIGHER_BIT==0) goto Lower;

		if( HIGHER_BIT==  White || HIGHER_BIT== White2)
		{
			OUT_B[adr_ink ]|=1 << (0);
			OUT_B[adr_ink ]|=1 << (1);
			OUT_B[adr_ink ]|=1 << (2);
			goto Lower;
		}
		if(HIGHER_BIT== Black || HIGHER_BIT== Black2 )
		{
			OUT_B[adr_ink ]|=0 << (0);
			OUT_B[adr_ink ]|=0 << (1);
			OUT_B[adr_ink ]|=0 << (2);
			goto Lower;
		}
		if(HIGHER_BIT== Green || HIGHER_BIT== Green2 || HIGHER_BIT== Green3)
		{
			OUT_B[adr_ink ]|=0 << (0);
			OUT_B[adr_ink ]|=1 << (1);
			OUT_B[adr_ink ]|=0 << (2);
			goto Lower;
		}
		if(HIGHER_BIT== Red)
		{
			OUT_B[adr_ink ]|=1 << (0);
			OUT_B[adr_ink ]|=0 << (1);
			OUT_B[adr_ink ]|=0 << (2);
			goto Lower;
		}
		if(HIGHER_BIT== Blue  || HIGHER_BIT==Blue3)
		{
			OUT_B[adr_ink ]|=0 << (0);
			OUT_B[adr_ink ]|=0 << (1);
			OUT_B[adr_ink ]|=1 << (2);
			goto Lower;
		}
		if( HIGHER_BIT == Purple || HIGHER_BIT==Purple2 || HIGHER_BIT==Purple3 )
		{
			OUT_B[adr_ink ]|=1 << (0);
			OUT_B[adr_ink ]|=0 << (1);
			OUT_B[adr_ink ]|=1 << (2);
			goto Lower;
		}
		if(HIGHER_BIT== Yellow /*|| HIGHER_BIT== Yellow2*/ )
		{
			OUT_B[adr_ink ]|=1 << (0);
			OUT_B[adr_ink ]|=1 << (1);
			OUT_B[adr_ink ]|=0 << (2);
			goto Lower;
		}
		if(HIGHER_BIT== (Azure ) )
		{
			OUT_B[adr_ink ]|=0 << (0);
			OUT_B[adr_ink ]|=1 << (1);
			OUT_B[adr_ink ]|=1 << (2);
			goto Lower;
		}

		//Lower
		Lower:

		NR_BIT++;
		if(LOWER_BIT==0) goto END_LOOP;

		if( LOWER_BIT==  White || LOWER_BIT==  White2  )
		{
			OUT_B[adr_ink ]|=1 << (4);
			OUT_B[adr_ink ]|=1 << (5);
			OUT_B[adr_ink ]|=1 << (6);
			goto END_LOOP;
		}
		if(LOWER_BIT==Black || LOWER_BIT==Black2)
		{
			OUT_B[adr_ink ]|=0 << (4);
			OUT_B[adr_ink ]|=0 << (5);
			OUT_B[adr_ink ]|=0 << (6);
			goto END_LOOP;
		}
		if(LOWER_BIT==Green || LOWER_BIT==Green2 || LOWER_BIT==Green3)
		{
			OUT_B[adr_ink ]|=0 << (4);
			OUT_B[adr_ink ]|=1 << (5);
			OUT_B[adr_ink ]|=0 << (6);
			goto END_LOOP;
		}
		if(LOWER_BIT==Red)
		{
			OUT_B[adr_ink ]|=1 << (4);
			OUT_B[adr_ink ]|=0 << (5);
			OUT_B[adr_ink ]|=0 << (6);
			goto END_LOOP;
		}
		if(LOWER_BIT==Blue ||  LOWER_BIT==Blue3)
		{
			OUT_B[adr_ink ]|=0 << (4);
			OUT_B[adr_ink ]|=0 << (5);
			OUT_B[adr_ink ]|=1 << (6);
			goto END_LOOP;
		}
		if(LOWER_BIT==Purple || LOWER_BIT==Purple2 || LOWER_BIT==Purple3)
		{
			OUT_B[adr_ink ]|=1 << (4);
			OUT_B[adr_ink ]|=0 << (5);
			OUT_B[adr_ink ]|=1 << (6);
			goto END_LOOP;
		}
		if(LOWER_BIT==Yellow /*|| LOWER_BIT==Yellow2*/)
		{
			OUT_B[adr_ink ]|=1 << (4);
			OUT_B[adr_ink ]|=1 << (5);
			OUT_B[adr_ink ]|=0 << (6);
			goto END_LOOP;
		}
		if(LOWER_BIT==Azure)
		{
			OUT_B[adr_ink ]|=0 << (4);
			OUT_B[adr_ink ]|=1 << (5);
			OUT_B[adr_ink ]|=1 << (6);
			goto END_LOOP;
		}

	END_LOOP:;

	}
}

}
void HAL_QSPI_TxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	for(int i=0; i<4; i++)
	{
		asm("NOP");
	}
 HAL_GPIO_TogglePin(LATCH_GPIO_Port, LATCH_Pin);
for(int i=0; i<4; i++)
{
	asm("NOP");
}
 HAL_GPIO_TogglePin(LATCH_GPIO_Port, LATCH_Pin);

 __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,100-scr_brightness);
}
void HUB_75_INIT()
{
	LL_TIM_EnableIT_CC1(TIM5);
	LL_TIM_EnableCounter(TIM5);

	  LL_TIM_EnableIT_CC1(TIM2);
	  LL_TIM_EnableCounter(TIM2);

	HAL_GPIO_WritePin(LINE_A_GPIO_Port, LINE_A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LINE_B_GPIO_Port, LINE_B_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LINE_C_GPIO_Port, LINE_C_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LATCH_GPIO_Port,LATCH_Pin,GPIO_PIN_RESET);


	  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);


	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,97);

	sCommand.DataMode    = QSPI_DATA_4_LINES;
	  sCommand.NbData      = 256; //Here define long of data 1 ROW

	  HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}
void Select_Send_Buf(uint8_t *BITMAP)
{
	   if(Bufor_Send_Picker==BUFOR1)
	   {
		   PrepareFullBuffer(BITMAP,OUT_B1);
		  			   SedingBufor_Adr=OUT_B1;
		  			   Bufor_Send_Picker=BUFOR2;
		   return;
	   }
	   if(Bufor_Send_Picker==BUFOR2)
	   {
		   PrepareFullBuffer(BITMAP,OUT_B2);
		   SedingBufor_Adr=OUT_B2;
		   Bufor_Send_Picker=BUFOR1;
		   return;
	   }
}
uint8_t* Verical_Scroll_Flow_withHOLD(uint8_t *BIT_MAP, uint8_t Row_Count, uint32_t Czas_P, uint32_t Time_hold_Start,uint32_t Time_hold_Stop, uint8_t HALF)//przesuwanie w pionie z zatrzymywaniem
{
	SCR_PROCESS=SCR_VIEWING_PROCESS_BUSY;


	if(f_start_view==1)
	{
		zT_View =HAL_GetTick();
		f_start_view=2;

		   for(int i=0; i<32; i++)
		  	{
		  		  for(int j=0; j<64; j++)
		  		  {
		  			Conv_BP[j+(i*64)]=BIT_MAP[ (k*64) +j+ (i*64) ];
		  		  }
		  	}
		   Select_Send_Buf(Conv_BP);
	}
	if(zT_View+Time_hold_Start <HAL_GetTick() && f_start_view==2)
			{
		zT_View =HAL_GetTick();
		f_start_view=3;
			}

	if(f_start_view==3)
	{

		Vertical_Scroll_Flow(BIT_MAP,Row_Count,Czas_P, HALF);
		 if( SCR_PROCESS==SCR_VIEWING_PROCESS_DONE) { SCR_PROCESS=SCR_VIEWING_PROCESS_BUSY; f_start_view=4; }

		 else{
			 zT_View =HAL_GetTick();

			 return Conv_BP;
		 }
	}

if(zT_View+Time_hold_Stop <HAL_GetTick() && f_start_view==4 )
			{
		zT_View =HAL_GetTick();
		f_start_view=1;
		Select_Send_Buf(Conv_BP);
		SCR_PROCESS=SCR_VIEWING_PROCESS_DONE;
			}
return Conv_BP;
}
uint8_t* Vertical_Scroll_Flow(uint8_t *BIT_MAP, uint8_t Row_Count, uint32_t Czas_P, uint8_t HALF) //plynne przesuwanie w pionie
{
	//this function execution maks 350us
	SCR_PROCESS=SCR_VIEWING_PROCESS_BUSY;

 if(zT_SCROLL+Czas_P < HAL_GetTick())
 {

	   for(int i=0; i<32; i++)
	  	{
	  		  for(int j=0; j<64; j++)
	  		  {
	  			 Conv_BP[j+(i*64)]=BIT_MAP[ (k*64) +j+ (i*64) ];
	  		  }
	  	}
	   k++;

	   if(k> (Row_Count/2) )
	   {
		   for(int f=0; f<l; f++)
		  	{
		  		  for(int d=0; d<64; d++)
		  		  {
		  			 Conv_BP[ (( (Row_Count/2) -l) *64 ) + d+(f*64)]=BIT_MAP[ d+(f*64) ];
		  		  }
		  	}

		   l++;
	   }


	   if( k== (Row_Count+1) || (HALF &&   k==( Row_Count/2) + 1 ) )
	   {
		   k=0; l=0;
		   SCR_PROCESS=SCR_VIEWING_PROCESS_DONE;
	   }

	   Select_Send_Buf(Conv_BP);

	   zT_SCROLL=HAL_GetTick();
}
 return Conv_BP;
}
uint8_t* Viewing_BitMapBy_Time(uint8_t *BIT_MAP, uint32_t Time)
{
	SCR_PROCESS=SCR_VIEWING_PROCESS_BUSY;
if(start_view_by_time==1)
{
	zT_View =HAL_GetTick();
	start_view_by_time=0;
	Select_Send_Buf(BIT_MAP);
}

if(zT_View+Time <HAL_GetTick() )
		{
	zT_View =HAL_GetTick();
	start_view_by_time=1;
	SCR_PROCESS=SCR_VIEWING_PROCESS_DONE;
		}

return BIT_MAP;
}
uint8_t* Horizontal_SCROLL(uint8_t *BIT_MAP, uint16_t Hor_Pixel_Count,uint32_t Time_hold, uint32_t Czas_P)
{																   //^^ czas postoju na poczatku  //Co ile przesuniecie o jeden pixel
	SCR_PROCESS=SCR_VIEWING_PROCESS_BUSY;
if(f_start_view==1)
{
	zT_View =HAL_GetTick();
	   for(int i=0; i<32; i++)
	  	{
	  		  for(int j=0; j<64; j++)
	  		  {
	  			 Conv_BP[j+(i*64)]= BIT_MAP[ j+(i*(Hor_Pixel_Count/2)) ];
	  		  }
	  	}
	   Select_Send_Buf(Conv_BP);
	f_start_view=2;
}
if(zT_View+Time_hold <HAL_GetTick() && f_start_view==2)
		{
	zT_View =HAL_GetTick();
	f_start_view=3;
		}
if(f_start_view==3)
	{
	 HOR_SCROLL_PROCES(BIT_MAP, Czas_P,Hor_Pixel_Count);
	 if( SCR_PROCESS==SCR_VIEWING_PROCESS_DONE) { SCR_PROCESS=SCR_VIEWING_PROCESS_BUSY; f_start_view=4; }
	 else{
		 zT_View =HAL_GetTick();
		 return Conv_BP;
	 }
	}
if(zT_View+Time_hold <HAL_GetTick() && f_start_view==4 )
		{
	zT_View =HAL_GetTick();
	f_start_view=1;
	 Select_Send_Buf(Conv_BP);
	SCR_PROCESS=SCR_VIEWING_PROCESS_DONE;
		}
 return Conv_BP;
}

uint8_t Wpr_Od_Wyzszej_cz_Bajtu=1;

uint8_t* HOR_SCROLL_PROCES(uint8_t *BIT_MAP, uint32_t Time_Pr, uint16_t Hor_Pixel_Count)
{
	SCR_PROCESS=SCR_VIEWING_PROCESS_BUSY;

	 if(zT_SCROLL+Time_Pr < HAL_GetTick())
	 {
		   for(int i=0; i<32; i++)
		  	{

		  		  for(int j=0; j<65; j++)
		  		  {
		  			  if(Wpr_Od_Wyzszej_cz_Bajtu)
		  			  {
		  				Conv_BP[j+(i*64)] =0;
		  				Conv_BP[j+(i*64) ]        |= (BIT_MAP[ k+ j+(i* (Hor_Pixel_Count/2))    ] & 0x0F) << 4 ;
		  				Conv_BP[j+(i*64) ]        |= (BIT_MAP[ k+ j+(i* (Hor_Pixel_Count/2)) +1 ] & 0xF0) >> 4 ;
		  			  }
		  			  else
		  			  {
		  				Conv_BP[j+(i*64)]= BIT_MAP[ k+ j+(i* (Hor_Pixel_Count/2)) ];
		  			  }
		  		  }
		  	}
			 if(Wpr_Od_Wyzszej_cz_Bajtu)
			 {
				Wpr_Od_Wyzszej_cz_Bajtu=0;
				  k++;
			 }
			 else
			 {
				 Wpr_Od_Wyzszej_cz_Bajtu=1;
			 }

		   if( k== ( (Hor_Pixel_Count-128) /2 )+1   )
		   {
			   k=0; l=0;
			   SCR_PROCESS=SCR_VIEWING_PROCESS_DONE;
		   }
		   zT_SCROLL=HAL_GetTick();
		   Select_Send_Buf(Conv_BP);



	}

	 return Conv_BP;
}


