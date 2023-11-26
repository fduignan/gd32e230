
#include <stdint.h>
#include "system_gd32e23x.h"
#include "gd32e23x_gpio.h"
#include "gd32e23x_rcu.h"
// Macros to enable/disable global interrupts
#define enable_interrupts() asm(" cpsie i ")
#define disable_interrupts() asm(" cpsid i ")
// macro for putting the CPU in to sleep mode
#define cpu_sleep() asm(" wfi ")
volatile uint32_t milliseconds=0;

void delay(uint32_t dly)
{
    while(dly--);
}
int main()
{
    SystemInit();  // system clock is set to 72MHz
    
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_deinit(GPIOA);
    gpio_mode_set(GPIOA,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_0);
    SysTick->LOAD=72000-1; // set reload value to 72000-1 to give a 1kHz interrupt rate
    SysTick->CTRL=7;  // enable counting and interrupts for SysTick timer 
    enable_interrupts();
    while(1)
    {
        cpu_sleep();
    }
}
    
void SysTick_Handler(void)
{
    milliseconds++;
    if (milliseconds > 999)
    { // toggle LED every second
        gpio_bit_toggle(GPIOA,GPIO_PIN_0);
        milliseconds = 0;
    }
}
