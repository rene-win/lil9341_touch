#include "ili9341_touch.h"

void Touch::Init()
{	
	CS_HIGH;
	CLK_HIGH;
	DIN_HIGH;
	IRQ_HIGH;
}

void Touch::read()
{
	unsigned long tx=0, temp_x=0;
	unsigned long ty=0, temp_y=0;
	int datacount=0;

	CS_LOW;                 
	pinMode(IRQ_PIN,  INPUT);
	
	for (int i=0; i < 10; i++) {
		if(!IRQ_CHECK) { 
			writeData(0x90);
			CLK_PULSE;		        			
			temp_x=readData();
			if(!IRQ_CHECK) {
				writeData(0xD0);   
				CLK_PULSE;   
				temp_y=readData();
				
				if ((temp_x>0) and (temp_x<4096) and (temp_y>0) and (temp_y<4096)) {
					tx+=temp_x;
					ty+=temp_y;
					datacount++;
				}
			}
		}
	}

	pinMode(IRQ_PIN,  OUTPUT);
	CS_HIGH;	            

	if (datacount == 10) {
		TP_X=tx/datacount;
		TP_Y=ty/datacount;
	} else {
		TP_X=-1;
		TP_Y=-1;
	}
}

bool Touch::dataAvailable()
{
	bool avail;
	pinMode(IRQ_PIN,  INPUT);
	avail = !(IRQ_CHECK);
	pinMode(IRQ_PIN,  OUTPUT);
	return avail;
}

int16_t Touch::getX()
{
	if ((TP_X==-1) or (TP_Y==-1)) return -1;
	long ret = long(long(TP_X - CAL_Y_TOP) * (-MAX_Y)) / long(CAL_Y_BOTTOM - CAL_Y_TOP) + long(MAX_Y);
	ret = constrain(ret, 0, MAX_Y);
	
	return ret;
}

int16_t Touch::getY()
{
	
	if ((TP_X==-1) or (TP_Y==-1)) return -1;
	long ret = long(long(TP_Y - CAL_X_LEFT) * (MAX_X)) / long(CAL_X_RIGTH - CAL_X_LEFT);
	ret = constrain(ret, 0, MAX_X);
	
	return ret;
}

void Touch::writeData(byte data)
{
	byte temp = data;
	CLK_LOW;
	for(byte count=0; count<8; count++)
	{
		if(temp & 0x80) {
			DIN_HIGH;
		} else {
			DIN_LOW;
		}
		temp = temp << 1;
		CLK_LOW;                
		CLK_HIGH;
	}
}

word Touch::readData()
{
	word data = 0;

	for(byte count=0; count<12; count++)
	{
		data <<= 1;
		CLK_PULSE;
		delayMicroseconds(5);
		if (PINC & 0x8)          
			data++;
	}
	return(data);
}

Touch Tch=Touch();
