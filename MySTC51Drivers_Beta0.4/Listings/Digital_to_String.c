#include "Digital_to_String.h"
void Str_add(char* str,char* str_end)  //�����ַ���
{
  u8 i=0,j=0;
	while(str[i]!='\0')     
	{
		i++;
	}	
	while(str_end[j]!='\0')     
	{
		str[i] = str_end[j];
		i++;
		j++;
	}
	str[i]  = '\0';	
}
void Str_reversal(char* str)     //�ߵ��ַ���
{
   u8 i=0,j=0;
	char temp;
	 while(str[j]!='\0')
		 j++;
	 if(j>0)
		j--;
	 while(j>i)
	 {
		 temp=str[i];
		 str[i]=str[j];
		 str[j]=temp;
		 i++;
		 j--;
	 }	  
}
void transform_int(unsigned long num,char* str) //����ת�ַ�����������
{
	u8 i,j;
	 if(num==0)
	{
		str[0]= '0';        	
		str[1]='\0';
	}
	else
	{	
		for(i=0;num>0;i++)    
		{                         
			j=num%10;           
			num=num/10;     
			str[i]= j+0x30;       
		}                         								
		str[i]= '\0';           
	}
}
void transform_dec(unsigned long num,char* str) //����ת�ַ�����С����
{
	int i,j;
	 if(num==0)
	{
		str[0]= '0';        	
		str[1]='\0';
	}
	else
	{	
		for(i=8;i>=0;i--)    
		{                         
			j=num%10;           
			num=num/10;     
			str[i]= j+0x30;       
		}
		str[9]= '\0';           
	}
}
char* digital_to_string(double num,uchar range)
{
	static char inte[11],deci[10],resrlt[22];
	code const char err[]="ERROR!";	
	double dec;   //С�������ݴ�
	char sign='+';  //+-����
	u8 i;//��ʱ����
	 
	
	//��� 4294967295(���ڸ����������������4294967168������4294967295)
	unsigned long integer=0,decimal=0;
		
  /*********�Ѹ��������������ֺ�С�����ֱַ𱣴浽����u32������************/
	
	if(num>=0)                       //������������
	{	                              //
		integer=(unsigned long)num;   //
		dec=(num-integer);            //
	}                               //
	else                            //
	{	                              //
		sign = '-';	                  //��������λ
		integer=(unsigned long)-num;  //
		dec=-(num+integer);           //
	}	                              //

	for(i=0;i<9;i++)            		//����С������
		  dec*=10;                    //
	decimal=(unsigned long)dec;     //

	if (integer>=4294967295)        //���ȡֵ��Χ
		return err;                   //���ش��󾯸�
	
	if(range>9)                     //��龫���Ƿ����Ҫ��
		range = 9;                    //�������޸�Ϊ��󾫶�
	

	/************************ת�����ַ���*****************************/
	
	inte[0]='\0';             //��������ַ���
	deci[0]='\0';             //
	resrlt[0]='\0';           //
	
	transform_int(integer,inte);  //��������ת�����ַ������ߵ��ģ�������Ϊʲô�Լ����
	Str_reversal(inte);       		//��ת���������ַ���
  transform_dec(decimal,deci);  //С������ת�����ַ���	

	
	deci[range]='\0';         //����С������
	
	if(sign=='-')             //�����ַ���
		Str_add(resrlt,"-");    //����λ
	Str_add(resrlt,inte);     //��������
	if(range>0)               //�������Ϊ0������ȥС������
	{
		Str_add(resrlt,".");    //С����
		Str_add(resrlt,deci);   //С������
	}
	
	return resrlt;            //�����ַ���ָ��
}