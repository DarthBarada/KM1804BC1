//----- Заголовочный файл MTDEVICE.h ------------------------------------
#pragma once
#include "vsm.h"

class MTDEVICE : public IDSIMMODEL
	{
	public:
		INT isdigital(CHAR *pinname);
		VOID setup(IINSTANCE *inst, IDSIMCKT *dsim);
		VOID runctrl(RUNMODES mode);
		VOID actuate(REALTIME time, ACTIVESTATE newstate);
		BOOL indicate(REALTIME time, ACTIVEDATA *data);
		VOID simulate(ABSTIME time, DSIMMODES mode);
		VOID callback(ABSTIME time, EVENTID eventid);
	private:
		IINSTANCE *inst;
		IDSIMCKT *ckt;
	
		// Регистр PQ
		int PQ;
		// Регистры общего назначения
		int POH[16];
	
		// Входные данные
		IDSIMPIN *Pin_29;	// Перенос в АЛУ (C0)
		IDSIMPIN *Pin_15;	// Тактовый сигнал (T)
		IDSIMPIN *Pin_40;	// Разрешение выходов (OE)

		// Адрес (A)
		IDSIMPIN *Pin_4;	// Адрес, 0-й разряд (A0)
		IDSIMPIN *Pin_3;	// Адрес, 1-й разряд (A1)
		IDSIMPIN *Pin_2;	// Адрес, 2-й разряд (A2)
		IDSIMPIN *Pin_1;	// Адрес, 3-й разряд (A3)
		// Адрес (B)
		IDSIMPIN *Pin_17;	// Адрес, 0-й разряд (B0)
		IDSIMPIN *Pin_18;	// Адрес, 1-й разряд (B1)
		IDSIMPIN *Pin_19;	// Адрес, 2-й разряд (B2)
		IDSIMPIN *Pin_20;	// Адрес, 3-й разряд (B3)
		// Данные (D)
		IDSIMPIN *Pin_25;	// Данные, 0-й разряд (D0)
		IDSIMPIN *Pin_24;	// Данные, 1-й разряд (D1)
		IDSIMPIN *Pin_23;	// Данные, 2-й разряд (D2)
		IDSIMPIN *Pin_22;	// Данные, 3-й разряд (D3)
		// I
		// Выбор источника операндов I0-I2
		IDSIMPIN *Pin_12;	// I0
		IDSIMPIN *Pin_13;	// I1
		IDSIMPIN *Pin_14;	// I2
		// Выбор функции I3-I5
		IDSIMPIN *Pin_26;	// I3
		IDSIMPIN *Pin_28;	// I4
		IDSIMPIN *Pin_27;	// I5
		// Выбор приёмника результата I6-I8
		IDSIMPIN *Pin_5;	// I6
		IDSIMPIN *Pin_7;	// I7
		IDSIMPIN *Pin_6;	// I8
		// Выходные данные (Y)
		IDSIMPIN *Pin_36;	// Данные, 0-й разряд (Y0)
		IDSIMPIN *Pin_37;	// Данные, 1-й разряд (Y1)
		IDSIMPIN *Pin_38;	// Данные, 2-й разряд (Y2)
		IDSIMPIN *Pin_39;	// Данные, 3-й разряд (Y3)
		// Флаги
		IDSIMPIN *Pin_11;	// Признак 0-го результата (Z)
		IDSIMPIN *Pin_31;	// Старший разряд результата АЛУ (F3)
		IDSIMPIN *Pin_34;	// Переполнение АЛУ (OVR)
		IDSIMPIN *Pin_33;	// Последовательный перенос АЛУ (C4)

		IDSIMPIN *Pin_35;	// Генерация переноса в АЛУ (G)
		IDSIMPIN *Pin_32;	// Распространение переноса АЛУ (P)
		// Остальное
		IDSIMPIN *Pin_8;	// Двунаправленный вывод сдвига старшего разряда РЗУ (PR3)
		IDSIMPIN *Pin_9;	// Двунаправленный вывод сдвига младшего разряда РЗУ (PR0)

		IDSIMPIN *Pin_16;	// Двунаправленный вывод сдвига старшего разряда регистра Q (PQ3)
		IDSIMPIN *Pin_21;	// Двунаправленный вывод сдвига младшего разряда регистра Q (PQ0)

		int TO_INT(IDSIMPIN * p8, IDSIMPIN *p4, IDSIMPIN *p2, IDSIMPIN *p1);
		int TO_INT(IDSIMPIN *p4, IDSIMPIN *p2, IDSIMPIN *p1);
	};