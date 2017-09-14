#Plataforma alvo para a compilacao, apenas influencia extensao do arquivo final (unix/win32)
TARGET := unix

MAINF := test.cxx

AUXF := pmatrix.cxx sirs.cxx

SOURCES := $(MAINF) $(AUXF)

OBJS := $(SOURCES:.cxx=.o)

#Extensao do executavel final
EXT =
ifeq ($(TARGET),win32)
	EXT = .exe
endif

EXEC = $(MAINF:.cxx=$(EXT))

#Flags para o compilador/linker
CXXFLAGS = -O3
LDFLAGS =

%.o : %.cxx
	$(CXX) $(CXXFLAGS) -c $^

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $(EXEC)



.PHONY: clean
clean:
	rm -rf $(OBJS) $(EXEC)
