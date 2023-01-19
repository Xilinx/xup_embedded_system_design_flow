// Copyright (C) 2022, Advanced Micro Devices, Inc.
//
// SPDX-License-Identifier: BSD-3-Clause
/*
 * devcfg.c
 *
 *  Created on: Aug 15, 2012
 *      Author: ckohn
 */

#include <stdlib.h>
#include "devcfg.h"
#include "xil_printf.h"


/*
 * SLCR registers
 */
#define SLCR_LOCK	   0xF8000004 /**< SLCR Write Protection Lock */
#define SLCR_UNLOCK	   0xF8000008 /**< SLCR Write Protection Unlock */
#define FPGA_RST_CTRL  0xF8000240 /**< FPGA Software Reset Control */
#define LVL_SHFTR_EN   0xF8000900 /**< FPGA Level Shifters Enable */

#define SLCR_LOCK_VAL	0x767B
#define SLCR_UNLOCK_VAL	0xDF0D


XDcfg *XDcfg_Initialize(u16 DeviceId)
{
	XDcfg *Instance = malloc(sizeof *Instance);
	XDcfg_Config *Config = XDcfg_LookupConfig(DeviceId);
	XDcfg_CfgInitialize(Instance, Config, Config->BaseAddr);

	return Instance;
}

int XDcfg_TransferBitfile(XDcfg *Instance, u32 StartAddress, u32 WordLength)
{
	int Status;
	volatile u32 IntrStsReg = 0;

	// TODO : not working although suggested procedure per TRM
	// Disable AXI Interface and Output Level Shifters (Input Level Shifters are still enabled)
//	Xil_Out32(SLCR_UNLOCK, SLCR_UNLOCK_VAL);
//	Xil_Out32(FPGA_RST_CTRL, 0xFFFFFFFF);
//	Xil_Out32(LVL_SHFTR_EN, 0xA);
//	Xil_Out32(SLCR_LOCK, SLCR_LOCK_VAL);

	// Clear DMA and PCAP Done Interrupts
	XDcfg_IntrClear(Instance, (XDCFG_IXR_DMA_DONE_MASK | XDCFG_IXR_D_P_DONE_MASK));

	// Transfer bitstream from DDR into fabric in non secure mode
	Status = XDcfg_Transfer(Instance, (u32 *) StartAddress, WordLength,	(u32 *) XDCFG_DMA_INVALID_ADDRESS, 0, XDCFG_NON_SECURE_PCAP_WRITE);
	if (Status != XST_SUCCESS)
		return Status;

	// Poll DMA Done Interrupt
	while ((IntrStsReg & XDCFG_IXR_DMA_DONE_MASK) != XDCFG_IXR_DMA_DONE_MASK)
		IntrStsReg = XDcfg_IntrGetStatus(Instance);

	// Poll PCAP Done Interrupt
	while ((IntrStsReg & XDCFG_IXR_D_P_DONE_MASK) != XDCFG_IXR_D_P_DONE_MASK)
		IntrStsReg = XDcfg_IntrGetStatus(Instance);

	// Enable AXI Interface and Input/Output Level Shifters
//	Xil_Out32(SLCR_UNLOCK, SLCR_UNLOCK_VAL);
//	Xil_Out32(LVL_SHFTR_EN, 0xF);
//	Xil_Out32(FPGA_RST_CTRL, 0x0);
//	Xil_Out32(SLCR_LOCK, SLCR_LOCK_VAL);

	return XST_SUCCESS;
}
