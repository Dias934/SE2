#include "flash.h"
static unsigned int* Flash_ADDR=(unsigned int*)ADDR;

void writeToFlash(void* ptr, unsigned int size){
	FLASH_WriteData(Flash_ADDR, ptr, size);
}

void readFromFlash(void* ptr){
	*(unsigned int*)ptr=*Flash_ADDR;
}
