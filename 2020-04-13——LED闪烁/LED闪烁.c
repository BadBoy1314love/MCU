#include <STC15.h>
#include <intrins.h>

sbit LED=P1^0;

void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 23;
	j = 205;
	k = 120;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Delay1min()
{
	unsigned int a=0;
	for(a=0;a<=120;a++)
	{
	Delay500ms();
  }
}

void Delay5min()
{
	unsigned int a=0;
	for(a=0;a<=600;a++)
	{
		Delay500ms();
	}
}

void main()
{
	while(1)
	{
		LED=~LED;
		Delay5min();
	}
}