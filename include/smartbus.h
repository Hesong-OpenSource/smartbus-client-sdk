
#if !defined(_SMARTBUS_H_INCLUDED_)
#define _SMARTBUS_H_INCLUDED_

#ifndef MAX_GLOBAL_SMART_NODE
#define MAX_GLOBAL_SMART_NODE 			16
#endif

#define MAX_SMARTBUS_NETCLI_UNITID_NUM	32	// net客户端值范围就是：16 － 47

#define MIN_SMARTBUS_NETCLI_UNITID		MAX_GLOBAL_SMART_NODE	// 最小net客户端unitid值为16。Net客户端的unitid不能小于16
#define MAX_SMARTBUS_NETCLI_UNITID		MAX_GLOBAL_SMART_NODE + MAX_SMARTBUS_NETCLI_UNITID_NUM - 1	// 最大net客户端unitid值为47。Net客户端的unitid小于等于47

#define MAX_SMARTBUS_NODE_NUM			MAX_GLOBAL_SMART_NODE + MAX_SMARTBUS_NETCLI_UNITID_NUM		// 16 + 32 = 48 最大节点数
#define MAX_SMARTBUS_NODE_CLI_NUM		16	// 最大节点内的客户端数
#define MAX_SMARTBUS_NODE_IPCCLI_NUM	MAX_SMARTBUS_NODE_CLI_NUM	// 最大节点内的客户端数


#define SMARTBUS_CMDTYPE_INTERNAL 		0
#define SMARTBUS_CMDTYPE_SYSTEM		 	1
#define SMARTBUS_CMDTYPE_FILE		 	2	// 文件
#define SMARTBUS_CMDTYPE_USER		 	3	// 用户数据
#define SMARTBUS_CMDTYPE_GUARD_CMD	 	4	// 守候实例命令
#define SMARTBUS_CMDTYPE_GUARD_FILE	 	5	// 守候实例文件传送

#define SMARTBUS_SYSCMD_PING_ACK	 	8	// Ping应答包的cmdtype


// 节点类型
#define SMARTBUS_NODECLI_TYPE_NULL		0
#define SMARTBUS_NODECLI_TYPE_NODE		1
#define SMARTBUS_NODECLI_TYPE_IPSC		2
#define SMARTBUS_NODECLI_TYPE_MONITOR	3
#define SMARTBUS_NODECLI_TYPE_AGENT		4
#define SMARTBUS_NODECLI_TYPE_DB		5



/* SmartBus 错误码定义                 */
#define SMARTBUS_ERR_OK						 0
#define SMARTBUS_ERR_ARGUMENT				-1	// 无效参数
#define SMARTBUS_ERR_CONN_NOT_ESTAB			-2	// 连接尚未建立	Connection is not established		-2
#define SMARTBUS_ERR_CONNECT_BREAK			-3
#define SMARTBUS_ERR_AUTHOR					-4	// 验证失败
#define SMARTBUS_ERR_USER					-5
#define SMARTBUS_ERR_PWD						-6
#define SMARTBUS_ERR_BUFF_FULL				-7	// 缓冲区满
#define SMARTBUS_ERR_NODE_NOTEXIST			-8	// 节点不存在
#define SMARTBUS_ERR_CLI_NOTEXIST			-9	// 客户端不存在
#define SMARTBUS_ERR_CONNECTED				-10	// 重复连接
#define SMARTBUS_ERR_SEND_OWN				-11	// 发送给自己
#define SMARTBUS_ERR_UNITID_INVALID			-12	// 无效的unitid
#define SMARTBUS_ERR_CLIENTID_INVALID		-13	// 无效的clientid
#define SMARTBUS_ERR_NON_INIT				-14	// 尚未初始化
#define SMARTBUS_ERR_MAX_DATASIZE			-15	// 发送的数据太大
#define SMARTBUS_ERR_CMDTYPE_INVALID		-16	// 无效的命令类型
#define SMARTBUS_ERR_CLIENTTYPE_INVALID	-17	// 无效的客户端类型
#define SMARTBUS_ERR_SEND_DATA				-18	// 发送数据错误
#define SMARTBUS_ERR_MEM_ALLOC				-19	// 分配内存错误
#define SMARTBUS_ERR_ESTABLI_CONNECT		-20	// 建立连接失败
#define SMARTBUS_ERR_CLI_TOOMANY			-21	// 客户端太多
#define SMARTBUS_ERR_CLI_EXIST				-22	// 客户端已存在
#define SMARTBUS_ERR_DEST_NONEXIST			-23	// 目标不存在
#define SMARTBUS_ERR_REGISTERED_REPEAT		-24	// 重复注册
#define SMARTBUS_ERR_TIMEOUT					-25	// 超时


#define SMARTBUS_ERR_OTHER					-99	// 其它错误



#define MAX_SMARTBUS_IPADDR_SIZE			64

enum CONNECTED_STATUS {
	CONNECTED_STATUS_INIT = 0,
	CONNECTED_STATUS_CONNECTING = 1,
	CONNECTED_STATUS_READY = 2,
	CONNECTED_STATUS_FAIL = 3,
	CONNECTED_STATUS_BLOCK = 4,
	CONNECTED_STATUS_CLOSE = 5,
	CONNECTED_STATUS_CONNECTED = 6,
	CONNECTED_STATUS_OK = 7
};

#pragma pack(push) //保存对齐状态
#pragma pack(1)	//设定为1字节对齐


// 数据包头结构定义
typedef struct
{
	unsigned short	head_flag;	// 头标识	: 0x5b15

	unsigned char	cmd;
	unsigned char	cmdtype;

	char	src_unit_client_type;
	char	src_unit_id;
	char	src_unit_client_id;

	char	dest_unit_client_type;
	char	dest_unit_id;
	char	dest_unit_client_id;

	char	reserved[2];

	long	packet_size;	// c#里要定义成int32
	long	datalen;		// c#里要定义成int32
}SMARTBUS_PACKET_HEAD;

#pragma pack(pop)//恢复对齐状态

#ifdef WIN32
#ifndef WINAPI
#define WINAPI __stdcall
#endif
#else
#define WINAPI
#endif

//// 被客户端连接
// local_clientid 本地clientid
// accesspoint_unitid : 连接点的UnitID
// ack ： 连接注册结果： 0 建立连接成功、< 0 连接失败
typedef void (WINAPI *smartbus_cli_connection_cb)(void * arg,unsigned char local_clientid, int accesspoint_unitid,int ack);

typedef void (WINAPI *smartbus_cli_disconnect_cb)(void * arg,unsigned char local_clientid);

typedef void (WINAPI *smartbus_cli_recvdata_cb)(void * arg,unsigned char local_clientid, SMARTBUS_PACKET_HEAD * head,void * data,int size);


// 全局节点客户端连接、断开通知
// unitid : 节点客户端的unitid
// clientid : 客户端ID。是node中心节点连接时，clientid值为-1
// clienttype : 客户端类型
// status : 连接状态： 0 断开连接、1 新建连接、2 已有的连接
// add_info ： 连接附加信息
typedef void (WINAPI *smartbus_global_connect_cb)(void * arg,char unitid,char clientid,char clienttype,char status,const char * add_info);


// 调用流程ACK（描述远程流程调用是否成功）
// projectid : 项目ID
// invoke_id : 调用ID
// head :  包头信息。ret结果超时或失败时，head为 NULL
// ack ： 结果，1 调用成功（有且执行SUBSTART节点）、< 1 调用失败。
// msg : 调用失败时的信息描述
// 注： SmartBusIpcCli_RemoteInvokeFlow()、SmartBusNetCli_RemoteInvokeFlow() 直接返回失败的，不再触发smartbus_invokeflow_ack_cb回调。
typedef void (WINAPI *smartbus_invokeflow_ack_cb)(void * arg,unsigned char local_clientid,SMARTBUS_PACKET_HEAD * head,const char * projectid,int invoke_id,int ack, const char * msg);

// 调用流程结果返回（子流程结束节点）
// projectid : 项目ID
// invoke_id : 调用ID
// head :  包头信息。ret结果超时或失败时，head为 NULL
// ret ： 结果，1 是结果返回、 < 1 错误（-25 超时）
// param : 结果参数串,JSON数组格式
typedef void (WINAPI *smartbus_invokeflow_ret_cb)(void * arg,unsigned char local_clientid,SMARTBUS_PACKET_HEAD * head,const char * projectid,int invoke_id,int ret, const char * param);


//
typedef void (WINAPI *smartbus_unitdata_cb)(unsigned char	cmd,unsigned char	cmdtype,const unsigned char * data,int size);


typedef void (WINAPI *PTraceEx)(const char * lpszMessage,...);

typedef void (WINAPI *PTraceStr)(const char * lpszMessage);


#endif
