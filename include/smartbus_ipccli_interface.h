
#if !defined(_SMARTBUS_IPCCLI_INTERFACE_H_INCLUDED_)
#define _SMARTBUS_IPCCLI_INTERFACE_H_INCLUDED_

#include "smartbus.h"

#ifdef __cplusplus
extern "C" {
#endif


///////////////////////////////////////////////////////////////////
// 设置Trace函数
void SmartBusIpcCli_SetTrace(PTraceEx traceex,PTraceEx traceerr);

// 设置Trace函数
void SmartBusIpcCli_SetTraceStr(PTraceStr tracestr,PTraceStr traceerr);

// 初始化
// clientype： 客户端类型
// clientid： 客户端ID。非IPSC类型客户端，clientid >= 10 and <= 255
int SmartBusIpcCli_Init(int clienttype,int clientid);

// 释放
void SmartBusIpcCli_Release();

// 设置回调函数
// client_conn_cb： 客户端连接结果
// recv_cb： 接收数据回调
// disconnect_cb: 连接端口回调
// invokeflow_ret_cb: 远程调用流程结果
// arg: 自定义数据
void SmartBusIpcCli_SetCallBackFn(smartbus_cli_connection_cb client_conn_cb,
		smartbus_cli_recvdata_cb recv_cb,smartbus_cli_disconnect_cb disconnect_cb,
		smartbus_invokeflow_ret_cb invokeflow_ret_cb,smartbus_global_connect_cb global_connect_cb,
		void * arg);

// 设置回调函数自定义数据
// arg:				自定义数据
void SmartBusIpcCli_SetCallBackFnArg(void * arg);

// 设置回调函数
// callback_name： 待设定的回调函数名称
// callbackfn：	回调函数指针
void SmartBusIpcCli_SetCallBackFnEx(const char * callback_name,void * callbackfn);

// 创建连接
int SmartBusIpcCli_CreateConnect(const char * author_username,const char * author_pwd,const char * add_info);

// 发送数据
// cmd：命令
// cmdtype: 命令类型，值为 2
int SmartBusIpcCli_SendData(unsigned char cmd,unsigned char cmdtype,int dst_unitid,int dst_clientid,int dst_clienttype,const void * data,int size);

// 发送Ping
int SmartBusIpcCli_SendPing(int dst_unitid,int dst_clientid,int dst_clienttype,const void * data,int size);

// 远程调用流程
// 返回值：<0 表示执行错误。> 0 invoke_id，调用ID，用于流程结果返回匹配用途。
// server_unitid
// processindex
// projectid
// flowid		:
// mode		: 调用模式：0 有流程返回、1 无流程返回
// timeout		: 有流程返回时的等待超时值
// in_valuelist : 整型、浮点型、JSON数组（子流程开始节点的传人参数自动变换为dict类型数据。）（对应的字符串内容最大长度不超过32K字节）
int SmartBusIpcCli_RemoteInvokeFlow(int server_unitid,int processindex,const char * projectid,const char * flowid,int mode, int timeout,const char * in_valuelist);

#ifdef __cplusplus
}
#endif



#endif
