
#if !defined(_SMARTBUS_NETCLI_INTERFACE_H_INCLUDED_)
#define _SMARTBUS_NETCLI_INTERFACE_H_INCLUDED_

#include "smartbus.h"

#ifdef WIN32
#ifdef SMARTBUS_NET_CLI_EXPORTS
#define SMARTBUS_NET_CLI_API __declspec(dllexport)
#else
#define SMARTBUS_NET_CLI_API __declspec(dllimport)
#endif
#else
#define SMARTBUS_NET_CLI_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////
#ifdef WIN32
#ifndef CDECL
#define CDECL	__cdecl
#endif
#else
#define CDECL
#endif

// ����Trace����
SMARTBUS_NET_CLI_API void CDECL SmartBusNetCli_SetTrace(PTraceEx traceex,PTraceEx traceerr);
SMARTBUS_NET_CLI_API void CDECL SmartBusNetCli_SetTraceStr(PTraceStr traceex,PTraceStr traceerr);

// ��ʼ��
// unitid�� �ͻ���ID��unitid >= 16
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_Init(unsigned char unitid);

// �ͷ�
SMARTBUS_NET_CLI_API void CDECL SmartBusNetCli_Release();

// ���ûص�����
// client_conn_cb�� �ͻ������ӽ��
// recv_cb��		�������ݻص�
// disconnect_cb:	���Ӷ˿ڻص�
// arg:				�Զ�������
SMARTBUS_NET_CLI_API void CDECL SmartBusNetCli_SetCallBackFn(smartbus_cli_connection_cb client_conn_cb,
		smartbus_cli_recvdata_cb recv_cb,smartbus_cli_disconnect_cb disconnect_cb,
		smartbus_invokeflow_ret_cb invokeflow_ret_cb,smartbus_global_connect_cb global_connect_cb,
		void * arg);

// ���ûص������Զ�������
// arg:				�Զ�������
SMARTBUS_NET_CLI_API void CDECL  SmartBusNetCli_SetCallBackFnArg(void * arg);

// ���ûص�����
// callback_name�� ���趨�Ļص���������
// callbackfn��	�ص�����ָ��
SMARTBUS_NET_CLI_API void CDECL  SmartBusNetCli_SetCallBackFnEx(const char * callback_name,void * callbackfn);

// ��������
// local_clientid		����clientid, >= 0 and <= 255
// local_clienttype		����clienttype
// masterip				Ŀ����IP��ַ
// masterport			Ŀ�����˿�
// slaverip				Ŀ���IP��ַ��û�дӵ�ַ�ģ���д0������""
// slaverport			Ŀ��Ӷ˿ڡ�û�дӶ˿ڵģ���д0xFFFF
// author_username		��֤�û���
// author_pwd			��֤����
// add_info				������Ϣ
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_CreateConnect(unsigned char local_clientid,int local_clienttype,const char * masterip,unsigned short masterport,const char * slaverip,unsigned short slaverport,const char * author_username,const char * author_pwd,const char * add_info);

// ��������
// ����ֵ��0 ��ʾ�ɹ��� < 0 ��ʾ����
// local_clientid		����clientid
// cmd������
// cmdtype: �������ͣ�ֵΪ 2
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_SendData(unsigned char local_clientid,unsigned char cmd,unsigned char cmdtype,int dst_unitid,int dst_clientid,int dst_clienttype,const void * data,int size);

// SendPing
// ����ֵ��0 ��ʾ�ɹ��� < 0 ��ʾ����
// local_clientid		����clientid
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_SendPing(unsigned char local_clientid,int dst_unitid,int dst_clientid,int dst_clienttype,const void * data,int size);

// Զ�̵�������
// ����ֵ��> 0 invoke_id������ID���������̽������ƥ����;��< 0 ��ʾ����
// local_clientid		����clientid
// server_unitid		Ŀ��unitid
// ipscindex			Ŀ��clientid
// projectid			Ŀ�����̵�ProjectID	
// flowid				Ŀ�����̵�FlowID
// mode		:			����ģʽ��0 �����̷��ء�1 �����̷���
// timeout		:		�����̷���ʱ�ĵȴ���ʱֵ����λms
// in_valuelist :		���͡������͡�JSON���飨�����̿�ʼ�ڵ�Ĵ��˲����Զ��任Ϊdict�������ݡ�������Ӧ���ַ���������󳤶Ȳ�����16K�ֽڣ�
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_RemoteInvokeFlow(unsigned char local_clientid,int server_unitid,int ipscindex,const char * projectid,const char * flowid,int mode, int timeout,const char * in_valuelist);


// ����֪ͨ��Ϣ
// ����ֵ��> 0 invoke_id������ID��< 0 ��ʾ����
// local_clientid		����clientid
// server_unitid		Ŀ��unitid
// ipscindex			Ŀ��clientid
// projectid			Ŀ�����̵�ProjectID
// title				֪ͨ�ı�ʾ
// mode		:		����ģʽ
// expires		:		��Ϣ��Ч�ڡ���λms
// param 		:		��Ϣ����
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_SendNotify(unsigned char local_clientid,int server_unitid,int processindex,const char * projectid,const char * title,int mode, int expires,const char * param);

#ifdef __cplusplus
}
#endif



#endif
