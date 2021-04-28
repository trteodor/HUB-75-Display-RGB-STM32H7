/*
 * LL_UART_TEO.h
 *
 *  Created on: Mar 2, 2021
 *      Author: Teodor
 */

#ifndef INC_LL_UART_TEO_H_
#define INC_LL_UART_TEO_H_
#include "main.h"
#include "stdbool.h"

#define ReceiveTimeout 30
#define RX_BUFFER_SIZE   200
#define TX_BUFFER_SIZE   220


typedef struct __UART_Handle_Td {
	 USART_TypeDef             	    *Instance;        /*!< UART registers base address        */
	  uint8_t                       *pTxBuffPtr;      /*!< Pointer to UART Tx transfer Buffer */
	  uint16_t                      TxXferSize;       /*!< UART Tx Transfer size              */
	  __IO uint16_t                 TxXferCount;      /*!< UART Tx Transfer Counter           */
	  __IO uint16_t                 TxXSendCount;

	  uint8_t                       *pRxBuffPtr;      /*!< Pointer to UART Rx transfer Buffer */
	  uint16_t                      RxXferSize;       /*!< UART Rx Transfer size              */
	  __IO uint16_t                 RxXferCount;      /*!< UART Rx Transfer Counter           */
	  __IO uint16_t 				RxXPrevferCount;
	  uint32_t 						zT;
	  uint32_t 						RecTimeout;
	  bool						    RecSomething;

}UART_Handle_Td;




extern UART_Handle_Td Thuart3;

extern void INIT_UART3();

extern void Teo_SysTick_CallBack();
extern void TUART_CallBack_IRQ(UART_Handle_Td *USARTx);

extern void UART_RX_Error_Callback(void);
extern void HandleEcho(UART_Handle_Td *USARTx);
extern void USART_CharReception_Callback(UART_Handle_Td *USARTx);
extern void PrintInfo(uint8_t *String, uint32_t Size);
extern void UserDataTreatment(uint8_t *DataBuffer, uint32_t Size);
extern void InitEcho(UART_Handle_Td *USARTx);

extern void UART_TX_Error_Callback(void);
extern void USART_TXEmpty_Callback(UART_Handle_Td *USARTx);
extern void USART_CharTransmitComplete_Callback(UART_Handle_Td *USARTx);

#endif /* INC_LL_UART_TEO_H_ */
