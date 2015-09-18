#ifndef EXT_MEM_H
#define EXT_MEM_H

#define ADC_START ((volatile char*)0x1400)
#define ADC_END 0x17FF
#define SRAM_START 0x1800
#define SRAM_END 0x1FFF

char ADC_read(int channel);

#endif