#v1.0 copyright Comine.com 20060901F06
# Simple Make file for nmake
#  -Revised to exclude extra search libraries

OUTPUT=MServices.exe
LIBS=
CC=cl.exe
CLINKER=link.exe
BASELIBS=
#Set -O2 (optimize for speed) there seems to be a bug in default optimization
FLAGS=-nologo -DWIN32 -O2 -DNDEBUG -MT
CFLAGS=
CLINKFLAGS=

########### Main.exe ##############
all : $(OUTPUT)
	@banner "Finished creating $(OUTPUT)"


############ Compile Object Files ################
.cpp.obj:
	$(CC) -c $(CFLAGS)  $(FLAGS) $**
	cp setargv.vc8  setargv.obj


############ Compile Object Files ################
.c.obj:
	$(CC) -c $(CFLAGS)  $(FLAGS) $**
	cp setargv.vc8  setargv.obj



############ Link Object Files  ##################
$(OUTPUT) : *.obj 
	$(CLINKER) $(CLINKFLAGS)  $**  $(LIBS)  $(BASELIBS)  -OUT:$@


############# Clean ###############
clean : 
	-rm -f *.obj /q
	

############ Clean All Exe+Objs #######
cleanall:
	-rm -f *.obj 
	-rm -f *.tli
	-rm -f *.tlh
	-rm -f $(OUTPUT)


