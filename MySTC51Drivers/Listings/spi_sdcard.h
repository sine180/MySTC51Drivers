#ifndef __SPI_SDCARD_H
#define __SPI_SDCARD_H
#include "define.h"
#include "delay.h"

#define USE_PETIT_FATFS 1
#define USE_WRITE_DISK 1
sbit SD_MISO = P2^0;
sbit SD_MOSI = P2^1;
sbit SD_SCLK = P2^2;
sbit SD_CS   = P2^3;

// SD������  
#define SD_TYPE_ERR     0X00  
#define SD_TYPE_MMC     0X01  
#define SD_TYPE_V1      0X02  
#define SD_TYPE_V2      0X04  
#define SD_TYPE_V2HC    0X06      
  
// SD������    
#define CMD0    0       //����λ
#define CMD1    1  
#define CMD8    8       //SEND_IF_COND  
#define CMD9    9       //��CSD
#define CMD10   10      //��CID
#define CMD12   12      //
#define CMD16   16      //����SectorSize Ӧ����0x00  
#define CMD17   17      //��sector  
#define CMD18   18      //��Multi sector  
#define CMD23   23      //���ö�sectorд��ǰԤ�Ȳ���N��block  
#define CMD24   24      //дsector  
#define CMD25   25      //дMulti sector  
#define CMD41   41      //Ӧ����0x00  
#define CMD55   55      //Ӧ����0x01  
#define CMD58   58      //��OCR
#define CMD59   59      //ʹ��/��ֹCRC,Ӧ����0x00  
  
  
#define MSD_RESPONSE_NO_ERROR      0x00    //�޴���
#define MSD_IN_IDLE_STATE          0x01    //����״̬
#define MSD_ERASE_RESET            0x02    //��������
#define MSD_ILLEGAL_COMMAND        0x04    //�������
#define MSD_COM_CRC_ERROR          0x08    //CRCͨ�Ŵ���
#define MSD_ERASE_SEQUENCE_ERROR   0x10    //�����������
#define MSD_ADDRESS_ERROR          0x20    //��ַ����
#define MSD_PARAMETER_ERROR        0x40    //��������
#define MSD_RESPONSE_FAILURE       0xFF    //�����������ʧ�ܵģ�û���κ���Ӧ

extern u8  SD_Type;

u8 SD_Initialize(void);

#if USE_PETIT_FATFS
    u8 SD_ReadDisk(u8*buf,u32 sector,u16 offset, u16 count);
    #if USE_WRITE_DISK
        u8 SD_WriteDisk(u8*buf,u32 sector);
    #endif
#else
    u8 SD_ReadDisk(u8*buf,u32 sector,u8 cnt);
    #if USE_WRITE_DISK
        u8 SD_WriteDisk(u8*buf,u32 sector,u8 cnt);
    #endif
#endif

#endif
