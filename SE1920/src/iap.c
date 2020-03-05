/*
 * iap.c
 *
 *  Created on: 21/11/2019
 *      Author: A38866
 */

#include "iap.h"
#include "string.h"

static IAP iap=(IAP)IAP_LOCATION;
static unsigned int *sram_buffer=(unsigned int*)SRAM_LOCATION;

static unsigned int cmd[5];
static unsigned int ret[5];

static unsigned int FLASH_PrepareForWrite(unsigned int startSector, unsigned int endSector){
	cmd[0]=PREPARE_FOR_WRITE;
	cmd[1]=startSector;
	cmd[2]=endSector;
	iap(cmd,ret);
	return ret[0];
}

unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector){
	if(FLASH_PrepareForWrite(startSector,endSector)==CMD_SUCCESS){
		cmd[0]=ERASE;
		cmd[3]=SystemCoreClock/1000;
		iap(cmd,ret);
	}
	return ret[0];
}

static int getSector (unsigned int addr){
	if(addr<=0xFFFF)
		return (addr/0x1000);
	return (addr/0x8000)+14; //-2+16
}

static unsigned int* getAddr (int sector){
	if(sector<16)
		return (unsigned int*)(sector*0x1000);
	return (unsigned int*)((sector-14)*0x8000);
}

unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size){
	int dstSector=getSector((unsigned int)dstAddr);
	int size_buffer=THIRTY_TWO_K;
	if(dstSector<16)
		size_buffer=FOUR_K;
	unsigned int *sectorAddr=getAddr(dstSector);
	memcpy(sram_buffer,sectorAddr,size_buffer);
	if(FLASH_EraseSectors(dstSector, dstSector) == CMD_SUCCESS){
		cmd[3]=FOUR_K;
		cmd[4]=SystemCoreClock/1000;
		memcpy(sram_buffer+((unsigned int*)dstAddr-sectorAddr),srcAddr,size);
		for (int i= 0; ret[0]==CMD_SUCCESS && i<size_buffer/(FOUR_K) && FLASH_PrepareForWrite(dstSector,dstSector)==CMD_SUCCESS; ++i) {
			cmd[0]=COPY_RAM_FLASH;
			cmd[1]=(unsigned int)(sectorAddr+(i*ONE_K)); //avançar 4096 bytes. unsigned int-> 4 bytes, logo avançar 1024 vezes, 4 bytes cada vez
			cmd[2]=(unsigned int)(sram_buffer+(i*ONE_K));
			iap(cmd, ret);
		}
		if(ret[0]==CMD_SUCCESS)
			FLASH_VerifyData(dstAddr, srcAddr, size);
		return ret[0];
	}
	return ret[0];
}

unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size){
	cmd[0]=COMPARE;
	cmd[1]=(unsigned int)dstAddr;
	if(cmd[1]%2!=0)
		cmd[1]--;
	cmd[2]=(unsigned int)srcAddr;
	if(cmd[2]%2!=0)
		cmd[2]--;
	cmd[3]=size;
	iap(cmd,ret);
	if(ret[0]==COMPARE_ERROR)
		return ret[1];
	return ret[0];
}


unsigned int FLASH_BlankSectors(unsigned int startSector, unsigned int endSector){
	cmd[0]=BLANK_CHECK;
	cmd[1]=startSector;
	cmd[2]=endSector;
	iap(cmd,ret);
	return ret[0];
}
