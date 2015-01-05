/**
 * @file smartbus_netcli_interface.h
 * @brief NET客户端API
 */

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
#define CDECL   __cdecl
#endif
#else
#define CDECL
#endif

/**
 * @brief 设置Trace函数
 */
SMARTBUS_NET_CLI_API void CDECL SmartBusNetCli_SetTrace(PTraceEx traceex,PTraceEx traceerr);

/**
 * @brief 设置Trace函数
 */
SMARTBUS_NET_CLI_API void CDECL SmartBusNetCli_SetTraceStr(PTraceStr traceex,PTraceStr traceerr);


/**
 * @brief 初始化
 * 
 * @param unitid 在连接到Smartbus体系后，本节点的单元ID。unitid >= 16，且全局唯一，不得重复
 * @return 初始化结果。1：成功；其它：见错误码
 * 
 * @remark 在调用其它库函数之前，请首先初始化
 */
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_Init(unsigned char unitid);


// 释放
/**
 * @brief 释放
 */
SMARTBUS_NET_CLI_API void CDECL SmartBusNetCli_Release();


/**
 * @brief 设置回调函数
 * 
 * @param client_conn_cb 接收数据回调
 * @param recv_cb 接收数据回调
 * @param disconnect_cb 连接断开回调
 * @param invokeflow_ret_cb 调用流程结果回调
 * @param global_connect_cb 全局连接事件回调
 * @param arg 自定义数据
 */
SMARTBUS_NET_CLI_API void CDECL SmartBusNetCli_SetCallBackFn(smartbus_cli_connection_cb client_conn_cb,
        smartbus_cli_recvdata_cb recv_cb,smartbus_cli_disconnect_cb disconnect_cb,
        smartbus_invokeflow_ret_cb invokeflow_ret_cb,smartbus_global_connect_cb global_connect_cb,
        void * arg);


/**
 * @brief 设置回调函数自定义数据
 * 
 * @param arg 自定义数据
 */
SMARTBUS_NET_CLI_API void CDECL  SmartBusNetCli_SetCallBackFnArg(void * arg);


/**
 * @brief 设置回调函数
 * 
 * @param callback_name 待设定的回调函数名称
 * @param callbackfn 回调函数指针
 */
SMARTBUS_NET_CLI_API void CDECL  SmartBusNetCli_SetCallBackFnEx(const char * callback_name,void * callbackfn);


/**
 * @brief 创建连接
 * @details 调用该函数后，如果该函数没有直接返回失败，客户端会自动尝试连接smartbus服务器，并在连接断开/失败时自动尝试重连
 * 
 * @param local_clientid 本地clientid, >= 0 and <= 255
 * @param local_clienttype 本地clienttype
 * @param masterip 主服务器IP地址
 * @param masterport 主服务器端口
 * @param slaverip 从服务器IP地址。没有从地址的，填写0，或者""
 * @param slaverport 从服务器端口。没有从端口的，填写0xFFFF
 * @param author_username 用户名
 * @param author_pwd 密码
 * @param add_info 附加信息
 * @return 连接结果。1：成功。其它：见错误码
 */
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_CreateConnect(unsigned char local_clientid,int local_clienttype,const char * masterip,unsigned short masterport,const char * slaverip,unsigned short slaverport,const char * author_username,const char * author_pwd,const char * add_info);


/**
 * @brief 发送数据
 * 
 * @param local_clientid 发送数据的本地客户端ID
 * @param cmd 命令
 * @param cmdtype 命令类型，值为 2
 * @param dst_unitid 目标的smartbus单元ID
 * @param dst_clientid 目标的smartbus客户端ID
 * @param dst_clienttype 目标的smartbus客户端类型
 * @param data 要发送的数据
 * @param size 要发送的数据的字节长度
 * @return 连接结果。0 表示成功、 < 0 表示错误。其它：见错误码
 */
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_SendData(unsigned char local_clientid,unsigned char cmd,unsigned char cmdtype,int dst_unitid,int dst_clientid,int dst_clienttype,const void * data,int size);


/**
 * @brief 发送PING命令
 * 
 * @param local_clientid 发送数据的本地客户端ID
 * @param dst_unitid 目标的smartbus单元ID
 * @param dst_clientid 目标的smartbus客户端ID
 * @param dst_clienttype 目标的smartbus客户端类型
 * @param data 要发送的数据
 * @param size 要发送的数据的字节长度
 * @return 结果。0 表示成功、 < 0 表示错误。其它：见错误码
 */
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_SendPing(unsigned char local_clientid,int dst_unitid,int dst_clientid,int dst_clienttype,const void * data,int size);


/**
 * @brief 调用流程
 * 
 * @param local_clientid 进行调用的本地clientid
 * @param server_unitid 目标IPSC服务器smartbus单元ID
 * @param ipscindex IPSC进程ID
 * @param projectid 流程项目ID
 * @param flowid 流程ID
 * @param mode 调用模式：0 有流程返回、1 无流程返回
 * @param timeout 有流程返回时的等待超时值
 * @param in_valuelist 流程输入参数里表。简单数据类型JSON数组（子流程开始节点的传人参数自动变换为list类型数据。）（对应的字符串内容最大长度不超过32K字节）
 * @return <0 表示执行错误。> 0 invoke_id，调用ID，用于流程结果返回匹配用途。
 */
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_RemoteInvokeFlow(unsigned char local_clientid,int server_unitid,int ipscindex,const char * projectid,const char * flowid,int mode, int timeout,const char * in_valuelist);


/**
 * @brief 发送通知消息
 * 
 * @param local_clientid 进行调用的本地clientid
 * @param server_unitid 目标IPSC服务器smartbus单元ID
 * @param processindex IPSC进程ID
 * @param projectid 流程项目ID
 * @param title 通知的标示
 * @param mode 调用模式
 * @param expires 消息有效期。单位ms
 * @param param 消息数据
 * @return 返回值：> 0 invoke_id，调用ID。< 0 表示错误。
 */
SMARTBUS_NET_CLI_API int CDECL SmartBusNetCli_SendNotify(unsigned char local_clientid,int server_unitid,int processindex,const char * projectid,const char * title,int mode, int expires,const char * param);

#ifdef __cplusplus
}
#endif



#endif
