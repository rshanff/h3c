/*******************************************************************************
 Copyright (c) 2011, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              info.h
  Project Code: Comware V700R001
   Module Name: INFO
  Date Created: 2011-12-29
        Author: guce 04152
   Description: INFOģ�����ӿں��ڲ���������

--------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
  YYYY-MM-DD  

*******************************************************************************/

#ifndef _INFO_H_
#define _INFO_H_

#ifdef __cplusplus
extern "C"{
#endif

/*************************************** �������� ***************************************/
/* ���� */
#define INFO_ID_MIN                     1U
#define INFO_ID_MAX                     100000U
#define INFO_ID_INVALID                 0U
#define INFO_ID_ISVALID(uiId)           ((INFO_ID_MIN <= (uiId)) && ((uiId) <= INFO_ID_MAX))

/* ���� */
#define INFO_NAME_MAXLEN                15UL
#define INFO_NAME_ISVALID(pcName)       (0 != ((pcName)[0]))

/* �Ա� */
typedef enum tagInfo_Sex
{
    INFO_SEX_FEMALE  = 1,
    INFO_SEX_MALE    = 2
}INFO_SEX_E;
#define INFO_SEX_ISVALID(enSex)         ((INFO_SEX_FEMALE == (enSex)) || (INFO_SEX_MALE == (enSex)))

/* ���� */
#define INFO_AGE_MIN                    18U
#define INFO_AGE_MAX                    65U
#define INFO_AGE_ISVALID(uiAge)         ((INFO_AGE_MIN <= (uiAge)) && ((uiAge) <= INFO_AGE_MAX))

/* ��� */
#define INFO_HEIGHT_MIN                 1U
#define INFO_HEIGHT_MAX                 300U
#define INFO_HEIGHT_ISVALID(uiHeight)   ((INFO_HEIGHT_MIN <= (uiHeight)) && ((uiHeight) <= INFO_HEIGHT_MAX))

/* �������� */
typedef struct tagInfo_Cfg
{
    UINT uiId;                          /* ���� */
    UINT uiAge;                         /* ���� */
    UINT uiHeight;                      /* ��� */
    INFO_SEX_E enSex;                   /* �Ա� */
    CHAR szName[INFO_NAME_MAXLEN + 1];  /* ���� */
    struct tagInfo_Cfg* pstCfgnext;        /* next */
}INFO_CFG_S;

/* ȫ�����ݺϷ� */
#define INFO_ALL_ISVALID(pstCfg) \
            (INFO_ID_ISVALID((pstCfg)->uiId) && \
             INFO_NAME_ISVALID((pstCfg)->szName) && \
             INFO_SEX_ISVALID((pstCfg)->enSex) && \
             INFO_AGE_ISVALID((pstCfg)->uiAge) && \
             INFO_HEIGHT_ISVALID((pstCfg)->uiHeight))

/* ���������������󳤶� */
#define INFO_IOBUF_MAXLEN               512UL

/*************************************** ����ӿ� ***************************************/
/* ��ʼ�� */
ULONG INFO_Init(VOID);
/* ���� */
VOID INFO_Run(VOID);
/* �˳� */
VOID INFO_Fini(VOID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _INFO_H_ */

