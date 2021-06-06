//----------------------------------------------------------------------
// Titel	:	Bamocar.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	21.05.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfügen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfügen der STM Include-Dateien
//----------------------------------------------------------------------
#include "can.h"
//----------------------------------------------------------------------

// Einfügen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "Bamocar.h"
#include "BasicUart.h"
#include "error.h"
//----------------------------------------------------------------------

// Lese Bamocar Register
//----------------------------------------------------------------------
void readBAMOReg(uint8_t REG)
{
	CAN_TxHeaderTypeDef BamoTxMsg;
	uint8_t BamoTxData[3], status;

	// Sendenachricht erstellen
	BamoTxMsg.StdId = BAMOCAR_TX_ID;
	BamoTxMsg.ExtId = 0;
	BamoTxMsg.RTR = CAN_RTR_DATA;
	BamoTxMsg.IDE = CAN_ID_STD;
	BamoTxMsg.DLC = 3;
	BamoTxMsg.TransmitGlobalTime=DISABLE;

	BamoTxData[0] = BAMOCAR_REG_READ;
	BamoTxData[1] = REG;
	BamoTxData[2] = INTVL_IMMEDIATE;

	status = HAL_CAN_AddTxMessage(&hcan3, &BamoTxMsg, BamoTxData, (uint32_t *)CAN_TX_MAILBOX0);
	hal_error(status);
}
//----------------------------------------------------------------------

// Lese Bamocar Register, Zeitinterval für wiederholten Rückgabewert
//----------------------------------------------------------------------
void readBAMORegIntvl(uint8_t REG, uint8_t interval)
{
	CAN_TxHeaderTypeDef BamoTxMsg;
	uint8_t BamoTxData[3], status;

	// Sendenachricht erstellen
	BamoTxMsg.StdId = BAMOCAR_TX_ID;
	BamoTxMsg.ExtId = 0;
	BamoTxMsg.RTR = CAN_RTR_DATA;
	BamoTxMsg.IDE = CAN_ID_STD;
	BamoTxMsg.DLC = 3;
	BamoTxMsg.TransmitGlobalTime=DISABLE;

	BamoTxData[0] = BAMOCAR_REG_READ;
	BamoTxData[1] = REG;
	BamoTxData[2] = interval;

	status = HAL_CAN_AddTxMessage(&hcan3, &BamoTxMsg, BamoTxData, (uint32_t *)CAN_TX_MAILBOX0);
	hal_error(status);
}
//----------------------------------------------------------------------

// Ermittle Register nach Empfang Bamocar CAN-ID
//----------------------------------------------------------------------
void BAMOCAN_ID(uint8_t* data, uint8_t dlc)
{
	uint8_t Reg = data[0];
	uint16_t speed = 0, strom;

	switch (Reg)
	{
		case BAMOCAR_REG_N_ACT_FILTER:
			speed = ((data[2]<<8) + data[1]);

// Uart Ausgabe
#ifdef DEBUG
			uartTransmit("Motordrehzahl\n", 14);
			uartTransmitNumber(speed, 10);
			uartTransmit("\n", 1);
#endif

			break;

		case BAMOCAR_REG_I_IST_FILTER:
			strom = ((data[2]<<8) + data[1]);

// Uart Ausgabe
#ifdef DEBUG
			uartTransmit("Motorstrom\n", 11);
			uartTransmitNumber(strom, 10);
			uartTransmit("\n", 1);
#endif

			break;

		case BAMOCAR_REG_STATUS:
			bamocar_stat.status1 = ((data[4] << 24) + (data[3] << 16) + (data[2] << 8) + data[1]);

// Uart Ausgabe
#ifdef DEBUG
			uartTransmit("Bamocar Status\n", 15);
			for (uint8_t i = 0; i < 4; i++)
			{
				uartTransmitNumber(bamocar_stat.status[i+1], 10);
				uartTransmit(" ", 1);
			}
			uartTransmit("\n", 1);
#endif

			break;

		case BAMOCAR_REG_ERROR:
			bamocar_error.error1 = ((data[2] << 8) + data[1]);
			bamocar_warnung.warnung1 = ((data[4] << 8) + data[3]);

// Uart Ausgabe
#ifdef DEBUG
			uartTransmit("Bamocar Error\n", 14);
			for (uint8_t i = 0; i < 4; i++)
			{
				uartTransmitNumber(data[1+i], 10);
				uartTransmit(" ", 1);
			}
			uartTransmit("\n", 1);
#endif

			break;

		case BAMOCAR_REG_STATUS_IO:
			bamocar_statIO.status1 = ((data[2] << 8) + data[1]);

// Uart Ausgabe
#ifdef DEBUG
			uartTransmit("Bamocar IO Status\n", 18);
			for (uint8_t i = 0; i < 4; i++)
			{
				uartTransmitNumber(bamocar_stat.status[i+1], 10);
				uartTransmit(" ", 1);
			}
			uartTransmit("\n", 1);
#endif

			break;

		case BAMOCAR_REG_FIRMWARE:
			bamocar_data.data = ((data[2]<<8) + data[1]);

// Uart Ausgabe
#ifdef DEBUG
			uartTransmit("Firmware\n", 9);
			uartTransmitNumber(bamocar_data.data, 16);
			uartTransmit("\n", 1);
#endif

			break;

		default:
			uartTransmit("Bamocar Register nicht definiert\n", 33);
			break;
	}
}
//----------------------------------------------------------------------

// Collect Bamocar Informationen
//----------------------------------------------------------------------
void BamocarInfo(void)
{
	#define STRING_BAMOCAR_FIRMWARE		"\nBAMOCAR Firmware:\t\t"
	#define STRING_BAMOCAR_SN_INTERN	"\nBAMOCAR Seriennummer Intern:\t\t"
	#define STRING_BAMOCAR_SN_EXTERN	"\nBAMOCAR Seriennummer Extern:\t\t"

	// Seriennummer auslesen und anzeigen (Intern)
	readBAMOReg(BAMOCAR_REG_SN_INTERN);
	uartTransmit(STRING_BAMOCAR_SN_INTERN, sizeof(STRING_BAMOCAR_SN_INTERN));
	uartTransmitNumber(bamocar_data.data, 16);								// Bamocar interne Seriennummer anzeigen
	uartTransmit("\n", 1);

	// Seriennummer auslesen und anzeigen (Extern)
	readBAMOReg(BAMOCAR_REG_SN_EXTERN);
	uartTransmit(STRING_BAMOCAR_SN_EXTERN, sizeof(STRING_BAMOCAR_SN_EXTERN));
	uartTransmitNumber(bamocar_data.data, 16);								// Bamocar externe Seriennummer anzeigen
	uartTransmit("\n", 1);

	// Firmware auslesen und anzeigen
	readBAMOReg(BAMOCAR_REG_FIRMWARE);
	uartTransmit(STRING_BAMOCAR_FIRMWARE, sizeof(STRING_BAMOCAR_FIRMWARE));
	uartTransmitNumber(bamocar_data.data, 16);								// Bamocar Firmware anzeigen
	uartTransmit("\n", 1);
}
//----------------------------------------------------------------------