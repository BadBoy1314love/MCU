#include <STC15.h>
#include <intrins.h>

sbit Relay=P1^1;              //继电器  用于间接控制电磁阀
sbit Infrared_sensor=P1^2;   //红外传感器  用于控制继电器的开启与关闭

void Delay10ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 117;
	j = 184;
	do
	{
		while (--j);
	} while (--i);
}

void main()
{
  Relay=1;           //继电器断开状态
	while(1)
	{
		unsigned int a=0; 
		P1:
		Relay=1;           //继电器断开状态
		if(Infrared_sensor==0)         //如果传感器检测到物体
		{
			while(1)                     //继电器持续断开，直到传感器检测不到物体，去P2
			{
				Relay=1;
				if(Infrared_sensor==1)          
				{
					goto P2;
				}	
			}
			
			P2:
			for(a=0;a<=30000;a++)          //延时5min，且在5min内继电器状态都为闭合
		  {
				Relay=0;
			  Delay10ms();
				if(Infrared_sensor==0)        //5min延时内，如果检测到物体，继电器持续闭合5min
				{
					for(a=0;a<=30000;a++)
					{
						Relay=0;
						Delay10ms();
						if(Infrared_sensor==1)     //当传感器检测不到物体时，去P1
						{
							goto P1;
						}
						else if(a==30000)             //当持续检测超过5min时，去P1
						{
							goto P1;
						}
					}
				}
		  }
		}
	}
}


/*
void delay30ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 2;
	j = 95;
	k = 43;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void delay50ms()		//@12.000MHz
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
*/

/*
void Delay60ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 3;
	j = 189;
	k = 92;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay100ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 144;
	k = 71;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}



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
*/
	

/*

误差较大的延时
void delay30ms(void)   //误差 -0.000000000002us
{
    unsigned char a,b,c;
    for(c=3;c>0;c--)
        for(b=212;b>0;b--)
            for(a=140;a>0;a--);
}

void delay50ms(void)   //误差 -0.000000000003us
{
    unsigned char a,b,c;
    for(c=123;c>0;c--)
        for(b=116;b>0;b--)
            for(a=9;a>0;a--);
}
*/


/*
之前写的一部分代码参考
void main()
{
	Initialize();
	while(1)
	{
		if(Infrared_sensor==0)
		{
			Infrared_sensor=0;
			delay50ms();
			Infrared_sensor=1;
			Relay=~Relay;
		}
	  while(Infrared_sensor);
	}
}




void main()
{
	Initialize();     //上电初始化
	while(1)
	{
		unsigned int a=0;
		Relay=1;          //继电器复位
		P1:
		if(Infrared_sensor1==0)     //如果红外传感器1检测到物体
		{
			P2:
			Infrared_sensor1=0;                
			Delay100ms();             //保持传感器输出为0持续100ms，即检测到物体持续100ms
			Infrared_sensor1=1;       //控制传感器1输出为1，取消保持
			
			if(Infrared_sensor2==0)     //如果红外传感器2受到阻挡
			{
				Infrared_sensor2=0;
				Delay60ms();             //保持传感器输出为0持续60ms，即认为有物体持续阻挡了60ms
				Infrared_sensor2=1;      //控制传感器2输出为1，取消保持
				while(1)
				{
					Relay=1;              //初始化传感器1与传感器2与以及继电器
					if(Infrared_sensor2==1)    //如果传感器2没有被阻挡，则跳出循环
					{
						break;
					}
				}
			}
			Relay=~Relay;             //继电器状态翻转
		  for(a=0;a<=6000;a++)
			{
				Delay50ms();
				if(Infrared_sensor1==0||Infrared_sensor2==0)  //在延时过程中有任何一个传感器受到阻挡即刻退出
				{
					goto P1;
				}
			}			//继电器持续运行的最大时间5min
		}
		if(Infrared_sensor2==0)     //如果红外传感器2先受到阻挡
		{
			goto P2;
		}
	}
}
*/


/*
void main()
{
	Initialize();
	while(1)
	{
		unsigned int a=0; 
		Initialize();
		if(Infrared_sensor1==0)
		{
			while(1)
			{
				Relay=1;
				if(Infrared_sensor1==1)
				{
					Relay=0;
				}
				break;
			}
			
			for(a=0;a<=6000;a++)
		  {
			Delay50ms();
			if(Infrared_sensor1==0)
			{
				Relay=1;
				break;
			}
			while(!Infrared_sensor1);
		  }
		}
	}
	
}

*/