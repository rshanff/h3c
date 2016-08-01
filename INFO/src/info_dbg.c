/*******************************************************************************
 Copyright (c) 2011, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              info_dbg.c
  Project Code: Comware V700R001
   Module Name: INFO
  Date Created: 2011-12-29
        Author: guce 04152
   Description: ������Ϣ

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
#include <stdarg.h>

/* system   public  */
#include <sys/basetype.h>
#include <sys/assert.h>

/* module   private */
#include "info.h"

/* ���Կ��� */
STATIC BOOL_T g_bInfoDbg = BOOL_FALSE;

/*****************************************************************************
    Func Name: INFO_dbg_Set
 Date Created: 2011-12-29
       Author: guce 04152
  Description: ���õ��Կ���
        Input: IN BOOL_T bSwitch    ����״̬
       Output:
       Return: VOID
      Caution:
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
VOID INFO_dbg_Set(IN BOOL_T bSwitch)
{
    g_bInfoDbg = bSwitch;

    return;
}

/*****************************************************************************
    Func Name: INFO_dbg_Get
 Date Created: 2011-12-29
       Author: guce 04152
  Description: ��ȡ���Կ���
        Input: VOID
       Output:
       Return: BOOL_T, BOOL_TRUE    ��
                       BOOL_FALSE   �ر�
      Caution:
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
BOOL_T INFO_dbg_Get(VOID)
{
    return g_bInfoDbg;
}

/*****************************************************************************
    Func Name: INFO_dbg_Print
 Date Created: 2011-12-29
       Author: guce 04152
  Description: ��ӡ������Ϣ
        Input: IN const CHAR *pcFunc    ������
               IN const CHAR *pcFmt     ��ʽ��
               ...                      ����
       Output:
       Return: VOID
      Caution:
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
VOID INFO_dbg_Print(IN const CHAR *pcFunc, IN const CHAR *pcFmt, ...)
{
    CHAR szBuf[INFO_IOBUF_MAXLEN];
    va_list stArgs;

    DBGASSERT(NULL != pcFunc);
    DBGASSERT(NULL != pcFmt);

    /* ƴװ�ɱ�β��� */
    szBuf[0] = 0;
    va_start(stArgs, pcFmt);
    (VOID)vsnprintf(szBuf, sizeof(szBuf), pcFmt, stArgs);
    va_end(stArgs);

    /* ��ӡ������Ϣ */
    printf("*DEBUG[%s]: %s\r\n", pcFunc, szBuf);

    return;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

