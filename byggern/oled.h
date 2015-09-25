#ifndef OLED_H_
#define OLED_H_
#define OLED_START_C ((volatile char*)0x1000)
#define OLED_START_D ((volatile char*)0x1200)




void oled_init();
void oled_print(char* input);
void write_c(unsigned char out_data);
void write_d(unsigned char out_data);
void oled_goto(char page, char column );
void oled_clear_page(char page);
void oled_clear_all();
void oled_print_char(char* input);

#endif /* OLED_H_ */