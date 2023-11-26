
#include <stdint.h>
#include "system_gd32e23x.h"
#include "gd32e23x_gpio.h"
#include "gd32e23x_rcu.h"
#include "gd32e23x_usart.h"
/* Pin assignments : 
 * PA9 -> USART0 TX
 * PA10 <- USART0 RX
 * 
*/
void eputs(char *string);
void printDecimal(uint32_t x);
void delay(uint32_t dly)
{
    while(dly--);
}
int main()
{
    int count=0;
    SystemInit();  // system clock is set to 72MHz
    
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_USART0);
    gpio_deinit(GPIOA);
    gpio_mode_set(GPIOA,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_0);
    gpio_mode_set(GPIOA,GPIO_MODE_AF,GPIO_PUPD_NONE,GPIO_PIN_9);
    gpio_mode_set(GPIOA,GPIO_MODE_AF,GPIO_PUPD_NONE,GPIO_PIN_10);
    gpio_af_set(GPIOA,1,GPIO_PIN_9);
    gpio_af_set(GPIOA,1,GPIO_PIN_10);
    usart_deinit(USART0);
    usart_word_length_set(USART0,8);
    usart_parity_config(USART0,USART_PM_NONE);
    usart_baudrate_set(USART0,9600);
    usart_stop_bit_set(USART0,USART_STB_1BIT);
    usart_enable(USART0);
    while(1)
    {
        eputs("count = ");
        printDecimal(count);
        eputs("\r\n");
        count++;
        gpio_bit_set(GPIOA,GPIO_PIN_0); 
        delay(1000000);
        gpio_bit_reset(GPIOA,GPIO_PIN_0);
        delay(1000000);
    }
}
void eputs(char *string)
{
    while(*string)
    {
        while((USART_STAT(USART0) & USART_STAT_TC)==0); // wait for any pending transmission to finish
        USART_TDATA(USART0)=*string;
        string++;
    }
}
void printDecimal(uint32_t x)
{
    char buffer[20];
    int index=19;
    buffer[index]=0;
    while(index > 0) 
    {
        index--;
        buffer[index]=( x % 10 ) + '0';
        x = x / 10;
        if (x==0)
            break;
        
    }
    eputs(&buffer[index]);
    
}
