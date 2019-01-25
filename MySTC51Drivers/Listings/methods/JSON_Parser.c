#include "JSON_Parser.h"

/***************************************
         һЩϵͳ�����ļ�ʵ��
 ***************************************/
 
int my_strlen(char *string)
{
    int len = 0;
    while (*string != '\0') {
        string++;
        len++;
    }
    return len;
}
 
const char *my_strstr(const char *str, const char *sub_str)
{
    int i;
    for( i = 0; str[i] != '\0'; i++)
    {
        int tem = i; //tem���������е���ʼ�ж��±�λ��
        int j = 0;
        while(str[i++] == sub_str[j++])
        {
            if(sub_str[j] == '\0')
            {
                return &str[tem];
            }
        }
        i = tem;
    }
    
    return "";
}
 
 
char* my_strncpy(char* dest, const char* src, int len)
{
    
    char* temp=dest;
    int i=0;
    while(i++ < len  && (*temp++ = *src++)!='\0')
    {
        
    }
    if(*(temp)!='\0')     *temp='\0';
    return dest;
    
}
 
int my_strcmp(char* str1, char* str2){
   while(*str1 && *str2 && *str1==*str2)
   {
    ++str1;
     ++str2;
   }
   return *str1-*str2;
}




/***************************************
 name:       JSON У�麯��
 input:      �ַ���
 output:     �Ϸ�JAON ����1 ���Ϸ�JSON ����0
 description:
 ***************************************/
 
char json_check(char *str)
{
    char str_length; //�����ַ����ȱ���
    str_length = my_strlen(str); //�����ַ�����
    if(str[0] == '{' && str[str_length-1] == '}') //ͨ����β�������ж��Ƿ�ΪJSON
    {
        return 1; //����ַ���Ϊ�Ϸ�JSON ����1
    }
    else
    {
        return 0; //����ַ���Ϊ�Ϸ�JSON ����0
    }
}
 
 
 
/***************************************
 name:       JSON ��ȡ��ֵ����
 input:      JSON�ַ��� Ҫ��ȡ�ļ��� ��ȡ��ֵ���ַ���
 output:     �����ȡ�ɹ�����1 ��ȡʧ�ܷ���0
 description:
 ***************************************/
 
char json_get_value(char *json,char *json_key , char *json_value)
{
    
    char *json_key_start; //���������ʼ��λ��
    char *json_key_end; //�������������λ��
    char json_key_length; //�����������
    
    char *json_value_start; //�����ֵ��ʼ��λ��
    char *json_value_end; //�����ֵ������λ��
    char json_value_length; //�����ֵ����
    
    json_key_start = my_strstr(json,json_key); //��ȡ������ʼ��λ��
    json_key_length = my_strlen(json_key); //��ȡ�����ĳ���
    
    
    json_key_end = json_key_start + json_key_length;  //��ȡ����������λ��
    
    
    if(json_key_start != 0 && *(json_key_start - 1) == '\"' && *(json_key_end) == '\"' && *(json_key_end + 1) == ':' && *(json_key_end + 2) == '\"' )
        
    {
        json_value_start = json_key_end + 3; //��ȡ��ֵ��ʼ��λ��
        json_value_end = my_strstr(json_value_start,"\""); //��ȡ��ֵ������λ��
        json_value_length = json_value_end - json_value_start; //��ȡ��ֵ�ĳ���
        
        my_strncpy(json_value,json_value_start,json_value_length); //����ֵ����ָ������
        
        json_value[json_value_length] = '\0'; //ָ�����һλ���ַ��������� \0
        
        return 1; //�ɹ���ȡ��ֵ ����1
    }
    else
    {
        json_value[0] = '\0';
        return 0; //ʧ�ܻ�ȡ��ֵ ����0
    }
}
 
 
 
/***************************************
 name:       JSON ��ֵ�ԱȺ���
 input:      JSON ��ֵ Ҫƥ����ַ�
 output:     ���ƥ��ɹ�����1 ʧ�ܷ���0
 description:
 ***************************************/
 
char json_check_value(char *str1, char *str2)
{
    if(my_strcmp(str1,str2) == 0)
    {
        return 1; //ƥ��ɹ�����1
    }
    else
    {
        return 0;//ƥ��ɹ�����0
    }
}
 