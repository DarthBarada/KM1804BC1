// 1804BC1.cpp: ���������� ���������������� ������� ��� ���������� DLL.
//

#include "stdafx.h"
#include "vsm.h"    // - ������������ ���� VSM API �� Labcenter Electronics.
#include "MTDEVICE.h" //-������������ ���� ��� ���������� ������ ����� ������.

//---------------------------------------------------------------------------
#define model_key 0x00000000 // - ��� ����������� �� Labcenter Electronics
//---------------------------------------------------------------------------

extern "C" IDSIMMODEL __declspec(dllexport) *createdsimmodel(CHAR *device, ILICENCESERVER *ils)
{
	if (ils->authorize(model_key))
	{
		return new MTDEVICE; // - ��������� �� ����� ������ FFDEVICE
	}
	else
	{
		return NULL;
	}
}

extern "C" VOID __declspec(dllexport) deletedsimmodel(IDSIMMODEL *model)
{
	delete (MTDEVICE *)model; // - ��������� �� IDSIMMODEL ���������, ������� ��� �����
	// - ������ �������� createdsimmodel.
}


