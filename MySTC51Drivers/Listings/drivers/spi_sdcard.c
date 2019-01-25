#include "spi_sdcard.h"
#include "uart.h"

//Ԥ����SD������ 
u8  SD_Type=0;

void spi_init()
{
    SD_CS = 1;
    SD_SCLK = 1;
    SD_MOSI = 1;
    SD_MISO = 1;
    delay_ms(1);
}
void spi_write(u8 sddat)
{
	u8 i;
	for(i=8; i; i--)
	{
		SD_SCLK = 0;
        delay5us();
		SD_MOSI = (sddat & 0x80);
		sddat <<= 1;
		SD_SCLK = 1;
        delay5us();
	}
	SD_MOSI = 1; 	
}

u8 spi_read(void)
{
	u8 Byte;
	u8 cnt;
	for(cnt=8; cnt; cnt--)
	{
		SD_SCLK = 0; 
        delay5us();        
		SD_SCLK = 1;
		Byte <<= 1;
		if(SD_MISO) 
            Byte++;
        delay5us(); 
	}
	return Byte;	
}

static u8 SD_WaitReady(void)  
{  
    u32 t=0;  
    do  
    {  
        if(spi_read()==0XFF)return 0;//OK  
        t++;        
    }while(t<0XFFFFFFFF);//�ȴ�
    return 1;  
}  

void SD_DisSelect(void)
{
    SD_CS=1;  
    spi_read(); 
}

u8 SD_Select(void)  
{  
    SD_CS=0;  
    if(SD_WaitReady()==0)return 0;//�ȴ��ɹ�
    SD_DisSelect();  
    return 1;//�ȴ�ʧ��
}  

u8 SD_SendCmd(u8 cmd, u32 arg, u8 crc)  
{  
    u8 r1;    
    u8 Retry=0;   
    SD_DisSelect();//ȡ���ϴ�Ƭѡ
    if(cmd!=CMD0){   
        if(SD_Select())return 0XFF;//Ƭѡʧ��   �Ӵ����Ϊ�β��ɹ�
    }
    SD_CS = 0;
    //����
    spi_write(cmd | 0x40);//�ֱ�д������
    spi_write(arg >> 24);  
    spi_write(arg >> 16);  
    spi_write(arg >> 8);  
    spi_write(arg);        
    spi_write(crc);
    
    if(cmd==CMD12)spi_read();//Skip a stuff byte when stop reading  
    //�ȴ���Ӧ��ʱ�˳�
    Retry=0X1F;  
    do  
    {  
        r1=spi_read();  
    }while((r1&0X80) && Retry--);      
    //����״ֵ̬ 
    return r1;      
}

u8 SD_GetResponse(u8 Response)  
{  
    u16 Count=0xFFF;//�ȴ�����                              
    while ((spi_read()!=Response)&&Count)Count--;//�ȴ��õ�׼ȷ�Ļ�Ӧ       
    if (Count==0)return MSD_RESPONSE_FAILURE;//�õ�ʧ�ܵĻ�Ӧ     
    else return MSD_RESPONSE_NO_ERROR;//��ȷ��Ӧ
}  

u8 SD_Initialize(void)
{
    u16 i;
    u16 retry;
    u8 buf[4];
    u8 r1;
    
    spi_init();
    for(i=0;i<10;i++)spi_read(); //��������74������
    retry =20;
    do
    {
        r1 = SD_SendCmd(CMD0,0,0x95);
    }while((r1 != 0x01) && retry--);
    SD_Type=0;
    if(r1 == 0x01)
    {
        if(SD_SendCmd(CMD8,0x1AA,0x87)==1)//SD V2.0
        {  
            for(i=0;i<4;i++)buf[i]=spi_read(); //Get trailing return value of R7 resp
            if(buf[2]==0X01&&buf[3]==0XAA)//���Ƿ�֧��2.7~3.6V
            {  
                retry=0XFFFE;
                do  
                {  
                    SD_SendCmd(CMD55,0,0X01);    //����CMD55
                    r1=SD_SendCmd(CMD41,0x40000000,0X01);//����CMD41
                }while(r1&&retry--);  
                if(retry&&SD_SendCmd(CMD58,0,0X01)==0)//����SD2.0�汾��ʼ
                {  
                    for(i=0;i<4;i++)buf[i]=spi_read();//�õ�OCRֵ
                    if(buf[0]&0x40)SD_Type=SD_TYPE_V2HC;    //���CCS
                    else SD_Type=SD_TYPE_V2;     
                }  
            }  
        }else//SD V1.x/ MMC V3  
        {  
            SD_SendCmd(CMD55,0,0X01);        //����CMD55  
            r1=SD_SendCmd(CMD41,0,0X01); //����CMD41  
            if(r1<=1)  
            {         
                SD_Type=SD_TYPE_V1;  
                retry=0XFFFE;  
                do //�ȴ��˳�IDLEģʽ
                {  
                    SD_SendCmd(CMD55,0,0X01);    //����CMD55  
                    r1=SD_SendCmd(CMD41,0,0X01);//����CMD41  
                }while(r1&&retry--);  
            }else  
            {  
                SD_Type=SD_TYPE_MMC;//MMC V3  
                retry=0XFFFE;  
                do //�ȴ��˳�IDLEģʽ 
                {                                                 
                    r1=SD_SendCmd(CMD1,0,0X01);//����CMD1  
                }while(r1&&retry--);    
            }  
            if(retry==0||SD_SendCmd(CMD16,512,0X01)!=0)SD_Type=SD_TYPE_ERR;//����Ŀ�
        }
    }
    SD_DisSelect();//ȡ��Ƭѡ
    if(SD_Type)return 0;  
    else if(r1)return r1;        
    return 0xaa;//��������
}

#if USE_PETIT_FATFS == 0
u8 SD_RecvData(u8*buf,u16 len)  
{                   
    if(SD_GetResponse(0xFE))return 1;//�ȴ�SD������������ʼ����0xFE  
    while(len--)//��ʼ��������  
    {  
        *buf=spi_read();  
        buf++;  
    }  
    //��������αCRC(dummy CRC)  
    spi_read();  
    spi_read();                                                             
    return 0;//��ȡ�ɹ�
}  

u8 SD_ReadDisk(u8*buf,u32 sector,u8 cnt)  
{  
    u8 r1;  
    if(SD_Type!=SD_TYPE_V2HC)sector <<= 9;//ת��Ϊ�ֽڵ�ַ
    if(cnt==1)  
    {  
        r1=SD_SendCmd(CMD17,sector,0X01);//������ 
        if(r1==0)//ָ��ͳɹ�
        {  
            r1=SD_RecvData(buf,512);//����512���ֽ�   
        }  
    }else  
    {  
        r1=SD_SendCmd(CMD18,sector,0X01);//����������
        do  
        {  
            r1=SD_RecvData(buf,512);//����512�ֽ�      
            buf+=512;    
        }while(--cnt && r1==0);       
        SD_SendCmd(CMD12,0,0X01);    //����ֹͣ����
    }     
    SD_DisSelect();//ȡ��Ƭѡ
    return r1;//  
}
#if USE_WRITE_DISK

u8 SD_SendBlock(u8*buf,u8 cmd)  
{     
    u16 t;              
    if(SD_WaitReady())return 1;//�ȴ�׼��ʧЧ
    spi_write(cmd);  
    if(cmd!=0XFD)//���ǽ���ָ��
    {  
        for(t=0;t<512;t++)spi_write(buf[t]);//
        spi_read();//����crc  
        spi_read();  
        t=spi_read();//������Ӧ  
        if((t&0x1F)!=0x05)return 2;//��Ӧ����                                                     
    }                                                                                     
    return 0;//д��ɹ�
} 

u8 SD_WriteDisk(u8*buf,u32 sector,u8 cnt)  
{  
    u8 r1;  
    if(SD_Type!=SD_TYPE_V2HC)sector *= 512;//ת��Ϊ�ֽڵ�ַ  
    if(cnt==1)  
    {  
        r1=SD_SendCmd(CMD24,sector,0X01);//д����
        if(r1==0)
        {  
            r1=SD_SendBlock(buf,0xFE);//д512�ֽ�     
        }  
    }else  
    {  
        if(SD_Type!=SD_TYPE_MMC)  
        {  
            SD_SendCmd(CMD55,0,0X01);      
            SD_SendCmd(CMD23,cnt,0X01);//����ָ��
        }  
        r1=SD_SendCmd(CMD25,sector,0X01);//����д����
        if(r1==0)  
        {  
            do  
            {  
                r1=SD_SendBlock(buf,0xFC);//д512�ֽ�    
                buf+=512;    
            }while(--cnt && r1==0);  
            r1=SD_SendBlock(0,0xFD);//д512�ֽڽ���  
        }  
    }     
    SD_DisSelect();//ȡ��Ƭѡ
    return r1;//  
} 
#endif
#else
u8 SD_RecvData(u8*buf,u16 offset, u16 count)  
{       
    u16 i=512-offset-count;
    if(SD_GetResponse(0xFE))return 1;//�ȴ�SD������������ʼ����0xFE  
    while(offset--)//��ʼ����ǰ������
    {  
        spi_read();  
    }
    while(count--)//��ʼ��������  
    {  
        *buf=spi_read();  
        buf++;  
    }
    while(i--)//��ʼ���պ�����
    {  
        spi_read();  
    }    
    //��������αCRC(dummy CRC)  
    spi_read();  
    spi_read();                                                             
    return 0;//��ȡ�ɹ�
}  

u8 SD_ReadDisk(u8*buf,u32 sector,u16 offset, u16 count)  
{  
    u8 r1;  
    if(offset+count>512) return 3;
    if(SD_Type!=SD_TYPE_V2HC)sector <<= 9;//ת��Ϊ�ֽڵ�ַ
    
    r1=SD_SendCmd(CMD17,sector,0X01);//������ 
    if(r1==0)//ָ��ͳɹ�
    {  
        r1=SD_RecvData(buf,offset,count);//����512���ֽ�   
    }  
    
    SD_DisSelect();//ȡ��Ƭѡ
    return r1;//  
}  

#if USE_WRITE_DISK
u8 SD_SendBlock(u8*buf,u16 count)  
{     
    u16 t;              
    for(t=0;t<count;t++)spi_write(buf[t]);//                                                                               
    return 0;//д��ɹ�
}  

u8 SD_WriteDisk(u8*buf,u32 sector)  
{  
    u8 r1=0; 
    u16 t;
    static u32 count=0;
    if (!buf) {
		if (sector) {
			// Initiate write process
            if(SD_Type!=SD_TYPE_V2HC)sector *= 512;//ת��Ϊ�ֽڵ�ַ  
            r1=SD_SendCmd(CMD24,sector,0X01);//д����
            if(r1 == 0)
            {
                if(SD_WaitReady())return 1;//�ȴ�׼��ʧЧ
                spi_write(0xFE);  //��ʼ����
            }
            count=0;
		} else {
			// Finalize write process
            for(t=0;t<512-count;t++)spi_write(0);//  
            spi_read();//����crc  
            spi_read();  
            r1=spi_read();//������Ӧ  
            if((r1&0x1F)!=0x05) r1 = 2;//��Ӧ����   
            else r1 = 0;
            SD_DisSelect();//ȡ��Ƭѡ
		}
	} else {
		// Send data to the disk
        count+=sector;
        if(count > 512) 
        {
            count-=sector;
            sector = 512 - count;
            count = 512;
        }
        r1=SD_SendBlock(buf,sector);//дsector���ֽ�     
	}        
    return r1;//  
} 
#endif
#endif