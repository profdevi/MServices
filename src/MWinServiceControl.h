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


//v2.0 copyright Comine.com 20150812W0852
#ifndef MWinServiceControl_h
#define MWinServiceControl_h

/////////////////////////////////////////////////////
#include <windows.h>
#include "MBuffer.h"
#include "MString.h"

//******************************************************
//**  MWinServiceControl class
//******************************************************
class MWinServiceControl
	{
	////////////////////////////////////////////////
	MBuffer mBuffer;								// Buffer Space
	int mServiceCount;								// Total Number of Services
	
	////////////////////////////////////////////////
	void ClearObject(void);
	
	////////////////////////////////////////////////
	public:
	MWinServiceControl(void);
	~MWinServiceControl(void);
	bool Create(void);
	bool Destroy(void);
	int GetCount(void);								// Services
	const char *GetShortName(int index);
	const char *GetLongName(int index);
	bool GetDescription(int index,MString &description);
	bool GetImagePath(int index,MString &imagepath);

	// returns the current state of service
	//=0(Failure) | SERVICE_CONTINUE_PENDING|SERVICE_PAUSE_PENDING|SERVICE_PAUSED
	//|SERVICE_RUNNING|SERVICE_START_PENDING|SERVICE_STOP_PENDING
	//|SERVICE_STOPPED
	unsigned int GetCurrentState(int index);
	
	//=-1(Failure)|=0(Disabled),=1(Manual Start),=2(AutoStart)
	int GetStartState(int index);

	//state=0(Disabled),=1(Manual Start),=2(AutoStart)
	bool SetStartState(int index,int state);

	// Get the service index given shortname
	int GetServiceIndex(const char *shortname);

	// Start Service
	bool StartService(int index,int argn,const char *argv[]);
	bool StopService(int index);
	bool PauseService(int index);
	bool ContinueService(int index);
	};


#endif // MWinServiceControl_h

