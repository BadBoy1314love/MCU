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

void main()
{
  Relay=1;           //�̵����Ͽ�״̬
	while(1)
	{
		unsigned int a=0; 
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
			for(a=0;a<=30000;a++)          //��ʱ5min������5min�ڼ̵���״̬��Ϊ�պ�
		  {
				Relay=0;
			  Delay10ms();
				if(Infrared_sensor==0)        //5min��ʱ�ڣ������⵽���壬�̵��������պ�5min
				{
					for(a=0;a<=30000;a++)
					{
						Relay=0;
						Delay10ms();
						if(Infrared_sensor==1)     //����������ⲻ������ʱ��ȥP1
						{
							goto P1;
						}
						else if(a==30000)             //��������ⳬ��5minʱ��ȥP1
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

���ϴ����ʱ
void delay30ms(void)   //��� -0.000000000002us
{
    unsigned char a,b,c;
    for(c=3;c>0;c--)
        for(b=212;b>0;b--)
            for(a=140;a>0;a--);
}

void delay50ms(void)   //��� -0.000000000003us
{
    unsigned char a,b,c;
    for(c=123;c>0;c--)
        for(b=116;b>0;b--)
            for(a=9;a>0;a--);
}
*/


/*
֮ǰд��һ���ִ���ο�
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
	Initialize();     //�ϵ��ʼ��
	while(1)
	{
		unsigned int a=0;
		Relay=1;          //�̵�����λ
		P1:
		if(Infrared_sensor1==0)     //������⴫����1��⵽����
		{
			P2:
			Infrared_sensor1=0;                
			Delay100ms();             //���ִ��������Ϊ0����100ms������⵽�������100ms
			Infrared_sensor1=1;       //���ƴ�����1���Ϊ1��ȡ������
			
			if(Infrared_sensor2==0)     //������⴫����2�ܵ��赲
			{
				Infrared_sensor2=0;
				Delay60ms();             //���ִ��������Ϊ0����60ms������Ϊ����������赲��60ms
				Infrared_sensor2=1;      //���ƴ�����2���Ϊ1��ȡ������
				while(1)
				{
					Relay=1;              //��ʼ��������1�봫����2���Լ��̵���
					if(Infrared_sensor2==1)    //���������2û�б��赲��������ѭ��
					{
						break;
					}
				}
			}
			Relay=~Relay;             //�̵���״̬��ת
		  for(a=0;a<=6000;a++)
			{
				Delay50ms();
				if(Infrared_sensor1==0||Infrared_sensor2==0)  //����ʱ���������κ�һ���������ܵ��赲�����˳�
				{
					goto P1;
				}
			}			//�̵����������е����ʱ��5min
		}
		if(Infrared_sensor2==0)     //������⴫����2���ܵ��赲
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