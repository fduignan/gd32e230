arm-none-eabi-gcc -static -mthumb -g3 -mcpu=cortex-m23 init.c main.c ../include/gd32e23x_gpio.c  ../include/gd32e23x_rcu.c ../include/system_gd32e23x.c  ../include/gd32e23x_misc.c -T linker_script.ld -o main.elf -nostartfiles
