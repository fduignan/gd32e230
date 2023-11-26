arm-none-eabi-gcc -mthumb -g3 -mcpu=cortex-m23 init.c main.c ../include/*.c -I ../include  -T linker_script.ld -o main.elf -nostartfiles 
