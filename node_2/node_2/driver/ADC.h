#ifndef ADC_H
#define ADC_H
#include <avr/io.h>

void init_ADC(void);
uint8_t ADC_read(void);
void check_and_report_goal( void );


#endif /* ADC_H */
