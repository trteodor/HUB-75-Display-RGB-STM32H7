/*
 * String_From_UART.c
 *
 *  Created on: Mar 4, 2021
 *      Author: Teodor
 */

#include "String_From_UART.h"
#include "Napisy.h"
#include "HUB_75.h"
#include "LL_UART_TEO.h"


uint8_t Created_By_UART_BMP[10000]={0};
int Set_Flag_String_From_Usart(uint8_t Ilosc_Lini);
uint8_t get_color_value(uint8_t Color_mark);
int Ilosc_Lini_tesktu=0;
uint32_t Z_czasOtrzymania_tekstu=0;

int Conv_String_From_UART_BMP(uint8_t *Rec_String, uint16_t CountData)
{
	uint8_t Line_nr=0;
	uint8_t Ilosc_zn_pop_rzedu=0;
	uint8_t Ilosc_znak_do_wstawienia=0;

	uint8_t count_line=0;

	uint8_t color_flag=0;

	for(int i=0; i<10000; i++)
	{
		 Created_By_UART_BMP[i]=0;
	}

	for(int i=0; i< CountData;   i++)
	{

		if( Rec_String[i]=='$' )
		{

			count_line++;

			color_flag=1;

										//rozmiar           	   							//rzad      	//bufor wyjsciowy   //color
			if(Create_String_buffer (Rec_String+Ilosc_zn_pop_rzedu+(Line_nr*3), Ilosc_znak_do_wstawienia , Line_nr , Created_By_UART_BMP, get_color_value(Rec_String[i+1]) )==0);
			else
			{
				return Line_nr+1; // za dluga linia nr Line_nr
			}

			if( Rec_String[i+2] != '\0')
			{
				return Line_nr+1; // inny blad
			}



			Ilosc_zn_pop_rzedu=Ilosc_zn_pop_rzedu+Ilosc_znak_do_wstawienia;
			i=i+3;

			Line_nr++;
			Ilosc_znak_do_wstawienia=0;

		}

		if(Ilosc_znak_do_wstawienia>17)
		{
			return Line_nr+1; // za dluga linia nr Line_nr
		}

		Ilosc_znak_do_wstawienia++;


	}

	Set_Flag_String_From_Usart(Line_nr);


	if(color_flag && (count_line==1 || count_line==2) )
	{
		return 20; //1-2 lub dwie linie
	}
	else if(color_flag && (count_line==3 || count_line==4) )
	{
		return 40; //3-4 lub dwie linie
	}
	else
	{
		return Line_nr+1; // inny blad
	}

}

uint8_t get_color_value(uint8_t Color_mark)
{
	switch(Color_mark)
	{
	case 'W':
		return White;
		break;
	case 'R':
		return Red;
		break;
	case 'G':
		return Green;
		break;
	case 'B':
		return Blue;
		break;
	case 'Y':
		return Yellow;
		break;
	case 'A':
		return Azure;
		break;
	case 'P':
		return Purple;
		break;
	default :
		return 0;
		break;
	}
}


int Set_Flag_String_From_Usart(uint8_t Ilosc_Lini)
{
	Ilosc_Lini_tesktu=Ilosc_Lini;
	Z_czasOtrzymania_tekstu=HAL_GetTick();
	return Ilosc_Lini_tesktu;
}

