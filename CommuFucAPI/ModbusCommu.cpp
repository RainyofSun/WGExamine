#include "StdAfx.h"
#include "ModbusCommu.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#ifdef _WIN32
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif
#include"unit-test.h"
#include"assert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum 
{
    TCP = 1,
    TCP_PI,
    RTU
};

CModbusCommu * CModbusCommu::m_pInstance[10] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

CModbusCommu::CModbusCommu(int nConnectID)
{
	ctx = NULL;
	m_nConnectID = nConnectID;
	use_backend = TCP;
}


CModbusCommu::~CModbusCommu(void)
{
	if ( ctx!= NULL)
	{	
		modbus_close(ctx);
		modbus_free(ctx);
	}

}

CModbusCommu* CModbusCommu::GetInstance(int nConnectID)
{
	if ((nConnectID>9) || (nConnectID<0))
	{
		AfxMessageBox(_T("ConnectID 超出0~9的范围！"));
		return NULL;
	}
	if (m_pInstance[nConnectID] == NULL)
	{
       m_pInstance[nConnectID] = new CModbusCommu(nConnectID);
	}
	return m_pInstance[nConnectID];
}

void CModbusCommu::DeleteInstance(int nConnectID)
{
	if (m_pInstance[nConnectID] != NULL)
	{
		delete m_pInstance[nConnectID];
		m_pInstance[nConnectID] = NULL;
	}
}

int CModbusCommu::ConnectServer(const char *ip_adress, int port )
{
	try
	{
		if (use_backend == TCP) 
		{
			ctx = modbus_new_tcp(ip_adress, port);
		} 
		else if (use_backend == TCP_PI) 
		{
			ctx = modbus_new_tcp_pi("::1", "1502");
		} 
		else 
		{
			ctx = modbus_new_rtu("/dev/ttyUSB1", 115200, 'N', 8, 1);
		}
		if (ctx == NULL) 
		{
			fprintf(stderr, "Unable to allocate libmodbus context\n");
			return -1;
		}
		modbus_set_debug(ctx, TRUE);
		modbus_set_error_recovery(ctx,
			/* modbus_error_recovery_mode(MODBUS_ERROR_RECOVERY_LINK |MODBUS_ERROR_RECOVERY_PROTOCOL)*/
			MODBUS_ERROR_RECOVERY_LINK_PROTOCOL);

		if (use_backend == RTU) 
		{
			modbus_set_slave(ctx, SERVER_ID);
		}
		modbus_get_response_timeout(ctx, &old_response_to_sec, &old_response_to_usec);
		if (modbus_connect(ctx) == -1) 
		{
			fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
			modbus_free(ctx);
			ctx = NULL;
			return -1;
		}
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}

int CModbusCommu::ConnectClient()
{
	try
	{
		int rc = 0;
		int i = 0;    
		if (use_backend == TCP) {
			ctx = modbus_new_tcp("192.168.5.200",502);
			query = (uint8_t *)malloc(MODBUS_TCP_MAX_ADU_LENGTH);
		} else if (use_backend == TCP_PI) {
			ctx = modbus_new_tcp_pi("::0", "1502");
			query = (uint8_t *)malloc(MODBUS_TCP_MAX_ADU_LENGTH);
		} else {
			ctx = modbus_new_rtu("/dev/ttyUSB0", 115200, 'N', 8, 1);
			modbus_set_slave(ctx, SERVER_ID);
			query = (uint8_t *)malloc(MODBUS_RTU_MAX_ADU_LENGTH);
		}
		header_length = modbus_get_header_length(ctx);
		modbus_set_debug(ctx, TRUE);
		mb_mapping = modbus_mapping_new_start_address(
			UT_BITS_ADDRESS, UT_BITS_NB,
			UT_INPUT_BITS_ADDRESS, UT_INPUT_BITS_NB,
			UT_REGISTERS_ADDRESS, UT_REGISTERS_NB_MAX,
			UT_INPUT_REGISTERS_ADDRESS, UT_INPUT_REGISTERS_NB);
		if (mb_mapping == NULL) {
			fprintf(stderr, "Failed to allocate the mapping: %s\n",
				modbus_strerror(errno));
			modbus_free(ctx);
			return -1;
		}
		/* Initialize input values that's can be only done server side. */
		modbus_set_bits_from_bytes(mb_mapping->tab_input_bits, 0, UT_INPUT_BITS_NB, UT_INPUT_BITS_TAB);
		/* Initialize values of INPUT REGISTERS */
		for (i=0; i < UT_INPUT_REGISTERS_NB; i++) {
			mb_mapping->tab_input_registers[i] = UT_INPUT_REGISTERS_TAB[i];;
		}

		if (use_backend == TCP) {
			s = modbus_tcp_listen(ctx, 1);
			rc=modbus_tcp_accept(ctx, &s);
		} else if (use_backend == TCP_PI) {
			s = modbus_tcp_pi_listen(ctx, 1);
			rc= modbus_tcp_pi_accept(ctx, &s);
		} else {
			rc = modbus_connect(ctx);
			//if (rc == -1) {
			//    fprintf(stderr, "Unable to connect %s\n", modbus_strerror(errno));
			//    modbus_free(ctx);
			//    return -1;
			//}
		}
		if (rc == -1) 
		{
			fprintf(stderr, "Unable to connect %s\n", modbus_strerror(errno));
			modbus_free(ctx);
			return -1;
		}
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}

int CModbusCommu::WriteCoil(int addr, int status)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		int rc = 0;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		}
		/** COIL BITS **/
		/* Single */
		rc = modbus_write_bit(ctx, addr, status);
		if(rc != 1)
		{
			return -1;//failed write
		}
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}


int CModbusCommu::ReadInputBits(int addr, int nb, uint8_t * dest)
{
	try
	{	
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		uint8_t *tab_rp_bits = NULL;
		int rc = 0;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		}
		tab_rp_bits = (uint8_t *) malloc(nb * sizeof(uint8_t));
		memset(tab_rp_bits, 0, nb * sizeof(uint8_t));

		/** COIL BITS **/
		rc = modbus_read_input_bits(ctx, addr, nb, tab_rp_bits);
		if(rc != nb)
		{
			free(tab_rp_bits);
			tab_rp_bits = NULL;
			return -1;//failed read nb points
		}	
		for(int i=0; i<nb; i++)
		{
			dest[i] = tab_rp_bits[i];
		}
		free(tab_rp_bits);
		tab_rp_bits = NULL;
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}

int CModbusCommu::ReadBits(int addr, int nb, uint8_t * dest)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		uint8_t *tab_rp_bits = NULL;
		int rc = 0;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		}
		tab_rp_bits = (uint8_t *) malloc(nb * sizeof(uint8_t));
		memset(tab_rp_bits, 0, nb * sizeof(uint8_t));

		/** COIL BITS **/
		rc = modbus_read_bits(ctx, addr, nb, tab_rp_bits);
		if(rc != nb)
		{
			free(tab_rp_bits);
			tab_rp_bits = NULL;
			return -1;//failed read nb points
		}	
		for(int i=0; i<nb; i++)
		{
			dest[i] = tab_rp_bits[i];
		}
		free(tab_rp_bits);
		tab_rp_bits = NULL;
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}

int CModbusCommu::WriteBits(int addr, int nb, const uint8_t *src)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		uint8_t *tab_rp_bits = NULL;
		int rc = 0;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		}	
		tab_rp_bits = (uint8_t *) malloc(nb * sizeof(uint8_t));
		memset(tab_rp_bits, 0, nb * sizeof(uint8_t));
		for(int i=0; i<nb; i++)	//赋值给临时指针
		{
			tab_rp_bits[i] = src[i];
		}
		modbus_set_bits_from_bytes(tab_rp_bits, 0, nb, src);
		rc = modbus_write_bits(ctx, addr, nb, tab_rp_bits);
		if(rc != nb)
		{
			free(tab_rp_bits);
			tab_rp_bits = NULL;
			return -1;//failed write nb points
		}
		free(tab_rp_bits);
		tab_rp_bits = NULL;
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}

int CModbusCommu::ReadRegisters(int addr, int nb, uint16_t *dest)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		uint16_t *tab_rp_registers = NULL;
		int rc = 0;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		}
		/* Allocate and initialize the memory to store the registers */
		tab_rp_registers = (uint16_t *) malloc(nb * sizeof(uint16_t));
		memset(tab_rp_registers, 0, nb * sizeof(uint16_t));
		rc = modbus_read_registers(ctx, addr, nb, tab_rp_registers);
		if(rc != nb)
		{
			free(tab_rp_registers);
			return -1;//failed read nb reg
		}
		for (int i=0; i<nb; i++)
		{
			dest[i] = tab_rp_registers[i];
		}
		free(tab_rp_registers);
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}


int CModbusCommu::ReadRegistersBool(int addr, bool &dest)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		uint16_t *tab_rp_registers = NULL;
		int nb = 1;
		int rc = 0;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		}
		/* Allocate and initialize the memory to store the registers */
		tab_rp_registers = (uint16_t *) malloc(nb * sizeof(uint16_t));
		memset(tab_rp_registers, 0, nb * sizeof(uint16_t));
		rc = modbus_read_registers(ctx, addr, nb, tab_rp_registers);
		if(rc != nb)
		{
			free(tab_rp_registers);
			return -1;//failed read nb reg
		}	 
		dest = (tab_rp_registers[0] & 0x00ff)!=0 ? true :false;
		free(tab_rp_registers);
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}


int CModbusCommu::WriteRegistersBool(int addr, bool value)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		int rc = 0;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		}	
		rc = modbus_write_register(ctx, addr, value);
		if(rc != 1)
		{
			return -1;//failed write register
		}
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}


int CModbusCommu::ReadRegistersShort(int addr, short &dest)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		uint16_t *tab_rp_registers = NULL;
		int nb = 1;
		int rc = 0;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		}
		/* Allocate and initialize the memory to store the registers */
		tab_rp_registers = (uint16_t *) malloc(nb * sizeof(uint16_t));
		memset(tab_rp_registers, 0, nb * sizeof(uint16_t));
		rc = modbus_read_registers(ctx, addr, nb, tab_rp_registers);
		if(rc != nb)
		{
			free(tab_rp_registers);
			return -1;//failed read nb reg
		}	 
		dest = tab_rp_registers[0];
		free(tab_rp_registers);
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}


int CModbusCommu::WriteRegistersShort(int addr, short value)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		int rc = 0;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		}	
		rc = modbus_write_register(ctx, addr, value);
		if(rc != 1)
		{
			return -1;//failed write register
		}
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}


int CModbusCommu::ReadRegistersInt(int addr, int &dest)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		uint16_t *tab_rp_registers = NULL;
		int nb = 2;
		int rc = 0;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		}
		/* Allocate and initialize the memory to store the registers */
		tab_rp_registers = (uint16_t *) malloc(nb * sizeof(uint16_t));
		memset(tab_rp_registers, 0, nb * sizeof(uint16_t));
		rc = modbus_read_registers(ctx, addr, nb, tab_rp_registers);
		if(rc != nb)
		{
			free(tab_rp_registers);
			return -1;//failed read nb reg
		}	    
		dest = (((uint32_t)tab_rp_registers[1] << 16) + tab_rp_registers[0]);
		free(tab_rp_registers);
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}


int CModbusCommu::WriteRegistersInt(int addr, int value)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		int rc = 0;
		int nb = 2;
		uint16_t src[2];
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		} 
		src[0] = (uint16_t)value;//先存低位，再存高位
		src[1] = (uint16_t)(value >> 16);   
		rc = modbus_write_registers(ctx, addr, nb, src);
		if(rc != nb)
		{
			return -1;//failed read nb reg
		}	
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}


int CModbusCommu::ReadRegistersFloat(int addr, float &dest)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		uint16_t *tab_rp_registers = NULL;
		int nb = 2;
		uint32_t uintValue;
		int rc = 0;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		}
		/* Allocate and initialize the memory to store the registers */
		tab_rp_registers = (uint16_t *) malloc(nb * sizeof(uint16_t));
		memset(tab_rp_registers, 0, nb * sizeof(uint16_t));
		rc = modbus_read_registers(ctx, addr, nb, tab_rp_registers);
		if(rc != nb)
		{
			free(tab_rp_registers);
			return -1;//failed read nb reg
		}	    
		uintValue = (((uint32_t)tab_rp_registers[1] << 16) + tab_rp_registers[0]);       
		memcpy(&dest, &uintValue, sizeof(float));
		free(tab_rp_registers);
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}


int CModbusCommu::WriteRegistersFloat(int addr, float value)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		int rc = 0;
		int nb = 2;
		uint16_t src[2];
		uint32_t uintValue;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		} 
		memcpy(&uintValue, &value, sizeof(float));
		src[0] = (uint16_t)uintValue;//先存低位，再存高位
		src[1] = (uint16_t)(uintValue >> 16);   
		rc = modbus_write_registers(ctx, addr, nb, src);
		if(rc != nb)
		{
			return -1;//failed read nb reg
		}	
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}


int CModbusCommu::ReadRegistersDouble(int addr, double &dest)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		uint16_t *tab_rp_registers = NULL;
		int nb = 4;
		uint64_t uWintValue;
		int rc = 0;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		}
		/* Allocate and initialize the memory to store the registers */
		tab_rp_registers = (uint16_t *) malloc(nb * sizeof(uint16_t));
		memset(tab_rp_registers, 0, nb * sizeof(uint16_t));
		rc = modbus_read_registers(ctx, addr, nb, tab_rp_registers);
		if(rc != nb)
		{
			free(tab_rp_registers);
			return -1;//failed read nb reg
		}	    
		uWintValue = ((uint64_t)(((uint32_t)tab_rp_registers[3] << 16) + tab_rp_registers[2])<<32) + (((uint32_t)tab_rp_registers[1] << 16) + tab_rp_registers[0]);       
		memcpy(&dest, &uWintValue, sizeof(double));
		free(tab_rp_registers);
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}


int CModbusCommu::WriteRegistersDouble(int addr, double value)
{
	try
	{
		if (NULL == ctx)//NO connect
		{
			return -10;
		}
		int rc = 0;
		int nb = 4;
		uint16_t src[4];
		uint64_t uWintValue;
		modbus_get_response_timeout (ctx, &(new_response_to_sec), &(new_response_to_usec));
		if(old_response_to_sec != new_response_to_sec || old_response_to_usec != new_response_to_usec)
		{
			return -1;//No response timeout modification on connect
		} 
		memcpy(&uWintValue, &value, sizeof(double));
		src[0] = (uint16_t)uWintValue;//先存低位，再存高位
		src[1] = (uint16_t)(uWintValue >> 16);  
		src[2] = (uint16_t)(uWintValue >> 32); 
		src[3] = (uint16_t)(uWintValue >> 48); 
		rc = modbus_write_registers(ctx, addr, nb, src);
		if(rc != nb)
		{
			return -1;//failed read nb reg
		}	
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}