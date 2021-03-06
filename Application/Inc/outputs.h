//----------------------------------------------------------------------
// Titel	:	Outputs.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	31.03.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_OUTPUTS_H_
#define INC_OUTPUTS_H_
//----------------------------------------------------------------------

// Strukturen definieren
//----------------------------------------------------------------------
struct system_out_tag {
	uint8_t J317 : 1;						// 0
	uint8_t F54 : 1;						// 1
	uint8_t F18 : 1;						// 2
	uint8_t DCDC_Enable : 1;				// 3
	uint8_t Gluehkerzen : 1;				// 4
	uint8_t MotorSDC : 1;					// 5
	uint8_t Klima : 1;						// 6
	uint8_t Power_On : 1;					// 7
} system_out;

struct highcurrent_out_tag {
	uint8_t Digital1 : 1;					// 0
	uint8_t Digital2 : 1;					// 1
	uint8_t Pumpe_Bremse : 1;				// 2
	uint8_t Pumpe_Kuhlung : 1;				// 3
	uint8_t Fan1 : 1;						// 4
	uint8_t Fan2 : 1;						// 5
	uint8_t Heater1 : 1;					// 6
	uint8_t Heater2 : 1;					// 7
} highcurrent_out;

struct leuchten_out_tag {
	uint8_t Bremslicht : 1;					// 0
	uint8_t Rueckfahrlicht : 1;				// 1
	uint8_t Generator : 1;					// 2
	uint8_t Buzzer : 1;						// 3
	uint8_t Ruechwarn : 1;					// 4
	uint8_t Ladeleuchte : 1;				// 5
	uint8_t Wischwarn : 1;					// 6
	uint8_t Bremswarn : 1;					// 7
	uint8_t Oelstand : 1;					// 8
	uint8_t Reserve : 1;					// 9
	uint8_t Anhaenger : 1;					// A
	uint8_t RedLed : 1;						// B
	uint8_t GreenLed : 1;					// C
	uint8_t BlueLed : 1;					// D
} leuchten_out;

struct komfort_out_tag {
	uint8_t BC_Rst_Out : 1;					// 0
	uint8_t BC_Up_Out : 1;					// 1
	uint8_t BC_Down_Out : 1;				// 2
	uint8_t BamoOut1 : 1;					// 3
	uint8_t BamoOut2 : 1;					// 4
} komfort_out;
//----------------------------------------------------------------------

// Definiere Konstanten
//----------------------------------------------------------------------
#define SYSTEM_OUTPUT					0b00000000							// 8 Bit, 8 Systemausgaenge
#define HIGHCURRENT_OUT					0b00000000							// 8 Bit, 8 Hochstromfaehige Ausgaenge
#define LED_OUTPUT						0b0000000000000000					// 16 Bit, 14 Leuchtdioden
#define KOMFORT_OUTPUT					0b00000000							// 8 Bit, 5 Komfortausgaenge
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void writeall_outputs(void);												// Schreibe alle Ausgaenge
//----------------------------------------------------------------------

#endif /* INC_OUTPUTS_H_ */
//----------------------------------------------------------------------
