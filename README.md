# MServices
Enables/Disables/Starts/Stops Windows Services.  Program sets default and minimal services, including older windows such as 2000/XP/Vista/...

usage:	MServices [options] [-?] 
	v1.6 copyright Comine.com

	Controls and displays Windows Services.  

options: Use the short name of a service for identity

            -s <name>+                 : Start Services
            
            -x <name>+                 : Stop Service 
            
            -p <name>+                 : Pause Service 
            
            -c <name>+                 : Continue Service 
            
            -a <name>+                 : Set Service to auto start
            
            -m <name>+                 : Set Service to manual Start
            
            -d <name>+                 : Set Service to disabled
            
            -i <name>+                 : Info Status of services
            
            -ir                        : Info on Running Services
            
            -is                        : Info on Stopped Services
            
            -ip                        : Info on Paused Services
            
            -l                         : Service Path Location
            
            -1                         : Start All Services
            
            -2                         : Start all services marked auto
            
            -3                         : Set Services to OS Original start
            
            -4                         : Set all services to auto start
            
            -5                         : Set all services to manual start
            
            -6                         : Set Services to OS Minimal start


