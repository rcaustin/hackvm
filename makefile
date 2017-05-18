CXX  = clang
FLGS = -Wall -Werror -std=c11
PRGM = hackvm
HASM = assembler

hack: source/logging.o source/fileio.o
	$(CXX) $(FLGS) source/hack.c source/logging.o source/fileio.o -o $(PRGM)

assembler: source/logging.o source/utility.o source/fileio.o
	$(CXX) $(FLGS) source/assembler.c source/logging.c source/utility.c source/fileio.c -o $(HASM)

clean:
	rm -f $(PRGM) $(HASM) source/*.o
