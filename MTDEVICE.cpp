//------- MTDEVICE.CPP ---------------------------------------------------------------
#include "stdafx.h"
#include "MTDEVICE.h" //- заголовочный файл для реализации класса нашей модели.
//------------------------------------------------------------------------------------

#define WORD_SIZE 4


int GetBit(int value, int number)
    {
        return (value >> number) & 1;
    }

bool IsBitSet(int value, int number)
	{	
		return GetBit(value, number) != 0;
	}

int Mask(int value, int size = -1)
    {
        if (size == -1) 
			{
				size = WORD_SIZE;
			}
        return value & ((1 << size) - 1);
    }

//--- DEVICE::isdigital --------------------------------------------------------------
INT MTDEVICE::isdigital(CHAR *pinname)
	{
		return 1;
	}

//--- DEVICE::setup ------------------------------------------------------------------
VOID MTDEVICE::setup(IINSTANCE *instance, IDSIMCKT *dsimckt)
	{
		inst = instance;
		ckt = dsimckt;

		// A
		Pin_4 = inst->getdsimpin("A0", true);	// A0
		Pin_3 = inst->getdsimpin("A1", true);	// A1
		Pin_2 = inst->getdsimpin("A2", true);	// A2
		Pin_1 = inst->getdsimpin("A3", true);	// A3
		// B
		Pin_17 = inst->getdsimpin("B0", true);	// B0
		Pin_18 = inst->getdsimpin("B1", true);	// B1
		Pin_19 = inst->getdsimpin("B2", true);	// B2
		Pin_20 = inst->getdsimpin("B3", true);	// B3
		// D
		Pin_25 = inst->getdsimpin("D0", true);	// D0
		Pin_24 = inst->getdsimpin("D1", true);	// D1
		Pin_23 = inst->getdsimpin("D2", true);	// D2
		Pin_22 = inst->getdsimpin("D3", true);	// D3
		// I
		Pin_12 = inst->getdsimpin("I0", true);	// I0
		Pin_13 = inst->getdsimpin("I1", true);	// I1
		Pin_14 = inst->getdsimpin("I2", true);	// I2
		Pin_26 = inst->getdsimpin("I3", true);	// I3
		Pin_28 = inst->getdsimpin("I4", true);	// I4
		Pin_27 = inst->getdsimpin("I5", true);	// I5
		Pin_5  = inst->getdsimpin("I6", true);	// I6
		Pin_7  = inst->getdsimpin("I7", true);	// I7
		Pin_6  = inst->getdsimpin("I8", true);	// I8
		// Y
		Pin_36 = inst->getdsimpin("Y0", true);	// Y0
		Pin_37 = inst->getdsimpin("Y1", true);	// Y1
		Pin_38 = inst->getdsimpin("Y2", true);	// Y2
		Pin_39 = inst->getdsimpin("Y3", true);	// Y3
		// input
		Pin_29 = inst->getdsimpin("C0", true);	// C0
		Pin_15 = inst->getdsimpin("T", true);	// T
		Pin_40 = inst->getdsimpin("OE", true);	// OE

		// flags
		Pin_11 = inst->getdsimpin("Z", true);	//  Z
		Pin_31 = inst->getdsimpin("F3", true);	//  F3
		Pin_34 = inst->getdsimpin("OVR", true);	//  OVR
		Pin_33 = inst->getdsimpin("C4", true);	//  C4

		Pin_35 = inst->getdsimpin("G", true); // G
		Pin_32 = inst->getdsimpin("P", true); // P

		Pin_8 = inst->getdsimpin("PR3", true); // PR3
		Pin_9 = inst->getdsimpin("PR0", true); // PR0

		Pin_16 = inst->getdsimpin("PQ3", true); // PQ3
		Pin_21 = inst->getdsimpin("PQ0", true); // PQ0

		Pin_36->setstate(SLO); // Y0 = 0
		Pin_37->setstate(SLO); // Y1 = 0
		Pin_38->setstate(SLO); // Y2 = 0
		Pin_39->setstate(SLO); // Y3 = 0

		Pin_11->setstate(SLO); // Z = 0
		Pin_31->setstate(SLO); // F3 = 0
		Pin_34->setstate(SLO); // OVR = 0
		Pin_33->setstate(SLO); // C4 = 0

		Pin_35->setstate(SLO); // G = 0
		Pin_32->setstate(SLO); // P = 0

		Pin_8->setstate(SLO);	// PR3 = 0
		Pin_9->setstate(SLO);	// PR0 = 0

		Pin_16->setstate(SLO);	// PQ3 = 0
		Pin_21->setstate(SLO);	// PQ0 = 0
	}


//---- DEVICE::runctrl ------------------------------------------------------------------
VOID MTDEVICE::runctrl(RUNMODES mode)
	{

	}

//---- DEVICE::actuate ------------------------------------------------------------------
VOID MTDEVICE::actuate(REALTIME time, ACTIVESTATE newstate)
	{
		//---- анализируется состояние (ACTIVESTATE newstate)
	}

//---- DEVICE::indicate ------------------------------------------------------------------
BOOL MTDEVICE::indicate(REALTIME time, ACTIVEDATA *data)
	{
		return FALSE;
	}

//---- DEVICE::simulate ------------------------------------------------------------------
VOID MTDEVICE::simulate(ABSTIME time, DSIMMODES mode)
	{
		if (Pin_15->isposedge() && ishigh(Pin_40->istate())) 
			{
				int A = TO_INT(Pin_1, Pin_2, Pin_3, Pin_4);
				int B = TO_INT(Pin_20, Pin_19, Pin_18, Pin_17);
				int D = TO_INT(Pin_22, Pin_23, Pin_24, Pin_25);

				int I20 = TO_INT(Pin_14, Pin_13, Pin_12);
				int I53 = TO_INT(Pin_27, Pin_28, Pin_26);
				int I86 = TO_INT(Pin_6, Pin_7, Pin_5);

				bool C0 = ishigh(Pin_29->istate());

				bool M0 = ishigh(Pin_29->istate());
				bool M1 = ishigh(Pin_29->istate());

				int R = 0;
				int S = 0;
				
				// Выбор источника операндов
				switch (I20) 
					{
						case 0u:
							R = POH[A];
							S = PQ;
							break;
						case 1u:
							R = POH[A];
							S = POH[B];
							break;
						case 2u:
							R = 0;
							S = PQ;
							break;
						case 3u:
							R = 0;
							S = POH[B];
							break;
						case 4u:
							R = 0;
							S = POH[A];
							break;
						case 5u:
							R = D;
							S = POH[A];
							break;
						case 6u:
							R = D;
							S = PQ;
							break;
						case 7u:
							R = D;
							S = 0;
							break;
						default:
							break;
					}

				int p = R | S;
				int g = R & S;

				bool p30 = p == 15;
				bool g30 = g > 0;

				int _F = 0;
				int _Y = 0;

				bool _F3 = 0;
				bool _C4 = 0;
				bool _OVR = 0;
				bool _Z = 0;

				bool _P = 0;
				bool _G = 0;

				switch (I53) 
					{
						case 0:					// F = R + S + CO
							{
								// Вычисляем функцию
								_F = R + S + C0;
							
								// Вычисляем флаги
								_P = !p30;

								bool g1 = IsBitSet(g, 1) || (IsBitSet(p, 1) && IsBitSet(g, 0));
								bool g2 = IsBitSet(g, 2) || (IsBitSet(p, 2) && g1);
								bool g3 = IsBitSet(g, 3) || (IsBitSet(p, 3) && g2);
								_G = !g3;

								bool c1 = IsBitSet(g, 0) || (IsBitSet(p, 0) && C0);
								bool c2 = IsBitSet(g, 1) || (IsBitSet(p, 1) && c1);
								bool c3 = IsBitSet(g, 2) || (IsBitSet(p, 2) && c2);
								bool c4 = IsBitSet(g, 3) || (IsBitSet(p, 3) && c3);
								_C4 = c4;
								_OVR = c3 != c4;

								break;
							}
						case 1:					// F = S - R - 1 + CO
							{
								// Вычисляем функцию
								_F = S + Mask(~R) + C0;	
							
								// Вычисляем флаги
								_P = !p30;

								bool g1 = IsBitSet(g, 1) || (IsBitSet(p, 1) && IsBitSet(g, 0));
								bool g2 = IsBitSet(g, 2) || (IsBitSet(p, 2) && g1);
								bool g3 = IsBitSet(g, 3) || (IsBitSet(p, 3) && g2);
								_G = !g3;

								bool c1 = IsBitSet(g, 0) || (IsBitSet(p, 0) && C0);
								bool c2 = IsBitSet(g, 1) || (IsBitSet(p, 1) && c1);
								bool c3 = IsBitSet(g, 2) || (IsBitSet(p, 2) && c2);
								bool c4 = IsBitSet(g, 3) || (IsBitSet(p, 3) && c3);
								_C4 = c4;
								_OVR = c3 != c4;

								break;
							}
						case 2:					// F = R - S - 1 + CO
							{
								// Вычисляем функцию
								_F = R + Mask(~S) + C0;
							
								// Вычисляем флаги
								_P = !p30;

								bool g1 = IsBitSet(g, 1) || (IsBitSet(p, 1) && IsBitSet(g, 0));
								bool g2 = IsBitSet(g, 2) || (IsBitSet(p, 2) && g1);
								bool g3 = IsBitSet(g, 3) || (IsBitSet(p, 3) && g2);
								_G = !g3;

								bool c1 = IsBitSet(g, 0) || (IsBitSet(p, 0) && C0);
								bool c2 = IsBitSet(g, 1) || (IsBitSet(p, 1) && c1);
								bool c3 = IsBitSet(g, 2) || (IsBitSet(p, 2) && c2);
								bool c4 = IsBitSet(g, 3) || (IsBitSet(p, 3) && c3);
								_C4 = c4;
								_OVR = c3 != c4;

								break;
							}
						case 3:					// F = R or S 
							{
								// Вычисляем функцию
								_F = R | S;
							
								// Вычисляем флаги
								_P = false;
								_G = p30;
								_C4 = !p30 || C0;
								_OVR = _C4;
								break;
							}
						case 4:					// F = R and S 
							{
								// Вычисляем функцию
								_F = R & S;

								// Вычисляем флаги
								_P = false;
								_G = !g30;
								_C4 = g30 || C0;
								_OVR = _C4;
								break;
							}
						case 5:					// F = not R and S
							{
								// Вычисляем функцию
								_F = Mask(~R) & S;

								// Вычисляем флаги
								_P = false;
								_G = !g30;
								_C4 = g30 || C0;
								_OVR = _C4;
								break;
							}
						case 6:					// F = R xor S
							{						
								// Вычисляем функцию
								_F = R ^ S;

								// Вычисляем флаги
								_P = g30;

								bool g_1 = IsBitSet(g, 1) || (IsBitSet(p, 1) && IsBitSet(p, 0));
								bool g_2 = IsBitSet(g, 2) || (IsBitSet(p, 2) && g_1);
								bool g_3 = IsBitSet(g, 3) || (IsBitSet(p, 3) && g_2);
								_G = g_3;

								bool c4_1 = IsBitSet(g, 1) || (IsBitSet(p, 1) && IsBitSet(p, 0) && (IsBitSet(g, 0) || !C0));
								bool c4_2 = IsBitSet(g, 2) || (IsBitSet(p, 2) && c4_1);
								bool c4_3 = IsBitSet(g, 3) || (IsBitSet(p, 3) && c4_2);
								_C4 = !c4_3;

								p = Mask(~p);
								g = Mask(~g);
								bool ovr_0 = IsBitSet(p, 0) || (IsBitSet(g, 0) && C0);
								bool ovr_1 = IsBitSet(p, 1) || (IsBitSet(g, 1) && ovr_0);
								bool ovr_2 = IsBitSet(p, 2) || (IsBitSet(g, 2) && ovr_1);
								bool ovr_3 = IsBitSet(p, 3) || (IsBitSet(g, 3) && ovr_2);
								_OVR = ovr_2 != ovr_3;
								break;
							}
						case 7:					// F = not(R xor S)
							{
								// Вычисляем функцию
								_F = Mask(~(R ^ S));

								// Вычисляем флаги
								_P = g30;

								bool g_1 = IsBitSet(g, 1) || (IsBitSet(p, 1) && IsBitSet(p, 0));
								bool g_2 = IsBitSet(g, 2) || (IsBitSet(p, 2) && g_1);
								bool g_3 = IsBitSet(g, 3) || (IsBitSet(p, 3) && g_2);
								_G = g_3;

								bool c4_1 = IsBitSet(g, 1) || (IsBitSet(p, 1) && IsBitSet(p, 0) && (IsBitSet(g, 0) || !C0));
								bool c4_2 = IsBitSet(g, 2) || (IsBitSet(p, 2) && c4_1);
								bool c4_3 = IsBitSet(g, 3) || (IsBitSet(p, 3) && c4_2);
								_C4 = !c4_3;

								p = Mask(~p);
								g = Mask(~g);
								bool ovr_0 = IsBitSet(p, 0) || (IsBitSet(g, 0) && C0);
								bool ovr_1 = IsBitSet(p, 1) || (IsBitSet(g, 1) && ovr_0);
								bool ovr_2 = IsBitSet(p, 2) || (IsBitSet(g, 2) && ovr_1);
								bool ovr_3 = IsBitSet(p, 3) || (IsBitSet(g, 3) && ovr_2);
								_OVR = ovr_2 != ovr_3;
								break;
							}
					}
				_F = Mask(_F);
				_F3 = IsBitSet(_F, 3);
				_Z = _F == 0;
				
				switch(I86)
					{
						case 0:			// PQ = F, Y = F
							PQ = _F;
							break;
						case 1:			// Y = F
							break;
						case 2:			// POH(B) = F, Y = POH(A)
						case 3:			// POH(B) = F, Y = F
							POH[B] = _F;
							break;
						case 4:			// POH(B) = F/2, PQ = Q/2, Y = F
							PQ = PQ >> 1;
							POH[B] = _F >> 1;
							break;
						case 5:			// POH(B) = F/2, Y = F 
							POH[B] = _F >> 1;
							break;
						case 6:			// POH(B) = 2F, PQ = 2Q, Y = F
							PQ = Mask(PQ << 1);
							POH[B] = Mask(_F << 1);
							break;
						case 7:			// POH(B) = 2F, Y = F
							POH[B] = Mask(_F << 1);
							break;
					}
				if(I86 == 2)
					_Y = POH[A];
				else
					_Y = _F;

				Pin_11->setstate(time, 1, _Z ? SHI : SLO);
				Pin_31->setstate(time, 1, _F3 ? SHI : SLO);
				Pin_34->setstate(time, 1, _OVR ? SHI : SLO);
				Pin_33->setstate(time, 1, _C4 ? SHI : SLO);

				Pin_35->setstate(time, 1, _G ? SHI : SLO);
				Pin_32->setstate(time, 1, _P ? SHI : SLO);

				Pin_36->setstate(time, 1, IsBitSet(_Y, 0) ? SHI : SLO);
				Pin_37->setstate(time, 1, IsBitSet(_Y, 1) ? SHI : SLO);
				Pin_38->setstate(time, 1, IsBitSet(_Y, 2) ? SHI : SLO);
				Pin_39->setstate(time, 1, IsBitSet(_Y, 3) ? SHI : SLO);
			}
	}

//---- DEVICE::callback ------------------------------------------------------------------
VOID MTDEVICE::callback(ABSTIME time, EVENTID eventid)
	{

	}

int MTDEVICE::TO_INT(IDSIMPIN * p8, IDSIMPIN * p4, IDSIMPIN * p2, IDSIMPIN * p1)
	{
		int res = 0U;
		if (ishigh(p8->istate())) 
			{
				res += 8;
			}
		if (ishigh(p4->istate())) 
			{
				res += 4;
			}
		if (ishigh(p2->istate())) 
			{
				res += 2;
			}
		if (ishigh(p1->istate())) 
			{
				res += 1;
			}
		return res;
	}

int MTDEVICE::TO_INT(IDSIMPIN * p4, IDSIMPIN * p2, IDSIMPIN * p1)
	{
		int res = 0U;
		if (ishigh(p4->istate())) 
			{
				res += 4;
			}
		if (ishigh(p2->istate())) 
			{
				res += 2;
			}
		if (ishigh(p1->istate())) 
			{
				res += 1;
			}
		return res;
	}