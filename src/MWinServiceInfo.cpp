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


//v1.4 copyright Comine.com 20231215F1706
#include "MStdLib.h"
#include "MMachineInfo.h"
#include "MWinServiceInfo.h"


//******************************************************
//**  TO DO
//******************************************************
/*

	1. The  Windows 10 list has services with _???? ending that
	needs to bematched with a local services that end with numbers.
	
	2.  The Minimal Service list for windows 10 is exact copy
		of Default Service List.   Need to find service list
		reference.

	3.  Need to double check all services again.  Windows 2000/XP/Vista

	4.  Need referneces for Windows 11 services

*/


//******************************************************
//**  Module Elements
//******************************************************
struct GServiceState
	{
	const char *Service;					// Service Name
	int StartState;							// startvalue 0(Disabled),1(Manual),2(Automatic)
	};


/////////////////////////////////////////////////////////////
// Default Documentation from : http://www.blackviper.com
static GServiceState GXPDefaultStart[]=
	{
	"Alerter",0,						// Alerter
	"ALG",1,							// Application Layer Gateway Service
	"AppMgmt",1,						// Application Management
	"aspnet_state",1,					// ASP.NET State Service 
	"AudioSrv",2,						// Windows Audio
	"BITS",1,							// Background Intelligent Transfer Service
	"Browser",2,						// Computer Browser
	"CiSvc",1,							// Indexing Service
	"ClipSrv",0,						// ClipBook
	"COMSysApp",1,						// COM+ System Application
	"CryptSvc",2,						// Cryptographic Services
	"DcomLaunch",2,						// DCOM Server Process Launcher
	"Dhcp",2,							// DHCP Client
	"dmadmin",1,						// Logical Disk Manager Administrative Service
	"dmserver",2,						// Logical Disk Manager
	"Dnscache",2,						// DNS Client
	"DXDebug",1,						// DirectX Debug Service
	"ERSvc",2,							// Error Reporting Service
	"Eventlog",2,						// Event Log
	"EventSystem",1,					// COM+ Event System
	"FastUserSwitchingCompatibility",1,	// Fast User Switching Compatibility
	"helpsvc",2,						// Help and Support
	"HidServ",0,						// Human Interface Device Access
	"HTTPFilter",1,						// HTTP SSL
	"IISADMIN",1,						// IIS Admin
	"ImapiService",1,					// IMAPI CD-Burning COM Service
	"lanmanserver",2,					// Server
	"lanmanworkstation",2,				// Workstation
	"LmHosts",2,						// TCP/IP NetBIOS Helper
	"MDM",1,							// Machine Debug Manager
	"Messenger",0,						// Messenger
	"mnmsrvc",1,						// NetMeeting Remote Desktop Sharing
	"MSDTC",1,							// Distributed Transaction Coordinator
	"MSFtpsvc",1,						// FTP Publishing
	"MSIServer",1,						// Windows Installer
	"MSMQ",1,							// Message Queuing
	"MSMQTriggers",1,					// Message Queuing Triggers
	"NetDDE",0,							// Network DDE
	"NetDDEdsdm",0,						// Network DDE DSDM
	"Netlogon",1,						// Net Logon 
	"Netman",1,							// Network Connections
	"Nla",1,							// Network Location Awareness (NLA)
	"NtLmSsp",1,						// NT LM Security Support Provider
	"NtmsSvc",1,						// Removable Storage
	"PlugPlay",2,						// Plug and Play
	"PolicyAgent",2,					// IPSEC Services
	"ProtectedStorage",2,				// Protected Storage
	"RasAuto",1,						// Remote Access Auto Connection Manager
	"RasMan",1,							// Remote Access Connection Manager
	"RDSessMgr",1,						// Remote Desktop Help Session Manager
	"RemoteAccess",0,					// Routing and Remote Access
	"RemoteRegistry",2,					// Remote Registry
	"RpcLocator",1,						// Remote Procedure Call (RPC) Locator
	"RpcSs",2,							// Remote Procedure Call (RPC)
	"RSVP",1,							// QoS RSVP
	"SamSs",2,							// Security Accounts Manager
	"SCardSvr",1,						// Smart Card
	"Schedule",2,						// Task Scheduler
	"seclogon",2,						// Secondary Logon
	"SENS",2,							// System Event Notification
	"SharedAccess",2,					// Windows Firewall/Internet Connection Sharing (ICS)
	"ShellHWDetection",2,				// Shell Hardware Detection
	"SMTPSVC",1,						// Simple Mail Transfer Protocol (SMTP)
	"Spooler",2,						// Print Spooler
	"srservice",2,						// System Restore Service
	"SSDPSRV",1,						// SSDP Discovery Service
	"stisvc",1,							// Windows Image Acquisition (WIA)
	"SwPrv",1,							// MS Software Shadow Copy Provider
	"SysmonLog",1,						// Performance Logs and Alerts   
	"TapiSrv",1,						// Telephony
	"TermService",1,					// Terminal Services
	"Themes",2,							// Themes
	"TlntSvr",1,						// Telnet
	"TrkWks",2,							// Distributed Link Tracking Client
	"upnphost",1,						// Universal Plug and Play Device Host
	"UPS",1,							// Uninterruptible Power Supply  
	"VSS",1,							// Volume Shadow Copy
	"W32Time",2,						// Windows Time 
	"W3SVC",1,							// World Wide Web Publishing
	"WebClient",2,						// WebClient
	"winmgmt",2,						// Windows Management Instrumentation
	"WmdmPmSN",1,						// Portable Media Serial Number Service
	"Wmi",1,							// Windows Management Instrumentation Driver Extensions
	"WmiApSrv",1,						// WMI Performance Adapter
	"wscsvc",2,							// Security Center
	"wuauserv",2,						// Automatic Updates
	"WZCSVC",2,							// Wireless Zero Configuration
	"xmlprov",1,						// Network Provisioning Service
	};


/////////////////////////////////////////////////////////////
static GServiceState GXPBareMinimum[]=
	{
	"Alerter",1,						// Alerter
	"ALG",1,							// Application Layer Gateway Service
	"AppMgmt",1,						// Application Management
	"aspnet_state",1,					// ASP.NET State Service 
	"AudioSrv",2,						// Windows Audio
	"BITS",1,							// Background Intelligent Transfer Service
	"Browser",1,						// Computer Browser
	"CiSvc",1,							// Indexing Service
	"ClipSrv",1,						// ClipBook
	"COMSysApp",1,						// COM+ System Application
	"CryptSvc",1,						// Cryptographic Services
	"DcomLaunch",1,						// DCOM Server Process Launcher
	"Dhcp",2,							// DHCP Client
	"dmadmin",1,						// Logical Disk Manager Administrative Service
	"dmserver",1,						// Logical Disk Manager
	"Dnscache",1,						// DNS Client
	"DXDebug",1,						// DirectX Debug Service
	"ERSvc",1,							// Error Reporting Service
	"Eventlog",2,						// Event Log
	"EventSystem",1,					// COM+ Event System
	"FastUserSwitchingCompatibility",1,	// Fast User Switching Compatibility
	"helpsvc",1,						// Help and Support
	"HidServ",0,						// Human Interface Device Access
	"HTTPFilter",1,						// HTTP SSL
	"IISADMIN",1,						// IIS Admin
	"ImapiService",1,					// IMAPI CD-Burning COM Service
	"lanmanserver",1,					// Server
	"lanmanworkstation",1,				// Workstation
	"LmHosts",1,						// TCP/IP NetBIOS Helper
	"MDM",1,							// Machine Debug Manager
	"Messenger",1,						// Messenger
	"mnmsrvc",1,						// NetMeeting Remote Desktop Sharing
	"MSDTC",1,							// Distributed Transaction Coordinator
	"MSFtpsvc",1,						// FTP Publishing
	"MSIServer",1,						// Windows Installer
	"MSMQ",1,							// Message Queuing
	"MSMQTriggers",1,					// Message Queuing Triggers
	"NetDDE",1,							// Network DDE
	"NetDDEdsdm",1,						// Network DDE DSDM
	"Netlogon",1,						// Net Logon 
	"Netman",1,							// Network Connections
	"Nla",1,							// Network Location Awareness (NLA)
	"NtLmSsp",1,						// NT LM Security Support Provider
	"NtmsSvc",1,						// Removable Storage
	"PlugPlay",1,						// Plug and Play
	"PolicyAgent",1,					// IPSEC Services
	"ProtectedStorage",2,				// Protected Storage
	"RasAuto",1,						// Remote Access Auto Connection Manager
	"RasMan",1,							// Remote Access Connection Manager
	"RDSessMgr",1,						// Remote Desktop Help Session Manager
	"RemoteAccess",1,					// Routing and Remote Access
	"RemoteRegistry",1,					// Remote Registry
	"RpcLocator",1,						// Remote Procedure Call (RPC) Locator
	"RpcSs",1,							// Remote Procedure Call (RPC)
	"RSVP",1,							// QoS RSVP
	"SamSs",1,							// Security Accounts Manager
	"SCardSvr",1,						// Smart Card
	"Schedule",1,						// Task Scheduler
	"seclogon",1,						// Secondary Logon
	"SENS",1,							// System Event Notification
	"SharedAccess",1,					// Windows Firewall/Internet Connection Sharing (ICS)
	"ShellHWDetection",1,				// Shell Hardware Detection
	"SMTPSVC",1,						// Simple Mail Transfer Protocol (SMTP)
	"Spooler",2,						// Print Spooler
	"srservice",1,						// System Restore Service
	"SSDPSRV",1,						// SSDP Discovery Service
	"stisvc",1,							// Windows Image Acquisition (WIA)
	"SwPrv",1,							// MS Software Shadow Copy Provider
	"SysmonLog",1,						// Performance Logs and Alerts   
	"TapiSrv",1,						// Telephony
	"TermService",1,					// Terminal Services
	"Themes",1,							// Themes
	"TlntSvr",1,						// Telnet
	"TrkWks",1,							// Distributed Link Tracking Client
	"upnphost",1,						// Universal Plug and Play Device Host
	"UPS",1,							// Uninterruptible Power Supply  
	"VSS",1,							// Volume Shadow Copy
	"W32Time",1,						// Windows Time 
	"W3SVC",1,							// World Wide Web Publishing
	"WebClient",1,						// WebClient
	"winmgmt",2,						// Windows Management Instrumentation
	"WmdmPmSN",1,						// Portable Media Serial Number Service
	"Wmi",1,							// Windows Management Instrumentation Driver Extensions
	"WmiApSrv",1,						// WMI Performance Adapter
	"wscsvc",1,							// Security Center
	"wuauserv",1,						// Automatic Updates
	"WZCSVC",2,							// Wireless Zero Configuration
	"xmlprov",1,						// Network Provisioning Service
	};


/////////////////////////////////////////////////////////////
static GServiceState GWin2000DefaultStart[]=
	{
	"Alerter",2,						// Alerter
	"ALG",1,							// Application Layer Gateway Service
	"AppMgmt",1,						// Application Management
	"aspnet_state",1,					// ASP.NET State Service 
	"AudioSrv",1,						// Windows Audio
	"BITS",1,							// Background Intelligent Transfer Service
	"Browser",2,						// Computer Browser
	"CiSvc",1,							// Indexing Service
	"ClipSrv",1,						// ClipBook
	"COMSysApp",1,						// COM+ System Application
	"CryptSvc",1,						// Cryptographic Services
	"DcomLaunch",1,						// DCOM Server Process Launcher
	"Dhcp",2,							// DHCP Client
	"dmadmin",1,						// Logical Disk Manager Administrative Service
	"dmserver",1,						// Logical Disk Manager
	"Dnscache",2,						// DNS Client
	"DXDebug",1,						// DirectX Debug Service
	"ERSvc",2,							// Error Reporting Service
	"Eventlog",2,						// Event Log
	"EventSystem",1,					// COM+ Event System
	"FastUserSwitchingCompatibility",1,	// Fast User Switching Compatibility
	"helpsvc",1,						// Help and Support
	"HidServ",1,						// Human Interface Device Access
	"HTTPFilter",1,						// HTTP SSL
	"IISADMIN",2,						// IIS Admin
	"ImapiService",1,					// IMAPI CD-Burning COM Service
	"lanmanserver",2,					// Server
	"lanmanworkstation",2,				// Workstation
	"LmHosts",2,						// TCP/IP NetBIOS Helper
	"MDM",1,							// Machine Debug Manager
	"Messenger",2,						// Messenger
	"mnmsrvc",1,						// NetMeeting Remote Desktop Sharing
	"MSDTC",2,							// Distributed Transaction Coordinator
	"MSFtpsvc",1,						// FTP Publishing
	"MSIServer",1,						// Windows Installer
	"MSMQ",1,							// Message Queuing
	"MSMQTriggers",1,					// Message Queuing Triggers
	"NetDDE",1,							// Network DDE
	"NetDDEdsdm",1,						// Network DDE DSDM
	"Netlogon",1,						// Net Logon 
	"Netman",1,							// Network Connections
	"Nla",1,							// Network Location Awareness (NLA)
	"NtLmSsp",1,						// NT LM Security Support Provider
	"NtmsSvc",1,						// Removable Storage
	"PlugPlay",2,						// Plug and Play
	"PolicyAgent",1,					// IPSEC Services
	"ProtectedStorage",2,				// Protected Storage
	"RasAuto",1,						// Remote Access Auto Connection Manager
	"RasMan",1,							// Remote Access Connection Manager
	"RDSessMgr",1,						// Remote Desktop Help Session Manager
	"RemoteAccess",0,					// Routing and Remote Access
	"RemoteRegistry",2,					// Remote Registry
	"RpcLocator",1,						// Remote Procedure Call (RPC) Locator
	"RpcSs",2,							// Remote Procedure Call (RPC)
	"RSVP",1,							// QoS RSVP
	"SamSs",2,							// Security Accounts Manager
	"SCardSvr",1,						// Smart Card
	"Schedule",2,						// Task Scheduler
	"seclogon",2,						// Secondary Logon
	"SENS",2,							// System Event Notification
	"SharedAccess",2,					// Windows Firewall/Internet Connection Sharing (ICS)
	"ShellHWDetection",2,				// Shell Hardware Detection
	"SMTPSVC",1,						// Simple Mail Transfer Protocol (SMTP)
	"Spooler",2,						// Print Spooler
	"srservice",2,						// System Restore Service
	"SSDPSRV",1,						// SSDP Discovery Service
	"stisvc",1,							// Windows Image Acquisition (WIA)
	"SwPrv",1,							// MS Software Shadow Copy Provider
	"SysmonLog",1,						// Performance Logs and Alerts   
	"TapiSrv",1,						// Telephony
	"TermService",0,					// Terminal Services
	"Themes",1,							// Themes
	"TlntSvr",1,						// Telnet
	"TrkWks",2,							// Distributed Link Tracking Client
	"upnphost",1,						// Universal Plug and Play Device Host
	"UPS",1,							// Uninterruptible Power Supply  
	"VSS",1,							// Volume Shadow Copy
	"W32Time",2,						// Windows Time 
	"W3SVC",2,							// World Wide Web Publishing
	"WebClient",2,						// WebClient
	"winmgmt",1,						// Windows Management Instrumentation
	"WmdmPmSN",1,						// Portable Media Serial Number Service
	"Wmi",1,							// Windows Management Instrumentation Driver Extensions
	"WmiApSrv",1,						// WMI Performance Adapter
	"wscsvc",1,							// Security Center
	"wuauserv",2,						// Automatic Updates
	"WZCSVC",2,							// Wireless Zero Configuration
	"xmlprov",1,						// Network Provisioning Service
	};


/////////////////////////////////////////////////////////////
static GServiceState GWin2000BareMinimum[]=
	{
	"Alerter",1,						// Alerter
	"ALG",1,							// Application Layer Gateway Service
	"AppMgmt",1,						// Application Management
	"aspnet_state",1,					// ASP.NET State Service 
	"AudioSrv",1,						// Windows Audio
	"BITS",1,							// Background Intelligent Transfer Service
	"Browser",1,						// Computer Browser
	"CiSvc",1,							// Indexing Service
	"ClipSrv",1,						// ClipBook
	"COMSysApp",1,						// COM+ System Application
	"CryptSvc",1,						// Cryptographic Services
	"DcomLaunch",1,						// DCOM Server Process Launcher
	"Dhcp",2,							// DHCP Client
	"dmadmin",1,						// Logical Disk Manager Administrative Service
	"dmserver",1,						// Logical Disk Manager
	"Dnscache",1,						// DNS Client
	"DXDebug",1,						// DirectX Debug Service
	"ERSvc",1,							// Error Reporting Service
	"Eventlog",1,						// Event Log
	"EventSystem",1,					// COM+ Event System
	"FastUserSwitchingCompatibility",1,	// Fast User Switching Compatibility
	"helpsvc",1,						// Help and Support
	"HidServ",1,						// Human Interface Device Access
	"HTTPFilter",1,						// HTTP SSL
	"IISADMIN",1,						// IIS Admin
	"ImapiService",1,					// IMAPI CD-Burning COM Service
	"lanmanserver",1,					// Server
	"lanmanworkstation",1,				// Workstation
	"LmHosts",1,						// TCP/IP NetBIOS Helper
	"MDM",1,							// Machine Debug Manager
	"Messenger",1,						// Messenger
	"mnmsrvc",1,						// NetMeeting Remote Desktop Sharing
	"MSDTC",1,							// Distributed Transaction Coordinator
	"MSFtpsvc",1,						// FTP Publishing
	"MSIServer",1,						// Windows Installer
	"MSMQ",1,							// Message Queuing
	"MSMQTriggers",1,					// Message Queuing Triggers
	"NetDDE",1,							// Network DDE
	"NetDDEdsdm",1,						// Network DDE DSDM
	"Netlogon",1,						// Net Logon 
	"Netman",1,							// Network Connections
	"Nla",1,							// Network Location Awareness (NLA)
	"NtLmSsp",1,						// NT LM Security Support Provider
	"NtmsSvc",1,						// Removable Storage
	"PlugPlay",1,						// Plug and Play
	"PolicyAgent",1,					// IPSEC Services
	"ProtectedStorage",2,				// Protected Storage
	"RasAuto",1,						// Remote Access Auto Connection Manager
	"RasMan",1,							// Remote Access Connection Manager
	"RDSessMgr",1,						// Remote Desktop Help Session Manager
	"RemoteAccess",0,					// Routing and Remote Access
	"RemoteRegistry",1,					// Remote Registry
	"RpcLocator",1,						// Remote Procedure Call (RPC) Locator
	"RpcSs",1,							// Remote Procedure Call (RPC)
	"RSVP",1,							// QoS RSVP
	"SamSs",1,							// Security Accounts Manager
	"SCardSvr",1,						// Smart Card
	"Schedule",1,						// Task Scheduler
	"seclogon",1,						// Secondary Logon
	"SENS",1,							// System Event Notification
	"SharedAccess",1,					// Windows Firewall/Internet Connection Sharing (ICS)
	"ShellHWDetection",1,				// Shell Hardware Detection
	"SMTPSVC",1,						// Simple Mail Transfer Protocol (SMTP)
	"Spooler",2,						// Print Spooler
	"srservice",1,						// System Restore Service
	"SSDPSRV",1,						// SSDP Discovery Service
	"stisvc",1,							// Windows Image Acquisition (WIA)
	"SwPrv",1,							// MS Software Shadow Copy Provider
	"SysmonLog",1,						// Performance Logs and Alerts   
	"TapiSrv",1,						// Telephony
	"TermService",0,					// Terminal Services
	"Themes",1,							// Themes
	"TlntSvr",1,						// Telnet
	"TrkWks",1,							// Distributed Link Tracking Client
	"upnphost",1,						// Universal Plug and Play Device Host
	"UPS",1,							// Uninterruptible Power Supply  
	"VSS",1,							// Volume Shadow Copy
	"W32Time",1,						// Windows Time 
	"W3SVC",1,							// World Wide Web Publishing
	"WebClient",1,						// WebClient
	"winmgmt",2,						// Windows Management Instrumentation
	"WmdmPmSN",1,						// Portable Media Serial Number Service
	"Wmi",1,							// Windows Management Instrumentation Driver Extensions
	"WmiApSrv",1,						// WMI Performance Adapter
	"wscsvc",1,							// Security Center
	"wuauserv",1,						// Automatic Updates
	"WZCSVC",2,							// Wireless Zero Configuration
	"xmlprov",1,						// Network Provisioning Service
	};


/////////////////////////////////////////////////////////////
// Default Documentation from HP Vista Machine
static GServiceState GVistaDefaultStart[]=
	{
	"AeLookupSvc",1,					// Application Experience
	"AgereModemAudio",2,				// Agere Modem Call Progress Audio
	"ALG",1,							// Application Layer Gateway Service
	"Appinfo",1,						// Application Information
	"AudioEndpointBuilder",2,			// Windows Audio Endpoint Builder
	"AudioSrv",2,						// Windows Audio
	"BFE",2,							// Base Filtering Engine
	"BITS",1,							// Background Intelligent Transfer Service
	"Browser",1,						// Computer Browser
	"CertPropSvc",1,					// Certificate Propagation
	"clr_optimization_v2.0.50727_32",1,	// Microsoft .NET Framework NGEN v2.0.50727_X86
	"clr_optimization_v2.0.50727_64",1,	// Microsoft .NET Framework NGEN v2.0.50727_X64
	"COMSysApp",1,						// COM+ System Application
	"CryptSvc",2,						// Cryptographic Services
	"DcomLaunch",2,						// DCOM Server Process Launcher
	"DFSR",1,							// DFS Replication
	"Dhcp",2,							// DHCP Client
	"Dnscache",2,						// DNS Client
	"dot3svc",1,						// Wired AutoConfig
	"DPS",2,							// Diagnostic Policy Service
	"EapHost",1,						// Extensible Authentication Protocol
	"ehRecvr",1,						// Windows Media Center Receiver Service
	"ehSched",1,						// Windows Media Center Scheduler Service
	"ehstart",1,						// Windows Media Center Service Launcher
	"EMDMgmt",2,						// ReadyBoost
	"Eventlog",2,						// Windows Event Log
	"EventSystem",2,					// COM+ Event System
	"fdPHost",1,						// Function Discovery Provider Host
	"FDResPub",1,						// Function Discovery Resource Publication
	"FontCache3.0.0.0",1,				// Windows Presentation Foundation Font Cache 3.0.0.0
	"GameConsoleService",1,				// GameConsoleService
	"gpsvc",2,							// Group Policy Client
	"hidserv",1,						// Human Interface Device Access
	"hkmsvc",1,							// Health Key and Certificate Management
	"IAANTMON",2,						// Intel(R) Matrix Storage Event Monitor
	"idsvc",1,							// Windows CardSpace
	"IKEEXT",2,							// IKE and AuthIP IPsec Keying Modules
	"IPBusEnum",1,						// PnP-X IP Bus Enumerator
	"iphlpsvc",2,						// IP Helper
	"KeyIso",1,							// CNG Key Isolation
	"KtmRm",1,							// KtmRm for Distributed Transaction Coordinator
	"LanmanServer",2,					// Server
	"LanmanWorkstation",2,				// Workstation
	"lltdsvc",1,						// Link-Layer Topology Discovery Mapper
	"lmhosts",2,						// TCP/IP NetBIOS Helper
	"Mcx2Svc",1,						// Windows Media Center Extender Service
	"MMCSS",2,							// Multimedia Class Scheduler
	"MpsSvc",2,							// Windows Firewall
	"MSDTC",1,							// Distributed Transaction Coordinator
	"MSiSCSI",1,						// Microsoft iSCSI Initiator Service
	"msiserver",1,						// Windows Installer
	"napagent",1,						// Network Access Protection Agent
	"Netlogon",1,						// Netlogon
	"Netman",1,							// Network Connections
	"netprofm",1,						// Network List Service
	"NetTcpPortSharing",1,				// Net.Tcp Port Sharing Service
	"NlaSvc",2,							// Network Location Awareness
	"nsi",2,							// Network Store Interface Service
	"p2pimsvc",1,						// Peer Networking Identity Manager
	"p2psvc",1,							// Peer Networking Grouping
	"PcaSvc",1,							// Program Compatibility Assistant Service
	"PerfHost",1,						// Performance Counter DLL Host
	"pla",1,							// Performance Logs & Alerts
	"PlugPlay",2,						// Plug and Play
	"PNRPAutoReg",1,					// PNRP Machine Name Publication Service
	"PNRPsvc",1,						// Peer Name Resolution Protocol
	"PolicyAgent",1,					// IPsec Policy Agent
	"ProfSvc",2,						// User Profile Service
	"ProtectedStorage",1,				// Protected Storage
	"QWAVE",1,							// Quality Windows Audio Video Experience
	"RasAuto",1,						// Remote Access Auto Connection Manager
	"RasMan",1,							// Remote Access Connection Manager
	"RemoteAccess",1,					// Routing and Remote Access
	"RemoteRegistry",1,					// Remote Registry
	"RpcLocator",1,						// Remote Procedure Call (RPC) Locator
	"RpcSs",2,							// Remote Procedure Call (RPC)
	"SamSs",2,							// Security Accounts Manager
	"SCardSvr",1,						// Smart Card
	"Schedule",2,						// Task Scheduler
	"SCPolicySvc",1,					// Smart Card Removal Policy
	"SDRSVC",1,							// Windows Backup
	"seclogon",1,						// Secondary Logon
	"SENS",2,							// System Event Notification Service
	"SessionEnv",1,						// Terminal Services Configuration
	"SharedAccess",1,					// Internet Connection Sharing (ICS)
	"ShellHWDetection",2,				// Shell Hardware Detection
	"slsvc",0,							// Software Licensing
	"SLUINotify",1,						// SL UI Notification Service
	"SNMPTRAP",1,						// SNMP Trap
	"Spooler",2,						// Print Spooler
	"SSDPSRV",1,						// SSDP Discovery
	"SstpSvc",1,						// Secure Socket Tunneling Protocol Service
	"stisvc",1,							// Windows Image Acquisition (WIA)
	"swprv",1,							// Microsoft Software Shadow Copy Provider
	"SysMain",2,						// Superfetch
	"TabletInputService",1,				// Tablet PC Input Service
	"TapiSrv",1,						// Telephony
	"TBS",1,							// TPM Base Services
	"TermService",1,					// Terminal Services
	"Themes",2,							// Themes
	"THREADORDER",1,					// Thread Ordering Server
	"TrkWks",2,							// Distributed Link Tracking Client
	"TrustedInstaller",1,				// Windows Modules Installer
	"UI0Detect",1,						// Interactive Services Detection
	"upnphost",1,						// UPnP Device Host
	"UxSms",2,							// Desktop Window Manager Session Manager
	"vds",1,							// Virtual Disk
	"VSS",1,							// Volume Shadow Copy
	"W32Time",1,						// Windows Time
	"wcncsvc",1,						// Windows Connect Now - Config Registrar
	"WcsPlugInService",1,				// Windows Color System
	"WdiServiceHost",2,					// Diagnostic Service Host
	"WdiSystemHost",1,					// Diagnostic System Host
	"WebClient",1,						// WebClient
	"Wecsvc",1,							// Windows Event Collector
	"wercplsupport",1,					// Problem Reports and Solutions Control Panel Support
	"WerSvc",1,							// Windows Error Reporting Service
	"WinDefend",2,						// Windows Defender
	"WinHttpAutoProxySvc",1,			// WinHTTP Web Proxy Auto-Discovery Service
	"Winmgmt",2,						// Windows Management Instrumentation
	"WinRM",1,							// Windows Remote Management (WS-Management)
	"Wlansvc",1,						// WLAN AutoConfig
	"wmiApSrv",1,						// WMI Performance Adapter
	"WMPNetworkSvc",1,					// Windows Media Player Network Sharing Service
	"WPCSvc",1,							// Parental Controls
	"WPDBusEnum",1,						// Portable Device Enumerator Service
	"wscsvc",2,							// Security Center
	"WSearch",2,						// Windows Search
	"wuauserv",2,						// Windows Update
	"wudfsvc",2,						// Windows Driver Foundation - User-mode Driver Framework	
	};



/////////////////////////////////////////////////////////////
// Default Documentation from : http://www.blackviper.com
static GServiceState GVistaBareMinimum[]=
	{
	"AeLookupSvc",1,					// Application Experience
	"AgereModemAudio",2,				// Agere Modem Call Progress Audio
	"ALG",1,							// Application Layer Gateway Service
	"Appinfo",1,						// Application Information
	"AudioEndpointBuilder",2,			// Windows Audio Endpoint Builder
	"AudioSrv",2,						// Windows Audio
	"BFE",1,							// Base Filtering Engine
	"BITS",2,							// Background Intelligent Transfer Service
	"Browser",2,						// Computer Browser
	"CertPropSvc",1,					// Certificate Propagation
	"clr_optimization_v2.0.50727_32",1,	// Microsoft .NET Framework NGEN v2.0.50727_X86
	"clr_optimization_v2.0.50727_64",1,	// Microsoft .NET Framework NGEN v2.0.50727_X64
	"COMSysApp",1,						// COM+ System Application
	"CryptSvc",2,						// Cryptographic Services
	"DcomLaunch",2,						// DCOM Server Process Launcher
	"DFSR",1,							// DFS Replication
	"Dhcp",2,							// DHCP Client
	"Dnscache",2,						// DNS Client
	"dot3svc",1,						// Wired AutoConfig
	"DPS",1,							// Diagnostic Policy Service
	"EapHost",1,						// Extensible Authentication Protocol
	"ehRecvr",1,						// Windows Media Center Receiver Service
	"ehSched",1,						// Windows Media Center Scheduler Service
	"ehstart",1,						// Windows Media Center Service Launcher
	"EMDMgmt",1,						// ReadyBoost
	"Eventlog",2,						// Windows Event Log
	"EventSystem",2,					// COM+ Event System
	"fdPHost",1,						// Function Discovery Provider Host
	"FDResPub",1,						// Function Discovery Resource Publication
	"FontCache3.0.0.0",1,				// Windows Presentation Foundation Font Cache 3.0.0.0
	"GameConsoleService",1,				// GameConsoleService
	"gpsvc",2,							// Group Policy Client
	"hidserv",1,						// Human Interface Device Access
	"hkmsvc",1,							// Health Key and Certificate Management
	"IAANTMON",1,						// Intel(R) Matrix Storage Event Monitor
	"idsvc",1,							// Windows CardSpace
	"IKEEXT",1,							// IKE and AuthIP IPsec Keying Modules
	"IPBusEnum",1,						// PnP-X IP Bus Enumerator
	"iphlpsvc",1,						// IP Helper
	"KeyIso",1,							// CNG Key Isolation
	"KtmRm",1,							// KtmRm for Distributed Transaction Coordinator
	"LanmanServer",2,					// Server
	"LanmanWorkstation",2,				// Workstation
	"lltdsvc",1,						// Link-Layer Topology Discovery Mapper
	"lmhosts",2,						// TCP/IP NetBIOS Helper
	"Mcx2Svc",1,						// Windows Media Center Extender Service
	"MMCSS",2,							// Multimedia Class Scheduler
	"MpsSvc",1,							// Windows Firewall
	"MSDTC",1,							// Distributed Transaction Coordinator
	"MSiSCSI",1,						// Microsoft iSCSI Initiator Service
	"msiserver",1,						// Windows Installer
	"napagent",1,						// Network Access Protection Agent
	"Netlogon",1,						// Netlogon
	"Netman",1,							// Network Connections
	"netprofm",2,						// Network List Service
	"NetTcpPortSharing",1,				// Net.Tcp Port Sharing Service
	"NlaSvc",2,							// Network Location Awareness
	"nsi",2,							// Network Store Interface Service
	"p2pimsvc",1,						// Peer Networking Identity Manager
	"p2psvc",1,							// Peer Networking Grouping
	"PcaSvc",1,							// Program Compatibility Assistant Service
	"PerfHost",1,						// Performance Counter DLL Host
	"pla",1,							// Performance Logs & Alerts
	"PlugPlay",2,						// Plug and Play
	"PNRPAutoReg",1,					// PNRP Machine Name Publication Service
	"PNRPsvc",1,						// Peer Name Resolution Protocol
	"PolicyAgent",1,					// IPsec Policy Agent
	"ProfSvc",1,						// User Profile Service
	"ProtectedStorage",1,				// Protected Storage
	"QWAVE",1,							// Quality Windows Audio Video Experience
	"RasAuto",1,						// Remote Access Auto Connection Manager
	"RasMan",1,							// Remote Access Connection Manager
	"RemoteAccess",1,					// Routing and Remote Access
	"RemoteRegistry",1,					// Remote Registry
	"RpcLocator",1,						// Remote Procedure Call (RPC) Locator
	"RpcSs",2,							// Remote Procedure Call (RPC)
	"SamSs",2,							// Security Accounts Manager
	"SCardSvr",1,						// Smart Card
	"Schedule",2,						// Task Scheduler
	"SCPolicySvc",1,					// Smart Card Removal Policy
	"SDRSVC",1,							// Windows Backup
	"seclogon",2,						// Secondary Logon
	"SENS",2,							// System Event Notification Service
	"SessionEnv",1,						// Terminal Services Configuration
	"SharedAccess",1,					// Internet Connection Sharing (ICS)
	"ShellHWDetection",1,				// Shell Hardware Detection
	"slsvc",1,							// Software Licensing
	"SLUINotify",1,						// SL UI Notification Service
	"SNMPTRAP",1,						// SNMP Trap
	"Spooler",2,						// Print Spooler
	"SSDPSRV",1,						// SSDP Discovery
	"SstpSvc",1,						// Secure Socket Tunneling Protocol Service
	"stisvc",1,							// Windows Image Acquisition (WIA)
	"swprv",1,							// Microsoft Software Shadow Copy Provider
	"SysMain",2,						// Superfetch
	"TabletInputService",1,				// Tablet PC Input Service
	"TapiSrv",1,						// Telephony
	"TBS",1,							// TPM Base Services
	"TermService",1,					// Terminal Services
	"Themes",1,							// Themes
	"THREADORDER",1,					// Thread Ordering Server
	"TrkWks",1,							// Distributed Link Tracking Client
	"TrustedInstaller",1,				// Windows Modules Installer
	"UI0Detect",1,						// Interactive Services Detection
	"upnphost",1,						// UPnP Device Host
	"UxSms",1,							// Desktop Window Manager Session Manager
	"vds",1,							// Virtual Disk
	"VSS",1,							// Volume Shadow Copy
	"W32Time",1,						// Windows Time
	"wcncsvc",1,						// Windows Connect Now - Config Registrar
	"WcsPlugInService",1,				// Windows Color System
	"WdiServiceHost",1,					// Diagnostic Service Host
	"WdiSystemHost",1,					// Diagnostic System Host
	"WebClient",1,						// WebClient
	"Wecsvc",1,							// Windows Event Collector
	"wercplsupport",1,					// Problem Reports and Solutions Control Panel Support
	"WerSvc",1,							// Windows Error Reporting Service
	"WinDefend",1,						// Windows Defender
	"WinHttpAutoProxySvc",1,			// WinHTTP Web Proxy Auto-Discovery Service
	"Winmgmt",2,						// Windows Management Instrumentation
	"WinRM",1,							// Windows Remote Management (WS-Management)
	"Wlansvc",1,						// WLAN AutoConfig
	"wmiApSrv",1,						// WMI Performance Adapter
	"WMPNetworkSvc",1,					// Windows Media Player Network Sharing Service
	"WPCSvc",1,							// Parental Controls
	"WPDBusEnum",1,						// Portable Device Enumerator Service
	"wscsvc",1,							// Security Center
	"WSearch",1,						// Windows Search
	"wuauserv",1,						// Windows Update
	"wudfsvc",1,						// Windows Driver Foundation - User-mode Driver Framework	
	};


/////////////////////////////////////////////////////////////
// Default Documentation from a freshly installed laptop
static GServiceState GWin7DefaultStart[]=
	{
	"AeLookupSvc",1,					// Application Experience",
	"ALG",1,							// Application Layer Gateway Service
	"AppIDSvc",1,						// Application Identity
	"Appinfo",1,						// Application Information
	"AppMgmt",1,						// Application Management
	"AudioEndpointBuilder",2,			// Windows Audio Endpoint Builder
	"Audiosrv",2,						// Windows Audio
	"AxInstSV",1,						// ActiveX Installer (AxInstSV)
	"BDESVC",1,							// BitLocker Drive Encryption Service
	"BFE",2,							// Base Filtering Engine
	"BITS",2,							// Background Intelligent Transfer Service
	"Browser",1,						// Computer Browser
	"bthserv",1,						// Bluetooth Support Service
	"CertPropSvc",1,					// Certificate Propagation
	"clr_optimization_v2.0.50727_32",1, // Microsoft .NET Framework NGEN v2.0.50727_X86
	"COMSysApp",1,						// COM+ System Application
	"CryptSvc",2,						// Cryptographic Services
	"CscService",2,						// Offline Files
	"DcomLaunch",2,						// DCOM Server Process Launcher
	"defragsvc",1,						// Disk Defragmenter
	"Dhcp",2,							// DHCP Client
	"Dnscache",2,						// DNS Client
	"dot3svc",1,						// Wired AutoConfig
	"DPS",2,							// Diagnostic Policy Service
	"EapHost",1,						// Extensible Authentication Protocol
	"EFS",1,							// Encrypting File System (EFS)
	"ehRecvr",1,						// Windows Media Center Receiver Service
	"ehSched",1,						// Windows Media Center Scheduler Service
	"eventlog",2,						// Windows Event Log
	"EventSystem",2,					// COM+ Event System
	"Fax",1,							// Fax
	"fdPHost",1,						// Function Discovery Provider Host
	"FDResPub",1,						// Function Discovery Resource Publication
	"FontCache",1,						// Windows Font Cache Service
	"FontCache3.0.0.0",1,				// Windows Presentation Foundation Font Cache 3.0.0.0
	"gpsvc",2,							// Group Policy Client
	"hidserv",1,						// Human Interface Device Access
	"hkmsvc",1,							// Health Key and Certificate Management
	"HomeGroupListener",1,				// HomeGroup Listener
	"HomeGroupProvider",1,				// HomeGroup Provider
	"idsvc",1,							// Windows CardSpace
	"IKEEXT",1,							// IKE and AuthIP IPsec Keying Modules
	"IPBusEnum",1,						// PnP-X IP Bus Enumerator
	"iphlpsvc",2,						// IP Helper
	"KeyIso",1,							// CNG Key Isolation
	"KtmRm",1,							// KtmRm for Distributed Transaction Coordinator
	"LanmanServer",2,					// Server
	"LanmanWorkstation",2,				// Workstation
	"lltdsvc",1,						// Link-Layer Topology Discovery Mapper
	"lmhosts",2,						// TCP/IP NetBIOS Helper
	"Mcx2Svc",0,						// Media Center Extender Service
	"MMCSS",2,							// Multimedia Class Scheduler
	"MpsSvc",2,							// Windows Firewall
	"MSDTC",1,							// Distributed Transaction Coordinator
	"MSiSCSI",1,						// Microsoft iSCSI Initiator Service
	"msiserver",1,						// Windows Installer
	"napagent",1,						// Network Access Protection Agent
	"Netlogon",1,						// Netlogon
	"Netman",1,							// Network Connections
	"netprofm",1,						// Network List Service
	"NetTcpPortSharing",0,				// Net.Tcp Port Sharing Service
	"NlaSvc",2,							// Network Location Awareness
	"nsi",2,							// Network Store Interface Service
	"p2pimsvc",1,						// Peer Networking Identity Manager
	"p2psvc",1,							// Peer Networking Grouping
	"PcaSvc",1,							// Program Compatibility Assistant Service
	"PeerDistSvc",1,					// BranchCache
	"pla",1,							// Performance Logs & Alerts
	"PlugPlay",2,						// Plug and Play
	"PNRPAutoReg",1,					// PNRP Machine Name Publication Service
	"PNRPsvc",1,						// Peer Name Resolution Protocol
	"PolicyAgent",1,					// IPsec Policy Agent
	"Power",2,							// Power
	"ProfSvc",2,						// User Profile Service
	"ProtectedStorage",1,				// Protected Storage
	"QWAVE",1,							// Quality Windows Audio Video Experience
	"RasAuto",1,						// Remote Access Auto Connection Manager
	"RasMan",1,							// Remote Access Connection Manager
	"RemoteAccess",0,					// Routing and Remote Access
	"RemoteRegistry",1,					// Remote Registry
	"RpcEptMapper",2,					// RPC Endpoint Mapper
	"RpcLocator",1,						// Remote Procedure Call (RPC) Locator
	"RpcSs",2,							// Remote Procedure Call (RPC)
	"SamSs",2,							// Security Accounts Manager
	"SCardSvr",1,						// Smart Card
	"Schedule",2,						// Task Scheduler
	"SCPolicySvc",1,					// Smart Card Removal Policy
	"SDRSVC",1,							// Windows Backup
	"seclogon",1,						// Secondary Logon
	"SENS",2,							// System Event Notification Service
	"SensrSvc",1,						// Adaptive Brightness
	"SessionEnv",1,						// Remote Desktop Configuration
	"SharedAccess",0,					// Internet Connection Sharing (ICS)
	"ShellHWDetection",2,				// Shell Hardware Detection
	"SNMPTRAP",1,						// SNMP Trap
	"Spooler",2,						// Print Spooler
	"sppsvc",2,							// Software Protection
	"sppuinotify",1,					// SPP Notification Service
	"SSDPSRV",1,						// SSDP Discovery
	"SstpSvc",1,						// Secure Socket Tunneling Protocol Service
	"StiSvc",1,							// Windows Image Acquisition (WIA)
	"StorSvc",1,						// Storage Service
	"swprv",1,							// Microsoft Software Shadow Copy Provider
	"SysMain",2,						// Superfetch
	"TabletInputService",1,				// Tablet PC Input Service
	"TapiSrv",1,						// Telephony
	"TBS",1,							// TPM Base Services
	"TermService",1,					// Remote Desktop Services
	"Themes",2,							// Themes
	"THREADORDER",1,					// Thread Ordering Server
	"TrkWks",2,							// Distributed Link Tracking Client
	"TrustedInstaller",2,				// Windows Modules Installer
	"UI0Detect",1,						// Interactive Services Detection
	"UmRdpService",1,					// Remote Desktop Services UserMode Port Redirector
	"upnphost",1,						// UPnP Device Host
	"UxSms",2,							// Desktop Window Manager Session Manager
	"VaultSvc",1,						// Credential Manager
	"vds",1,							// Virtual Disk
	"VSS",1,							// Volume Shadow Copy
	"W32Time",1,						// Windows Time
	"wbengine",1,						// Block Level Backup Engine Service
	"WbioSrvc",1,						// Windows Biometric Service
	"wcncsvc",1,						// Windows Connect Now - Config Registrar
	"WcsPlugInService",1,				// Windows Color System
	"WdiServiceHost",2,					// Diagnostic Service Host
	"WdiSystemHost",2,					// Diagnostic System Host
	"WebClient",1,						// WebClient
	"Wecsvc",1,							// Windows Event Collector
	"wercplsupport",1,					// Problem Reports and Solutions Control Panel Support
	"WerSvc",1,							// Windows Error Reporting Service
	"WinDefend",2,						// Windows Defender
	"WinHttpAutoProxySvc",1,			// WinHTTP Web Proxy Auto-Discovery Service
	"Winmgmt",2,						// Windows Management Instrumentation
	"WinRM",1,							// Windows Remote Management (WS-Management)
	"Wlansvc",2,						// WLAN AutoConfig
	"wmiApSrv",1,						// WMI Performance Adapter
	"WMPNetworkSvc",1,					// Windows Media Player Network Sharing Service
	"WPCSvc",1,							// Parental Controls
	"WPDBusEnum",1,						// Portable Device Enumerator Service
	"wscsvc",2,							// Security Center
	"WSearch",2,						// Windows Search
	"wuauserv",2,						// Windows Update
	"wudfsvc",2,						// Windows Driver Foundation - User-mode Driver Framework
	"WwanSvc",1							// WWAN AutoConfig
	};


//////////////////////////////////////////////////////////////////
// Default Documentation from : http://www.blackviper.com
static GServiceState GWin7BareMinimum[]=
	{
	"AeLookupSvc",1,					// Application Experience",
	"ALG",1,							// Application Layer Gateway Service
	"AppIDSvc",1,						// Application Identity
	"Appinfo",1,						// Application Information
	"AppMgmt",1,						// Application Management
	"AudioEndpointBuilder",2,			// Windows Audio Endpoint Builder
	"Audiosrv",2,						// Windows Audio
	"AxInstSV",1,						// ActiveX Installer (AxInstSV)
	"BDESVC",1,							// BitLocker Drive Encryption Service
	"BFE",1,							// Base Filtering Engine
	"BITS",1,							// Background Intelligent Transfer Service
	"Browser",1,						// Computer Browser
	"bthserv",1,						// Bluetooth Support Service
	"CertPropSvc",1,					// Certificate Propagation
	"clr_optimization_v2.0.50727_32",1, // Microsoft .NET Framework NGEN v2.0.50727_X86
	"COMSysApp",1,						// COM+ System Application
	"CryptSvc",2,						// Cryptographic Services
	"CscService",1,						// Offline Files
	"DcomLaunch",2,						// DCOM Server Process Launcher
	"defragsvc",1,						// Disk Defragmenter
	"Dhcp",2,							// DHCP Client
	"Dnscache",1,						// DNS Client
	"dot3svc",1,						// Wired AutoConfig
	"DPS",1,							// Diagnostic Policy Service
	"EapHost",1,						// Extensible Authentication Protocol
	"EFS",1,							// Encrypting File System (EFS)
	"ehRecvr",1,						// Windows Media Center Receiver Service
	"ehSched",1,						// Windows Media Center Scheduler Service
	"eventlog",2,						// Windows Event Log
	"EventSystem",2,					// COM+ Event System
	"Fax",1,							// Fax
	"fdPHost",1,						// Function Discovery Provider Host
	"FDResPub",1,						// Function Discovery Resource Publication
	"FontCache",1,						// Windows Font Cache Service
	"FontCache3.0.0.0",1,				// Windows Presentation Foundation Font Cache 3.0.0.0
	"gpsvc",2,							// Group Policy Client
	"hidserv",1,						// Human Interface Device Access
	"hkmsvc",1,							// Health Key and Certificate Management
	"HomeGroupListener",1,				// HomeGroup Listener
	"HomeGroupProvider",1,				// HomeGroup Provider
	"idsvc",1,							// Windows CardSpace
	"IKEEXT",1,							// IKE and AuthIP IPsec Keying Modules
	"IPBusEnum",1,						// PnP-X IP Bus Enumerator
	"iphlpsvc",1,						// IP Helper
	"KeyIso",1,							// CNG Key Isolation
	"KtmRm",1,							// KtmRm for Distributed Transaction Coordinator
	"LanmanServer",2,					// Server
	"LanmanWorkstation",2,				// Workstation
	"lltdsvc",1,						// Link-Layer Topology Discovery Mapper
	"lmhosts",1,						// TCP/IP NetBIOS Helper
	"Mcx2Svc",1,						// Media Center Extender Service
	"MMCSS",2,							// Multimedia Class Scheduler
	"MpsSvc",1,							// Windows Firewall
	"MSDTC",1,							// Distributed Transaction Coordinator
	"MSiSCSI",1,						// Microsoft iSCSI Initiator Service
	"msiserver",1,						// Windows Installer
	"napagent",1,						// Network Access Protection Agent
	"Netlogon",1,						// Netlogon
	"Netman",1,							// Network Connections
	"netprofm",1,						// Network List Service
	"NetTcpPortSharing",1,				// Net.Tcp Port Sharing Service
	"NlaSvc",2,							// Network Location Awareness
	"nsi",2,							// Network Store Interface Service
	"p2pimsvc",1,						// Peer Networking Identity Manager
	"p2psvc",1,							// Peer Networking Grouping
	"PcaSvc",1,							// Program Compatibility Assistant Service
	"PeerDistSvc",1,					// BranchCache
	"pla",1,							// Performance Logs & Alerts
	"PlugPlay",2,						// Plug and Play
	"PNRPAutoReg",1,					// PNRP Machine Name Publication Service
	"PNRPsvc",1,						// Peer Name Resolution Protocol
	"PolicyAgent",1,					// IPsec Policy Agent
	"Power",2,							// Power
	"ProfSvc",2,						// User Profile Service
	"ProtectedStorage",1,				// Protected Storage
	"QWAVE",1,							// Quality Windows Audio Video Experience
	"RasAuto",1,						// Remote Access Auto Connection Manager
	"RasMan",1,							// Remote Access Connection Manager
	"RemoteAccess",0,					// Routing and Remote Access
	"RemoteRegistry",1,					// Remote Registry
	"RpcEptMapper",1,					// RPC Endpoint Mapper
	"RpcLocator",1,						// Remote Procedure Call (RPC) Locator
	"RpcSs",1,							// Remote Procedure Call (RPC)
	"SamSs",2,							// Security Accounts Manager
	"SCardSvr",1,						// Smart Card
	"Schedule",2,						// Task Scheduler
	"SCPolicySvc",1,					// Smart Card Removal Policy
	"SDRSVC",1,							// Windows Backup
	"seclogon",1,						// Secondary Logon
	"SENS",2,							// System Event Notification Service
	"SensrSvc",1,						// Adaptive Brightness
	"SessionEnv",1,						// Remote Desktop Configuration
	"SharedAccess",0,					// Internet Connection Sharing (ICS)
	"ShellHWDetection",2,				// Shell Hardware Detection
	"SNMPTRAP",1,						// SNMP Trap
	"Spooler",2,						// Print Spooler
	"sppsvc",2,							// Software Protection
	"sppuinotify",1,					// SPP Notification Service
	"SSDPSRV",1,						// SSDP Discovery
	"SstpSvc",1,						// Secure Socket Tunneling Protocol Service
	"StiSvc",1,							// Windows Image Acquisition (WIA)
	"StorSvc",1,						// Storage Service
	"swprv",1,							// Microsoft Software Shadow Copy Provider
	"SysMain",2,						// Superfetch
	"TabletInputService",1,				// Tablet PC Input Service
	"TapiSrv",1,						// Telephony
	"TBS",1,							// TPM Base Services
	"TermService",1,					// Remote Desktop Services
	"Themes",1,							// Themes
	"THREADORDER",1,					// Thread Ordering Server
	"TrkWks",1,							// Distributed Link Tracking Client
	"TrustedInstaller",1,				// Windows Modules Installer
	"UI0Detect",1,						// Interactive Services Detection
	"UmRdpService",1,					// Remote Desktop Services UserMode Port Redirector
	"upnphost",1,						// UPnP Device Host
	"UxSms",1,							// Desktop Window Manager Session Manager
	"VaultSvc",1,						// Credential Manager
	"vds",1,							// Virtual Disk
	"VSS",1,							// Volume Shadow Copy
	"W32Time",1,						// Windows Time
	"wbengine",1,						// Block Level Backup Engine Service
	"WbioSrvc",1,						// Windows Biometric Service
	"wcncsvc",1,						// Windows Connect Now - Config Registrar
	"WcsPlugInService",1,				// Windows Color System
	"WdiServiceHost",1,					// Diagnostic Service Host
	"WdiSystemHost",1,					// Diagnostic System Host
	"WebClient",1,						// WebClient
	"Wecsvc",1,							// Windows Event Collector
	"wercplsupport",1,					// Problem Reports and Solutions Control Panel Support
	"WerSvc",1,							// Windows Error Reporting Service
	"WinDefend",1,						// Windows Defender
	"WinHttpAutoProxySvc",1,			// WinHTTP Web Proxy Auto-Discovery Service
	"Winmgmt",2,						// Windows Management Instrumentation
	"WinRM",1,							// Windows Remote Management (WS-Management)
	"Wlansvc",1,						// WLAN AutoConfig
	"wmiApSrv",1,						// WMI Performance Adapter
	"WMPNetworkSvc",1,					// Windows Media Player Network Sharing Service
	"WPCSvc",1,							// Parental Controls
	"WPDBusEnum",1,						// Portable Device Enumerator Service
	"wscsvc",1,							// Security Center
	"WSearch",1,						// Windows Search
	"wuauserv",1,						// Windows Update
	"wudfsvc",1,						// Windows Driver Foundation - User-mode Driver Framework
	"WwanSvc",1							// WWAN AutoConfig
	};


//////////////////////////////////////////////////
static GServiceState GWin10DefaultStart[] =
	{
	"AxInstSV",1,
	"AJRouter",1,
	"AppReadiness",1,
	"AppHostSvc",1,
	"AppIDSvc",1,
	"Appinfo",1,
	"ALG",1,
	"AppMgmt",1,
	"AppXSVC",1,
	"AssignedAccessManagerSvc",1,
	"aspnet_state",1,
	"tzautoupdate",0,
	"BthAvctpSvc",1,
	"BITS",1,
	"BrokerInfrastructure",2,
	"BFE",2,
	"BDESVC",1,
	"wbengine",1,
	"BTAGService",1,
	"bthserv",1,
	"BluetoothUserService_????",1,
	"PeerDistSvc",1,
	"camsvc",1,
	"CaptureService_????",1,
	"CertPropSvc",1,
	"c2wts",1,
	"NfsClnt",0,
	"ClipSVC",1,
	"KeyIso",1,
	"EventSystem",2,
	"COMSysApp",1,
	"Browser",1,
	"CDPSvc",2,
	"CDPUserSvc_????",2,
	"DiagTrack",2,
	"PimIndexMaintenanceSvc_????",1,
	"CoreMessagingRegistrar",2,
	"VaultSvc",1,
	"CryptSvc",2,
	"DsSvc",1,
	"DusmSvc",2,
	"DcomLaunch",2,
	"DoSvc",2,
	"DeviceAssociationService",1,
	"DeviceInstall",1,
	"DmEnrollmentSvc",1,
	"DsmSVC",1,
	"DevicePickerUserSvc_????",1,
	"DevicesFlowUserSvc_????",1,
	"DevQueryBroker",1,
	"Dhcp",2,
	"diagsvc",1,
	"DPS",2,
	"WdiServiceHost",1,
	"WdiSystemHost",1,
	"TrkWks",2,
	"MSDTC",1,
	"dmwappushsvc",1,
	"Dnscache",2,
	"MapsBroker",2,
	"DsRoleSvc",1,
	"embeddedmode",1,
	"EFS",1,
	"EntAppSvc",1,
	"EapHost",1,
	"Fax",1,
	"fhsvc",1,
	"fdPHost",1,
	"FDResPub",1,
	"BcastDVRUserService_????",1,
	"lfsvc",1,
	"GraphicsPerfSvc",1,
	"gpsvc",2,
	"hns",1,
	"hidserv",1,
	"HvHost",1,
	"vmickvpexchange",1,
	"vmicguestinterface",1,
	"vmicshutdown",1,
	"vmicheartbeat",1,
	"vmcompute",1,
	"vmicvmsession",1,
	"vmicrdv",1,
	"vmictimesync",1,
	"vmms",2,
	"vmicvss",1,
	"IISADMIN",2,
	"IKEEXT",1,
	"irmon",1,
	"UI0Detect",1,
	"SharedAccess",1,
	"iphlpsvc",2,
	"IpxlatCfgSvc",1,
	"PolicyAgent",1,
	"KtmRm",1,
	"lltdsvc",1,
	"wlpasvc",1,
	"LSM",2,
	"LPDSVC",2,
	"LxssManager",1,
	"MSMQ",2,
	"MSMQTriggers",2,
	"MessagingService_????",1,
	"diagnosticshub.standardcollector.service",1,
	"wlidsvc",1,
	"AppVClient",0,
	"ftpsvc",1,
	"MSiSCSI",1,
	"MsKeyboardFilter",1,
	"NgcSvc",1,
	"NgcCtnrSvc",1,
	"swprv",1,
	"smphost",1,
	"InstallService",1,
	"SmsRouter",1,
	"WmsRepair",2,
	"Wms",2,
	"NaturalAuthentication",1,
	"NetMsmqActivator",1,
	"NetPipeActivator",1,
	"NetTcpActivator",1,
	"NetTcpPortSharing",1,
	"Netlogon",1,
	"NcdAutoSetup",1,
	"NcbService",1,
	"Netman",1,
	"NcaSVC",1,
	"netprofm",1,
	"NlaSvc",2,
	"NetSetupSvc",1,
	"nsi",2,
	"CscService",1,
	"ssh - agent",1,
	"defragsvc",1,
	"WpcMonSvc",1,
	"SEMgrSvc",1,
	"PNRPsvc",1,
	"p2psvc",1,
	"p2pimsvc",1,
	"PerfHost",1,
	"pla",1,
	"PhoneSvc",1,
	"PlugPlay",1,
	"PNRPAutoReg",1,
	"WPDBusEnum",1,
	"Power",2,
	"Spooler",2,
	"PrintNotify",1,
	"PrintWorkflowUserSvc_????",1,
	"wercplsupport",1,
	"PcaSvc",2,
	"QWAVE",1,
	"RmSvc",1,
	"RasAuto",1,
	"RasMan",1,
	"SessionEnv",1,
	"TermService",1,
	"UmRdpService",1,
	"RpcSs",2,
	"RpcLocator",1,
	"RemoteRegistry",0,
	"RetailDemo",1,
	"iprip",2,
	"RemoteAccess",0,
	"RpcEptMapper",2,
	"seclogon",1,
	"SstpSvc",1,
	"SamSs",2,
	"wscsvc",2,
	"SensorDataService",1,
	"SensrSvc",1,
	"SensorService",1,
	"LanmanServer",2,
	"shpamsvc",0,
	"ShellHWDetection",2,
	"simptcp",1,
	"SCardSvr",0,
	"ScDeviceEnum",1,
	"SCPolicySvc",1,
	"SNMP",1,
	"SNMPTRAP",1,
	"sppsvc",2,
	"SharedRealitySvc",1,
	"svsvc",1,
	"SSDPSRV",1,
	"StateRepository",1,
	"WiaRpc",1,
	"StorSvc",1,
	"TieringEngineService",1,
	"SysMain",2,
	"OneSyncSvc_????",2,
	"SENS",2,
	"SystemEventsBroker",2,
	"SgrmBroker",2,
	"Schedule",2,
	"lmhosts",1,
	"TapiSrv",1,
	"Themes",2,
	"TimeBroker",1,
	"TabletInputService",1,
	"UwfServcingSvc",1,
	"UsoSvc",1,
	"upnphost",1,
	"UserDataSvc_????",1,
	"UnistoreSvc_????",1,
	"UevAgentService",0,
	"UserManager",2,
	"ProfSvc",2,
	"vds",1,
	"VSS",1,
	"W3LOGSVC",1,
	"WalletService",1,
	"WMSVC",1,
	"TokenBroker",1,
	"WebClient",1,
	"WFDSConSvc",1,
	"AudioSrv",2,
	"AudioEndpointBuilder",2,
	"SDRSVC",1,
	"WbioSrvc",1,
	"FrameServer",1,
	"wcncsvc",1,
	"Wcmsvc",2,
	"Sense",1,
	"WdNisSvc",1,
	"WinDefend",2,
	"MpsSvc",2,
	"SecurityHealthService",2,
	"WEPHOSTSVC",1,
	"WerSvc",1,
	"Wecsvc",1,
	"EventLog",2,
	"FontCache",2,
	"StiSvc",1,
	"wisvc",1,
	"msiserver",1,
	"LicenseManager",1,
	"Winmgmt",2,
	"WMPNetworkSvc",1,
	"icssvc",1,
	"TrustedInstaller",1,
	"spectrum",1,
	"FontCache3.0.0.0",1,
	"WAS",1,
	"WpnService",2,
	"WpnUserService_????",2,
	"PushToInstall",1,
	"WinRM",1,
	"WSearch",2,
	"W32Time",1,
	"wuauserv",1,
	"WaaSMedicSvc",1,
	"WinHttpAutoProxySvc",1,
	"dot3svc",1,
	"WlanSvc",2,
	"wmiApSrv",1,
	"workfolderssvc",1,
	"LanmanWorkstation",2,
	"W3SVC",2,
	"WwanSvc",1,
	"XboxGipSvc",1,
	"xbgm",1,
	"XblAuthManager",1,
	"XblGameSave",1,
	"XboxNetApiSvc",1,
	};



//////////////////////////////////////////////////
static GServiceState GWin10BareMinimum[] =
	{
	"AxInstSV",1,
	"AJRouter",1,
	"AppReadiness",1,
	"AppHostSvc",1,
	"AppIDSvc",1,
	"Appinfo",1,
	"ALG",1,
	"AppMgmt",1,
	"AppXSVC",1,
	"AssignedAccessManagerSvc",1,
	"aspnet_state",1,
	"tzautoupdate",0,
	"BthAvctpSvc",1,
	"BITS",1,
	"BrokerInfrastructure",2,
	"BFE",2,
	"BDESVC",1,
	"wbengine",1,
	"BTAGService",1,
	"bthserv",1,
	"BluetoothUserService_????",1,
	"PeerDistSvc",1,
	"camsvc",1,
	"CaptureService_????",1,
	"CertPropSvc",1,
	"c2wts",1,
	"NfsClnt",0,
	"ClipSVC",1,
	"KeyIso",1,
	"EventSystem",2,
	"COMSysApp",1,
	"Browser",1,
	"CDPSvc",2,
	"CDPUserSvc_????",2,
	"DiagTrack",2,
	"PimIndexMaintenanceSvc_????",1,
	"CoreMessagingRegistrar",2,
	"VaultSvc",1,
	"CryptSvc",2,
	"DsSvc",1,
	"DusmSvc",2,
	"DcomLaunch",2,
	"DoSvc",2,
	"DeviceAssociationService",1,
	"DeviceInstall",1,
	"DmEnrollmentSvc",1,
	"DsmSVC",1,
	"DevicePickerUserSvc_????",1,
	"DevicesFlowUserSvc_????",1,
	"DevQueryBroker",1,
	"Dhcp",2,
	"diagsvc",1,
	"DPS",2,
	"WdiServiceHost",1,
	"WdiSystemHost",1,
	"TrkWks",2,
	"MSDTC",1,
	"dmwappushsvc",1,
	"Dnscache",2,
	"MapsBroker",2,
	"DsRoleSvc",1,
	"embeddedmode",1,
	"EFS",1,
	"EntAppSvc",1,
	"EapHost",1,
	"Fax",1,
	"fhsvc",1,
	"fdPHost",1,
	"FDResPub",1,
	"BcastDVRUserService_????",1,
	"lfsvc",1,
	"GraphicsPerfSvc",1,
	"gpsvc",2,
	"hns",1,
	"hidserv",1,
	"HvHost",1,
	"vmickvpexchange",1,
	"vmicguestinterface",1,
	"vmicshutdown",1,
	"vmicheartbeat",1,
	"vmcompute",1,
	"vmicvmsession",1,
	"vmicrdv",1,
	"vmictimesync",1,
	"vmms",2,
	"vmicvss",1,
	"IISADMIN",2,
	"IKEEXT",1,
	"irmon",1,
	"UI0Detect",1,
	"SharedAccess",1,
	"iphlpsvc",2,
	"IpxlatCfgSvc",1,
	"PolicyAgent",1,
	"KtmRm",1,
	"lltdsvc",1,
	"wlpasvc",1,
	"LSM",2,
	"LPDSVC",2,
	"LxssManager",1,
	"MSMQ",2,
	"MSMQTriggers",2,
	"MessagingService_????",1,
	"diagnosticshub.standardcollector.service",1,
	"wlidsvc",1,
	"AppVClient",0,
	"ftpsvc",1,
	"MSiSCSI",1,
	"MsKeyboardFilter",1,
	"NgcSvc",1,
	"NgcCtnrSvc",1,
	"swprv",1,
	"smphost",1,
	"InstallService",1,
	"SmsRouter",1,
	"WmsRepair",2,
	"Wms",2,
	"NaturalAuthentication",1,
	"NetMsmqActivator",1,
	"NetPipeActivator",1,
	"NetTcpActivator",1,
	"NetTcpPortSharing",1,
	"Netlogon",1,
	"NcdAutoSetup",1,
	"NcbService",1,
	"Netman",1,
	"NcaSVC",1,
	"netprofm",1,
	"NlaSvc",2,
	"NetSetupSvc",1,
	"nsi",2,
	"CscService",1,
	"ssh - agent",1,
	"defragsvc",1,
	"WpcMonSvc",1,
	"SEMgrSvc",1,
	"PNRPsvc",1,
	"p2psvc",1,
	"p2pimsvc",1,
	"PerfHost",1,
	"pla",1,
	"PhoneSvc",1,
	"PlugPlay",1,
	"PNRPAutoReg",1,
	"WPDBusEnum",1,
	"Power",2,
	"Spooler",2,
	"PrintNotify",1,
	"PrintWorkflowUserSvc_????",1,
	"wercplsupport",1,
	"PcaSvc",2,
	"QWAVE",1,
	"RmSvc",1,
	"RasAuto",1,
	"RasMan",1,
	"SessionEnv",1,
	"TermService",1,
	"UmRdpService",1,
	"RpcSs",2,
	"RpcLocator",1,
	"RemoteRegistry",0,
	"RetailDemo",1,
	"iprip",2,
	"RemoteAccess",0,
	"RpcEptMapper",2,
	"seclogon",1,
	"SstpSvc",1,
	"SamSs",2,
	"wscsvc",2,
	"SensorDataService",1,
	"SensrSvc",1,
	"SensorService",1,
	"LanmanServer",2,
	"shpamsvc",0,
	"ShellHWDetection",2,
	"simptcp",1,
	"SCardSvr",0,
	"ScDeviceEnum",1,
	"SCPolicySvc",1,
	"SNMP",1,
	"SNMPTRAP",1,
	"sppsvc",2,
	"SharedRealitySvc",1,
	"svsvc",1,
	"SSDPSRV",1,
	"StateRepository",1,
	"WiaRpc",1,
	"StorSvc",1,
	"TieringEngineService",1,
	"SysMain",2,
	"OneSyncSvc_????",2,
	"SENS",2,
	"SystemEventsBroker",2,
	"SgrmBroker",2,
	"Schedule",2,
	"lmhosts",1,
	"TapiSrv",1,
	"Themes",2,
	"TimeBroker",1,
	"TabletInputService",1,
	"UwfServcingSvc",1,
	"UsoSvc",1,
	"upnphost",1,
	"UserDataSvc_????",1,
	"UnistoreSvc_????",1,
	"UevAgentService",0,
	"UserManager",2,
	"ProfSvc",2,
	"vds",1,
	"VSS",1,
	"W3LOGSVC",1,
	"WalletService",1,
	"WMSVC",1,
	"TokenBroker",1,
	"WebClient",1,
	"WFDSConSvc",1,
	"AudioSrv",2,
	"AudioEndpointBuilder",2,
	"SDRSVC",1,
	"WbioSrvc",1,
	"FrameServer",1,
	"wcncsvc",1,
	"Wcmsvc",2,
	"Sense",1,
	"WdNisSvc",1,
	"WinDefend",2,
	"MpsSvc",2,
	"SecurityHealthService",2,
	"WEPHOSTSVC",1,
	"WerSvc",1,
	"Wecsvc",1,
	"EventLog",2,
	"FontCache",2,
	"StiSvc",1,
	"wisvc",1,
	"msiserver",1,
	"LicenseManager",1,
	"Winmgmt",2,
	"WMPNetworkSvc",1,
	"icssvc",1,
	"TrustedInstaller",1,
	"spectrum",1,
	"FontCache3.0.0.0",1,
	"WAS",1,
	"WpnService",2,
	"WpnUserService_????",2,
	"PushToInstall",1,
	"WinRM",1,
	"WSearch",2,
	"W32Time",1,
	"wuauserv",1,
	"WaaSMedicSvc",1,
	"WinHttpAutoProxySvc",1,
	"dot3svc",1,
	"WlanSvc",2,
	"wmiApSrv",1,
	"workfolderssvc",1,
	"LanmanWorkstation",2,
	"W3SVC",2,
	"WwanSvc",1,
	"XboxGipSvc",1,
	"xbgm",1,
	"XblAuthManager",1,
	"XblGameSave",1,
	"XboxNetApiSvc",1,
	};




//******************************************************
//**  MWinServiceInfo class
//******************************************************
void MWinServiceInfo::ClearObject(void)
	{
	mCount=0;
	mList=NULL;
	}


////////////////////////////////////////////////
MWinServiceInfo::MWinServiceInfo(void)
	{  ClearObject();  }


////////////////////////////////////////////////
MWinServiceInfo::~MWinServiceInfo(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MWinServiceInfo::Create(bool minservices)
	{
	Destroy();

	MMachineInfo machine;
	if(machine.Create()==false)
		{
		Destroy();  return false;
		}

	// Get Machine Version
	int majorversion=machine.GetMajorVersion();
	int minorversion=machine.GetMinorVersion();

	if(majorversion==5 && minorversion==0)
		{
		//=We have an Win2000 machine
		if(minservices==true)
			{
			mList=GWin2000BareMinimum;
			mCount=sizeof(GWin2000BareMinimum)/sizeof(GServiceState);	
			}
		else
			{
			mList=GWin2000DefaultStart;
			mCount=sizeof(GWin2000DefaultStart)/sizeof(GServiceState);
			}
		}
	else if(majorversion==5 && minorversion==1)
		{
		//=We have an XP Machine
		if(minservices==true)
			{
			mList=GXPBareMinimum;
			mCount=sizeof(GXPBareMinimum)/sizeof(GServiceState);
			}
		else
			{
			mList=GXPDefaultStart;
			mCount=sizeof(GXPDefaultStart)/sizeof(GServiceState);
			}
		}
	else if(majorversion==6 && minorversion==0)
		{
		//=We have a Vista Machine
		if(minservices==true)
			{
			mList=GVistaBareMinimum;
			mCount=sizeof(GVistaBareMinimum)/sizeof(GServiceState);	
			}
		else
			{
			mList=GVistaDefaultStart;
			mCount=sizeof(GVistaDefaultStart)/sizeof(GServiceState);
			}
		}
	else if(majorversion==6 && minorversion==1)
		{
		//=We have an Windows 7
		if(minservices==true)
			{
			mList=GWin7BareMinimum;
			mCount=sizeof(GWin7BareMinimum)/sizeof(GServiceState);	
			}
		else
			{
			mList=GWin7DefaultStart;
			mCount=sizeof(GWin7DefaultStart)/sizeof(GServiceState);
			}
		}
	else if(majorversion==6 && minorversion==2)
		{
		//=We have an Windows 10 or above
		if(minservices==true)
			{
			mList=GWin10BareMinimum;
			mCount=sizeof(GWin10BareMinimum)/sizeof(GServiceState);	
			}
		else
			{
			mList=GWin10DefaultStart;
			mCount=sizeof(GWin10DefaultStart)/sizeof(GServiceState);
			}
		}
	else
		{
		Destroy();
		return false;
		}

	return true;
	}


////////////////////////////////////////////////
bool MWinServiceInfo::Destroy(void)
	{
	ClearObject();
	return true;
	}


////////////////////////////////////////////////
int MWinServiceInfo::GetCount(void)		// Count of Services in Default
	{  return mCount;  }


////////////////////////////////////////////////
const char *MWinServiceInfo::GetServiceName(int index)		// Get Service Name
	{
	if(index<0 || index>=mCount)
		{
		return NULL;
		}

	return mList[index].Service;
	}


////////////////////////////////////////////////
int MWinServiceInfo::GetStartState(int index)				// Get Start State
	{
	if(index<0 || index>=mCount)
		{
		return -1;
		}

	return mList[index].StartState;
	}


