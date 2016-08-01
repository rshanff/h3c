/*******************************************************************************
 Copyright (c) 2011, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              info_data.h
  Project Code: Comware V700R001
   Module Name: INFO
  Date Created: 201x-xx-xx
        Author: xxxx 00000
   Description: �ڲ����ݲ���
                ����������ɾ�������á���ȡ������

--------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
  YYYY-MM-DD  

*******************************************************************************/

#ifndef _INFO_DATA_H_
#define _INFO_DATA_H_

#ifdef __cplusplus
extern "C"{
#endif

/*************************************** ���ݲ��� ***************************************/
/* �ж�ָ�����ŵ������Ƿ���� */
BOOL_T INFO_data_IsExist(IN UINT uiId);

/* ��ȡ���� */
ULONG INFO_data_GetData(IN UINT uiId, OUT INFO_CFG_S *pstCfg);

/*************************************** ���� ***************************************/
/* �ж�����������֯�Ƿ�Ϊ�� */
BOOL_T INFO_data_IsEmpty(VOID);

/* ��ȡ"��һ��/��һ��"�����ݹ��� */
UINT INFO_data_GetFirst(VOID);
UINT INFO_data_GetNext(IN UINT uiId);

/* �����ӿ� */
#define INFO_FOREACH(uiId) \
for ((uiId)  = INFO_data_GetFirst(); \
     (uiId) != INFO_ID_INVALID; \
     (uiId)  = INFO_data_GetNext(uiId))

/*************************************** ��ʼ�� ***************************************/
ULONG INFO_data_Init(VOID);
VOID INFO_data_Fini(VOID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _INFO_DATA_H_ */

