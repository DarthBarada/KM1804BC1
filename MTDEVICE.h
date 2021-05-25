//----- ������������ ���� MTDEVICE.h ------------------------------------
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
	
		// ������� PQ
		int PQ;
		// �������� ������ ����������
		int POH[16];
	
		// ������� ������
		IDSIMPIN *Pin_29;	// ������� � ��� (C0)
		IDSIMPIN *Pin_15;	// �������� ������ (T)
		IDSIMPIN *Pin_40;	// ���������� ������� (OE)

		// ����� (A)
		IDSIMPIN *Pin_4;	// �����, 0-� ������ (A0)
		IDSIMPIN *Pin_3;	// �����, 1-� ������ (A1)
		IDSIMPIN *Pin_2;	// �����, 2-� ������ (A2)
		IDSIMPIN *Pin_1;	// �����, 3-� ������ (A3)
		// ����� (B)
		IDSIMPIN *Pin_17;	// �����, 0-� ������ (B0)
		IDSIMPIN *Pin_18;	// �����, 1-� ������ (B1)
		IDSIMPIN *Pin_19;	// �����, 2-� ������ (B2)
		IDSIMPIN *Pin_20;	// �����, 3-� ������ (B3)
		// ������ (D)
		IDSIMPIN *Pin_25;	// ������, 0-� ������ (D0)
		IDSIMPIN *Pin_24;	// ������, 1-� ������ (D1)
		IDSIMPIN *Pin_23;	// ������, 2-� ������ (D2)
		IDSIMPIN *Pin_22;	// ������, 3-� ������ (D3)
		// I
		// ����� ��������� ��������� I0-I2
		IDSIMPIN *Pin_12;	// I0
		IDSIMPIN *Pin_13;	// I1
		IDSIMPIN *Pin_14;	// I2
		// ����� ������� I3-I5
		IDSIMPIN *Pin_26;	// I3
		IDSIMPIN *Pin_28;	// I4
		IDSIMPIN *Pin_27;	// I5
		// ����� �������� ���������� I6-I8
		IDSIMPIN *Pin_5;	// I6
		IDSIMPIN *Pin_7;	// I7
		IDSIMPIN *Pin_6;	// I8
		// �������� ������ (Y)
		IDSIMPIN *Pin_36;	// ������, 0-� ������ (Y0)
		IDSIMPIN *Pin_37;	// ������, 1-� ������ (Y1)
		IDSIMPIN *Pin_38;	// ������, 2-� ������ (Y2)
		IDSIMPIN *Pin_39;	// ������, 3-� ������ (Y3)
		// �����
		IDSIMPIN *Pin_11;	// ������� 0-�� ���������� (Z)
		IDSIMPIN *Pin_31;	// ������� ������ ���������� ��� (F3)
		IDSIMPIN *Pin_34;	// ������������ ��� (OVR)
		IDSIMPIN *Pin_33;	// ���������������� ������� ��� (C4)

		IDSIMPIN *Pin_35;	// ��������� �������� � ��� (G)
		IDSIMPIN *Pin_32;	// ��������������� �������� ��� (P)
		// ��������� (���� �� ��������)
		IDSIMPIN *Pin_8;	// ��������������� ����� ������ �������� ������� ��� (PR3)
		IDSIMPIN *Pin_9;	// ��������������� ����� ������ �������� ������� ��� (PR0)

		IDSIMPIN *Pin_16;	// ��������������� ����� ������ �������� ������� �������� Q (PQ3)
		IDSIMPIN *Pin_21;	// ��������������� ����� ������ �������� ������� �������� Q (PQ0)

		int TO_INT(IDSIMPIN * p8, IDSIMPIN *p4, IDSIMPIN *p2, IDSIMPIN *p1);
		int TO_INT(IDSIMPIN *p4, IDSIMPIN *p2, IDSIMPIN *p1);
	};