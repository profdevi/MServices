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


//v1.6 copyright Comine.com 20231215F1711
#include "MStdLib.h"
#include "MCommandArg.h"
#include "MWinServiceControl.h"
#include "MWinServiceInfo.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MServices";		// Used in Help
static const char *GApplicationVersion="1.6";			// Used in Help


////////////////////////////////////////////////////
static void GDisplayHelp(void);
static bool GListServices(void);		// List out Services
static bool GListServices(int state);	// List out Services
static bool GListServicesLocation(void);	// List out Service Location
static bool GSetStartState(const char *service,int state);
static bool GStopService(const char *service);
static bool GStartService(const char *service);
static bool GPauseService(const char *service);
static bool GContinueService(const char *service);
static bool GStatusService(const char *service);
static bool GFullAutoStart(void);
static bool GFullManualStart(void);
static bool GSetServiceStart(bool bareminimum);
static bool GStartAutoServices(void);
static bool GStartAllServices(void);


////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);

	// Check for help display
	if(args.CheckRemoveHelp()==true) { GDisplayHelp();  return 0; }


	// start service
	if(args.CheckRemoveArg("-s")==true)
		{
		int i;
		for(i=1;i<args.GetArgCount();++i)
			{
			MStdPrintf("%-20s: ",args.GetArg(i));
			if(GStartService(args.GetArg(i))==true)
				{  MStdPrintf("ok\n");  }
			}

		return 0;
		}

	// stop services
	if(args.CheckRemoveArg("-x")==true)
		{
		int i;
		for(i=1;i<args.GetArgCount();++i)
			{
			MStdPrintf("%-20s: ",args.GetArg(i));
			if(GStopService(args.GetArg(i))==true)
				{  MStdPrintf("ok\n");  }
			}

		return 0;
		}

	// Pause Services
	if(args.CheckRemoveArg("-p")==true)
		{
		int i;
		for(i=1;i<args.GetArgCount();++i)
			{
			MStdPrintf("%-20s: ",args.GetArg(i));
			if(GPauseService(args.GetArg(i))==true)
				{  MStdPrintf("ok\n");  }
			}

		return 0;
		}

	// Continue Services
	if(args.CheckRemoveArg("-c")==true)
		{
		int i;
		for(i=1;i<args.GetArgCount();++i)
			{
			MStdPrintf("%-20s: ",args.GetArg(i));
			if(GContinueService(args.GetArg(i))==true)
				{  MStdPrintf("ok\n");  }
			}

		return 0;
		}

	// set services to auto start
	if(args.CheckRemoveArg("-a")==true)
		{
		int i;
		for(i=1;i<args.GetArgCount();++i)
			{
			MStdPrintf("%-20s: ",args.GetArg(i));
			if(GSetStartState(args.GetArg(i),2)==true)
				{  MStdPrintf("ok\n");  }
			}

		return 0;
		}

	// set services to manual start
	if(args.CheckRemoveArg("-m")==true)
		{
		int i;
		for(i=1;i<args.GetArgCount();++i)
			{
			MStdPrintf("%-20s: ",args.GetArg(i));
			if(GSetStartState(args.GetArg(i),1)==true)
				{  MStdPrintf("ok\n");  }
			}

		return 0;
		}

	// set services to disabled
	if(args.CheckRemoveArg("-d")==true)
		{
		int i;
		for(i=1;i<args.GetArgCount();++i)
			{
			MStdPrintf("%-20s: ",args.GetArg(i));
			if(GSetStartState(args.GetArg(i),0)==true)
				{  MStdPrintf("ok\n");  }
			}

		return 0;
		}

	// status services
	if(args.CheckRemoveArg("-i")==true)
		{
		int i;
		for(i=1;i<args.GetArgCount();++i)
			{
			MStdPrintf("%-20s: ",args.GetArg(i));
			GStatusService(args.GetArg(i));
			}

		return 0;
		}

	// Info on running processes
	if(args.CheckRemoveArg("-ir")==true)
		{
		GListServices(SERVICE_RUNNING);
		return 0;
		}

	// Info on stopped processes
	if(args.CheckRemoveArg("-is")==true)
		{
		GListServices(SERVICE_STOPPED);
		return 0;
		}

	// Info on paused processes
	if(args.CheckRemoveArg("-ip")==true)
		{
		GListServices(SERVICE_PAUSED);
		return 0;
		}

	// Show service location 
	if(args.CheckRemoveArg("-l")==true)
		{
		GListServicesLocation();
		return 0;
		}

	// start all services
	if(args.CheckRemoveArg("-1")==true)
		{
		GStartAllServices();
		return 0;
		}

	// start all services marked auto
	if(args.CheckRemoveArg("-2")==true)
		{
		GStartAutoServices();
		return 0;
		}

	// Set all services to original os
	if(args.CheckRemoveArg("-3")==true)
		{
		GSetServiceStart(false);
		return 0;
		}

	// full auto start
	if(args.CheckRemoveArg("-4")==true)
		{
		GFullAutoStart();
		return 0;
		}

	// full manual start
	if(args.CheckRemoveArg("-5")==true)
		{
		GFullManualStart();
		return 0;
		}

	// set os to minimum start
	if(args.CheckRemoveArg("-6")==true)
		{
		GSetServiceStart(true);
		return 0;
		}

	GListServices();
	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"   usage:   %s [options] [-?]\n"
			"            v%s copyright Comine.com\n"
			"\n"
			"            Controls and displays NT Services.  \n"
			"\n"
			"   options: Use the short name of a service for identity\n"
			"            -s <name>+                 : Start Services\n"
			"            -x <name>+                 : Stop Service \n"
			"            -p <name>+                 : Pause Service \n"
			"            -c <name>+                 : Continue Service \n"
			"            -a <name>+                 : Set Service to auto start\n"
			"            -m <name>+                 : Set Service to manual Start\n"
			"            -d <name>+                 : Set Service to disabled\n"
			"            -i <name>+                 : Info Status of services\n"
			"            -ir                        : Info on Running Services\n"
			"            -is                        : Info on Stopped Services\n"
			"            -ip                        : Info on Paused Services\n"
			"            -l                         : Service Path Location\n"
			"            -1                         : Start All Services\n"
			"            -2                         : Start all services marked auto\n"
			"            -3                         : Set Services to OS Original start\n"
			"            -4                         : Set all services to auto start\n"
			"            -5                         : Set all services to manual start\n"
			"            -6                         : Set Services to OS Minimal start\n"
			,GApplicationName,GApplicationVersion);
	}


///////////////////////////////////////////////////////
// Displays all Services
static bool GListServices(void)
	{
	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Control\n");
		return false;
		}

	int i;
	for(i=0;i<control.GetCount();++i)
		{
		// Print out Startstate
		int startstate=control.GetStartState(i);
		if(startstate<0)
			{  MStdPrintf(" ????    ");  }
		else if(startstate==0)
			{  MStdPrintf(" Dis  ");  }
		else if(startstate==1)
			{  MStdPrintf(" Man  ");  }
		else if(startstate==2)
			{  MStdPrintf(" Auto ");  }

		// Check for current status
		unsigned int state=control.GetCurrentState(i);
		if(state==SERVICE_PAUSED)
			{  MStdPrintf("Paus"); }
		else if(state==SERVICE_RUNNING)
			{  MStdPrintf("Run "); }
		else if(state==SERVICE_STOPPED)
			{  MStdPrintf("Stop"); }
		else
			{  MStdPrintf(" ? ");  }

		MStdPrintf("  %s - ",control.GetShortName(i));

		MStdPrintf("%s",control.GetLongName(i) );

		MStdPrintf("\n");
		}

	return true;
	}


///////////////////////////////////////////////////////
// Displays Services
static bool GListServices(int viewstate)
	{
	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Control\n");
		return false;
		}

	int i;
	for(i=0;i<control.GetCount();++i)
		{
		unsigned int state=control.GetCurrentState(i);
		if(state!=(unsigned int)viewstate) { continue; }
		// Print out Startstate
		int startstate=control.GetStartState(i);
		if(startstate<0)
			{  MStdPrintf(" ????    ");  }
		else if(startstate==0)
			{  MStdPrintf(" Dis  ");  }
		else if(startstate==1)
			{  MStdPrintf(" Man  ");  }
		else if(startstate==2)
			{  MStdPrintf(" Auto ");  }

		// Check for current status
		if(state==SERVICE_PAUSED)
			{  MStdPrintf("Paus"); }
		else if(state==SERVICE_RUNNING)
			{  MStdPrintf("Run "); }
		else if(state==SERVICE_STOPPED)
			{  MStdPrintf("Stop"); }
		else
			{  MStdPrintf(" ? ");  }

		MStdPrintf("  %s - ",control.GetShortName(i));

		MStdPrintf("%s",control.GetLongName(i) );

		MStdPrintf("\n");
		}

	return true;
	}


///////////////////////////////////////////////////////
// Displays all Services
static bool GListServicesLocation(void)
	{
	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Control\n");
		return false;
		}

	int i;
	for(i=0;i<control.GetCount();++i)
		{
		MStdPrintf("%s",control.GetShortName(i));

		MString location;
		if(control.GetImagePath(i,location)==false)
			{
			location.Create("No Path Found");
			}

		MStdPrintf(" => %s",location.Get() );

		MStdPrintf("\n");
		}

	return true;
	}


/////////////////////////////////////////////////////////////
// Start a service
static bool GSetStartState(const char *service,int state)
	{
	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Controler\n");
		return false;
		}

	int index=control.GetServiceIndex(service);
	if(index<0)
		{
		MStdPrintf("*Service Name not found\n");
		return false;
		}

	if(control.SetStartState(index,state)==false)
		{
		MStdPrintf("Unable to set service start start\n");
		return false;
		}
	
	return true;
	}


//////////////////////////////////////////////////////////////
// Start a service
static bool GStartService(const char *service)
	{
	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Controler\n");
		return false;
		}

	int index=control.GetServiceIndex(service);
	if(index<0)
		{
		MStdPrintf("*Service Name not found\n");
		return false;
		}

	const char *argv[2]={service,NULL};

	if(control.StartService(index,1,argv)==false)
		{
		MStdPrintf("*Unable to start service\n");
		return false;
		}

	return true;
	}


//////////////////////////////////////////////////////////////
// Stop a service
static bool GStopService(const char *service)
	{
	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Controler\n");
		return false;
		}

	int index=control.GetServiceIndex(service);
	if(index<0)
		{
		MStdPrintf("*Service Name not found\n");
		return false;
		}

	if(control.StopService(index)==false)
		{
		MStdPrintf("*Unable to stop service\n");
		return false;
		}

	return true;
	}


//////////////////////////////////////////////////////////////
// Pause a service
static bool GPauseService(const char *service)
	{
	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Controler\n");
		return false;
		}

	int index=control.GetServiceIndex(service);
	if(index<0)
		{
		MStdPrintf("*Service Name not found\n");
		return false;
		}

	if(control.PauseService(index)==false)
		{
		MStdPrintf("*Unable to pause service\n");
		return false;
		}

	return true;
	}


//////////////////////////////////////////////////////////////
// Continue a service
static bool GContinueService(const char *service)
	{
	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Controler\n");
		return false;
		}

	int index=control.GetServiceIndex(service);
	if(index<0)
		{
		MStdPrintf("*Service Name not found\n");
		return false;
		}

	if(control.ContinueService(index)==false)
		{
		MStdPrintf("*Unable to continue service\n");
		return false;
		}

	return true;
	}


////////////////////////////////////////////////////////////
// Status of Service
static bool GStatusService(const char *service)
	{
	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Controler\n");
		return false;
		}

	int index=control.GetServiceIndex(service);
	if(index<0)
		{
		MStdPrintf("*Service Name not found\n");
		return false;
		}

	unsigned int state=control.GetCurrentState(index);
	if(state==SERVICE_PAUSED)
		{  MStdPrintf("paused  "); }
	else if(state==SERVICE_RUNNING)
		{  MStdPrintf("running "); }
	else if(state==SERVICE_STOPPED)
		{  MStdPrintf("stopped "); }
	else
		{  MStdPrintf("  ?     "); }

	// Print out Startstate
	int startstate=control.GetStartState(index);
	if(startstate<0)
		{  MStdPrintf(" ?     ");  }
	else if(startstate==0)
		{  MStdPrintf("disabled ");  }
	else if(startstate==1)
		{  MStdPrintf("manual   ");  }
	else if(startstate==2)
		{  MStdPrintf("auto     ");  }

	MStdPrintf("\n");
	return true;
	}


////////////////////////////////////////////////////////////
static bool GFullAutoStart(void)
	{
	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Controler\n");
		return false;
		}

	int i;
	for(i=0;i<control.GetCount();++i)
		{
		MStdPrintf("%-20s: ",control.GetShortName(i));
		if(GSetStartState(control.GetShortName(i),2)==true)
			{  MStdPrintf("ok\n");  }
		}

	return true;
	}


////////////////////////////////////////////////////////////
static bool GFullManualStart(void)
	{
	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Controler\n");
		return false;
		}

	int i;
	for(i=0;i<control.GetCount();++i)
		{
		MStdPrintf("%-20s: ",control.GetShortName(i));
		if(GSetStartState(control.GetShortName(i),1)==true)
			{  MStdPrintf("ok\n");  }
		}

	return true;
	}


///////////////////////////////////////////////////////////
static bool GSetServiceStart(bool bareminimum)
	{
	MWinServiceInfo serviceinfo;
	if(serviceinfo.Create(bareminimum)==false)
		{
		MStdPrintf("*Unable to get OS Service Information\n");
		return false;
		}

	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Controler\n");
		return false;
		}

	int i;
	for(i=0;i<serviceinfo.GetCount();++i)
		{
		int index=control.GetServiceIndex(serviceinfo.GetServiceName(i));
		if(index<0) { continue; }

		if(control.SetStartState(index,serviceinfo.GetStartState(i))==true)
			{
			MStdPrintf("%-20s: ok\n",serviceinfo.GetServiceName(i) );
			}
		else
			{
			MStdPrintf("%-20s: *Failed*\n",serviceinfo.GetServiceName(i) );
			// Unable to set service to default
			}
		}

	return true;
	}


/////////////////////////////////////////////////////////////////////////
// Start all Services marked as Auto
static bool GStartAutoServices(void)
	{
	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Controler\n");
		return false;
		}

	int i;
	for(i=0;i<control.GetCount();++i)
		{
		int startstate=control.GetStartState(i);
		if(startstate!=2) { continue; }

		MStdPrintf(" %-20s: ",control.GetShortName(i));
		if(GStartService(control.GetShortName(i))==true)
			{  MStdPrintf("ok\n"); continue; }		
		}
	
	return true;
	}


/////////////////////////////////////////////////////////////////////////
// Start all Services marked as Auto
static bool GStartAllServices(void)
	{
	MWinServiceControl control;
	if(control.Create()==false)
		{
		MStdPrintf("*Unable to init Service Controler\n");
		return false;
		}

	int i;
	for(i=0;i<control.GetCount();++i)
		{
		MStdPrintf(" %-20s: ",control.GetShortName(i));
		if(GStartService(control.GetShortName(i))==true)
			{  MStdPrintf("ok\n"); continue; }		
		}
	
	return true;
	}


