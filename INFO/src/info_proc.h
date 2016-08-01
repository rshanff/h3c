/*******************************************************************************
 Copyright (c) 2011, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              info_proc.h
  Project Code: Comware V700R001
   Module Name: INFO
  Date Created: 201x-xx-xx
        Author: xxxx 00000
   Description: ���幦�ܴ���

--------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
  YYYY-MM-DD  

*******************************************************************************/

#ifndef _INFO_PROC_H_
#define _INFO_PROC_H_

#ifdef __cplusplus
extern "C"{
#endif

/*****************************************************************************
    Func Name: INFO_PROC_PF
 Date Created: 2011-12-29
       Author: xxxx 00000
  Description: ���ܴ�����ԭ��
        Input: IN const CHAR *pcInputStr    �����ַ���
       Output: 
       Return: ULONG, ERROR_SUCCESS         ����ɹ�
                      OTHER                 ����ʧ��
      Caution: 1.�����ַ�����ĳЩ���ܴ���ʱ���Ժ���
               2.ʧ��ʱ��Ҫ���ؾ�������룬�����ò�δ�ӡ�û���ʾ��Ϣ
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
typedef ULONG (*INFO_PROC_PF)(IN const CHAR *pcInputStr);

/* "���"��"ɾ��"��"�޸�"��"��ʾ" */
ULONG INFO_proc_Add(IN const CHAR *pcInputStr);
ULONG INFO_proc_Delete(IN const CHAR *pcInputStr);
ULONG INFO_proc_Modify(IN const CHAR *pcInputStr);
ULONG INFO_proc_Display(IN const CHAR *pcInputStr);

/* �˳� */
ULONG INFO_proc_Exit(IN const CHAR *pcInputStr);

/* ���Կ��ز��� */
ULONG INFO_proc_OpenDebug(IN const CHAR *pcInputStr);
ULONG INFO_proc_CloseDebug(IN const CHAR *pcInputStr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _INFO_PROC_H_ */

