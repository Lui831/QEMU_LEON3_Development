/*
 ============================================================================
 Name        : mem_test.c
 Author      : Bunduki, Yuri
 Version     :
 Copyright   : DLR
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#include "address.h"
#include "drv_wtdg.h"
#include "register.h"

#define VERBOSE 1

clock_t memCpy8(uint8_t *usFrom, uint8_t *usTo, uint32_t size, uint32_t shift){
	uint32_t ulCounter;
	clock_t lTimeBef, lTimeAfter = 0;

#if VERBOSE
	printf("Starting 8-bit cpy test with shift: %lu\n", shift);
#endif
	lTimeBef = clock();
	for(ulCounter=0; ulCounter<size; ulCounter++){
		usTo[ulCounter+shift] = usFrom[ulCounter];
	}

	lTimeAfter = clock();
	printf("[Cpy 8-bit]Time Elapsed: %lu us\n", (long) lTimeAfter-lTimeBef);
	return lTimeAfter-lTimeBef;
}

clock_t memCpy16(uint16_t *usFrom, uint16_t *usTo, uint32_t size, uint32_t shift){
	uint32_t ulCounter;
	clock_t lTimeBef, lTimeAfter = 0;

#if VERBOSE
	printf("Starting 16-bit cpy test with shift: %lu\n", shift);
#endif

	lTimeBef = clock();
	for(ulCounter=0; ulCounter< size/2; ulCounter++){
		usTo[ulCounter+shift] = usFrom[ulCounter];
	}

	lTimeAfter = clock();
	printf("[Cpy 16-bit]Time Elapsed: %lu us\n", (long) lTimeAfter-lTimeBef);
	return lTimeAfter-lTimeBef;
}

clock_t memCpy32(uint32_t *usFrom, uint32_t *usTo, uint32_t size, uint32_t shift){
	uint32_t ulCounter;
	clock_t lTimeBef, lTimeAfter = 0;

#if VERBOSE
	printf("Starting 32-bit cpy test with shift: %lu\n", shift);
#endif

	lTimeBef = clock();
	for(ulCounter=0; ulCounter< size/4; ulCounter++){
		usTo[ulCounter+shift] = usFrom[ulCounter];
	}

	lTimeAfter = clock();
	printf("[Cpy 32-bit]Time Elapsed: %lu us\n", (long) lTimeAfter-lTimeBef);
	return lTimeAfter-lTimeBef;
}

clock_t memCpy64(uint64_t *usFrom, uint64_t *usTo, uint32_t size, uint32_t shift){
	uint32_t ulCounter;
	clock_t lTimeBef, lTimeAfter = 0;
#if VERBOSE
	printf("Starting 64-bit cpy test with shift: %lu\n", shift);
#endif
	lTimeBef = clock();
	for(ulCounter=0; ulCounter< size/8; ulCounter++){
		usTo[ulCounter] = usFrom[ulCounter];
	}

	lTimeAfter = clock();
	printf("[Cpy 64-bit]Time Elapsed: %lu us\n", (long) lTimeAfter-lTimeBef);
	return lTimeAfter-lTimeBef;
}

int main(void) {
	_SET_WDG_DISABLE();

	uint8_t buf1[5*1024*1024+8];
	uint8_t buf2[5*1024*1024];
	uint32_t ui32Counter = 0;

	int i=0;
	clock_t lTimeBef, lTimeAfter = 0;
	clock_t l8BitON[8], l16BitON[8], l32BitON[8], l64BitON[8];
	clock_t l8BitOFF[8], l16BitOFF[8], l32BitOFF[8], l64BitOFF[8];

	clock_t mem_cpy[2];

	uint16_t *p16Buf1, *p16Buf2;
	p16Buf1 =(uint16_t *) &buf1;
	p16Buf2 =(uint16_t *) &buf2;

	uint32_t *p32Buf1, *p32Buf2;
	p32Buf1 =(uint32_t *) &buf1;
	p32Buf2 =(uint32_t *) &buf2;

	uint64_t *p64Buf1, *p64Buf2;
	p64Buf1 =(uint64_t *) &buf1;
	p64Buf2 =(uint64_t *) &buf2;

	#define MCTRL_MCFG3_REG (*(volatile unsigned int*)(0x80000008))

	printf("Initializing memory...\n");
	for(ui32Counter = 0; ui32Counter < 5*1024*1024+8; ui32Counter++){
//		buf1[ui32Counter] = rand() % 255; //Too slow
		buf1[ui32Counter] = 42;
	}


	// for(i=0; i<8; i++){
	// 	l8BitON[i] = memCpy8((uint8_t *) &buf1,(uint8_t *) &buf2, 40*1024*1024, i);
	// 	l16BitON[i] = memCpy16(p16Buf1, p16Buf2, 40*1024*1024, i);
	// 	l32BitON[i] = memCpy32(p32Buf1, p32Buf2, 40*1024*1024, i);
	// 	l64BitON[i] = memCpy64(p64Buf1, p64Buf2, 40*1024*1024, i);
	// }

	l8BitON[0] = memCpy8((uint8_t *) &buf1,(uint8_t *) &buf2, 5*1024*1024, 0);
	l16BitON[0] = memCpy16(p16Buf1, p16Buf2, 5*1024*1024, 0);
	l32BitON[0] = memCpy32(p32Buf1, p32Buf2, 5*1024*1024, 0);
	l64BitON[0] = memCpy64(p64Buf1, p64Buf2, 5*1024*1024, 0);

#if VERBOSE
	printf("Starting 64-bit cpy test with memcpy\n");
#endif
	lTimeBef = clock();
	memcpy(p64Buf1, p64Buf2, sizeof(buf2)/8); //sizeof(uint64_t)
	lTimeAfter = clock();
	mem_cpy[0] = lTimeAfter - lTimeBef;
#if VERBOSE
	printf("[memcpy 64-bit]Time Elapsed ON: %lu us\n", mem_cpy[0]);
#endif
	lTimeAfter = 0;
	lTimeBef = 0;

	/* Disabling EDAC */
#if VERBOSE
	printf("Disabling EDAC\n");
#endif
	// uint32_t *pEDAC = (uintptr_t) 0x80000008;
	MCTRL_MCFG3_REG &= ~(1 << 9);
//#if VERBOSE
//	printf("EDAC byte after mod content and addr: %lu, %x\n", *pEDAC, pEDAC);
//#endif

	/* Run tests for off */
	// for(i=0; i<8; i++){
	// 	l8BitOFF[i] = memCpy8((uint8_t *) &buf1,(uint8_t *) &buf2, 40*1024*1024, i);
	// 	l16BitOFF[i] = memCpy16(p16Buf1, p16Buf2, 40*1024*1024, i);
	// 	l32BitOFF[i] = memCpy32(p32Buf1, p32Buf2, 40*1024*1024, i);
	// 	l64BitOFF[i] = memCpy64(p64Buf1, p64Buf2, 40*1024*1024, i);
	// }

	l8BitOFF[0] = memCpy8((uint8_t *) &buf1,(uint8_t *) &buf2, 5*1024*1024, 0);
	l16BitOFF[0] = memCpy16(p16Buf1, p16Buf2, 5*1024*1024, 0);
	l32BitOFF[0] = memCpy32(p32Buf1, p32Buf2, 5*1024*1024, 0);
	l64BitOFF[0] = memCpy64(p64Buf1, p64Buf2, 5*1024*1024, 0);

#if VERBOSE
	printf("Starting 64-bit cpy test with memcpy\n");
#endif
	lTimeBef = clock();
	memcpy(p64Buf1, p64Buf2, sizeof(buf2)/8); //sizeof(uint64_t)
	lTimeAfter = clock();
	mem_cpy[1] = lTimeAfter - lTimeBef;
#if VERBOSE
	printf("[memcpy 64-bit]Time Elapsed OFF: %lu us\n", mem_cpy[1]);
#endif

	/* Display results */
	printf("Results ON\n8-bit,16-bit,32-bit,64-bit\n");
	// for (i=0; i<8; i++){
	// 	printf("Shift-%i - %lu, %lu, %lu, %lu\n", i,(long) l8BitON[i],(long) l16BitON[i],
	// 										(long) l32BitON[i],(long) l64BitON[i]);
	// }
	printf("Shift-%i - %lu, %lu, %lu, %lu\n", 0,(long) l8BitON[0],(long) l16BitON[0],
											(long) l32BitON[0],(long) l64BitON[0]);

	printf("Using memcpy %lu\n",(long) mem_cpy[0]);

	printf("Results OFF\n8-bit,16-bit,32-bit,64-bit\n");
	// for (i=0; i<8; i++){
	// 	printf("Shift-%i - %lu, %lu, %lu, %lu\n", i,(long) l8BitOFF[i],(long) l16BitOFF[i],
	// 										(long) l32BitOFF[i],(long) l64BitOFF[i]);
	// }
	printf("Shift-%i - %lu, %lu, %lu, %lu\n", 0,(long) l8BitOFF[0],(long) l16BitOFF[0],
											(long) l32BitOFF[0],(long) l64BitOFF[0]);

	printf("Using memcpy %lu\n",(long) mem_cpy[1]);

	printf("End of test.\n");
	return EXIT_SUCCESS;
}
