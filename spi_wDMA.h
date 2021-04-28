/*
 * spi_wDMA.h
 *
 *  Created on: Feb 10, 2021
 *      Author: Teodor
 */

#ifndef INC_SPI_WDMA_H_
#define INC_SPI_WDMA_H_


extern uint32_t zCzasER;
extern uint32_t zCzasSL;
extern uint32_t zT_zmB;
extern uint32_t zT_dT;


extern void Configure_TDMA(void);
extern void Configure_TSPI2(void);
extern void Activate_TSPI2(void);
extern void CPU_CACHE_Enable(void);
extern void DMA1_TransmitComplete_Callback(void);
extern void SPI_TransferError_Callback(void);
extern uint8_t aTxBuffer[];
extern void uchwyt();

extern __IO uint8_t ubTransmissionComplete;
#endif /* INC_SPI_WDMA_H_ */
