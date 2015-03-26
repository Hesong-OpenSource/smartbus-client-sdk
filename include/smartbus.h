/**
 * @file smartbus.h
 */

#if !defined(_SMARTBUS_H_INCLUDED_)
#define _SMARTBUS_H_INCLUDED_

#ifndef MAX_GLOBAL_SMART_NODE
#define MAX_GLOBAL_SMART_NODE 			16
#endif

#define MAX_SMARTBUS_NETCLI_UNITID_NUM	32	/**< net客户端值范围就是：16 － 47

 #define MIN_SMARTBUS_NETCLI_UNITID		MAX_GLOBAL_SMART_NODE	/**< 最小net客户端unitid值为16。Net客户端的unitid不能小于16
 #define MAX_SMARTBUS_NETCLI_UNITID		MAX_GLOBAL_SMART_NODE + MAX_SMARTBUS_NETCLI_UNITID_NUM - 1	/**< 最大net客户端unitid值为47。Net客户端的unitid小于等于47

 #define MAX_SMARTBUS_NODE_NUM			MAX_GLOBAL_SMART_NODE + MAX_SMARTBUS_NETCLI_UNITID_NUM		/**< 16 + 32 = 48 最大节点数
 #define MAX_SMARTBUS_NODE_CLI_NUM		16	/**< 最大节点内的客户端数
 #define MAX_SMARTBUS_NODE_IPCCLI_NUM	MAX_SMARTBUS_NODE_CLI_NUM	/**< 最大节点内的客户端数

 #define SMARTBUS_CMDTYPE_INTERNAL 		0
 #define SMARTBUS_CMDTYPE_SYSTEM		 	1
 #define SMARTBUS_CMDTYPE_FILE		 	2	/**< 文件
 #define SMARTBUS_CMDTYPE_USER		 	3	/**< 用户数据
 #define SMARTBUS_CMDTYPE_GUARD_CMD	 	4	/**< 守候实例命令
 #define SMARTBUS_CMDTYPE_GUARD_FILE	 	5	/**< 守候实例文件传送

 #define SMARTBUS_SYSCMD_PING_ACK	 	8	/**< Ping应答包的cmdtype

 // 节点类型
 #define SMARTBUS_NODECLI_TYPE_NULL		0
 #define SMARTBUS_NODECLI_TYPE_NODE		1
 #define SMARTBUS_NODECLI_TYPE_IPSC		2
 #define SMARTBUS_NODECLI_TYPE_MONITOR	3
 #define SMARTBUS_NODECLI_TYPE_AGENT		4
 #define SMARTBUS_NODECLI_TYPE_DB		5

 /* SmartBus 错误码定义                 */
#define SMARTBUS_ERR_OK						 0
#define SMARTBUS_ERR_ARGUMENT				-1	/**< 无效参数 */
#define SMARTBUS_ERR_CONN_NOT_ESTAB			-2	/**< 连接尚未建立	Connection is not established -2 */
#define SMARTBUS_ERR_CONNECT_BREAK			-3
#define SMARTBUS_ERR_AUTHOR					-4	/**<< 验证失败 */
#define SMARTBUS_ERR_USER					-5
#define SMARTBUS_ERR_PWD						-6
#define SMARTBUS_ERR_BUFF_FULL				-7	/**< 缓冲区满 */
#define SMARTBUS_ERR_NODE_NOTEXIST			-8	/**< 节点不存在 */
#define SMARTBUS_ERR_CLI_NOTEXIST			-9	/**< 客户端不存在 */
#define SMARTBUS_ERR_CONNECTED				-10	/**< 重复连接 */
#define SMARTBUS_ERR_SEND_OWN				-11	/**< 发送给自己 */
#define SMARTBUS_ERR_UNITID_INVALID			-12	/**< 无效的unitid */
#define SMARTBUS_ERR_CLIENTID_INVALID		-13	/**< 无效的clientid */
#define SMARTBUS_ERR_NON_INIT				-14	/**< 尚未初始化 */
#define SMARTBUS_ERR_MAX_DATASIZE			-15	/**< 发送的数据太大 */
#define SMARTBUS_ERR_CMDTYPE_INVALID		-16	/**< 无效的命令类型 */
#define SMARTBUS_ERR_CLIENTTYPE_INVALID	-17	/**< 无效的客户端类型 */
#define SMARTBUS_ERR_SEND_DATA				-18	/**< 发送数据错误 */
#define SMARTBUS_ERR_MEM_ALLOC				-19	/**< 分配内存错误 */
#define SMARTBUS_ERR_ESTABLI_CONNECT		-20	/**< 建立连接失败 */
#define SMARTBUS_ERR_CLI_TOOMANY			-21	/**< 客户端太多 */
#define SMARTBUS_ERR_CLI_EXIST				-22	/**< 客户端已存在 */
#define SMARTBUS_ERR_DEST_NONEXIST			-23	/**< 目标不存在 */
#define SMARTBUS_ERR_REGISTERED_REPEAT		-24	/**< 重复注册 */
#define SMARTBUS_ERR_TIMEOUT					-25	/**< 超时 */

#define SMARTBUS_ERR_OTHER					-99	/**< 其它错误 */

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
/**
 * 数据包头结构定义
 */
typedef struct _SMARTBUS_PACKET_HEAD {
	unsigned short head_flag;	/**< 头标识	: 0x5b15 */

	unsigned char cmd;	/**< 命令 */
	unsigned char cmdtype; /**< 命令类型 */

	char src_unit_client_type; /**< 发送者类型 */
	char src_unit_id; /**< 发送者单元ID */
	char src_unit_client_id; /**< 发送者客户端ID */

	char dest_unit_client_type; /**< 接收者类型 */
	char dest_unit_id; /**< 接收者单元ID */
	char dest_unit_client_id; /**< 接收者客户端ID */

	char reserved[2]; /**< 保留 */

	long packet_size;	/**< 包大小. c#里要定义成int32 */
	long datalen;		/**< 数据部分长度. c#里要定义成int32 */
} SMARTBUS_PACKET_HEAD;
#pragma pack(pop)//恢复对齐状态

#ifdef WIN32
#ifndef WINAPI
#define WINAPI __stdcall
#endif
#else
#define WINAPI
#endif

/**
 * @brief 客户端连接成功回调函数类型
 * @details 当客户端连接Smartbus服务器成功之后，该类型回调函数被调用。
 *
 * @param arg 自定义数据
 * @param local_clientid 连接成功的本地clientid
 * @param accesspoint_unitid 连接点的UnitID
 * @param ack 连接注册结果： 0 建立连接成功、< 0 连接失败
 */
typedef void (WINAPI *smartbus_cli_connection_cb)(void * arg,
	unsigned char local_clientid, int accesspoint_unitid, int ack);

/**
 * @brief 客户端连接断开回调函数类型
 * @details 当客户端与smartbus服务器连接断开之后，该类型回调函数被调用。
 *
 * @param local_clientid 连接失败的本地clientid
 */
typedef void (WINAPI *smartbus_cli_disconnect_cb)(void * arg,
	unsigned char local_clientid);

/**
 * @brief 接收数据回调函数类型
 * @details 当客户端从smartbus收到数据时，该类型回调函数被调用。
 *
 * @param args 自定义数据
 * @param local_clientid 收到数据的的本地clientid
 * @param head 数据包头
 * @param data 数据包体
 * @param size 包体字节长度
 */
typedef void (WINAPI *smartbus_cli_recvdata_cb)(void * arg,
	unsigned char local_clientid, SMARTBUS_PACKET_HEAD * head, void * data,
	int size);

/**
 * @brief 全局节点客户端连接、断开通知回调函数类型
 * @details 当smartbus上某个节点发生连接或者断开时，该类型回调函数被调用。
 *
 * @param args 自定义数据
 * @param unitid 发生连接或断开事件的Smartbus节点单元ID
 * @param clientid 发生连接或断开事件的Smartbus节点单元中的客户端ID
 * @param clienttype 发生连接或断开事件的Smartbus节点单元中的客户端类型
 * @param status 连接状态： 0 断开连接、1 新建连接、2 已有的连接
 * @param add_info 连接附加信息
 */
typedef void (WINAPI *smartbus_global_connect_cb)(void * arg, char unitid,
	char clientid, char clienttype, char status, const char * add_info);

/**
 * @brief 调用流程是否成功回调函数类型
 * @details 在调用流程之后，通过该回调函数类型获知流程调用是否成功
 *
 * @param arg 自定义数据
 * @param local_clientid 流程调用发起者的本地smartbuts客户端ID
 * @param head smartbus消息头。包头信息。ret结果超时或失败时，head为 NULL
 * @param projectid 流程项目ID
 * @param invoke_id 调用ID
 * @param ack 流程调用是否成功。1表示成功，其它请参靠考误码
 * @param msg 调用失败时的信息描述
 *
 * @remark SmartBusIpcCli_RemoteInvokeFlow()、SmartBusNetCli_RemoteInvokeFlow() 直接返回失败的，不再触发smartbus_invokeflow_ack_cb回调。
 */
typedef void (WINAPI *smartbus_invokeflow_ack_cb)(void * arg,
	unsigned char local_clientid, SMARTBUS_PACKET_HEAD * head,
	const char * projectid, int invoke_id, int ack, const char * msg);

/**
 * @brief 调用流程结果返回回调函数类型
 * @details 通过类类型的回调函数，获取被调用流程的“子项目结束”节点的返回值列表
 *
 * @param args 自定义数据
 * @param local_clientid 流程调用发起者的本地smartbuts客户端ID
 * @param head smartbus消息头
 * @param projectid 流程项目ID
 * @param invoke_id 调用ID
 * @param ret 返回值。1表示正常返回，-25表示超时，小于1表示错误,其它请见错误码
 * @param param 结果参数串,采用JSON数组格式
 */
typedef void (WINAPI *smartbus_invokeflow_ret_cb)(void * arg,
	unsigned char local_clientid, SMARTBUS_PACKET_HEAD* head,
	const char* projectid, int invoke_id, int ret, const char * param);

typedef void (WINAPI *smartbus_unitdata_cb)(unsigned char cmd,
	unsigned char cmdtype, const unsigned char* data, int size);

typedef void (WINAPI *PTraceEx)(const char * lpszMessage, ...);

typedef void (WINAPI *PTraceStr)(const char * lpszMessage);

#endif
