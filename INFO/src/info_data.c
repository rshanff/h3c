/*******************************************************************************
 Copyright (c) 2011, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              info_data.c
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

#ifdef __cplusplus
extern "C"{
#endif

/* standard library */
#include <stdlib.h>

/* system   public  */
#include <sys/basetype.h>
#include <sys/error.h>
#include <sys/assert.h>
#include <sys/list.h>

/* module   private */
#include "info.h"

/* ��Ϣ���ݽṹ */
typedef struct tagInfo_Data
{
                            /* ������֯���[*] */
    INFO_CFG_S stCfg;       /* �������� */
}INFO_DATA_S;

/* the head point of pstCfg*/
INFO_CFG_S* pstCfghead = NULL;

/*****************************************************************************
    Func Name: INFO_data_IsExist[*]
 Date Created: 201x-xx-xx
       Author: xxxx 00000
  Description: �ж�ָ�����ŵ������Ƿ����
        Input: IN UINT uiId         ����
       Output:
       Return: BOOL_T, BOOL_TRUE    ����
                       BOOL_FALSE   ������
      Caution:
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
BOOL_T INFO_data_IsExist(IN UINT uiId)
{
    INFO_CFG_S* pstCfgtemp = pstCfghead;
    for( ; pstCfgtemp != NULL; pstCfgtemp = pstCfgtemp->pstCfgnext )
    {
        if(pstCfgtemp->uiId == uiId)
        {
            return BOOL_TRUE;
        }
    }
    return BOOL_FALSE;
}

/*****************************************************************************
    Func Name: INFO_data_IsEmpty[*]
 Date Created: 201x-xx-xx
       Author: xxxx 00000
  Description: �ж�����������֯�Ƿ�Ϊ��
        Input:
       Output:
       Return: BOOL_T, BOOL_TRUE    ������֯Ϊ��
                       BOOL_FALSE   ������֯�ǿ�
      Caution:
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
BOOL_T INFO_data_IsEmpty(VOID)
{
    if(pstCfghead == NULL)
        return BOOL_TRUE;
    return BOOL_FALSE;
}

/*****************************************************************************
    Func Name: INFO_data_GetData[*]
 Date Created: 201x-xx-xx
       Author: xxxx 00000
  Description: ��ȡ��������
        Input: IN UINT uiId             ����
       Output: OUT INFO_CFG_S *pstCfg   ��������
       Return: ULONG, ERROR_SUCCESS     ����ɹ�
                      OTHER             ����ʧ��
      Caution: ���ν��ڷ��سɹ�ʱ��Ч
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
ULONG INFO_data_GetData(IN UINT uiId, OUT INFO_CFG_S *pstCfg)
{
    INFO_CFG_S* pstCfgtemp = pstCfghead;
    for( ; pstCfgtemp != NULL; pstCfgtemp = pstCfgtemp->pstCfgnext )
    {
        if(pstCfgtemp->uiId == uiId)
        {
            *pstCfg = *pstCfgtemp;
            return ERROR_SUCCESS;
        }
    }
    return ERROR_FAILED;
}

/*****************************************************************************
    Func Name: INFO_data_GetFirst[*]
 Date Created: 201x-xx-xx
       Author: xxxx 00000
  Description: ��ȡ��һ�������ݹ���
        Input: VOID
       Output:
       Return: UINT, != INFO_ID_INVALID     ��һ�������ݵĹ���
                     == INFO_ID_INVALID     δ�ҵ�
      Caution:
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
UINT INFO_data_GetFirst(VOID)
{
    if(pstCfghead == NULL)
    {
        return INFO_ID_INVALID;
    }
    else
        return pstCfghead->uiId;
}

/*****************************************************************************
    Func Name: INFO_data_GetNext[*]
 Date Created: 201x-xx-xx
       Author: xxxx 00000
  Description: ��ȡ��һ�������ݹ���
        Input: IN UINT uiId                 ��ǰ����
       Output:
       Return: UINT, != INFO_ID_INVALID     ��һ������
                     == INFO_ID_INVALID     δ�ҵ�
      Caution: �˽ӿڻ�ȡ��һ�����Ų����������uiId�����Ƿ�������
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
UINT INFO_data_GetNext(IN UINT uiId)
{
    INFO_CFG_S* pstCfgtemp = pstCfghead;
    for( ; pstCfgtemp != NULL; pstCfgtemp = pstCfgtemp->pstCfgnext)
    {
        if(pstCfgtemp->uiId == uiId && pstCfgtemp->pstCfgnext != NULL)
        {
            return pstCfgtemp->pstCfgnext->uiId;
        }
        if(pstCfgtemp->uiId > uiId)
        {
            return pstCfgtemp->uiId;
        }
    }
    return INFO_ID_INVALID;
}

/*****************************************************************************
    Func Name: INFO_data_Init[*]
 Date Created: 201x-xx-xx
       Author: xxxx 00000
  Description: ģ���ʼ��
        Input:
       Output:
       Return: ULONG, ERROR_SUCCESS     ����ɹ�
                      OTHER             ����ʧ��
      Caution: Ŀǰʼ�ճɹ�
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
ULONG INFO_data_Init(VOID)
{
    pstCfghead = NULL;
    return ERROR_SUCCESS;
}

/*****************************************************************************
    Func Name: INFO_data_Fini[*]
 Date Created: 201x-xx-xx
       Author: xxxx 00000
  Description: ģ���˳�
        Input:
       Output:
       Return: VOID
      Caution: ���ô˽ӿ�ǰ�������Ѿ���ʼ����
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
VOID INFO_data_Fini(VOID)
{
    return;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

