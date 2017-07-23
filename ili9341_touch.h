#ifndef ili9341_touch_h
#define ili9341_touch_h

#include "Arduino.h"

//Screen calibration
#define CAL_X_LEFT 250
#define CAL_X_RIGTH 4000
#define CAL_Y_TOP 3900
#define CAL_Y_BOTTOM 200

//resolution
#define MAX_X 239
#define MAX_Y 319

// pins
#define IRQ_PIN A4

// bitmasks
#define CLK_BM 0x01
#define CS_BM 	0x02
#define DIN_BM	0x04
#define DO_BM	0x08
#define IRQ_BM	0x10

// pin states
#define CLK_HIGH 	{DDRC |= CLK_BM;	PORTC |=  CLK_BM;} //A0 0
#define CLK_LOW  	{DDRC |= CLK_BM;	PORTC &=~ CLK_BM;}
#define CS_LOW  	{DDRC |= CS_BM;	PORTC &=~ CS_BM;} //A1 2
#define CS_HIGH 	{DDRC |= CS_BM;	PORTC |=  CS_BM;} 
#define DIN_LOW  	{DDRC |= DIN_BM;	PORTC &=~ DIN_BM;} //A2 4
#define DIN_HIGH 	{DDRC |= DIN_BM;	PORTC |=  DIN_BM;}
#define DO_LOW  	{DDRC |= DO_BM;	PORTC &=~ DO_BM;} //A3 8
#define DO_HIGH   {DDRC |= DO_BM;	PORTC |=  DO_BM;}
#define IRQ_LOW  	{DDRC |= IRQ_BM;	PORTC &=~ IRQ_BM;} //A4 16
#define IRQ_HIGH 	{DDRC |= IRQ_BM;	PORTC |=  IRQ_BM;}

#define CLK_PULSE CLK_HIGH; CLK_LOW;
#define IRQ_CHECK (PINC & IRQ_BM)

class Touch
{
	public:
		int16_t	TP_X ,TP_Y;

		void	Init();
		void	read();
		bool	dataAvailable();
		int16_t	getX();
		int16_t	getY();
    
    private:
		void	writeData(byte data);
		word	readData();

};

extern Touch Tch;

#endif
