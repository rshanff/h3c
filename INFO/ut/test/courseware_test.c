#ifdef __cplusplus
extern "C"{
#endif

#include <string.h>
#include <sys/string_ex.h>

#include <sys/basetype.h>
#include <sys/error.h>
#include <sys/list.h>
#include "../../src/info.h"
#include "../../src/info_data.h"
#include "../../src/info_dbg.h"
#include "../../src/info_parse.h"
#include "../../src/info_proc.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#include <gtest/gtest.h>
#include "../stub/stub.h"

#define UTC_INFO_proc_Add
/*#######################################################################
#�����������: UT_INFO_proc_Add_001
#��  ��  ��  : ���ܲ���
#������������: ���һ����Ա��Ϣ�ɹ�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : һ����Ա����Ϣ��id=10 name=jack sex=2 age=20 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣ�ɹ�
               ��ѯ��Ա�Ѵ���
               ��ѯ��Ա��Ϣ������һ��
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 001)
{
    ULONG ulErrCode;
    BOOL_T bIsExist;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���Ԥ�ڽ�� */
    bIsExist = INFO_data_IsExist(10);
    EXPECT_EQ(BOOL_TRUE, bIsExist);
    ulErrCode = INFO_data_GetData(10, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    EXPECT_EQ(10, stCfg.uiId);
    EXPECT_EQ(2, stCfg.enSex);
    EXPECT_EQ(20, stCfg.uiAge);
    EXPECT_EQ(175, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_002
#��  ��  ��  : ���ܲ���
#������������: ��������Ա��Ϣ�ɹ�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : ��Ա��Ϣ1��id=10 name=jack10 sex=1 age=30 height=100
               ��Ա��Ϣ2��id=1  name=jack1  sex=2 age=40 height=250
               ��Ա��Ϣ3��id=50 name=jack50 sex=1 age=50 height=200
               ��Ա��Ϣ4��id=99 name=jack99 sex=2 age=33 height=111
               ��Ա��Ϣ5��id=44 name=jack44 sex=1 age=22 height=222
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��������Ա��Ϣ�ɹ�
               ���԰�˳���ȡ�����Ա��Ϣ
               ��Ա��Ϣ������һ��
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 002)
{
    ULONG ulErrCode;
    UINT uiId;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode  = INFO_proc_Add("id=10 name=jack10 sex=1 age=30 height=100");
    ulErrCode |= INFO_proc_Add("id=1  name=jack1  sex=2 age=40 height=250");
    ulErrCode |= INFO_proc_Add("id=50 name=jack50 sex=1 age=50 height=200");
    ulErrCode |= INFO_proc_Add("id=99 name=jack99 sex=2 age=33 height=111");
    ulErrCode |= INFO_proc_Add("id=44 name=jack44 sex=1 age=22 height=222");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���Ԥ�ڽ�� */
    uiId = INFO_data_GetFirst();
    ulErrCode = INFO_data_GetData(uiId, &stCfg);
    EXPECT_EQ(1, stCfg.uiId);
    EXPECT_EQ(2, stCfg.enSex);
    EXPECT_EQ(40, stCfg.uiAge);
    EXPECT_EQ(250, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack1"));
    uiId = INFO_data_GetNext(uiId);
    ulErrCode = INFO_data_GetData(uiId, &stCfg);
    EXPECT_EQ(10, stCfg.uiId);
    EXPECT_EQ(1, stCfg.enSex);
    EXPECT_EQ(30, stCfg.uiAge);
    EXPECT_EQ(100, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack10"));
    uiId = INFO_data_GetNext(uiId);
    ulErrCode = INFO_data_GetData(uiId, &stCfg);
    EXPECT_EQ(44, stCfg.uiId);
    EXPECT_EQ(1, stCfg.enSex);
    EXPECT_EQ(22, stCfg.uiAge);
    EXPECT_EQ(222, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack44"));
    uiId = INFO_data_GetNext(uiId);
    ulErrCode = INFO_data_GetData(uiId, &stCfg);
    EXPECT_EQ(50, stCfg.uiId);
    EXPECT_EQ(1, stCfg.enSex);
    EXPECT_EQ(50, stCfg.uiAge);
    EXPECT_EQ(200, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack50"));
    uiId = INFO_data_GetNext(uiId);
    ulErrCode = INFO_data_GetData(uiId, &stCfg);
    EXPECT_EQ(99, stCfg.uiId);
    EXPECT_EQ(2, stCfg.enSex);
    EXPECT_EQ(33, stCfg.uiAge);
    EXPECT_EQ(111, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack99"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_003
#��  ��  ��  : �߽����
#������������: ���Ϸ��߽�ֵ����û���Ϣ�ɹ�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : ��Ա��Ϣ1(��С�߽�ֵ)��id=1      name=1               sex=1 age=18 height=1
               ��Ա��Ϣ2(���߽�ֵ)��id=100000 name=123456789012345 sex=2 age=65 height=300
               ��Ա��Ϣ3(С�߽�ֵ1 )��id=2      name=11              sex=1 age=19 height=2
               ��Ա��Ϣ4(С�߽�ֵ2 )��id=3      name=111             sex=1 age=20 height=3
               ��Ա��Ϣ5(��߽�ֵ1 )��id=99999  name=12345678901234  sex=2 age=64 height=299
               ��Ա��Ϣ6(��߽�ֵ2 )��id=99998  name=1234567890123   sex=2 age=63 height=298
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣ�ɹ�
               ��Ա��Ϣ������һ��
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 003)
{
    ULONG ulErrCode;
    UINT uiId;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=1      name=1               sex=1 age=18 height=1  ");
    ulErrCode = INFO_proc_Add("id=100000 name=123456789012345 sex=2 age=65 height=300");
    ulErrCode = INFO_proc_Add("id=2      name=11              sex=1 age=19 height=2  ");
    ulErrCode = INFO_proc_Add("id=3      name=111             sex=1 age=20 height=3  ");
    ulErrCode = INFO_proc_Add("id=99999  name=12345678901234  sex=2 age=64 height=299");
    ulErrCode = INFO_proc_Add("id=99998  name=1234567890123   sex=2 age=63 height=298");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���Ԥ�ڽ�� */
    uiId = INFO_data_GetFirst();
    ulErrCode = INFO_data_GetData(uiId, &stCfg);
    EXPECT_EQ(1, stCfg.uiId);
    EXPECT_EQ(1, stCfg.enSex);
    EXPECT_EQ(18, stCfg.uiAge);
    EXPECT_EQ(1, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "1"));
    uiId = INFO_data_GetNext(uiId);
    ulErrCode = INFO_data_GetData(uiId, &stCfg);
    EXPECT_EQ(2, stCfg.uiId);
    EXPECT_EQ(1, stCfg.enSex);
    EXPECT_EQ(19, stCfg.uiAge);
    EXPECT_EQ(2, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "11"));
    uiId = INFO_data_GetNext(uiId);
    ulErrCode = INFO_data_GetData(uiId, &stCfg);
    EXPECT_EQ(3, stCfg.uiId);
    EXPECT_EQ(1, stCfg.enSex);
    EXPECT_EQ(20, stCfg.uiAge);
    EXPECT_EQ(3, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "111"));
    uiId = INFO_data_GetNext(uiId);
    ulErrCode = INFO_data_GetData(uiId, &stCfg);
    EXPECT_EQ(99998, stCfg.uiId);
    EXPECT_EQ(2, stCfg.enSex);
    EXPECT_EQ(63, stCfg.uiAge);
    EXPECT_EQ(298, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "1234567890123"));
    uiId = INFO_data_GetNext(uiId);
    ulErrCode = INFO_data_GetData(uiId, &stCfg);
    EXPECT_EQ(99999, stCfg.uiId);
    EXPECT_EQ(2, stCfg.enSex);
    EXPECT_EQ(64, stCfg.uiAge);
    EXPECT_EQ(299, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "12345678901234"));
    uiId = INFO_data_GetNext(uiId);
    ulErrCode = INFO_data_GetData(uiId, &stCfg);
    EXPECT_EQ(100000, stCfg.uiId);
    EXPECT_EQ(2, stCfg.enSex);
    EXPECT_EQ(65, stCfg.uiAge);
    EXPECT_EQ(300, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "123456789012345"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_004
#��  ��  ��  : ѹ������
#������������: ������ԣ����5000��Ա����Ϣ
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : ѭ����Ӷ����Ա��Ϣ��id=x name=jack sex=2 age=20 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣ�ɹ�
               ���һ��Ա����Ϣ��������һ��
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 004)
{
    ULONG ulErrCode;
    UINT uiLoop;
    CHAR szInputStr[512];
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    for (uiLoop = 1; uiLoop < 100000; uiLoop = uiLoop + 20)
    {
        scnprintf(szInputStr, sizeof(szInputStr), "id=%u name=jack sex=2 age=20 height=175", uiLoop);
        ulErrCode |= INFO_proc_Add(szInputStr);
    }
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���Ԥ�ڽ�� */
    ulErrCode = INFO_data_GetData(5001, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    EXPECT_EQ(5001, stCfg.uiId);
    EXPECT_EQ(2, stCfg.enSex);
    EXPECT_EQ(20, stCfg.uiAge);
    EXPECT_EQ(175, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_005
#��  ��  ��  : �쳣����
#������������: �ظ����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : ��Ա��Ϣ��id=10 name=xxxx sex=1 age=55 height=222
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_ALREADY_EXIST
               ��ѯ��Ա�Ѵ���
               ��ѯ��Ա��Ϣ��Ԥ����������һ��
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 005)
{
    ULONG ulErrCode;
    BOOL_T bIsExist;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10 name=xxxx sex=1 age=55 height=222");
    EXPECT_EQ(ERROR_ALREADY_EXIST, ulErrCode);

    /* ���Ԥ�ڽ�� */
    bIsExist = INFO_data_IsExist(10);
    EXPECT_EQ(BOOL_TRUE, bIsExist);
    ulErrCode = INFO_data_GetData(10, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    EXPECT_EQ(10, stCfg.uiId);
    EXPECT_EQ(2, stCfg.enSex);
    EXPECT_EQ(20, stCfg.uiAge);
    EXPECT_EQ(175, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_006
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬�û���Ϣ������ַ���
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��������ַ���
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 006)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_007
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬����Ϊ����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=100001 name=jack             sex=2 age=20 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 007)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=100001 name=jack             sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_008
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬����Ϊ����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=0      name=jack             sex=2 age=20 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 008)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=0      name=jack             sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_009
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬�Ա�Ϊ����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=10     name=jack             sex=3 age=20 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 009)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10     name=jack             sex=3 age=20 height=175");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_010
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬�Ա�Ϊ����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=10     name=jack             sex=0 age=20 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 010)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10     name=jack             sex=0 age=20 height=175");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_011
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬��������Ϊ����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=10     name=1234567890123456 sex=2 age=20 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 011)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10     name=1234567890123456 sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_012
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬��������Ϊ����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=10     name=                 sex=2 age=20 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 012)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10     name=                 sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_013
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬����Ϊ����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=10     name=jack             sex=2 age=66 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 013)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10     name=jack             sex=2 age=66 height=175");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_014
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬����Ϊ����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=10     name=jack             sex=2 age=17 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 014)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10     name=jack             sex=2 age=17 height=175");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_015
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬���Ϊ����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=10     name=jack             sex=2 age=20 height=301
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 015)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10     name=jack             sex=2 age=20 height=301");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_016
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬���Ϊ����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=10     name=jack             sex=2 age=20 height=0
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 016)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10     name=jack             sex=2 age=20 height=0");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_017
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬ȱ�ٹ���
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��          name=jack             sex=2 age=20 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 017)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("          name=jack             sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_018
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬ȱ������
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=10                           sex=2 age=20 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 018)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10                           sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_019
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬ȱ���Ա�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=10     name=jack                   age=20 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 019)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10     name=jack                   age=20 height=175");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_020
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬ȱ������
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=10     name=jack             sex=2        height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 020)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10     name=jack             sex=2        height=175");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_021
#��  ��  ��  : �쳣����
#������������: �Ƿ����룬ȱ�����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=10     name=jack             sex=2 age=20
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 021)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10     name=jack             sex=2 age=20           ");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Add_022
#��  ��  ��  : �쳣����
#������������: �����ڴ�ʧ��
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
#��       �� : �û���Ϣ��id=10 name=jack sex=2 age=20 height=175
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : ��ӳ�Ա��Ϣʧ�ܣ����ش�����ERROR_NO_ENOUGH_RESOURCE
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Add, 022)
{
    ULONG ulErrCode;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ��malloc��׮�������ڴ�ʧ�� */
    stub_set_one((VOID *)malloc, (VOID *)stub_malloc_ng);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_NO_ENOUGH_RESOURCE, ulErrCode);

    /* ���׮ */
    stub_reset_all();

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

#define UT_CORRECTMEMBERNUM 15UL
STATIC const CHAR *g_szCorrectMemberInfo[UT_CORRECTMEMBERNUM] = {
    "id=11 name=jack01 sex=1 age=21 height=170",    /* 0 */
    "id=12 name=jack02 sex=2 age=22 height=171",
    "id=13 name=jack03 sex=1 age=23 height=172",
    "id=14 name=jack04 sex=2 age=24 height=173",
    "id=15 name=jack05 sex=1 age=25 height=174",
    "id=16 name=jack06 sex=2 age=26 height=175",    /* 5 */
    /* ����3��ID��ͬ��Ϣ */
    "id=17 name=jack07 sex=1 age=27 height=176",
    "id=18 name=jack08 sex=2 age=28 height=177",
    "id=19 name=jack09 sex=1 age=29 height=178",
    "id=17 name=jack10 sex=2 age=30 height=179",    /* 9 */
    "id=18 name=jack11 sex=1 age=31 height=180",
    "id=19 name=jack12 sex=2 age=32 height=181",
    /* ����ID��ͬ */
    "id=20 name=jack13 sex=1 age=33 height=182",    /* 12 */
    "id=20 name=jack14 sex=2 age=34 height=183",
    "id=20 name=jack15 sex=1 age=35 height=184"     /* 14 */
};

/* ��g_szCorrectMemberInfo��Ӧ */
INFO_CFG_S g_stMemberData[UT_CORRECTMEMBERNUM] = {
 {11, 21, 170, INFO_SEX_FEMALE, "jack01"},
 {12, 22, 171, INFO_SEX_MALE,   "jack02"},
 {13, 23, 172, INFO_SEX_FEMALE, "jack03"},
 {14, 24, 173, INFO_SEX_MALE,   "jack04"},
 {15, 25, 174, INFO_SEX_FEMALE, "jack05"},
 {16, 26, 175, INFO_SEX_MALE,   "jack06"},
 {17, 27, 176, INFO_SEX_FEMALE, "jack07"},
 {18, 28, 177, INFO_SEX_MALE,   "jack08"},
 {19, 29, 178, INFO_SEX_FEMALE, "jack09"},
 {17, 30, 179, INFO_SEX_MALE,   "jack10"},
 {18, 31, 180, INFO_SEX_FEMALE, "jack11"},
 {19, 32, 181, INFO_SEX_MALE,   "jack12"},
 {20, 33, 182, INFO_SEX_FEMALE, "jack13"},
 {20, 34, 183, INFO_SEX_MALE,   "jack14"},
 {20, 35, 184, INFO_SEX_FEMALE, "jack15"}
};

#define UTC_INFO_proc_Delete
/*#######################################################################
#�����������: UT_INFO_proc_Delete_001
#��  ��  ��  : ���ܲ���
#������������: ɾ��1����Ա�ɹ�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ���1����Ա
#��       �� : pcInputStr=Ա��ID
#�� �� �� �� : ִ�в�����
#Ԥ �� �� �� : ��Աɾ��
#              INFO_proc_Delete���سɹ�
#��  ��  ��  : liaohui kf2309
#��      ��  : 2011-12-31
#######################################################################*/
TEST(UT_INFO_proc_Delete, 001)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;
    ULONG ulFirstMember = 0;

    /* ��ʼ������ */
    INFO_data_Init();

    /* ���һ����Ա */
    ulErrCode = INFO_proc_Add(g_szCorrectMemberInfo[ulFirstMember]);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    ulErrCode = INFO_data_GetData(g_stMemberData[ulFirstMember].uiId, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���ñ��⺯�� */
    ulErrCode = INFO_proc_Delete("id=11");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    ulErrCode = INFO_data_GetData(g_stMemberData[ulFirstMember].uiId, &stCfg);
    EXPECT_EQ(ERROR_FAILED, ulErrCode);


    /* ȥ��ʼ������ */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Delete_002
#��  ��  ��  : ���ܲ���
#������������: ɾ��3����Ա�ɹ�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ���3����Ա
#��       �� : pcInputStr=Ա��ID
#�� �� �� �� : ִ�в�����
#Ԥ �� �� �� : ���г�Աɾ��
#              INFO_proc_Delete���سɹ�
#��  ��  ��  : liaohui kf2309
#��      ��  : 2011-12-31
#######################################################################*/
TEST(UT_INFO_proc_Delete, 002)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;
    INT iMemberNum = 3;
    INT iCurMember;
    BOOL_T bIsEmpty;

    /* ��ʼ������ */
    INFO_data_Init();

    /* ��ӳ�Ա */
    for (iCurMember = 0; iCurMember < iMemberNum; iCurMember++)
    {
        ulErrCode = INFO_proc_Add(g_szCorrectMemberInfo[iCurMember]);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

        ulErrCode = INFO_data_GetData(g_stMemberData[iCurMember].uiId, &stCfg);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    }

    for (iCurMember = iMemberNum - 1; iCurMember >= 0; iCurMember--)
    {
        /* ���ñ��⺯�� */
        ulErrCode = INFO_proc_Delete(g_szCorrectMemberInfo[iCurMember]);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
        ulErrCode = INFO_data_GetData(g_stMemberData[iCurMember].uiId, &stCfg);
        EXPECT_EQ(ERROR_FAILED, ulErrCode);
    }

    bIsEmpty = INFO_data_IsEmpty();
    EXPECT_EQ(BOOL_TRUE, bIsEmpty);

    /* ȥ��ʼ������ */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Delete_003
#��  ��  ��  : ���ܲ���
#������������: ɾ��5����Ա�ɹ�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ���5����Ա
#��       �� : pcInputStr=Ա��ID
#�� �� �� �� : ִ�в�����
#Ԥ �� �� �� : ���г�Աɾ��
#              INFO_proc_Delete���سɹ�
#��  ��  ��  : liaohui kf2309
#��      ��  : 2011-12-31
#######################################################################*/
TEST(UT_INFO_proc_Delete, 003)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;
    INT iMemberNum = 5;
    INT iCurMember;
    BOOL_T bIsEmpty;

    /* ��ʼ������ */
    INFO_data_Init();

    /* ��ӳ�Ա */
    for (iCurMember = 0; iCurMember < iMemberNum; iCurMember++)
    {
        ulErrCode = INFO_proc_Add(g_szCorrectMemberInfo[iCurMember]);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

        ulErrCode = INFO_data_GetData(g_stMemberData[iCurMember].uiId, &stCfg);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    }

    for (iCurMember = iMemberNum - 1; iCurMember >=0; iCurMember--)
    {
        /* ���ñ��⺯�� */
        ulErrCode = INFO_proc_Delete(g_szCorrectMemberInfo[iCurMember]);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
        ulErrCode = INFO_data_GetData(g_stMemberData[iCurMember].uiId, &stCfg);
        EXPECT_EQ(ERROR_FAILED, ulErrCode);
    }

    bIsEmpty = INFO_data_IsEmpty();
    EXPECT_EQ(BOOL_TRUE, bIsEmpty);

    /* ȥ��ʼ������ */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Delete_004
#��  ��  ��  : ���ܲ���
#������������: ɾ���ĳ�Ա������
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ���5����Ա
#��       �� : pcInputStr=�����ڵ�Ա��ID
#�� �� �� �� : ִ�в�����
#Ԥ �� �� �� : û�г�Ա��ɾ��
#              INFO_proc_Delete���سɹ�
#��  ��  ��  : liaohui kf2309
#��      ��  : 2011-12-31
#######################################################################*/
TEST(UT_INFO_proc_Delete, 004)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;
    INT iMemberNum = 5;
    INT iCurMember;

    /* ��ʼ������ */
    INFO_data_Init();

    /* ��ӳ�Ա */
    for (iCurMember = 0; iCurMember < iMemberNum; iCurMember++)
    {
        ulErrCode = INFO_proc_Add(g_szCorrectMemberInfo[iCurMember]);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

        ulErrCode = INFO_data_GetData(g_stMemberData[iCurMember].uiId, &stCfg);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    }

    /* ���ñ��⺯�� */
    ulErrCode = INFO_proc_Delete("id=1000");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    for (iCurMember = 0; iCurMember < iMemberNum; iCurMember++)
    {
        ulErrCode = INFO_data_GetData(g_stMemberData[iCurMember].uiId, &stCfg);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    }

    /* ȥ��ʼ������ */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Delete_005
#��  ��  ��  : ���ܲ���
#������������: ɾ���ĳ�Աʧ�ܣ�������ЧID
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ���5����Ա
#��       �� : pcInputStr=��ЧԱ��ID
#�� �� �� �� : ִ�в�����
#Ԥ �� �� �� : û�г�Ա��ɾ��
#              INFO_proc_Delete����ERROR_INVALID_PARAMETER
#��  ��  ��  : liaohui kf2309
#��      ��  : 2011-12-31
#######################################################################*/
TEST(UT_INFO_proc_Delete, 005)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;
    INT iMemberNum = 5;
    INT iCurMember;

    /* ��ʼ������ */
    INFO_data_Init();

    /* ��ӳ�Ա */
    for (iCurMember = 0; iCurMember < iMemberNum; iCurMember++)
    {
        ulErrCode = INFO_proc_Add(g_szCorrectMemberInfo[iCurMember]);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

        ulErrCode = INFO_data_GetData(g_stMemberData[iCurMember].uiId, &stCfg);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    }

    /* ���ñ��⺯�� */
    ulErrCode = INFO_proc_Delete("id=0");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    for (iCurMember = 0; iCurMember < iMemberNum; iCurMember++)
    {
        ulErrCode = INFO_data_GetData(g_stMemberData[iCurMember].uiId, &stCfg);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    }

    /* ���ñ��⺯�� */
    ulErrCode = INFO_proc_Delete("id=100001");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    for (iCurMember = 0; iCurMember < iMemberNum; iCurMember++)
    {
        ulErrCode = INFO_data_GetData(g_stMemberData[iCurMember].uiId, &stCfg);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    }

    /* ȥ��ʼ������ */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Delete_006
#��  ��  ��  : ���ܲ���
#������������: ɾ��100000����Ա�ɹ�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ���100000����Ա
#��       �� : pcInputStr=Ա��ID
#�� �� �� �� : ִ�в�����
#Ԥ �� �� �� : ���г�Աɾ��
#              INFO_proc_Delete���سɹ�
#��  ��  ��  : liaohui kf2309
#��      ��  : 2011-12-31
#######################################################################*/
TEST(UT_INFO_proc_Delete, 006)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;
    INT iMemberNum = 10000;
    INT iCurMember;
    BOOL_T bIsEmpty;
    CHAR szInfo[INFO_IOBUF_MAXLEN];
    CHAR *pcString;
    UINT uiId;
    UINT uiCount;

    /* ��ʼ������ */
    INFO_data_Init();

    pcString = szInfo;

    /* ��ӳ�Ա */
    for (iCurMember = 1; iCurMember <= iMemberNum; iCurMember++)
    {
        (VOID)scnprintf(pcString, sizeof(szInfo), "id=%d name=jack01 sex=1 age=21 height=170", iCurMember);
        ulErrCode = INFO_proc_Add(pcString);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    }

    uiCount = 0;
    INFO_FOREACH(uiId)
    {
        uiCount++;
    }
    EXPECT_EQ(iMemberNum, uiCount);

    for (iCurMember = iMemberNum; iCurMember > 0; iCurMember--)
    {
        pcString = szInfo;
        (VOID)scnprintf(pcString, sizeof(szInfo), "id=%u", iCurMember);

        /* ���ñ��⺯�� */
        ulErrCode = INFO_proc_Delete(pcString);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    }

    bIsEmpty = INFO_data_IsEmpty();
    EXPECT_EQ(BOOL_TRUE, bIsEmpty);

    /* ȥ��ʼ������ */
    INFO_data_Fini();
}

#define UTC_INFO_proc_Modify
/*#######################################################################
#�����������: UT_INFO_proc_Modify_001
#��  ��  ��  : ���ܲ���
#������������: �����޸ģ�ֻ�޸�����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : �޸ĳ�Ա��Ϣ��id=10 name=jackabc
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣ�ɹ�
               ��ѯ��Ա��Ϣ������һ��
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 001)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Modify("id=10 name=jackabc");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���Ԥ�ڽ�� */
    ulErrCode = INFO_data_GetData(10, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    EXPECT_EQ(10, stCfg.uiId);
    EXPECT_EQ(2, stCfg.enSex);
    EXPECT_EQ(20, stCfg.uiAge);
    EXPECT_EQ(175, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jackabc"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_002
#��  ��  ��  : ���ܲ���
#������������: �����޸ģ�ֻ�޸��Ա�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : �޸ĳ�Ա��Ϣ��id=10 sex=1
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣ�ɹ�
               ��ѯ��Ա��Ϣ������һ��
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 002)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Modify("id=10 sex=1");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���Ԥ�ڽ�� */
    ulErrCode = INFO_data_GetData(10, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    EXPECT_EQ(10, stCfg.uiId);
    EXPECT_EQ(1, stCfg.enSex);
    EXPECT_EQ(20, stCfg.uiAge);
    EXPECT_EQ(175, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_003
#��  ��  ��  : ���ܲ���
#������������: �����޸ģ�ֻ�޸�����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : �޸ĳ�Ա��Ϣ��id=10 age=35
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣ�ɹ�
               ��ѯ��Ա��Ϣ������һ��
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 003)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Modify("id=10 age=35");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���Ԥ�ڽ�� */
    ulErrCode = INFO_data_GetData(10, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    EXPECT_EQ(10, stCfg.uiId);
    EXPECT_EQ(2, stCfg.enSex);
    EXPECT_EQ(35, stCfg.uiAge);
    EXPECT_EQ(175, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_004
#��  ��  ��  : ���ܲ���
#������������: �����޸ģ�ֻ�޸����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : �޸ĳ�Ա��Ϣ��id=10 height=181
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣ�ɹ�
               ��ѯ��Ա��Ϣ������һ��
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 004)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Modify("id=10 height=181");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���Ԥ�ڽ�� */
    ulErrCode = INFO_data_GetData(10, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    EXPECT_EQ(10, stCfg.uiId);
    EXPECT_EQ(2, stCfg.enSex);
    EXPECT_EQ(20, stCfg.uiAge);
    EXPECT_EQ(181, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_005
#��  ��  ��  : ���ܲ���
#������������: �����޸ģ�ֻ�޸�����������
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : �޸ĳ�Ա��Ϣ��id=10 name=jack123456 age=45
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣ�ɹ�
               ��ѯ��Ա��Ϣ������һ��
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 005)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Modify("id=10 name=jack123456 age=45");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���Ԥ�ڽ�� */
    ulErrCode = INFO_data_GetData(10, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    EXPECT_EQ(10, stCfg.uiId);
    EXPECT_EQ(2, stCfg.enSex);
    EXPECT_EQ(45, stCfg.uiAge);
    EXPECT_EQ(175, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack123456"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_006
#��  ��  ��  : ���ܲ���
#������������: �����޸ģ�ֻ�޸��Ա�+���
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : �޸ĳ�Ա��Ϣ��id=10 sex=1 height=185
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣ�ɹ�
               ��ѯ��Ա��Ϣ������һ��
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 006)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Modify("id=10 sex=1 height=185");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���Ԥ�ڽ�� */
    ulErrCode = INFO_data_GetData(10, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    EXPECT_EQ(10, stCfg.uiId);
    EXPECT_EQ(1, stCfg.enSex);
    EXPECT_EQ(20, stCfg.uiAge);
    EXPECT_EQ(185, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_007
#��  ��  ��  : �쳣����
#������������: ���Ų�����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : �޸ĳ�Ա��Ϣ��id=100 sex=1 height=185
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣʧ�ܣ�����ERROR_NOT_FOUND
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 007)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Modify("id=100 sex=1 height=185");
    EXPECT_EQ(ERROR_NOT_FOUND, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_008
#��  ��  ��  : �쳣����
#������������: ����Ϊ�Ƿ�ֵ
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : �޸ĳ�Ա��Ϣ��id=100005 sex=1 height=185
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣʧ�ܣ�����ERROR_INVALID_PARAMETER
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 008)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Modify("id=100005 sex=1 height=185");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_009
#��  ��  ��  : ѹ������
#������������: �޸Ĵ��������û���Ϣ
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ѭ���������û���Ϣ��id=x name=jack sex=2 age=20 height=175
#��       �� : ѭ���޸ĳ�Ա��Ϣ��id=x name=jackabc sex=1 age=35 height=195
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣ�ɹ�
               ��ѯ�û���Ϣ�޸���ȷ
#��  ��  ��  : wkf2298
#��      ��  : 2011��12��31��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 009)
{
    ULONG ulErrCode;
    UINT uiId;
    CHAR szInputStr[512];
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode = INFO_data_Init();
    for (uiId = 100000; uiId > 0; uiId = uiId - 20)
    {
        scnprintf(szInputStr, sizeof(szInputStr), "id=%u name=jack sex=2 age=20 height=175", uiId);
        ulErrCode |= INFO_proc_Add(szInputStr);
    }
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* �������й��ţ������޸ĺ��� */
    INFO_FOREACH(uiId)
    {
        scnprintf(szInputStr, sizeof(szInputStr), "id=%u name=jackabc sex=1 age=35 height=195", uiId);
        ulErrCode |= INFO_proc_Modify(szInputStr);
    }
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���Ԥ�ڽ�� */
    uiId = INFO_data_GetNext(993);
    ulErrCode = INFO_data_GetData(uiId, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    EXPECT_EQ(uiId, stCfg.uiId);
    EXPECT_EQ(1, stCfg.enSex);
    EXPECT_EQ(35, stCfg.uiAge);
    EXPECT_EQ(195, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jackabc"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_011
#��  ��  ��  : ���ܲ���
#������������: �޸�1����Ա������Ϣ�ɹ�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ���1����Ա
#��       �� : pcInputStr=Ա����Ϣ
#�� �� �� �� : ִ�в�����
#Ԥ �� �� �� : ��Ա�����޸�
#              INFO_proc_Modify���سɹ�
#��  ��  ��  : liaohui kf2309
#��      ��  : 2011-12-31
#######################################################################*/
TEST(UT_INFO_proc_Modify, 011)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;
    ULONG ulFirstMember = 12;

    /* ��ʼ������ */
    INFO_data_Init();

    /* ���һ����Ա */
    ulErrCode = INFO_proc_Add(g_szCorrectMemberInfo[ulFirstMember]);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    ulErrCode = INFO_data_GetData(g_stMemberData[ulFirstMember].uiId, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���ñ��⺯�� */
    ulErrCode = INFO_proc_Modify(g_szCorrectMemberInfo[ulFirstMember + 1]);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    ulErrCode = INFO_data_GetData(g_stMemberData[ulFirstMember].uiId, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    EXPECT_EQ(g_stMemberData[ulFirstMember + 1].enSex, stCfg.enSex);
    EXPECT_EQ(g_stMemberData[ulFirstMember + 1].uiAge, stCfg.uiAge);
    EXPECT_EQ(g_stMemberData[ulFirstMember + 1].uiHeight, stCfg.uiHeight);
    EXPECT_STREQ(g_stMemberData[ulFirstMember + 1].szName, stCfg.szName);

    /* ȥ��ʼ������ */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_012
#��  ��  ��  : ���ܲ���
#������������: �޸�3����Ա������Ϣ�ɹ�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ���3����Ա
#��       �� : pcInputStr=Ա����Ϣ
#�� �� �� �� : ִ�в�����
#Ԥ �� �� �� : ���г�Աɾ��
#              INFO_proc_Modify���سɹ�
#��  ��  ��  : liaohui kf2309
#��      ��  : 2011-12-31
#######################################################################*/
TEST(UT_INFO_proc_Modify, 012)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;
    INT iStart = 6;
    INT iEnd = 9;
    INT iModifyStart = 9;
    INT iModifyEnd = 12;
    INT iCur;
    BOOL_T bIsEmpty;

    /* ��ʼ������ */
    INFO_data_Init();

    /* ��ӳ�Ա */
    for (iCur = iStart; iCur < iEnd; iCur++)
    {
        ulErrCode = INFO_proc_Add(g_szCorrectMemberInfo[iCur]);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

        ulErrCode = INFO_data_GetData(g_stMemberData[iCur].uiId, &stCfg);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    }

    for (iCur = iModifyStart; iCur < iModifyEnd; iCur++)
    {
        /* ���ñ��⺯�� */
        ulErrCode = INFO_proc_Modify(g_szCorrectMemberInfo[iCur]);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
        ulErrCode = INFO_data_GetData(g_stMemberData[iCur].uiId, &stCfg);
        EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
        EXPECT_EQ(g_stMemberData[iCur].enSex, stCfg.enSex);
        EXPECT_EQ(g_stMemberData[iCur].uiAge, stCfg.uiAge);
        EXPECT_EQ(g_stMemberData[iCur].uiHeight, stCfg.uiHeight);
        EXPECT_STREQ(g_stMemberData[iCur].szName, stCfg.szName);
    }

    bIsEmpty = INFO_data_IsEmpty();
    EXPECT_EQ(BOOL_FALSE, bIsEmpty);

    /* ȥ��ʼ������ */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_013
#��  ��  ��  : ���ܲ���
#������������: �����޸ģ�ֻ�޸��Ա�+���+����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : �޸ĳ�Ա��Ϣ��id=10 sex=1 height=185 age=21
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣ�ɹ�
               ��ѯ��Ա��Ϣ������һ��
#��  ��  ��  : lifan
#��      ��  : 2016��8��7��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 013)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Modify("id=10 sex=1 height=185 age=21");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���Ԥ�ڽ�� */
    ulErrCode = INFO_data_GetData(10, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    EXPECT_EQ(10, stCfg.uiId);
    EXPECT_EQ(1, stCfg.enSex);
    EXPECT_EQ(21, stCfg.uiAge);
    EXPECT_EQ(185, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jack"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_014
#��  ��  ��  : ���ܲ���
#������������: �����޸ģ�ֻ�޸�����+�Ա�+����
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : �޸ĳ�Ա��Ϣ��id=10 sex=1 height=185 age=21
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣ�ɹ�
               ��ѯ��Ա��Ϣ������һ��
#��  ��  ��  : lifan
#��      ��  : 2016��8��7��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 014)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Modify("id=10 name=jackabc sex=1 age=21");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ���Ԥ�ڽ�� */
    ulErrCode = INFO_data_GetData(10, &stCfg);
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);
    EXPECT_EQ(10, stCfg.uiId);
    EXPECT_EQ(1, stCfg.enSex);
    EXPECT_EQ(21, stCfg.uiAge);
    EXPECT_EQ(175, stCfg.uiHeight);
    EXPECT_EQ(0, strcmp(stCfg.szName, "jackabc"));

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_015
#��  ��  ��  : �쳣����
#������������: ����Ƿ�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : �޸ĳ�Ա��Ϣ��id=100 age=0
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣʧ�ܣ�����ERROR_NOT_FOUND
#��  ��  ��  : lifan
#��      ��  : 2016��8��7��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 015)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Modify("id=100 age=1");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}

/*#######################################################################
#�����������: UT_INFO_proc_Modify_016
#��  ��  ��  : �쳣����
#������������: �Ա�Ƿ�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : �޸ĳ�Ա��Ϣ��id=100 sex=0
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣʧ�ܣ�����ERROR_NOT_FOUND
#��  ��  ��  : lifan
#��      ��  : 2016��8��7��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 016)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Modify("id=100 sex=3");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}
/*#######################################################################
#�����������: UT_INFO_proc_Modify_017
#��  ��  ��  : �쳣����
#������������: ��߷Ƿ�
#�� Ҫ �� �� : ��
#Ԥ �� �� �� : ��ʼ������ṹ
               ��ӳ�Ա��Ϣ��id=10 name=jack sex=2 age=20 height=175
#��       �� : �޸ĳ�Ա��Ϣ��id=100 height=0
#�� �� �� �� : ִ�в�������
#Ԥ �� �� �� : �޸ĳ�Ա��Ϣʧ�ܣ�����ERROR_NOT_FOUND
#��  ��  ��  : lifan
#��      ��  : 2016��8��7��
#######################################################################*/
TEST(UT_INFO_proc_Modify, 017)
{
    ULONG ulErrCode;
    INFO_CFG_S stCfg;

    /* ��ʼ�� */
    ulErrCode  = INFO_data_Init();
    ulErrCode |= INFO_proc_Add("id=10 name=jack sex=2 age=20 height=175");
    EXPECT_EQ(ERROR_SUCCESS, ulErrCode);

    /* ������Ӻ��� */
    ulErrCode = INFO_proc_Modify("id=100 height=301");
    EXPECT_EQ(ERROR_INVALID_PARAMETER, ulErrCode);

    /* ȥ��ʼ�� */
    INFO_data_Fini();
}