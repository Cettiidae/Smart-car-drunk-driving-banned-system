#ifndef __ADC_H
#define __ADC_H
extern unsigned int adc_sum;
extern unsigned int adc_num;
extern unsigned int sum_index;
extern unsigned int adc_ave[201];
extern unsigned int adc_value;
extern double adc;

void ADC12_Init(void);

#endif