/*
 * LL_UART_TEO.c
 *
 *  Created on: Mar 2, 2021
 *      Author: Teodor
 */
#include "main.h"
#include "stdio.h"
#include "LL_UART_TEO.h"

#include "String_From_UART.h"


void Print_Data();
void Teo_SysTick_CallBack();
void  TUART_CallBack_IRQ(UART_Handle_Td *USARTx);
void StartReception(void);
void HandleEcho(UART_Handle_Td *USARTx);
void USART_TXEmpty_Callback(UART_Handle_Td *USARTx);
void USART_CharTransmitComplete_Callback(UART_Handle_Td *USARTx);

UART_Handle_Td Thuart3;

uint8_t Rx_USART3[RX_BUFFER_SIZE];
uint8_t Tx_USART3[TX_BUFFER_SIZE];

void INIT_UART3()
{
	  Thuart3.Instance=USART3;
	  Thuart3.pTxBuffPtr=Tx_USART3;
	  Thuart3.TxXferSize=sizeof(Tx_USART3);
	  Thuart3.TxXferCount=0;
	  Thuart3.TxXSendCount=0;
	  Thuart3.pRxBuffPtr=Rx_USART3;
	  Thuart3.RxXferSize=sizeof(Rx_USART3);
	  Thuart3.RxXPrevferCount=0;
	  Thuart3.RecTimeout=ReceiveTimeout;
	  Thuart3.zT=0;
	  Thuart3.RecSomething=false;

	  InitEcho(&Thuart3);
}

void InitEcho(UART_Handle_Td *USARTx)
{
  LL_USART_ClearFlag_ORE(USARTx->Instance);
  LL_USART_EnableIT_RXNE(USARTx->Instance);
  LL_USART_EnableIT_ERROR(USARTx->Instance);
}

void HandleEcho(UART_Handle_Td *USARTx)
{
	if(USARTx->RxXferCount!=0)
	{
		USARTx->RecSomething=true;
	}
	if(USARTx->RxXferCount!=USARTx->RxXPrevferCount)
	{
		USARTx->RxXPrevferCount= USARTx->RxXferCount ;
		USARTx->zT=HAL_GetTick();
	}
	if( (USARTx->zT + USARTx->RecTimeout  < HAL_GetTick() )  && USARTx->RecSomething )
	{
		USARTx->RecSomething=false;
		USARTx->zT=HAL_GetTick();


		int status=Conv_String_From_UART_BMP( USARTx->pRxBuffPtr ,  USARTx->RxXferCount) ;   // musi byc wywolana znim z zeruje ten RxXferCount!

		 USARTx->RxXferCount=0;

		for(int i=0; i<USARTx->TxXferSize; i++)
					 {
						 USARTx->pTxBuffPtr[i]=0;
					 }




		if(status==20)  //status==0 non error
		{
			USARTx->TxXferCount=sprintf(  (char*)  USARTx->pTxBuffPtr ,"Przyjołem, 2 linie powinny być wyśw. poprawnie\r");
		}
		else if(status==40)  //status==0 non error
		{
			USARTx->TxXferCount=sprintf(  (char*)  USARTx->pTxBuffPtr ,"Przyjołem, 4 linie powinny być wyśw. poprawnie\r");
		}
		else
		{
			USARTx->TxXferCount=sprintf(  (char*)  USARTx->pTxBuffPtr ,"Linia %i jest za długa lub wystąpił inny błąd \r", status);
		}



		 for(int i=0; i< (USARTx->RxXferSize) ; i++)
		 {
			 USARTx->pRxBuffPtr[i]=0;
		 }
			 Print_Data(USARTx);
	}
}

void USART_CharReception_Callback(UART_Handle_Td *USARTx)
{
	USARTx->pRxBuffPtr[USARTx->RxXferCount++] = LL_USART_ReceiveData8(USARTx->Instance);
}

void Print_Data(UART_Handle_Td *USARTx)
{
    LL_USART_TransmitData8(USARTx->Instance, USARTx->pTxBuffPtr[ USARTx->TxXSendCount++ ]);

        LL_USART_EnableIT_TXE(USARTx->Instance);
    	LL_USART_EnableIT_TC(USARTx->Instance);
}
void USART_TXEmpty_Callback(UART_Handle_Td *USARTx)
{
  if( USARTx->TxXSendCount == ( USARTx->TxXferCount - 1))
  {

    LL_USART_DisableIT_TXE(USARTx->Instance);

    LL_USART_EnableIT_TC(USARTx->Instance);
  }
  LL_USART_TransmitData8(USARTx->Instance, USARTx->pTxBuffPtr[ USARTx->TxXSendCount++ ]);
}

void USART_CharTransmitComplete_Callback(UART_Handle_Td *USARTx)
{
  if(USARTx->TxXSendCount == USARTx->TxXferCount)
  {
	  USARTx->TxXSendCount=0;
  }
}

void TUART_CallBack_IRQ(UART_Handle_Td *USARTx)
{
	 if(LL_USART_IsActiveFlag_RXNE(USARTx->Instance) && LL_USART_IsEnabledIT_RXNE(USARTx->Instance))
		  {
		    USART_CharReception_Callback(USARTx);
		  }

		  if(LL_USART_IsEnabledIT_TXE(USARTx->Instance) && LL_USART_IsActiveFlag_TXE(USARTx->Instance))
		  {
		    USART_TXEmpty_Callback(USARTx);
		  }
		  if(LL_USART_IsEnabledIT_TC(USARTx->Instance) && LL_USART_IsActiveFlag_TC(USARTx->Instance))
		  {
		    LL_USART_ClearFlag_TC(USARTx->Instance);
		    USART_CharTransmitComplete_Callback(USARTx);
		  }
}

