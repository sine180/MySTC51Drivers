#ifndef __JSON_Parser_H
#define __JSON_Parser_H

/***************************************
           JSON��غ�������
***************************************/
char json_check(char *str); //JSON У�麯��
char json_get_value(char *json,char *json_key , char *json_value); //JSON��ȡ��ֵ
char json_check_value(char *str1, char *str2); //JSON ��ֵ�ԱȺ���



/***************************************
         JSON������ʹ��ʾ������
***************************************/
//    rs = json_check(json);
//    if(rs == 1){
//        printf("json is valid....\r\n");
//    }else{
//        printf("json is invalid....\r\n");
//    }

//    rs =  json_get_value(json,"test_key",&value);
//    if(rs == 1){
//        printf("parser test_key success : %s\r\n",value);
//    }else{
//        printf("parser test_key fail....\r\n");
//    }

#endif
