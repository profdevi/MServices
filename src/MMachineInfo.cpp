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
#include <windows.h>
#include <intrin.h>
#include "MStdLib.h"
#include "MMachineInfo.h"


///////////////////////////////////////
#ifdef MSTDLIB_OS_WINDOWS
#pragma comment(lib,"kernel32.lib")
#endif // MSTDLIB_IS_WINDOWS

//*****************************************************************
//** Module Info
//*****************************************************************
/*
	This CPUInfo code lifted from 
*/
static char GCPUInfoBuffer[100];
const char *GGetCPUInfo(void)
	{
	MStdMemZero(GCPUInfoBuffer,50);

	// ref https://stackoverflow.com/questions/4443864/how-do-i-get-hardware-info-such-as-cpu-name-total-ram-etc-with-vb6
	int cpuinfo[4]={-1};

	__cpuid(cpuinfo,0x80000002);
	MStdMemCpy(GCPUInfoBuffer,cpuinfo,sizeof(cpuinfo) );

	__cpuid(cpuinfo, 0x80000003);
	memcpy(GCPUInfoBuffer + 16, cpuinfo, sizeof(cpuinfo));

	__cpuid(cpuinfo, 0x80000004);
	memcpy(GCPUInfoBuffer + 32, cpuinfo, sizeof(cpuinfo));

	return GCPUInfoBuffer;
	}


//*****************************************************************
//** MMachine Info
//*****************************************************************
void MMachineInfo::ClearObject(void)
	{
	mVersionInfo=NULL;
	mMachineName=NULL;
	mWindowsDirectory=NULL;
	mSystemDirectory=NULL;
	mMemInfo=NULL;
	}


////////////////////////////////////////////////////////////
MMachineInfo::MMachineInfo(bool create)
	{
	ClearObject();
	if(create==true && Create()==false)
		{
		return;
		}
	}


////////////////////////////////////////////////////////////
MMachineInfo::~MMachineInfo(void)
	{  Destroy();  }


////////////////////////////////////////////////////////////
bool MMachineInfo::Create(void)
	{
	Destroy();

	// Allocate space for data
	mVersionInfo=new(std::nothrow) OSVERSIONINFOA;
	mMachineName=new(std::nothrow) char[MAX_COMPUTERNAME_LENGTH+1];
	mWindowsDirectory=new(std::nothrow) char[MAX_PATH+1];
	mSystemDirectory=new(std::nothrow) char[MAX_PATH+1];
	mMemInfo=new(std::nothrow) MEMORYSTATUSEX;

	if(	mVersionInfo==NULL || mMachineName==NULL
			|| mWindowsDirectory==NULL || mSystemDirectory==NULL 
			|| mMemInfo==NULL)
		{
		Destroy();
		return false;
		}


	// Init Infor
	MStdMemSet(mVersionInfo,0,sizeof(*mVersionInfo) );
	mVersionInfo->dwOSVersionInfoSize=sizeof(*mVersionInfo);

	if(GetVersionExA((LPOSVERSIONINFOA)mVersionInfo)==FALSE)
		{
		Destroy();
		return false;
		}

	// Get Machine Name
	DWORD namesize=MAX_COMPUTERNAME_LENGTH+1;
	if(GetComputerNameA(mMachineName,&namesize)==FALSE)
		{
		Destroy();
		return false;
		}

	// Get Windows Directory
	if(GetWindowsDirectoryA(mWindowsDirectory,MAX_PATH+1)==FALSE)
		{
		Destroy();
		return false;
		}

	// Get System Directory
	if(GetSystemDirectoryA(mSystemDirectory,MAX_PATH+1)==FALSE)
		{
		Destroy();
		return false;
		}

	// Get MMemoryInfo
	MStdMemZero(mMemInfo,sizeof(*mMemInfo) );
	mMemInfo->dwLength = sizeof(*mMemInfo);

	if(GlobalMemoryStatusEx(mMemInfo)==FALSE)
		{
		Destroy();
		return false;
		}

	return true;
	}


////////////////////////////////////////////////////////////
bool MMachineInfo::Destroy(void)
	{
	if(mVersionInfo!=NULL)
		{
		delete mVersionInfo;
		mVersionInfo=NULL;
		}

	if(mMachineName!=NULL)
		{
		delete[] mMachineName;
		mMachineName=NULL;
		}

	if(mSystemDirectory!=NULL)
		{
		delete[] mSystemDirectory;
		mSystemDirectory=NULL;
		}

	if(mWindowsDirectory!=NULL)
		{
		delete[] mWindowsDirectory;
		mWindowsDirectory=NULL;
		}

	if(mMemInfo!=NULL)
		{
		delete mMemInfo;
		mMemInfo=NULL;
		}

	ClearObject();
	return true;
	}


////////////////////////////////////////////////////////////
int MMachineInfo::GetMajorVersion(void)
	{
	return (int)mVersionInfo->dwMajorVersion;
	}


////////////////////////////////////////////////////////////
int MMachineInfo::GetMinorVersion(void)
	{
	return (int)mVersionInfo->dwMinorVersion;
	}


////////////////////////////////////////////////////////////
int MMachineInfo::GetBuildNumber(void)
	{
	return (int)mVersionInfo->dwBuildNumber;
	}


/////////////////////////////////////////////////////////////
const char *MMachineInfo::GetCSDVersion(void)
	{
	return mVersionInfo->szCSDVersion;
	}


////////////////////////////////////////////////////////////
const char *MMachineInfo::GetVersionInfo(void)
	{
	return mVersionInfo->szCSDVersion;
	}


///////////////////////////////////////////////////////////
const char *MMachineInfo::GetMachineName(void)
	{
	return mMachineName;
	}


///////////////////////////////////////////////////////////
const char *MMachineInfo::GetWindowsDir(void)
	{
	return mWindowsDirectory;
	}


///////////////////////////////////////////////////////////
const char *MMachineInfo::GetSystemDir(void)
	{
	return mSystemDirectory;
	}


//////////////////////////////////////////////////////////
bool MMachineInfo::SetMachineName(const char *name)
	{
	if(name==NULL || *name==0)
		{
		// COmputer Name is bad
		return false;
		}
	if(::SetComputerNameA(name)==FALSE)
		{
		// Unable to set computer name
		return false;
		}

	return true;	
	}


////////////////////////////////////////////////////////
const char *MMachineInfo::GetOSName(void)
	{
	const int majorid=GetMajorVersion();
	const int minorid=GetMinorVersion();
	const char *csdversion=GetCSDVersion();
	
	// Ref: http://www.codeguru.com/cpp/misc/misc/system/article.php/c8973
	if(majorid==3)
		{
		return "Windows NT 3.5";
		}
	else if(majorid==4)
		{
		if(minorid==0)
			{
			if(*csdversion=='C' || *csdversion=='B')
				{
				return "Windows 95 ISR2";
				}

			return "Windows 95";
			}
		else if(minorid==10)
			{
			if(*csdversion=='A')
				{
				return "Windows 98 SE";
				}

			return "Windows 98";
			}
		else if(minorid==90)
			{
			return "Windows ME";
			}

		return "Windows NT 4";
		}
	else if(majorid==5)
		{
		if(minorid==0)
			{
			return "Windows 2000";
			}
		else if(minorid==1)
			{
			return "Windows XP";
			}
		else if(minorid==2)
			{
			return "Windows XP Pro 64";
			}

		return "Windows XP";
		}
	else if(majorid==6)
		{
		if(minorid==0)
			{
			return "Windows Vista";
			}
		else if(minorid==1)
			{
			return "Windows 7";
			}
		else if(minorid==2)
			{
			return "Windows 8";
			}
		}

	return "Unknown Windows";
	}


/////////////////////////////////////////////
int MMachineInfo::GetMemoryInUsePercent(void)
	{
	return (int)mMemInfo->dwMemoryLoad;
	}


//////////////////////////////////////////////
int MMachineInfo::GetPhysicalMemoryMB(void)
	{
	return (int)(mMemInfo->ullTotalPhys/(1024*1024) );
	}


/////////////////////////////////////////////
int MMachineInfo::GetPhysicalMemoryAvailibleMB(void)
	{
	return (int)(mMemInfo->ullAvailPhys/(1024*1024) );
	}


//////////////////////////////////////////////
int MMachineInfo::GetVirtualMemoryMB(void)
	{
	return (int)(mMemInfo->ullTotalVirtual/(1024*1024) );
	}


///////////////////////////////////////////////
int MMachineInfo::GetVirtualMemoryAvailibleMB(void)
	{
	return (int)(mMemInfo->ullAvailVirtual/(1024*1024) );
	}


//////////////////////////////////////////////
const char *MMachineInfo::GetCPUInfo(void)
	{
	return GGetCPUInfo();
	}	


