#pragma once
#include "modbus.h"
class AFX_EXT_CLASS CModbusCommu
{
public:
	CModbusCommu(int nConnectID);
	~CModbusCommu(void);
public:
	CModbusCommu* GetInstance(int nConnectID);
	void DeleteInstance(int nConnectID);
	int ConnectServer(const char *ip_adress, int port );
	int ConnectClient();
	//1 bit
	int WriteCoil(int addr, int status);
	//nb bit
	int ReadInputBits(int addr, int nb, uint8_t*  dest);
	//nb bit
	int ReadBits(int addr, int nb, uint8_t*  dest);
	//nb bit
	int WriteBits(int addr, int nb, const uint8_t *src);
	//registers shorts
	int ReadRegisters(int addr, int nb, uint16_t *dest);
	//registers bool
	int ReadRegistersBool(int addr, bool &dest);
	//registers bool
	int WriteRegistersBool(int addr, /*int nb,*/ bool value);	
	//registers shorts
	int ReadRegistersShort(int addr, short &dest);
	//sigle register short
	int WriteRegistersShort(int addr, short value);
	//registers int
	int ReadRegistersInt(int addr, int &dest);
	//registers int
	int WriteRegistersInt(int addr, int value);
	//registers float
	int ReadRegistersFloat(int addr, float &dest);
	//registers float
	int WriteRegistersFloat(int addr, float value);
	//registers double
	int ReadRegistersDouble(int addr, double &dest);
	//registers double
	int WriteRegistersDouble(int addr, double value);
private:
//Communication
	int use_backend;
	modbus_mapping_t *mb_mapping;  
	modbus_t *ctx;
	uint8_t *query;
    int header_length;
	int s;
	uint32_t old_response_to_sec;
    uint32_t old_response_to_usec;
	uint32_t new_response_to_sec;
    uint32_t new_response_to_usec;
    uint32_t old_byte_to_sec;
    uint32_t old_byte_to_usec;	
private:
	static CModbusCommu *m_pInstance[10];
	int m_nConnectID;
};

