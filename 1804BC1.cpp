// 1804BC1.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "vsm.h"    // - заголовочный файл VSM API от Labcenter Electronics.
#include "MTDEVICE.h" //-заголовочный файл для реализации класса нашей модели.

//---------------------------------------------------------------------------
#define model_key 0x00000000 // - код авторизации от Labcenter Electronics
//---------------------------------------------------------------------------

extern "C" IDSIMMODEL __declspec(dllexport) *createdsimmodel(CHAR *device, ILICENCESERVER *ils)
{
	if (ils->authorize(model_key))
	{
		return new MTDEVICE; // - указатель на класс модели FFDEVICE
	}
	else
	{
		return NULL;
	}
}

extern "C" VOID __declspec(dllexport) deletedsimmodel(IDSIMMODEL *model)
{
	delete (MTDEVICE *)model; // - указатель на IDSIMMODEL интерфейс, который был ранее
	// - создан функцией createdsimmodel.
}


