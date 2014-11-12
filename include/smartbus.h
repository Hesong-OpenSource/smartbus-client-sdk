
#if !defined(_SMARTBUS_H_INCLUDED_)
#define _SMARTBUS_H_INCLUDED_

#ifndef MAX_GLOBAL_SMART_NODE
#define MAX_GLOBAL_SMART_NODE 			16
#endif

#define MAX_SMARTBUS_NETCLI_UNITID_NUM	32	// net�ͻ���ֵ��Χ���ǣ�16 �� 47

#define MIN_SMARTBUS_NETCLI_UNITID		MAX_GLOBAL_SMART_NODE	// ��Сnet�ͻ���unitidֵΪ16��Net�ͻ��˵�unitid����С��16
#define MAX_SMARTBUS_NETCLI_UNITID		MAX_GLOBAL_SMART_NODE + MAX_SMARTBUS_NETCLI_UNITID_NUM - 1	// ���net�ͻ���unitidֵΪ47��Net�ͻ��˵�unitidС�ڵ���47

#define MAX_SMARTBUS_NODE_NUM			MAX_GLOBAL_SMART_NODE + MAX_SMARTBUS_NETCLI_UNITID_NUM		// 16 + 32 = 48 ���ڵ���
#define MAX_SMARTBUS_NODE_CLI_NUM		16	// ���ڵ��ڵĿͻ�����
#define MAX_SMARTBUS_NODE_IPCCLI_NUM	MAX_SMARTBUS_NODE_CLI_NUM	// ���ڵ��ڵĿͻ�����


#define SMARTBUS_CMDTYPE_INTERNAL 		0
#define SMARTBUS_CMDTYPE_SYSTEM		 	1
#define SMARTBUS_CMDTYPE_FILE		 	2	// �ļ�
#define SMARTBUS_CMDTYPE_USER		 	3	// �û�����
#define SMARTBUS_CMDTYPE_GUARD_CMD	 	4	// �غ�ʵ������
#define SMARTBUS_CMDTYPE_GUARD_FILE	 	5	// �غ�ʵ���ļ�����

#define SMARTBUS_SYSCMD_PING_ACK	 	8	// PingӦ�����cmdtype


// �ڵ�����
#define SMARTBUS_NODECLI_TYPE_NULL		0
#define SMARTBUS_NODECLI_TYPE_NODE		1
#define SMARTBUS_NODECLI_TYPE_IPSC		2
#define SMARTBUS_NODECLI_TYPE_MONITOR	3
#define SMARTBUS_NODECLI_TYPE_AGENT		4
#define SMARTBUS_NODECLI_TYPE_DB		5



/* SmartBus �����붨��                 */
#define SMARTBUS_ERR_OK						 0
#define SMARTBUS_ERR_ARGUMENT				-1	// ��Ч����
#define SMARTBUS_ERR_CONN_NOT_ESTAB			-2	// ������δ����	Connection is not established		-2
#define SMARTBUS_ERR_CONNECT_BREAK			-3
#define SMARTBUS_ERR_AUTHOR					-4	// ��֤ʧ��
#define SMARTBUS_ERR_USER					-5
#define SMARTBUS_ERR_PWD						-6
#define SMARTBUS_ERR_BUFF_FULL				-7	// ��������
#define SMARTBUS_ERR_NODE_NOTEXIST			-8	// �ڵ㲻����
#define SMARTBUS_ERR_CLI_NOTEXIST			-9	// �ͻ��˲�����
#define SMARTBUS_ERR_CONNECTED				-10	// �ظ�����
#define SMARTBUS_ERR_SEND_OWN				-11	// ���͸��Լ�
#define SMARTBUS_ERR_UNITID_INVALID			-12	// ��Ч��unitid
#define SMARTBUS_ERR_CLIENTID_INVALID		-13	// ��Ч��clientid
#define SMARTBUS_ERR_NON_INIT				-14	// ��δ��ʼ��
#define SMARTBUS_ERR_MAX_DATASIZE			-15	// ���͵�����̫��
#define SMARTBUS_ERR_CMDTYPE_INVALID		-16	// ��Ч����������
#define SMARTBUS_ERR_CLIENTTYPE_INVALID	-17	// ��Ч�Ŀͻ�������
#define SMARTBUS_ERR_SEND_DATA				-18	// �������ݴ���
#define SMARTBUS_ERR_MEM_ALLOC				-19	// �����ڴ����
#define SMARTBUS_ERR_ESTABLI_CONNECT		-20	// ��������ʧ��
#define SMARTBUS_ERR_CLI_TOOMANY			-21	// �ͻ���̫��
#define SMARTBUS_ERR_CLI_EXIST				-22	// �ͻ����Ѵ���
#define SMARTBUS_ERR_DEST_NONEXIST			-23	// Ŀ�겻����
#define SMARTBUS_ERR_REGISTERED_REPEAT		-24	// �ظ�ע��
#define SMARTBUS_ERR_TIMEOUT					-25	// ��ʱ


#define SMARTBUS_ERR_OTHER					-99	// ��������



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

#pragma pack(push) //�������״̬
#pragma pack(1)	//�趨Ϊ1�ֽڶ���


// ���ݰ�ͷ�ṹ����
typedef struct
{
	unsigned short	head_flag;	// ͷ��ʶ	: 0x5b15

	unsigned char	cmd;
	unsigned char	cmdtype;

	char	src_unit_client_type;
	char	src_unit_id;
	char	src_unit_client_id;

	char	dest_unit_client_type;
	char	dest_unit_id;
	char	dest_unit_client_id;

	char	reserved[2];

	long	packet_size;	// c#��Ҫ�����int32
	long	datalen;		// c#��Ҫ�����int32
}SMARTBUS_PACKET_HEAD;

#pragma pack(pop)//�ָ�����״̬

#ifdef WIN32
#ifndef WINAPI
#define WINAPI __stdcall
#endif
#else
#define WINAPI
#endif

//// ���ͻ�������
// local_clientid ����clientid
// accesspoint_unitid : ���ӵ��UnitID
// ack �� ����ע������ 0 �������ӳɹ���< 0 ����ʧ��
typedef void (WINAPI *smartbus_cli_connection_cb)(void * arg,unsigned char local_clientid, int accesspoint_unitid,int ack);

typedef void (WINAPI *smartbus_cli_disconnect_cb)(void * arg,unsigned char local_clientid);

typedef void (WINAPI *smartbus_cli_recvdata_cb)(void * arg,unsigned char local_clientid, SMARTBUS_PACKET_HEAD * head,void * data,int size);


// ȫ�ֽڵ�ͻ������ӡ��Ͽ�֪ͨ
// unitid : �ڵ�ͻ��˵�unitid
// clientid : �ͻ���ID����node���Ľڵ�����ʱ��clientidֵΪ-1
// clienttype : �ͻ�������
// status : ����״̬�� 0 �Ͽ����ӡ�1 �½����ӡ�2 ���е�����
// add_info �� ���Ӹ�����Ϣ
typedef void (WINAPI *smartbus_global_connect_cb)(void * arg,char unitid,char clientid,char clienttype,char status,const char * add_info);


// ��������ACK������Զ�����̵����Ƿ�ɹ���
// projectid : ��ĿID
// invoke_id : ����ID
// head :  ��ͷ��Ϣ��ret�����ʱ��ʧ��ʱ��headΪ NULL
// ack �� �����1 ���óɹ�������ִ��SUBSTART�ڵ㣩��< 1 ����ʧ�ܡ�
// msg : ����ʧ��ʱ����Ϣ����
// ע�� SmartBusIpcCli_RemoteInvokeFlow()��SmartBusNetCli_RemoteInvokeFlow() ֱ�ӷ���ʧ�ܵģ����ٴ���smartbus_invokeflow_ack_cb�ص���
typedef void (WINAPI *smartbus_invokeflow_ack_cb)(void * arg,unsigned char local_clientid,SMARTBUS_PACKET_HEAD * head,const char * projectid,int invoke_id,int ack, const char * msg);

// �������̽�����أ������̽����ڵ㣩
// projectid : ��ĿID
// invoke_id : ����ID
// head :  ��ͷ��Ϣ��ret�����ʱ��ʧ��ʱ��headΪ NULL
// ret �� �����1 �ǽ�����ء� < 1 ����-25 ��ʱ��
// param : ���������,JSON�����ʽ
typedef void (WINAPI *smartbus_invokeflow_ret_cb)(void * arg,unsigned char local_clientid,SMARTBUS_PACKET_HEAD * head,const char * projectid,int invoke_id,int ret, const char * param);


//
typedef void (WINAPI *smartbus_unitdata_cb)(unsigned char	cmd,unsigned char	cmdtype,const unsigned char * data,int size);


typedef void (WINAPI *PTraceEx)(const char * lpszMessage,...);

typedef void (WINAPI *PTraceStr)(const char * lpszMessage);


#endif
