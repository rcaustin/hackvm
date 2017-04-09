CXX  = clang
FLGS = -Wall -Werror -std=c11
PRGM = hackvm
HASM = assembler

hack:
	$(CXX) $(FLGS) source/hack.c source/logging.c source/fileio.c -o $(PRGM)

assembler:
	$(CXX) $(FLGS) source/assembler.c source/logging.c source/fileio.c -o $(HASM)

clean:
	rm $(PRGM) $(HASM)
