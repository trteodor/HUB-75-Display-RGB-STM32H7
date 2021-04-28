/*
 * spi_wDMA.c
 *
 *  Created on: Feb 10, 2021
 *      Author: Teodor
 */

#include "main.h"
#include "tim.h"
#include "lptim.h"
/* Private typedef -----------------------------------------------------------*/
LL_SPI_InitTypeDef spi_initstruct;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint8_t ubButtonPress = 0;

/* Buffer used for transmission */
//uint8_t R_B[]=    {0xFF,0x01,0x10,0x03,     0x0,0x00,0x00,0x01};
uint8_t aTxBuffer[] = {0x80,0x00,0xFF,0x00,     0x00,0x00,0x00,0x01};


uint8_t ubNbDataToTransmit = sizeof(aTxBuffer);
__IO uint8_t ubTransmissionComplete = 0;

void     Configure_TDMA(void);
void     Configure_TSPI2(void);
void 	 Activate_TSPI2(void);
void 	 CPU_CACHE_Enable(void);
void uchwyt();

uint32_t zCzasER=0;
uint32_t zCzasSL=0;
uint32_t zT_zmB=0;
uint32_t zT_dT=0;

/**
  * @brief  This function configures the DMA Channels for SPI1 and SPI6
  * @note  This function is used to :
  *        -1- Enable DMA1 and BDMA clock
  *        -2- Configure NVIC for DMA1 and BDMA transfer complete/error interrupts
  *        -3- Configure the DMA1_Stream7 functional parameters
  *        -4- Configure the BDMA_Channel0 functional parameters
  *        -5- Enable DMA1 and BDMA interrupts complete/error
  * @param   None
  * @retval  None
  */
void Configure_TDMA(void)
{

  /* (1) Configure the DMA1_Stream2 functional parameters */
  LL_DMA_ConfigAddresses(DMA1,
                         LL_DMA_STREAM_2,
                         (uint32_t)aTxBuffer, (uint32_t) &(SPI4->TXDR),
                         LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_STREAM_2));

  LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_2, ubNbDataToTransmit);
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_STREAM_2, LL_DMAMUX1_REQ_SPI4_TX);

  /* (1) Configure the DMA1_Stream1 functional parameters */
   LL_DMA_ConfigAddresses(DMA1,
                          LL_DMA_STREAM_1,
                          (uint32_t)aTxBuffer, (uint32_t) &(SPI3->TXDR),
                          LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_STREAM_1));

   LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_1, ubNbDataToTransmit);
   LL_DMA_SetPeriphRequest(DMA1, LL_DMA_STREAM_1, LL_DMAMUX1_REQ_SPI3_TX);

  /* (2) Configure the DMA1_Stream0 functional parameters */
  LL_DMA_ConfigAddresses(DMA1,
                         LL_DMA_STREAM_0,
                         (uint32_t)aTxBuffer, (uint32_t) &(SPI1->TXDR),
                         LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_STREAM_0));

  LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, ubNbDataToTransmit);
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_STREAM_0, LL_DMAMUX1_REQ_SPI1_TX);

  /* (5) Enable DMA interrupts complete/error */

  LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_1);
  LL_DMA_EnableIT_TE(DMA1, LL_DMA_STREAM_1);

  LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_2);
  LL_DMA_EnableIT_TE(DMA1, LL_DMA_STREAM_2);



  LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_0);
  LL_DMA_EnableIT_TE(DMA1, LL_DMA_STREAM_0);

}

void Configure_TSPI2(void)
{
	  LL_SPI_EnableDMAReq_TX(SPI3);

	  LL_SPI_EnableDMAReq_TX(SPI4);


	  LL_SPI_EnableDMAReq_TX(SPI1);
}

void Activate_TSPI2(void)
{
  /* Enable SPI */
  LL_SPI_Enable(SPI4);
  LL_SPI_Enable(SPI3);
  LL_SPI_Enable(SPI1);

  /* Enable DMA Stream Tx */

  LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_1);

  LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_2);

  LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0);
  /* Master transfer start */
  LL_SPI_StartMasterTransfer(SPI3);

  LL_SPI_StartMasterTransfer(SPI4);

  LL_SPI_StartMasterTransfer(SPI1);


}


void uchwyt()
{
	//for(int i=0; i<250; i++)
	//{
			//some us delay
	//}
	  HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin,GPIO_PIN_SET); //wlaczam latcha
		for(int i=0; i<50; i++)
		{
				//some us delay
		}
	  HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin,GPIO_PIN_RESET); //wylaczam latcha
}


void DMA1_TransmitComplete_Callback(void)
{
  /* DMA Tx transfer completed */

	  LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_2);



  ubTransmissionComplete=1;


}

void SPI_TransferError_Callback(void)
{
  /* Disable DMA1 Tx Channel */
//  LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_2);

}
