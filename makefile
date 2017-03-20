CXX  = clang
FLGS = -Wall -Werror -std=c11
PRGM = hack

all:
	$(CXX) $(FLGS) source/hack.c source/logging.c source/fileio.c -o $(PRGM)

clean:
	rm $(PRGM)
