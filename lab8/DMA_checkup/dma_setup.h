#ifndef DMA_SETUP_H_
#define DMA_SETUP_H_

#include "data_types.h"
#include "dma_registers.h"
#include "i2s_registers.h"
#include "register_cpu.h"
#include "register_system.h"
#include "global_constants.h"

extern Int16 DMA_InpL[PING_PONG_SIZE];
extern Int16 DMA_InpR[PING_PONG_SIZE];
extern Int16 DMA_OutL[PING_PONG_SIZE];
extern Int16 DMA_OutR[PING_PONG_SIZE];

extern Int16 PingPongFlagInL;
extern Int16 PingPongFlagInR;
extern Int16 PingPongFlagOutL;
extern Int16 PingPongFlagOutR;

void DMA0_setup(void);
void DMA0_enable_CH(Uint16 channel_number);
interrupt void DMA_ISR(void);

Uint32 convert_address(Int16 *buffer);

#endif /*DMA_SETUP_H_*/
