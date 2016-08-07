/*******************************************************************************
 Copyright (c) 2011, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              info_main.c
  Project Code: Comware V700R001
   Module Name: INFO
  Date Created: 2011-12-29
        Author: guce 04152
   Description:

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

/* system   public  */
#include <sys/basetype.h>
#include <sys/error.h>
#include <sys/assert.h>

/* module   private */
#include "info.h"
#include "info_dbg.h"
#include "info_data.h"
#include "info_proc.h"

/* �˵����� */
typedef enum tagInfo_Menu
{
    INFO_MENU_UNSPEC,
    INFO_MENU_ADD,              /* ��� */
    INFO_MENU_DELETE,           /* ɾ�� */
    INFO_MENU_MODIFY,           /* �޸� */
    INFO_MENU_DISPLAY,          /* ��ʾ */
    INFO_MENU_EXIT,             /* �˳� */
    INFO_MENU_OPEN_DEBUG,       /* �򿪵��Կ��� */
    INFO_MENU_CLOSE_DEBUG,      /* �رյ��Կ��� */
    INFO_MENU_MAX
}INFO_MENU_E;
#define INFO_MENU_ISVALID(enMenu)   ((INFO_MENU_UNSPEC < (enMenu)) && ((enMenu) < INFO_MENU_MAX))

/* �������ݽṹ */
typedef struct tagInfo_Func
{
    const CHAR      *pcMenu;    /* �˵����� */
    INFO_PROC_PF    pfProc;     /* ������ */
}INFO_FUNC_S;

/* �������� */
STATIC INFO_FUNC_S g_astInfoFunc[] =
{
    [INFO_MENU_ADD]         = {"Add",           INFO_proc_Add},
    [INFO_MENU_DELETE]      = {"Delete",        INFO_proc_Delete},
    [INFO_MENU_MODIFY]      = {"Modify",        INFO_proc_Modify},
    [INFO_MENU_DISPLAY]     = {"Display",       INFO_proc_Display},
    [INFO_MENU_EXIT]        = {"Exit",          INFO_proc_Exit},
    [INFO_MENU_OPEN_DEBUG]  = {"Open debug",    INFO_proc_OpenDebug},
    [INFO_MENU_CLOSE_DEBUG] = {"Close debug",   INFO_proc_CloseDebug}
};

/*****************************************************************************
    Func Name: info_main_DisplayMenu
 Date Created: 2011-12-29
       Author: guce 04152
  Description: ��ʾ�˵�
        Input:
       Output:
       Return: VOID
      Caution:
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
STATIC VOID info_main_DisplayMenu(VOID)
{
    INFO_MENU_E enEach;

    /* ��ʾÿ���˵���Ŀ */
    printf("\r\n");
    for (enEach = (INFO_MENU_E)(INFO_MENU_UNSPEC + 1); enEach < INFO_MENU_MAX; enEach++)
    {
        printf("%u.%s\r\n", enEach, g_astInfoFunc[enEach].pcMenu);
    }
    printf("\r\n");

    return;
}

/*****************************************************************************
    Func Name: info_main_DisplayErrInfo
 Date Created: 2011-12-29
       Author: guce 04152
  Description: ���������ʾ��Ϣ
        Input: IN ULONG ulErrCode   ������
       Output:
       Return: VOID
      Caution:
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
STATIC VOID info_main_DisplayErrInfo(IN ULONG ulErrCode)
{
    const CHAR *pcErrInfo;

    /* ���ִ�����ʾ��Ϣ */
    switch (ulErrCode)
    {
        case ERROR_INVALID_PARAMETER:
        {
            pcErrInfo = "The parameter is incorrect.\r\n";
            break;
        }
        case ERROR_NOT_FOUND:
        {
            pcErrInfo = "The specified item was not found.\r\n";
            break;
        }
        case ERROR_ALREADY_EXIST:
        {
            pcErrInfo = "The item already exists.\r\n";
            break;
        }
        case ERROR_NOTSUPPORT:
        {
            pcErrInfo = "The operation is not supported.\r\n";
            break;
        }
        case ERROR_NO_ENOUGH_RESOURCE:
        {
            pcErrInfo = "Not enough resources are available to complete the operation.\r\n";
            break;
        }
        default:
        {
            pcErrInfo = "The operation completed unsuccessfully.\r\n";
            break;
        }
    }

    /* ��� */
    printf("%s", pcErrInfo);

    return;
}

/*****************************************************************************
    Func Name: info_main_GetMenuChoice
 Date Created: 2011-12-29
       Author: guce 04152
  Description: ���û���������ȡ"�˵�ѡ��"
        Input:
       Output: OUT INFO_MENU_E *penMenu �˵�ѡ��
       Return: ULONG, ERROR_SUCCESS     ����ɹ�
                      OTHER             ����ʧ��
      Caution: 1.���ν��ڴ���ɹ�ʱ��Ч
               2.����ɹ�ʱ��"�˵�ѡ��"�Ѿ���֤Ϊ�Ϸ���
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
STATIC ULONG info_main_GetMenuChoice(OUT INFO_MENU_E *penMenu)
{
    CHAR szBuf[INFO_IOBUF_MAXLEN];
    INFO_MENU_E enMenu;
    ULONG ulErrCode;

    DBGASSERT(NULL != penMenu);

    /* ������Ϣ */
    printf("Your choice:");

    /* ��ȡ"�˵�ѡ��" */
    szBuf[0] = 0;
    (VOID)fgets(szBuf, (INT)sizeof(szBuf), stdin);

    /* �����ɹ� */
    if ((1 == sscanf(szBuf, "%u", &enMenu)) && (INFO_MENU_ISVALID(enMenu)))
    {
        *penMenu = enMenu;

        INFO_DBG_PRINT("User choice %u.", enMenu);
        ulErrCode = ERROR_SUCCESS;
    }
    else /* ����ʧ�� */
    {
        INFO_DBG_PRINT("Input parse failed.");
        ulErrCode = ERROR_INVALID_PARAMETER;
    }

    return ulErrCode;
}

/*****************************************************************************
    Func Name: info_main_GetInputStr
 Date Created: 2011-12-29
       Author: guce 04152
  Description: ���ݲ˵�ѡ����û���������ȡ"�����ַ���"
        Input: IN INFO_MENU_E enMenu    �˵�ѡ��
               IN ULONG ulInputLen      �����ַ�����������С
       Output: OUT CHAR *pcInputStr     �����ַ���
       Return: VOID
      Caution: "�����ַ���"�ĺϷ�����Ҫ�������幦�ܺ������м��
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
STATIC VOID info_main_GetInputStr(IN INFO_MENU_E enMenu, IN ULONG ulInputLen, OUT CHAR *pcInputStr)
{
    DBGASSERT(INFO_MENU_ISVALID(enMenu));
    DBGASSERT(0 < ulInputLen);
    DBGASSERT(NULL != pcInputStr);

    pcInputStr[0] = 0;

    /* �ֱ��ȡ"�����ַ���" */
    switch (enMenu)
    {
        /* ��Ҫ����ȫ����Ϣ */
        case INFO_MENU_ADD:             /* ��� */
        {
            printf("Format :id=(1-100000) name=(len<=15) sex=(F=1,M=2) age=(18-65) height=(1-300)\r\n");
            printf("Example:id=10 name=jack sex=2 age=20 height=175\r\n");
            printf("Input Info:");
            (VOID)fgets(pcInputStr, (INT)ulInputLen, stdin);
            break;
        }
        /* ��Ҫ����ID */
        case INFO_MENU_DELETE:          /* ɾ�� */
        {
            printf("Format :id=(1-100000)\r\n");
            printf("Example:id=10\r\n");
            printf("Input Id:");
            (VOID)fgets(pcInputStr, (INT)ulInputLen, stdin);
            break;
        }
        /* ��Ҫ����ID+������Ϣ */
        case INFO_MENU_MODIFY:          /* �޸� */
        {
            printf("Format :id=(1-100000) [name=(len<=15) sex=(F=1,M=2) age=(18-65) height=(1-300)]*\r\n");
            printf("Example:id=10 name=jack sex=2 \r\n");
            printf("Example:id=10 age=20 height=175\r\n");
            printf("Input Info:");
            (VOID)fgets(pcInputStr, (INT)ulInputLen, stdin);
            break;
        }
        /* ����Ҫ���� */
        case INFO_MENU_DISPLAY:         /* ��ʾ */
        case INFO_MENU_EXIT:            /* �˳� */
        case INFO_MENU_OPEN_DEBUG:      /* �򿪵��Կ��� */
        case INFO_MENU_CLOSE_DEBUG:     /* �رյ��Կ��� */
        {
            break;
        }
        default:
        {
            DBGASSERT(0);
            break;
        }
    }

    return;
}

/*****************************************************************************
    Func Name: INFO_Run
 Date Created: 2011-12-29
       Author: guce 04152
  Description: ����
        Input:
       Output:
       Return: VOID
      Caution:
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
VOID INFO_Run(VOID)
{
    ULONG ulErrCode;
    INFO_MENU_E enMenu;
    CHAR szInputStr[INFO_IOBUF_MAXLEN];

    /* ���������� */
    do
    {
        /* ��ʾ�˵� */
        info_main_DisplayMenu();

        /* ��ȡ"�˵�ѡ��" */
        enMenu = INFO_MENU_UNSPEC;
        szInputStr[0] = 0;
        ulErrCode = info_main_GetMenuChoice(&enMenu);
        if (ERROR_SUCCESS == ulErrCode)
        {
            /* ��ȡ"�����ַ���" */
            info_main_GetInputStr(enMenu, sizeof(szInputStr), szInputStr);

            /* ִ����Ӧ���� */
            DBGASSERT(NULL != g_astInfoFunc[enMenu].pfProc);
            ulErrCode = g_astInfoFunc[enMenu].pfProc(szInputStr);
        }

        /* �����ʾ��Ϣ */
        if (ERROR_SUCCESS != ulErrCode)
        {
            info_main_DisplayErrInfo(ulErrCode);
        }
    }while (INFO_MENU_EXIT != enMenu); /* ���˳������ */

    return;
}

/*****************************************************************************
    Func Name: INFO_Init
 Date Created: 2011-12-29
       Author: guce 04152
  Description: ��ʼ��
        Input:
       Output:
       Return: ULONG, ERROR_SUCCESS     ����ɹ�
                      OTHER             ����ʧ��
      Caution:
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
ULONG INFO_Init(VOID)
{
    ULONG ulErrCode;

    ulErrCode = INFO_data_Init();

    return ulErrCode;
}

/*****************************************************************************
    Func Name: INFO_Fini
 Date Created: 2011-12-29
       Author: guce 04152
  Description: �˳�
        Input:
       Output:
       Return: VOID
      Caution:
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
VOID INFO_Fini(VOID)
{
    INFO_data_Fini();

    return;
}

/*****************************************************************************
    Func Name: main
 Date Created: 2011-12-29
       Author: guce 04152
  Description: �������
        Input: IN INT iArgc         ��θ���
               IN CHAR *apcArgv[]   ���ָ��
       Output:
       Return: INT, ERROR_SUCCESS   ����ɹ�
                    OTHER           ����ʧ��
      Caution:
------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
  YYYY-MM-DD

*****************************************************************************/
INT main(IN INT iArgc, IN CHAR *apcArgv[])
{
    ULONG ulErrCode;

    IGNORE_PARAM(iArgc);
    IGNORE_PARAM(apcArgv);

    /* ��ʼ�� */
    ulErrCode = INFO_Init();
    if (ERROR_SUCCESS == ulErrCode)
    {
        /* ���� */
        INFO_Run();
    }

    /* �˳� */
    INFO_Fini();

    return (INT)(ulErrCode);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

