// Copyright (C) 2022, Advanced Micro Devices, Inc.
//
// SPDX-License-Identifier: BSD-3-Clause
#include "xparameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xil_cache.h"
#include "xdevcfg.h"
#include "xil_io.h"
#include "xil_types.h" 

// Read function for STDIN
extern char inbyte(void);

#define PS_RST_CTRL_REG			(XPS_SYS_CTRL_BASEADDR + 0x200)
#define PS_RST_MASK			0x1	/* PS software reset */
#define SLCR_UNLOCK_OFFSET		0x8

int main()
{
	u32 MultiBootReg = 0;
	XDcfg XDcfg_0;

	// Initialize Device Configuration Interface
	XDcfg_Config *Config = XDcfg_LookupConfig(XPAR_XDCFG_0_DEVICE_ID);
	XDcfg_CfgInitialize(&XDcfg_0, Config, Config->BaseAddr);

	// Display Menu
    int Exit = 0;
    int OptionCurr;
    int OptionNext = 1; // start-up default
	while(Exit != 1) {
		do {
			print("    1: Lab1\n\r");
			print("    2: Lab2\n\r");
			print("    0: Exit\n\r");
			print("> ");

			OptionCurr = OptionNext;
			OptionNext = inbyte();
			if (isalpha(OptionNext)) {
				OptionNext = toupper(OptionNext);
			}

			xil_printf("%c\n\r", OptionNext);
		} while (!isdigit(OptionNext));

		if (OptionCurr == OptionNext)
			continue;

		switch (OptionNext) {
			case '0':
				Exit = 1;
				break;
			case '1':
				  print("Loading Lab1 project\r\n");
				  MultiBootReg = 0x00400000/0x8000; // 0x00400000 is the base address where lab1.bin is stored
				  Xil_Out32(0xF8000000 + SLCR_UNLOCK_OFFSET, 0xDF0DDF0D); // unlock SLCR
				  XDcfg_WriteReg(XDcfg_0.Config.BaseAddr, XDCFG_MULTIBOOT_ADDR_OFFSET, MultiBootReg); // write to multiboot reg
				  // synchronize
				  __asm__(
						"dsb\n\t"
						"isb"
					);
				  // Generate soft reset
				  Xil_Out32(PS_RST_CTRL_REG, PS_RST_MASK);
				break;
			case '2':
				  print("Loading Lab2 project\r\n");
				  MultiBootReg = 0x00800000/0x8000; // 0x00800000 is the base address where lab3.bin is stored
				  Xil_Out32(0xF8000000 + SLCR_UNLOCK_OFFSET, 0xDF0DDF0D); // unlock SLCR
				  XDcfg_WriteReg(XDcfg_0.Config.BaseAddr, XDCFG_MULTIBOOT_ADDR_OFFSET, MultiBootReg); // write to multiboot reg
				  // synchronize
					__asm__(
						"dsb\n\t"
						"isb"
					);
				  // Generate soft reset
			      Xil_Out32(PS_RST_CTRL_REG, PS_RST_MASK);
				break;

				break;
			default:
				break;
		}
	}

    return 0;
}

