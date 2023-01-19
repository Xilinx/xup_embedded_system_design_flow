// Copyright (C) 2022, Advanced Micro Devices, Inc.
//
// SPDX-License-Identifier: BSD-3-Clause
#include "xparameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xil_cache.h"
#include "ff.h"
#include "devcfg.h"
#include "xil_io.h"
#include "xil_types.h"

// Parameters for Partial Reconfiguration
#define BITFILE_ADDR   0x1200000
#define LAB1_BITFILE_LEN  0x03dbb00 // BIN formatted BITfile length
#define LAB2_BITFILE_LEN  0x03dbb00
#define LAB1_ELFBIN_ADDR  0x00200000 // BIN formatted ELF address
#define LAB2_ELFBIN_ADDR  0x00600000
#define LAB1_ELFBINFILE_LEN  0x00008008 // BIN formatted ELF length
#define LAB2_ELFBINFILE_LEN  0x00008008
#define LAB1_ELF_EXEC_ADDR  0x0020074c // ELF main() entry point
#define LAB2_ELF_EXEC_ADDR  0x00600584

// Read function for STDIN
extern char inbyte(void);

static FATFS fatfs;

// Driver Instantiations
static XDcfg *XDcfg_0;

// prototype for load_elf
void load_elf(u32 loadaddress);

int SD_Init()
{
	FRESULT rc;

	rc = f_mount(&fatfs, "", 0);
	if (rc) {
		xil_printf(" ERROR : f_mount returned %d\r\n", rc);
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

int SD_LoadBitFile(char *FileName, u32 DestinationAddress, u32 ByteLength)
{
	FIL fil;
	FRESULT rc;
	UINT br;

	rc = f_open(&fil, FileName, FA_READ);
	if (rc) {
		xil_printf(" ERROR : f_open returned %d\r\n", rc);
		return XST_FAILURE;
	}

	rc = f_lseek(&fil, 0);
	if (rc) {
		xil_printf(" ERROR : f_lseek returned %d\r\n", rc);
		return XST_FAILURE;
	}

	rc = f_read(&fil, (void*) DestinationAddress, ByteLength, &br);
	if (rc) {
		xil_printf(" ERROR : f_read returned %d\r\n", rc);
		return XST_FAILURE;
	}

	rc = f_close(&fil);
	if (rc) {
		xil_printf(" ERROR : f_close returned %d\r\n", rc);
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

int SD_ElfLoad(char *FileName, u32 DestinationAddress, u32 ByteLength)
{
	FIL fil;
	FRESULT rc;
	UINT br;

	rc = f_open(&fil, FileName, FA_READ);
	if (rc) {
		xil_printf(" ERROR : f_open returned %d\r\n", rc);
		return XST_FAILURE;
	}

	rc = f_lseek(&fil, 0);
	if (rc) {
		xil_printf(" ERROR : f_lseek returned %d\r\n", rc);
		return XST_FAILURE;
	}

	rc = f_read(&fil, (void*) DestinationAddress, ByteLength, &br);
	if (rc) {
		xil_printf(" ERROR : f_read returned %d\r\n", rc);
		return XST_FAILURE;
	}

	rc = f_close(&fil);
	if (rc) {
		xil_printf(" ERROR : f_close returned %d\r\n", rc);
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}



int main()
{
	int Status;


    // Initialize SD controller and transfer partials to DDR
	SD_Init();

	// Initialize Device Configuration Interface
	XDcfg_0 = XDcfg_Initialize(XPAR_XDCFG_0_DEVICE_ID);

    // Display Menu
    int Exit = 0;
    int OptionCurr;
    int OptionNext = 1; // start-up default
	while(Exit != 1) {
		do {
			print("\n");
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
				// Flush and disable Data Cache
				Xil_DCacheDisable();
				xil_printf("Loading lab1 BIT file\n\r");
				SD_LoadBitFile("lab1.bin", BITFILE_ADDR, (LAB1_BITFILE_LEN << 2));
				// Invalidate and enable Data Cache
				Xil_DCacheEnable();
				Xil_Out32(0xF8000008,0x0000DF0D); // Unlock devcfg.SLCR
				Xil_Out32(0xF8000900,0xA); // turn-off the level shifter
				Xil_Out32(0xF8000004,0x767B); 	  // Lock devcfg.SLCR
				Status = XDcfg_TransferBitfile(XDcfg_0, BITFILE_ADDR, LAB1_BITFILE_LEN);
				if (Status != XST_SUCCESS) {
					xil_printf("Error : FPGA configuration failed!\n\r");
					exit(EXIT_FAILURE);
				}
				xil_printf("lab1.bin loaded!, executing its application.\n\r");
				Xil_Out32(0xF8000008,0x0000DF0D); // Unlock devcfg.SLCR
				Xil_Out32(0xF8000900, 0xF); // turn-ON the level shifter
				Xil_Out32(0xF8000004,0x767B); // Lock devcfg.SLCR
				SD_ElfLoad("lab1elf.bin", LAB1_ELFBIN_ADDR, LAB1_ELFBINFILE_LEN);
				load_elf(LAB1_ELF_EXEC_ADDR);
				break;
			case '2':
				// Flush and disable Data Cache
				Xil_DCacheDisable();
				xil_printf("Loading lab2 BIT file\n\r");
				SD_LoadBitFile("lab2.bin", BITFILE_ADDR, (LAB2_BITFILE_LEN << 2));
				// Invalidate and enable Data Cache
				Xil_DCacheEnable();
				Xil_Out32(0xF8000008,0x0000DF0D); // Unlock devcfg.SLCR
				Xil_Out32(0xF8000900,0xA); // turn-off the level shifter
				Xil_Out32(0xF8000004,0x767B); // Lock devcfg.SLCR
				Status = XDcfg_TransferBitfile(XDcfg_0, BITFILE_ADDR, LAB2_BITFILE_LEN);
				if (Status != XST_SUCCESS) {
					xil_printf("Error : FPGA configuration failed!\n\r");
					exit(EXIT_FAILURE);
				}
				xil_printf("Lab3.bin loaded!, executing its application.\n\r");
				Xil_Out32(0xF8000008,0x0000DF0D); // Unlock devcfg.SLCR
				Xil_Out32(0xF8000900, 0xF); // turn-ON the level shifter
				Xil_Out32(0xF8000004,0x767B); // Lock devcfg.SLCR
				SD_ElfLoad("lab2elf.bin", LAB2_ELFBIN_ADDR, LAB2_ELFBINFILE_LEN);
				load_elf(LAB2_ELF_EXEC_ADDR);
				break;
			default:
				break;
		}
	}

    return 0;
}

