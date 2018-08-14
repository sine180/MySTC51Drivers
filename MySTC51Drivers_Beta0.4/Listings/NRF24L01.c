#include"define.h"
#include"DELAY.h"
#include"NRF24L01.h"

uchar code TX_ADDRESS[5] = {0,0,0,0,1}; 	//������ַ
uchar code RX_ADDRESS_P0[5] = {0,0,0,0,1};//�ӻ�0��ַ
uchar code RX_ADDRESS_P1[5] = {1,1,1,1,1};//�ӻ�1��ַ
uchar code RX_ADDRESS_P2[1] = {2};        //�ӻ�2��ַ
uchar code RX_ADDRESS_P3[1] = {3};        //�ӻ�3��ַ
uchar code RX_ADDRESS_P4[1] = {4};        //�ӻ�4��ַ
uchar code RX_ADDRESS_P5[1] = {5};        //�ӻ�5��ַ
#define Data_width  1 //���ݳ���
#define Data_rt  15   //�Զ��ط�����

/**/
uchar SPI_RW(uchar dat)		 //	SPI��дָ��
{
	uchar i;
	for(i=0;i<8;i++)
	{
		SCK = 0;
		MOSI = (dat&0x80);
		dat <<= 1;
		SCK = 1;
		dat |= MISO; 
	}
	SCK = 0;
	return dat;
}
uchar NRF24L01_read_reg(uchar reg)	//��ĳ���Ĵ�����״̬
{
	uchar value;
	CSN=0;					 //����CSN���������
  	SPI_RW(reg);	 		 //д�Ĵ���ָ��
	value = SPI_RW(0);		 //���Ĵ���ֵ
	CSN=1;					 //����CSN����ֹ����
	return value;			 //���ؼĴ���״̬
}
uchar NRF24L01_write_reg(uchar reg,uchar value)	  //д��ĳ���Ĵ���дָ�������״̬
{
	uchar status;
	CSN=0;					//����CSN���������
  	status = SPI_RW(reg);	//д�Ĵ���ָ��������Ĵ���״̬
	SPI_RW(value);			//д�Ĵ���ֵ
	CSN=1;					//����CSN����ֹ����
	return status;			//���ؼĴ���֮ǰ��ֵ
}
uchar NRF24L01_read_buf(uchar reg,uchar *pbuf,uchar n)
{
   	uchar i,status;
   	CSN=0;					//����CSN���������
   	status = SPI_RW(reg);	//д�Ĵ���ָ��������Ĵ���״̬
	for(i=0;i<n;i++)
		pbuf[i] = SPI_RW(0);//�ӼĴ�������һ�ֽ�����
	CSN = 1;				//����CSN����ֹ����
	return status;
}
uchar NRF24L01_write_buf(uchar reg,uchar *pbuf,uchar n)
{
   	uchar i,status;
   	CSN=0;					//����CSN���������
   	status = SPI_RW(reg);	//д�Ĵ���ָ��������Ĵ���״̬
	for(i=0;i<n;i++)
		SPI_RW(pbuf[i]);	//дһ�ֽ����ݵ��Ĵ���
	CSN = 1;				//����CSN����ֹ����
	return status;
} 

void NRF24L01_init()
{
	CE = 0;		   //��Ƶ��·����ʹ�ܣ��ߵ�ƽ�������͵�ƽֹͣ
	CSN = 1;	   //SPI�����ߵ�ƽ�����͵�ƽ��ֹ
	SCK = 0;	   //ʱ�����ͣ���ֹ��д�Ĵ���
	IRQ = 1;	   //�жϸ�λ���ȴ������ж��ź�
	NRF24L01_write_reg(WRITE_REG + EN_AA, 0x3f);	 			//���н���ͨ�������Զ�Ӧ��
	NRF24L01_write_reg(WRITE_REG + EN_RXADDR, 0x3f);	 		//����ͨ��ȫ����
	NRF24L01_write_reg(WRITE_REG + SETUP_AW, 0x03);	 			//���ý���/�����ַ���Ϊ5�ֽ�
	NRF24L01_write_reg(WRITE_REG + SETUP_RETR, Data_rt);		//�Զ����ͼ��250+86us������15
	NRF24L01_write_reg(WRITE_REG + RF_CH, 0x00);		 		//�����ŵ�����Ϊ2.4Ghz���շ�����һ��
	NRF24L01_write_reg(WRITE_REG + RX_PW_P0, Data_width);		//����ͨ��0�����ֽ���
	NRF24L01_write_reg(WRITE_REG + RX_PW_P1, Data_width);		//����ͨ��1�����ֽ���
	NRF24L01_write_reg(WRITE_REG + RX_PW_P2, Data_width);		//����ͨ��2�����ֽ���
	NRF24L01_write_reg(WRITE_REG + RX_PW_P3, Data_width);		//����ͨ��3�����ֽ���
	NRF24L01_write_reg(WRITE_REG + RX_PW_P4, Data_width);		//����ͨ��4�����ֽ���
	NRF24L01_write_reg(WRITE_REG + RX_PW_P5, Data_width);		//����ͨ��5�����ֽ���
	NRF24L01_write_reg(WRITE_REG + RF_SETUP, 0x0f);	 			//��������Ϊ1Mhz�����͹������ֵ0db
	NRF24L01_write_buf(WRITE_REG + TX_ADDR,TX_ADDRESS,5);		//д�����ص�ַ
	NRF24L01_write_buf(WRITE_REG + RX_ADDR_P0,RX_ADDRESS_P0,5);	//д����ͨ��0���ջ���ַ
	NRF24L01_write_buf(WRITE_REG + RX_ADDR_P1,RX_ADDRESS_P1,5);	//д����ͨ��1���ջ���ַ
	NRF24L01_write_buf(WRITE_REG + RX_ADDR_P2,RX_ADDRESS_P2,1); //д����ͨ��2���ջ���ַ
	NRF24L01_write_buf(WRITE_REG + RX_ADDR_P3,RX_ADDRESS_P3,1); //д����ͨ��3���ջ���ַ
	NRF24L01_write_buf(WRITE_REG + RX_ADDR_P4,RX_ADDRESS_P4,1); //д����ͨ��4���ջ���ַ
	NRF24L01_write_buf(WRITE_REG + RX_ADDR_P5,RX_ADDRESS_P5,1); //д����ͨ��5���ջ���ַ
} 
void RX_MODE()
{
	NRF24L01_write_reg(WRITE_REG + CONFIG, 0x0f);//IRQ�շ�����ж���Ӧ��16λCRC������ģʽ  
	CE = 1;
}
void TX_MODE()
{
	NRF24L01_write_reg(WRITE_REG + CONFIG, 0x0e);//IRQ�շ�����ж���Ӧ��16λCRC������ģʽ
	CE = 1;
}
uchar TX_packet(uchar *tx_buf)
{
	uchar tx_flag = 1;
 	CE = 0;	//ֹͣ��Ƶ��·����
	NRF24L01_write_reg(WRITE_REG + STATUS,0xff);			//����жϱ�־λ	
	NRF24L01_write_buf(WR_TX_PLOAD,tx_buf,Data_width);		//װ��Ҫ���͵�����
	CE = 1;	//�ø�CE���������ݷ���
	delay_ms(Data_rt/2);   
	if(NRF24L01_read_reg(STATUS)&0x10)
		tx_flag = 0;
	return(tx_flag);	 
}
uchar RX_packet(uchar *rx_buf)
{
   	uchar revalue = 0,sta;
	sta = NRF24L01_read_reg(STATUS);	  	//��״̬�Ĵ���
	if(sta&0x40) 	//��������жϱ�־λΪ1
	{
		CE = 0;										   	//SPIʹ��
	 	NRF24L01_read_buf(RD_RX_PLOAD,rx_buf,Data_width);	//��ȡ����
		revalue = 1;								   	//��ȡ������ɱ�־��1	
		NRF24L01_write_reg(WRITE_REG + STATUS,0xff);	//����жϱ�־λ	
	}
	CE = 1;
	return revalue;//���ض�ȡ������ɱ�־
}