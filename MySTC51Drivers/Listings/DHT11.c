#include "DHT11.h"



u8 COM(u8 * U8comdata)
{
	u8 i;
	u8 U8FLAG,U8temp;
	for(i=0; i<8; i++)
	{

		U8FLAG=2;
		while((!P2_0)&&U8FLAG++);
		delay10us();
		delay10us();

		delay10us();
		U8temp=0;
		if(P2_0)U8temp=1;
		U8FLAG=2;
		while((P2_0)&&U8FLAG++);
		//��ʱ������forѭ��
		if(U8FLAG==1) return 0;
		//�ж�����λ��0����1

		// ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1

		*U8comdata<<=1;
		*U8comdata|=U8temp;        //0
	}//rof
	return 1;
}


u8 DH11_dat[5];
u8 dht11_get_data(u8 *RH, u8 *T)
{
	u8 U8FLAG,U8temp;
	
	//��������18ms
	P2_0=0;
	delay_ms(20);
	P2_0=1;
	//������������������ ������ʱ20us
	delay10us();
	delay10us();
	delay10us();
	delay10us();
	//������Ϊ���� �жϴӻ���Ӧ�ź�
	P2_0=1;
	//�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������
	if(!P2_0)		 //T !
	{
		U8FLAG=2;
		//�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����
		while((!P2_0)&&U8FLAG++);
		U8FLAG=2;
		//�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
		while((P2_0)&&U8FLAG++);
		//���ݽ���״̬
		if(!COM(&(DH11_dat[0]))) return 1;
		if(!COM(&(DH11_dat[1]))) return 2;
		if(!COM(&(DH11_dat[2]))) return 3;
		if(!COM(&(DH11_dat[3]))) return 4;
		if(!COM(&(DH11_dat[4]))) return 5;
		P2_0=1;
		//����У��

		U8temp=(DH11_dat[0]+DH11_dat[1]+DH11_dat[2]+DH11_dat[3]);
		if(U8temp==DH11_dat[4])
		{
			*RH = DH11_dat[0];
			*T = DH11_dat[2];
			return 0;
		}//fi
	}//fi
	return 6;
}
