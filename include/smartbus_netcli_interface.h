
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

// 设置Trace函数
SMARTBUS_NET_CLI_API void CDECL SmartBusNetCli_SetTrace(PTraceEx traceex,PTraceEx traceerr);
SMARTBUS_NET_CLI_API void CDECL SmartBusNetCli_SetTraceStr(PTraceStr traceex,PTraceStr traceerr);

// 初始化
// unitid： 客户端ID。unitid >= 16
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_Init(unsigned char unitid);

// 释放
SMARTBUS_NET_CLI_API void CDECL SmartBusNetCli_Release();

// 设置回调函数
// client_conn_cb： 客户端连接结果
// recv_cb：		接收数据回调
// disconnect_cb:	连接端口回调
// arg:				自定义数据
SMARTBUS_NET_CLI_API void CDECL SmartBusNetCli_SetCallBackFn(smartbus_cli_connection_cb client_conn_cb,
		smartbus_cli_recvdata_cb recv_cb,smartbus_cli_disconnect_cb disconnect_cb,
		smartbus_invokeflow_ret_cb invokeflow_ret_cb,smartbus_global_connect_cb global_connect_cb,
		void * arg);

// 设置回调函数自定义数据
// arg:				自定义数据
SMARTBUS_NET_CLI_API void CDECL  SmartBusNetCli_SetCallBackFnArg(void * arg);

// 设置回调函数
// callback_name： 待设定的回调函数名称
// callbackfn：	回调函数指针
SMARTBUS_NET_CLI_API void CDECL  SmartBusNetCli_SetCallBackFnEx(const char * callback_name,void * callbackfn);

// 创建连接
// local_clientid		本地clientid, >= 0 and <= 255
// local_clienttype		本地clienttype
// masterip				目标主IP地址
// masterport			目标主端口
// slaverip				目标从IP地址。没有从地址的，填写0，或者""
// slaverport			目标从端口。没有从端口的，填写0xFFFF
// author_username		验证用户名
// author_pwd			验证密码
// add_info				附加信息
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_CreateConnect(unsigned char local_clientid,int local_clienttype,const char * masterip,unsigned short masterport,const char * slaverip,unsigned short slaverport,const char * author_username,const char * author_pwd,const char * add_info);

// 发送数据
// 返回值：0 表示成功、 < 0 表示错误。
// local_clientid		本地clientid
// cmd：命令
// cmdtype: 命令类型，值为 2
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_SendData(unsigned char local_clientid,unsigned char cmd,unsigned char cmdtype,int dst_unitid,int dst_clientid,int dst_clienttype,const void * data,int size);

// SendPing
// 返回值：0 表示成功、 < 0 表示错误。
// local_clientid		本地clientid
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_SendPing(unsigned char local_clientid,int dst_unitid,int dst_clientid,int dst_clienttype,const void * data,int size);

// 远程调用流程
// 返回值：> 0 invoke_id，调用ID，用于流程结果返回匹配用途。< 0 表示错误。
// local_clientid		本地clientid
// server_unitid		目标unitid
// ipscindex			目标clientid
// projectid			目标流程的ProjectID	
// flowid				目标流程的FlowID
// mode		:			调用模式：0 有流程返回、1 无流程返回
// timeout		:		有流程返回时的等待超时值。单位ms
// in_valuelist :		整型、浮点型、JSON数组（子流程开始节点的传人参数自动变换为dict类型数据。）（对应的字符串内容最大长度不超过16K字节）
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_RemoteInvokeFlow(unsigned char local_clientid,int server_unitid,int ipscindex,const char * projectid,const char * flowid,int mode, int timeout,const char * in_valuelist);


// 发送通知消息
// 返回值：> 0 invoke_id，调用ID。< 0 表示错误。
// local_clientid		本地clientid
// server_unitid		目标unitid
// ipscindex			目标clientid
// projectid			目标流程的ProjectID
// title				通知的标示
// mode		:		调用模式
// expires		:		消息有效期。单位ms
// param 		:		消息数据
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_SendNotify(unsigned char local_clientid,int server_unitid,int processindex,const char * projectid,const char * title,int mode, int expires,const char * param);

#ifdef __cplusplus
}
#endif



#endif
