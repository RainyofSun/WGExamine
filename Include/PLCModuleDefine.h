#pragma once
#include <stdint.h>

///////////////////////////////// Modbus ���� /////////////////////////////////////////
#define  PLCConfigPath  "..\\Data\\Config\\AddressValid.dat"

// ����PLC��վλ�� -- �����ö�������ٻ���
enum PLCMARK 
{
	PLC_0,
	PLC_1,
	PLC_MARK_NUM // ö����������ֱ��ʹ��
};

// ���ֲ�ͬ�ı��������� X Y M D
enum AddrType
{
	Addr_X = 0,
	Addr_Y,
	Addr_M,
	Addr_D,
	ADDR_TYPE_SUM
};

enum PLCValueType
{
	PLC_Value_bool = 0,
	PLC_Value_int,
	PLC_Value_short,
	PLC_Value_float,
	PLC_Value_double,
	PLC_Value_uint8,
	PLC_Value_uint16,
};

enum PLCOperateType
{
	PLC_Operation_Read = 0,
	PLC_Operation_Write,
};

// ÿ��ͨѶ ��ȡ�ĵ�ַ��
#define  COMM_READ_LENGTH 100
// ����ȡ����
#define  COMM_READ_MAX 80

// ����ַ ����ַ��0��ʼ��
#define  COMM_MAX_ADDR 8000
#define  COMM_MAX_XY_ADDR 80

struct sData
{ 
	bool b;
	int i; 
	short sh; 
	float f; 
	double db;
	uint8_t uint8;
	uint16_t uint16;
};

// VM Get/Set Value ʱ��ʹ�õ�Key���� PLC1-D-0015 �� Length == 11 )
#define PLC_KEY_NAME_LENGTH 11

struct sSetData
{ 
	PLCMARK mark;
	AddrType type;
	PLCValueType valueType;
	bool b;
	int i; 
	short sh; 
	float f; 
	double db;
	uint8_t uint8;
	uint16_t uint16;
};

struct SplitDataStruct 
{
	PLCMARK mark;
	AddrType type;
	int address;
	bool isValid;
};

//ERR DEFINE
#define    PLC_SUCCESS                       0     //�ɹ�
#define    PLC_CONNECT_FAIL                 -10   //��������ʧ��
#define    PLC_READ_FAIL                    -11   //������ʧ��

/// PLC Э������
enum PLCProtocolType 
{
	PLC_TCP = 0,
	PLC_UDP,
	PLC_MODBUS
};

/// PLC ������Ϣ
struct PLCConnectInfo
{
	CString ip;
	int port;
	// PLC��ʶ����modbusʹ��
	PLCMARK mark;

	void initialization() 
	{
		ip = "";
		port = 0;
		mark = PLC_0;
	}

	PLCConnectInfo()
	{
		initialization();
	}
};

/////////////////////////////////// �������ݰ����� ///////////////////////////////////////
#define ORDER_PACKET_ID 1					// �������ݰ�ID
#define ORDER_PACKET_SIZE 512				// �������ݰ����������

// �������ݰ�
struct OrderPackage
{
	char data[ORDER_PACKET_SIZE];	// ����

	void initParam()
	{
		for (int i=0; i<ORDER_PACKET_SIZE; i++)
		{
			data[i] = 0;
		}
	}

	OrderPackage()
	{
		initParam();
	}

	OrderPackage operator=(const OrderPackage &other)
	{
		memcpy(data, other.data, sizeof(data));

		return *this;
	}
};

///////////////////////////////// �������ݰ����� /////////////////////////////////////////
// ���ݰ� int �������������
#define  PACKAGE_MAX_SIZE				512
// ���ݰ����������ֽڴ�С
#define  PACKAGE_DATA_TYPE_BYTE_SIZE	4
// ͨѶʱfloat ������int����ת������
#define CONVERT_VALUE_ACCURACY			10000
// ��ʼ���ݰ�ID
#define PACKET_ID_NONE					0
// int ֵλ��
#define BIT_SIZE						32

// ��������ID
enum write_packet_id
{
	write_packet_id_1 = 2,
	write_packet_id_2,
	write_packet_id_3,
	write_packet_id_4,
	write_packet_id_5
};

// �������ݰ�ID
enum read_packet_id
{
	read_packet_id = 1,
	read_packet_quick = 2
};

// �������ݰ�
struct PLCPackage 
{
	int data[PACKAGE_MAX_SIZE];

	void initialization()
	{
		for (int i = 0; i < PACKAGE_MAX_SIZE; i ++)
		{
			data[i] = 0;
		}
	}

	PLCPackage()
	{
		initialization();
	}

	PLCPackage operator=(const PLCPackage &other)
	{
		memcpy(data, other.data, sizeof(data));
		return *this;
	}
};