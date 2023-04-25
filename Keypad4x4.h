#ifndef __KEYPAD4X4__   
#define __KEYPAD4X4__  

unsigned char check_but();
void scan_row(unsigned char r);
unsigned char check_col();
unsigned char get_key();
void show_button(unsigned char key);
void num_generator(int key, int *OperandPointer);
#endif