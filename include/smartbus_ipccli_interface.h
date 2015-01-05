/**
 * @file smartbus_ipccli_interface.h
 * @brief IPC客户端API
 */


#if !defined(_SMARTBUS_IPCCLI_INTERFACE_H_INCLUDED_)
#define _SMARTBUS_IPCCLI_INTERFACE_H_INCLUDED_

#include "smartbus.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief 设置Trace函数
 */
void SmartBusIpcCli_SetTrace(PTraceEx traceex,PTraceEx traceerr);


/**
 * @brief 设置Trace函数
 */
void SmartBusIpcCli_SetTraceStr(PTraceStr tracestr,PTraceStr traceerr);


/**
 * @brief 新建Smartbus客户端
 * @details 注意IPC类型的客户端在一个进程内只能新建一个
 * 
 * @param clienttype Smartbus客户端类型
 * @param clientid Smartbus客户端ID。非IPSC类型客户端，clientid >= 10 and <= 255。
 * 
 * @return 新建结果。1：成功；其它：见错误码
 * 
 * @remark 在调用其它库函数之前，请首先初始化
 */
int SmartBusIpcCli_Init(int clienttype,int clientid);


/**
 * @brief 释放
 */
void SmartBusIpcCli_Release();


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
void SmartBusIpcCli_SetCallBackFn(smartbus_cli_connection_cb client_conn_cb,
        smartbus_cli_recvdata_cb recv_cb,smartbus_cli_disconnect_cb disconnect_cb,
        smartbus_invokeflow_ret_cb invokeflow_ret_cb,smartbus_global_connect_cb global_connect_cb,
        void * arg);


/**
 * @brief 设置回调函数自定义数据
 * 
 * @param arg 自定义数据
 */
void SmartBusIpcCli_SetCallBackFnArg(void * arg);


/**
 * @brief 设置回调函数
 * 
 * @param callback_name 待设定的回调函数名称
 * @param callbackfn 回调函数指针
 */
void SmartBusIpcCli_SetCallBackFnEx(const char * callback_name,void * callbackfn);


/**
 * @brief 创建连接
 * @details 调用该函数后，如果该函数没有直接返回失败，客户端会自动尝试连接smartbus服务器，并在连接断开/失败时自动尝试重连
 * 
 * @param author_username 用户名
 * @param author_pwd 密码
 * @param add_info 附加信息
 * @return 结果。1：成功。其它：见错误码
 */
int SmartBusIpcCli_CreateConnect(const char * author_username,const char * author_pwd,const char * add_info);


/**
 * @brief 发送数据
 * 
 * @param cmd 命令
 * @param cmdtype 命令类型，值为 2
 * @param dst_unitid 目标的smartbus单元ID
 * @param dst_clientid 目标的smartbus客户端ID
 * @param dst_clienttype 目标的smartbus客户端类型
 * @param data 要发送的数据
 * @param size 要发送的数据的字节长度
 * @return 结果。0 表示成功、 < 0 表示错误。其它：见错误码
 */
int SmartBusIpcCli_SendData(unsigned char cmd,unsigned char cmdtype,int dst_unitid,int dst_clientid,int dst_clienttype,const void * data,int size);


/**
 * @brief 发送PING命令
 * 
 * @param dst_unitid 目标的smartbus单元ID
 * @param dst_clientid 目标的smartbus客户端ID
 * @param dst_clienttype 目标的smartbus客户端类型
 * @param data 要发送的数据
 * @param size 要发送的数据的字节长度
 * @return 结果。0 表示成功、 < 0 表示错误。其它：见错误码
 */
int SmartBusIpcCli_SendPing(int dst_unitid,int dst_clientid,int dst_clienttype,const void * data,int size);


/**
 * @brief 调用流程
 * 
 * @param server_unitid 目标IPSC服务器smartbus单元ID
 * @param processindex IPSC进程ID
 * @param projectid 流程项目ID
 * @param flowid 流程ID
 * @param mode 调用模式：0 有流程返回、1 无流程返回
 * @param timeout 有流程返回时的等待超时值
 * @param in_valuelist 流程输入参数里表。简单数据类型JSON数组（子流程开始节点的传人参数自动变换为list类型数据。）（对应的字符串内容最大长度不超过32K字节）
 * @return <0 表示执行错误。> 0 invoke_id，调用ID，用于流程结果返回匹配用途。
 */
int SmartBusIpcCli_RemoteInvokeFlow(int server_unitid,int processindex,const char * projectid,const char * flowid,int mode, int timeout,const char * in_valuelist);


/**
 * @brief 发送通知消息
 * 
 * @param server_unitid 目标IPSC服务器smartbus单元ID
 * @param processindex IPSC进程ID
 * @param projectid 流程项目ID
 * @param title 通知的标示
 * @param mode 调用模式
 * @param expires 消息有效期。单位ms
 * @param param 消息数据
 * @return 返回值：> 0 invoke_id，调用ID。< 0 表示错误。
 */
int SmartBusNetCli_SendNotify(int server_unitid,int processindex,const char * projectid,const char * title,int mode, int expires,const char * param);


#ifdef __cplusplus
}
#endif



#endif
