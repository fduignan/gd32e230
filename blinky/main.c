
#include <stdint.h>
#include "system_gd32e23x.h"
#include "gd32e23x_gpio.h"
#include "gd32e23x_rcu.h"
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

    while(1)
    {
        gpio_bit_set(GPIOA,GPIO_PIN_0);
        delay(1000000);
        gpio_bit_reset(GPIOA,GPIO_PIN_0);
        delay(1000000);
    }
}
    
