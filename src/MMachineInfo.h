/*
Copyright (C) 2011-2023, Comine.com ( profdevi@ymail.com )
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
- The the names of the contributors of this project may not be used to 
  endorse or promote products derived from this software without specific 
  prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
`AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/


//v1.11 copyright Comine.com 20231216S1205
#ifndef MMachineInfo_h
#define MMachineInfo_h

//////////////////////////////////////////////
#include <windows.h>
#include "MStdLib.h"

//////////////////////////////////////////////
class MMachineInfo
	{
	OSVERSIONINFOA *mVersionInfo;
	char *mMachineName;
	char *mWindowsDirectory;
	char *mSystemDirectory;
	MEMORYSTATUSEX *mMemInfo;

	//////////////////////////////////////////
	void ClearObject(void);

	//////////////////////////////////////////
	public:
	MMachineInfo(bool create=false);
	~MMachineInfo(void);
	bool Create(void);
	bool Destroy(void);
	int GetMajorVersion(void);
	int GetMinorVersion(void);
	int GetBuildNumber(void);
	const char *GetCSDVersion(void);
	const char *GetVersionInfo(void);
	const char *GetMachineName(void);
	const char *GetWindowsDir(void);
	const char *GetSystemDir(void);
	bool SetMachineName(const char *name);
	const char *GetOSName(void);
	int GetMemoryInUsePercent(void);
	int GetPhysicalMemoryMB(void);
	int GetPhysicalMemoryAvailibleMB(void);
	int GetVirtualMemoryMB(void);
	int GetVirtualMemoryAvailibleMB(void);
	const char *GetCPUInfo(void);					// String Identifying CPU
	};


#endif // MMachineInfo_h

