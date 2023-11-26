void init(void);
void Default_Handler(void);
int main(void);
void SysTick_Handler(void);
// The following are 'declared' in the linker script
extern unsigned char  INIT_DATA_VALUES;
extern unsigned char  INIT_DATA_START;
extern unsigned char  INIT_DATA_END;
extern unsigned char  BSS_START;
extern unsigned char  BSS_END;
// the section "vectors" is placed at the beginning of flash 
// by the linker script
const void * Vectors[] __attribute__((section(".vectors"))) ={
	(void *)0x20002000, 	/* Top of stack (8k) */ 
	init,   		     /* Reset Handler */
	Default_Handler,	/* NMI */
	Default_Handler,	/* Hard Fault */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */ 
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* SVCall */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* PendSV */
	SysTick_Handler,        /* SysTick */	
/* External interrupt handlers follow */
	Default_Handler, 	/* 0: WWDG */
	Default_Handler, 	/* 1: LVD  */
	Default_Handler, 	/* 2: RTC */
	Default_Handler, 	/* 3: FMC */
	Default_Handler, 	/* 4: RCU */
	Default_Handler, 	/* 5: EXTI Line 0 and 1 */
	Default_Handler, 	/* 6: EXTI Line 2 and 3 */
	Default_Handler, 	/* 7: EXTI Line 4 to 15 */
	Default_Handler, 	/* 8: Reserved */
	Default_Handler, 	/* 9:  DMA Channel 0 */
	Default_Handler, 	/* 10: DMA Channel 1 and 2 */
	Default_Handler, 	/* 11: DMA Channel 3 and 4 */
	Default_Handler, 	/* 12: ADC and comparator */
	Default_Handler, 	/* 13: Timer 0 Brake, update, trigger and Commutation */
	Default_Handler, 	/* 14: Timer 0 Capture compare */
	Default_Handler, 	/* 15: Reserved */
	Default_Handler, 	/* 16: Timer 2 */
	Default_Handler, 	/* 17: Timer 5 */
	Default_Handler, 	/* 18: Reserved */
	Default_Handler, 	/* 19: Timer 13 */
	Default_Handler, 	/* 20: Timer 14 */
	Default_Handler, 	/* 21: Timer 15 */
	Default_Handler, 	/* 22: Timer 16 */
	Default_Handler, 	/* 23: I2C0 event */
	Default_Handler, 	/* 24: I2C1 event */
	Default_Handler, 	/* 25: SPI0 */
	Default_Handler, 	/* 26: SPI1 */
	Default_Handler, 	/* 27: USART0 */
	Default_Handler, 	/* 28: USART1 */
    Default_Handler, 	/* 29: Reserved */
	Default_Handler, 	/* 30: Reserved */
	Default_Handler, 	/* 31: Reserved */
	Default_Handler, 	/* 32: I2C0 error */
	Default_Handler, 	/* 33: Reserved */
	Default_Handler, 	/* 34: I2C1 error */	
};
void init()
{
// do global/static data initialization
	unsigned char *src;
	unsigned char *dest;
	unsigned len;
	src= &INIT_DATA_VALUES;
	dest= &INIT_DATA_START;
	len= &INIT_DATA_END-&INIT_DATA_START;
	while (len--)
		*dest++ = *src++;
// zero out the uninitialized global/static variables
	dest = &BSS_START;
	len = &BSS_END - &BSS_START;
	while (len--)
		*dest++=0;
	main();
}

void Default_Handler()
{
	while(1);
}
