/*****************************************************************************
 Copyright (c) 2008, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
------------------------------------------------------------------------------
                            error.h
  Project Code: Comware V7
   Module Name:
  Date Created: 2008-4-7 
        Author: c02254
   Description: ͨ�ô�����

------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------------
                                                                             
*****************************************************************************/

#ifndef _SYS_ERROR_H_
#define _SYS_ERROR_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* ȥ�����ȼ��ȱ��,�Ӵ�����ת���� ��ԴID */
#define ERROR_GET_RCID(errno)           ((errno) & 0x0FFFFFFF);  

#define ERROR_SEVERITY_SUCCESS          0x0
#define ERROR_SEVERITY_INFO             0x1
#define ERROR_SEVERITY_WARNING          0x2
#define ERROR_SEVERITY_ERROR            0x3

#define ERROR_GET_MODULEFACILITY(ulMID) (((ulMID)>>16)&0xfff)

#define ERROR_DEFINE(sev,fac,code)      ((ULONG)(((ULONG)((sev)&3)<<29) | \
                                        ((ULONG)((fac)& 0x0FFF)<<16)    | \
                                        ((ULONG)((code)&0xFFFF))))

#define ERROR_GET_SEVERITY(errno)       (((ULONG)(errno)>>29)&3) 
#define ERROR_GET_FACILITY(errno)       (((ULONG)(errno)>>16)&0x0FFF)
#define ERROR_GET_CODE(errno)           ((ULONG)(errno)&0xFFFF)

#define IS_SUCCED(errno)                ((((ULONG)(errno)>>29)&3) == ERROR_SEVERITY_SUCCESS)
#define IS_INFO(errno)                  ((((ULONG)(errno)>>29)&3) == ERROR_SEVERITY_INFO)
#define IS_WARNING(errno)               ((((ULONG)(errno)>>29)&3) == ERROR_SEVERITY_WARNING)
#define IS_ERROR(errno)                 ((((ULONG)(errno)>>29)&3) == ERROR_SEVERITY_ERROR)

#define ERROR_COMMON_FACILITY                 ERROR_GET_MODULEFACILITY(0x00010000UL)
/* Leopard�Ĵ����� ȡֵ�� 0x00010000 (FacilityΪ0x001) ��ʼ��
   �����������FacilityΪ0x001,����ģ��Ĵ������Facility��0x002��ʼ��
*/   
                                        
#define ERROR_SUCCESS                         0x0000UL
#define ERROR_FAILED                          ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0x1UL)
#define ERROR_INVALID_PARAMETER               ERROR_DEFINE(ERROR_SEVERITY_INFO,    ERROR_COMMON_FACILITY, 0x2UL)
#define ERROR_BAD_STATE                       ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x3UL)
#define ERROR_BAD_MSG                         ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x4UL)
#define ERROR_NOT_FOUND                       ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0x5UL)
#define ERROR_ALREADY_EXIST                   ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0x6UL)
#define ERROR_TIMEOUT                         ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0x7UL)
#define ERROR_NOTSUPPORT                      ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0x8UL)
#define ERROR_INCOMPLETE                      ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0x9UL)
#define ERROR_NOT_INITIALIZED                 ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0xAUL)
#define ERROR_NO_ENOUGH_RESOURCE              ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0xBUL)
#define ERROR_VALUE_OUT_OF_RANGE              ERROR_DEFINE(ERROR_SEVERITY_INFO,    ERROR_COMMON_FACILITY, 0xCUL)
#define ERROR_INIT_ERROR                      ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0xDUL)
#define ERROR_NOT_READY                       ERROR_DEFINE(ERROR_SEVERITY_INFO,    ERROR_COMMON_FACILITY, 0xEUL)
#define ERROR_NO_ENOUGH_HARDWARE_RESOURCE     ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0xFUL)
#define ERROR_RESOURCE_CONFLICT               ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0x10UL)
#define ERROR_VLAN_NOTEXIST                   ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x11UL)
#define ERROR_VLAN_NOTSTATIC                  ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x12UL)
#define ERROR_VLAN_ISSUBVLAN                  ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x13UL)
#define ERROR_VLAN_OVERFLOWLIMIT              ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x14UL)
#define ERROR_VLAN_NOINTERFACE                ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x15UL)  /* The vlan-interface does not exist.*/
#define ERROR_VLAN_GETSUPERVLANIDFAILED       ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x16UL)  /* Failed to get super vlan ID */
#define ERROR_VLAN_GETSUPERVLANIFFAILED       ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x17UL)  /* Failed to get super vlan interface */
#define ERROR_INVALID_IP                      ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x18UL)  /* Invalid IP address*/
#define ERROR_INVALID_MAC                     ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x19UL)  /* Invalid MAC address*/
#define ERROR_FEATURE_NOT_ENABLED             ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x1AUL)  /* process hasn't been started */
#define ERROR_VPN_NOTEXIST                    ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x20UL)  /* VPN-Instance does not exist */
#define ERROR_PORT_NOTALLOWVLAN               ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x21UL)  /* Port doesn't belong to VLAN or trunk doesn't allow VLAN to pass */
#define ERROR_ENTRY_REACHLIMIT                ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x22UL)  /* Too many entries */
#define ERROR_END_OF_TABLE                    ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x23UL)  /* Too many entries */
#define ERROR_BATCH_COMPLETE                  ERROR_DEFINE(ERROR_SEVERITY_SUCCESS, ERROR_COMMON_FACILITY, 0x24UL)
#define ERROR_PERMISSION_DENY                 ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x25UL)  /* Permission denied */
#define ERROR_VLAN_ENDVLANLESSTHENSTARTVLAN   ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x26UL)  /* The end VLAN ID must be greater than or equal to the start VLAN ID. */
#define ERROR_GROUP_DENY                      ERROR_DEFINE(ERROR_SEVERITY_ERROR,   ERROR_COMMON_FACILITY, 0x27UL)  /* group denied */

#ifndef __KERNEL__

/*****************************************************************************
  Description: ���ñ�ִ���̵߳Ĵ�����
        Input: IN INT   iErrorNo   ָ���Ĵ�����
                (�����Ǳ�׼�����룬Ҳ������Leopard������)
       Output: None
       Return: None
      Caution: ֻ�����û�̬����
*****************************************************************************/
VOID SetLastError(IN INT iErrorNo);

/*****************************************************************************
  Description: ��ȡ��ִ���̵߳Ĵ�����
        Input: None
       Output: None
       Return: INT    ��ǰ�߳�������õĴ����롣 
      Caution: ֻ�����û�̬����
*****************************************************************************/
INT  GetLastError (VOID);

/*****************************************************************************
  Description: ��ӡ���̵߳Ĵ�����Ϣ(ͨ��GetLastError��ȡ��ǰ������),
               �������� perror.��������:

                1. �ýӿڼ��ܴ�ӡComware V7�����룬Ҳ�ܴ�ӡ��׼�����롣 
                2. perror��ӡ��ȱʡ�������̨stdout�����Ϣ�������ӿ������½��
                   �û������ʾ��Ϣ�� 
                   �ú�����Ҫ����Ϊ�����д���Ĳ��������á�
                3. perror��ӡ�Ƕ������:No such file or directory
                   ���ӿڴ�ӡ�����������.

        Input: IN CHAR * pcMsg,    ���������������Ϣ���Ը�����
       Output: None
       Return: None
*****************************************************************************/ 
VOID  PrintErrorMsg(IN CHAR * pcMsg);

#endif



/*****************************************************************************
  Description: ��������Ĵ�����iErrorNo��ʽ��������Ϣ, �������ṩ������,
               ��������strerror_r �ӿ�,
               ��������:
               1. �ýӿڼ��ܸ�ʽ��Comware V7�����룬Ҳ�ܸ�ʽ����׼�����롣 
        Input: IN INT   iErrorNo,     ָ���Ĵ����롣
               IN ULONG ulLen,        ָ��������������ĳ��ȡ�
       Output: OUT CHAR *pcBuf,       ָ�������������
       Return: �����������ַ
      Caution: Ϊ�˱�֤�ͱ�׼��strerror_r �ӿڼ��ݣ����ӿڵ�IN��OUT˳�򲻷��Ϲ淶
               ��ʽ�����ɵ��ַ�����һ�㲻�����ؼ��𣬿�������������䣬Ҳ�����Ƕ��
               
               �������û�̬���ں�̬����,����ش�����������ں�ע�ᡣ
*****************************************************************************/ 
CHAR * FormatErrorMsg(IN INT iErrorNo, OUT CHAR * pcBuf,IN ULONG ulLen);


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */
#endif /* _SYS_ERROR_H_ */

