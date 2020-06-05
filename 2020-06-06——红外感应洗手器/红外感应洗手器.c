/*
PXM1：PXM0
 0     0  准双向口（传统IO）
 0     1  推挽输出（强上拉 ，电流可达20mA,尽量少用）
 1     0  仅为输入（高阻）
 1     1  开漏，如传统8051的P0口
 =00--->Standard,    01--->push-pull
 =10--->pure input,  11--->open drain
*/

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

int main(void)
{
	unsigned int ON_T;             //用于存放继电器闭合时间的全局变量
	unsigned int MAX_T=30000;       //用于存放继电器闭合最大时间的全局变量
	
	P1M1=0x00;    // 0000 0000
	P1M0=0x02;    // 0000 0010    将P1^1继电器信号输出端口设置为推挽输出
	
  Relay=1;           //继电器断开状态
	
	while(1)
	{
		
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
			for(ON_T=0;ON_T<=MAX_T;ON_T++)          //延时5min，且在5min内继电器状态都为闭合
		  {
				Relay=0;
			  Delay10ms();
				if(Infrared_sensor==0)        //5min延时内，如果检测到物体，继电器继续保持闭合5min剩余时间 (出水遮挡检测)
				{
					for(;ON_T<=MAX_T;ON_T++)
					{
						Relay=0;
						Delay10ms();
						if(Infrared_sensor==1)     //当传感器检测不到物体时，去P1
						{
							goto P1;
						}
						else if(ON_T==MAX_T)             //当持续检测达到5min剩余时间时，去P1
						{
							goto P1;
						}
					}
				}
		  }
		}
	}
}