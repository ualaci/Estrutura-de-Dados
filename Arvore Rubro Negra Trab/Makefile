
SYSTEM  = x86-64_linux
LIBFORMAT = static_pic

OPTIONS = -O3
COMP = g++ -c


# ---------------------------------------------------------------------
# Compiler selection
# ---------------------------------------------------------------------
CCC = gcc
SRCDIR =
OBJDIR = obj

OBJ_PRJ =

CCFLAGS = $(CCOPT)

OBJ_LIB =

Projeto :  $(OBJ_PRJ) $(OBJ_LIB)
	$(CCC) $(CCFLAGS) -o programa.exe main.c ARN.c $(OBJ_PRJ) $(OBJ_LIB)

clean:
	rm -f *.o
	rm -f *~
	rm Projeto
