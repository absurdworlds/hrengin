ifdef HR_C_COMPILER
 CC = $(HR_C_COMPILER)
else
 CC = cc -std=c99
endif

ifdef HR_CXX_COMPILER
 CXX = $(HR_CXX_COMPILER)
else
 CXX = g++ -std=c++11 
endif

CompilerFlags  = -g -D_DEBUG
CompilerFlags += -fPIC
CompilerFlags += -fvisibility=hidden

#InstallDir = ../../bin
InstallDir = /usr/local/bin

CPPFLAGS = $(Defines) $(Includes)
CXXFLAGS = $(CompilerFlags)
LDFLAGS = $(Libraries)

example: $(Objects)
	$(CXX) $(Objects) $(CPPFLAGS) $(CXXFLAGS) -o $(ExecutableName) $(LDFLAGS)
	cp -f $(ExecutableName) ../../bin
	
all: example 

install:
	install $(ExecutableName) $(InstallDir)


.PHONY : clean
clean:
	-rm $(ExecutableName) $(Objects)
