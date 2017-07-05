// Log4CPPConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CLog4CPP.h"
using namespace itas109;

int _tmain(int argc, _TCHAR* argv[])
{
	CLog4CPP m_log;
	m_log.Init();

	m_log.LogOut("Just for test");

	unsigned char a[4] = { 0x0 };
	a[0] = 0x01;
	a[1] = 0x02;
	a[2] = 0x03;
	a[3] = 0x04;

	m_log.LogOutHex(a, 4);

	return 0;
}

