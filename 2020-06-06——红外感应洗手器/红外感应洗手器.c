/*
PXM1��PXM0
 0     0  ׼˫��ڣ���ͳIO��
 0     1  ���������ǿ���� �������ɴ�20mA,�������ã�
 1     0  ��Ϊ���루���裩
 1     1  ��©���紫ͳ8051��P0��
 =00--->Standard,    01--->push-pull
 =10--->pure input,  11--->open drain
*/

#include <STC15.h>
#include <intrins.h>

sbit Relay=P1^1;              //�̵���  ���ڼ�ӿ��Ƶ�ŷ�
sbit Infrared_sensor=P1^2;   //���⴫����  ���ڿ��Ƽ̵����Ŀ�����ر�

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
	unsigned int ON_T;             //���ڴ�ż̵����պ�ʱ���ȫ�ֱ���
	unsigned int MAX_T=30000;       //���ڴ�ż̵����պ����ʱ���ȫ�ֱ���
	
	P1M1=0x00;    // 0000 0000
	P1M0=0x02;    // 0000 0010    ��P1^1�̵����ź�����˿�����Ϊ�������
	
  Relay=1;           //�̵����Ͽ�״̬
	
	while(1)
	{
		
		P1:
		Relay=1;           //�̵����Ͽ�״̬
		if(Infrared_sensor==0)         //�����������⵽����
		{
			while(1)                     //�̵��������Ͽ���ֱ����������ⲻ�����壬ȥP2
			{
				Relay=1;
				if(Infrared_sensor==1)          
				{
					goto P2;
				}	
			}
			
			P2:
			for(ON_T=0;ON_T<=MAX_T;ON_T++)          //��ʱ5min������5min�ڼ̵���״̬��Ϊ�պ�
		  {
				Relay=0;
			  Delay10ms();
				if(Infrared_sensor==0)        //5min��ʱ�ڣ������⵽���壬�̵����������ֱպ�5minʣ��ʱ�� (��ˮ�ڵ����)
				{
					for(;ON_T<=MAX_T;ON_T++)
					{
						Relay=0;
						Delay10ms();
						if(Infrared_sensor==1)     //����������ⲻ������ʱ��ȥP1
						{
							goto P1;
						}
						else if(ON_T==MAX_T)             //���������ﵽ5minʣ��ʱ��ʱ��ȥP1
						{
							goto P1;
						}
					}
				}
		  }
		}
	}
}