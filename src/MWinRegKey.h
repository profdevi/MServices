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


//v2.3 copyright Comine.com 20180515T0646
#ifndef MWinRegKey_h
#define MWinRegKey_h

////////////////////////////////////////////////////
#include <windows.h>
#include "MString.h"
#include "MBuffer.h"

// Data types are REG_BINARY, REG_DWORD, REG_DWORD_LITTLE_ENDIAN
// REG_DWORD_BIG_ENDIAN  REG_EXPAND_SZ  REG_LINK  REG_MULTI_SZ REG_NONE
// REG_RESOURCE_LIST  REG_SZ

////////////////////////////////////////////////////
class MWinRegKey
	{
	static DWORD mTmpType;
	static DWORD mTmpSize;
	HKEY mKeyHandle;

	//////////////////////////////////////////////
	void ClearObject(void);
	bool CreateNewKey(const char *keyname,HKEY root,bool setvolatile,REGSAM access);
	bool CreateNewKey(const wchar_t *keyname,HKEY root,bool setvolatile,REGSAM access);
	bool OpenExistingKey(const char *keyname,HKEY root,REGSAM access);
	bool OpenExistingKey(const wchar_t *keyname,HKEY root,REGSAM access);

	////////////////////////////////////////////////
	public:
	MWinRegKey(void);
	~MWinRegKey(void);
	bool Create(bool create			// =true if create a fresh key
			,const char *keyname
			,HKEY root=HKEY_CURRENT_USER
			,bool setvolatile=true  // =true if key will be gone by shutdown
			,REGSAM access=KEY_READ|KEY_WRITE); // Create/Open Key
	bool Create(bool create			// =true if create a fresh key
			,const wchar_t *keyname
			,HKEY root=HKEY_CURRENT_USER
			,bool setvolatile=true  // =true if key will be gone by shutdown
			,REGSAM access=KEY_READ|KEY_WRITE); // Create/Open Key
	bool Destroy(void);
	HKEY GetKey(void);
	bool SetValueData(const char *name,const char *data);
	bool SetValueData(const wchar_t *name,const wchar_t *data);
	bool SetValueDataExpand(const char *name,const char *data);
	bool SetValueDataExpand(const wchar_t *name,const wchar_t *data);

	bool SetValueData(const char *name,DWORD value);
	bool SetValueData(const wchar_t *name,DWORD value);
	bool GetValueData(const char *name,MString &outvalue); // outvalue is a return value
	bool GetValueData(const wchar_t *name,MStringWide &outvalue); // outvalue is a return value
	bool GetValueData(const char *name,DWORD &value);
	bool GetValueData(const wchar_t *name,DWORD &value);
	bool GetValueData(const char *name,MBuffer &buffer);
	bool GetValueData(const wchar_t *name,MBuffer &buffer);
	bool DeleteValue(const char *name);
	bool DeleteValue(const wchar_t *name);
	bool GetValueTypeSize(const char *name,DWORD &type,DWORD &size=mTmpSize);
	bool GetValueTypeSize(const wchar_t *name,DWORD &type,DWORD &size=mTmpSize);
	bool GetSubKeyName(int index,MString &name);		// Keep increasing index until false
	bool GetSubKeyName(int index,MStringWide &name);	// Keep increasing index until false
	bool GetValueName(int index,MString &name,DWORD &type=mTmpType,DWORD &size=mTmpSize);
	bool GetValueName(int index,MStringWide &name,DWORD &type=mTmpType,DWORD &size=mTmpSize);
	bool DoesNameExist(const char *name);
	bool DoesNameExist(const wchar_t *name);

	/////// Class Methods //////////////////
	static bool Delete(const char *keyname,HKEY root=HKEY_CURRENT_USER);	// fails if child keys exist
	static bool Delete(const wchar_t *keyname,HKEY root=HKEY_CURRENT_USER);	// fails if child keys exist
	static bool DeleteTree(const char *keyname,HKEY root);					// Recursively delete key
	static bool DeleteTree(const wchar_t *keyname,HKEY root);				// Recursively delete key
	static bool DoesKeyExist(const char *keyname,HKEY root=HKEY_CURRENT_USER);
	static bool DoesKeyExist(const wchar_t *keyname,HKEY root=HKEY_CURRENT_USER);
	};


#endif // MWinRegKey_h

