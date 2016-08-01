/*******************************************************************************
 Copyright (c) 2011, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              info_parse.c
  Project Code: Comware V700R001
   Module Name: INFO
  Date Created: 2011-12-29
        Author: guce 04152
   Description: ������������

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
#include <stdio.h>
#include <string.h>

/* system   public  */
#include <sys/basetype.h>
#include <sys/assert.h>
#include <sys/string_ex.h>

/* module   private */
#include "info.h"

/*****************************************************************************
    Func Name: info_parse_Each
 Date Created: 2011-12-29
       Author: guce 04152
  Description: ��������������
        Input: IN const CHAR *pcEach        �����������ַ���
       Output: OUT INFO_CFG_S *pstCfg       ��������
       Return: VOID
      Caution:
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
STATIC VOID info_parse_Each(IN const CHAR *pcEach, OUT INFO_CFG_S *pstCfg)
{
    DBGASSERT(NULL != pcEach);
    DBGASSERT(NULL != pstCfg);

    /* ���� */
    if (0 == strncmp(pcEach, "id", strlen("id")))
    {
        sscanf(pcEach, "id=%u", &(pstCfg->uiId));
    }
    /* ���� */
    else if (0 == strncmp(pcEach, "name", strlen("name")))
    {
        INT iRet;
        CHAR szData[INFO_IOBUF_MAXLEN];

        iRet = sscanf(pcEach, "name=%s", szData);
        if ((1 == iRet) && (strlen(szData) <= INFO_NAME_MAXLEN))
        {
            strncpy(pstCfg->szName, szData, sizeof(pstCfg->szName));
        }
    }
    /* �Ա� */
    else if (0 == strncmp(pcEach, "sex", strlen("sex")))
    {
        sscanf(pcEach, "sex=%u", &(pstCfg->enSex));
    }
    /* ���� */
    else if (0 == strncmp(pcEach, "age", strlen("age")))
    {
        sscanf(pcEach, "age=%u", &(pstCfg->uiAge));
    }
    /* ��� */
    else if (0 == strncmp(pcEach, "height", strlen("height")))
    {
        sscanf(pcEach, "height=%u", &(pstCfg->uiHeight));
    }

    return;
}

/*****************************************************************************
    Func Name: INFO_parse_InputStr
 Date Created: 2011-12-29
       Author: guce 04152
  Description: ���������ַ����õ���������
        Input: IN const CHAR *pcInputStr    �����ַ���
       Output: OUT INFO_CFG_S *pstCfg       ��������
       Return: VOID
      Caution: 1.�������������ǰ���ɷǷ�ֵ���������Դ��жϽ�������Щ����
               2.ͬһ�������ݳ��ֶ�Σ�֮ǰ�����Ľ���ᱻ����
               3.strsep���дԴ�ַ�������Ҫ�ȿ���һ��
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
VOID INFO_parse_InputStr(IN const CHAR *pcInputStr, OUT INFO_CFG_S *pstCfg)
{
    CHAR szString[INFO_IOBUF_MAXLEN];
    CHAR *pcString;
    CHAR *pcEach;

    DBGASSERT(NULL != pcInputStr);
    DBGASSERT(strlen(pcInputStr) < INFO_IOBUF_MAXLEN);
    DBGASSERT(NULL != pstCfg);

    /* ���γ�ʼ��Ϊ�Ƿ�ֵ */
    memset(pstCfg, 0, sizeof(INFO_CFG_S));

    /* �����û������ַ��� */
    strlcpy(szString, pcInputStr, sizeof(szString));
    pcString = szString;
    while (NULL != (pcEach = strsep(&pcString, " ")))   /* ��"�ո�"��ָ������� */
    {
        /* ���ν����������� */
        info_parse_Each(pcEach, pstCfg);
    }

    return;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

