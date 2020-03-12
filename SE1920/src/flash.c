#include "flash.h"

static unsigned int* Flash_ADDR=(unsigned int*)0;
static unsigned short sector=0;

int init_flash(unsigned int id){
	unsigned int res=0;
	do{
		readFromFlash(&res);
		if(res==id){
			Flash_ADDR++;
			return SECTOR_FOUND;
		}
		else{
			sector++;
			if(sector<(unsigned short)SECTOR_THRESHOLD)
				Flash_ADDR+=SECTOR_INTERVAL_4K/4;
			else
				Flash_ADDR+=SECTOR_INTERVAL_32K/4;
		}
	}while(sector<SECTOR_MAX);
	sector=0;
	Flash_ADDR=(unsigned int*)0;
	do{
		res=FLASH_BlankSectors(sector,sector);
		if(res==CMD_SUCCESS){
			writeToFlash(&id,sizeof(id));
			Flash_ADDR++;
			return SECTOR_AVAILABLE;
		}
		else{
			sector++;
			if(sector<SECTOR_THRESHOLD)
				Flash_ADDR+=SECTOR_INTERVAL_4K/4;
			else
				Flash_ADDR+=SECTOR_INTERVAL_32K/4;
		}
	}while(sector<SECTOR_MAX);
	return SECTOR_NOT_FOUND;
}

void writeToFlash(void* ptr, unsigned int size){
	FLASH_WriteData(Flash_ADDR, ptr, size);
}

void readFromFlash(void* ptr){
	*(unsigned int*)ptr=*Flash_ADDR;
}
