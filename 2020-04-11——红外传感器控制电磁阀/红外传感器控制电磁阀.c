#include <STC15.h>
#include <intrins.h>

/*
sbit Led_Red=P1^0;
*/

sbit Relay=P1^0;
sbit Infrared_sensor=P3^2;

/*
void Delay50ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 3;
	j = 72;
	k = 161;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay1000ms()		//@12.000MHz
{

	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 46;
	j = 153;
	k = 245;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay5000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 228;
	j = 253;
	k = 219;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
*/


void Initialize()
{
	Relay=1;
	Infrared_sensor=1; 
}
/*
if(k%2==1)
		{
			Relay=0;
		}
		else if(k%2==0)
		{
			Relay=1;
			k=0;
		}
*/
void main()
{
	unsigned int k=0;
  Initialize();
	while(1)
	{
		if(Infrared_sensor==0)
		{
			k++;
		}
	//	while(Infrared_sensor);
		switch(k)
			{
			case 1:Relay=0;break;
			case 2:Relay=1;k=0;break;
			}
	}
}