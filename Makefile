CC:=gcc
CFLAGS:=-Wall
.PHONY:=all clean
INCLUDE:=./mosaic/src
LINK_DIRS:=./mosaic/
LINK:=mosaic


all: libeaux.a test mosaic


libeaux.a: eaux.o mosaic/libmosaic.a
	ar rcs libeaux.a eaux.o mosaic/libmosaic.a 

mosaic/libmosaic.a:
	$(MAKE) -C mosaic/

eaux.o: src/eaux.c src/eaux.h mosaic
	${CC} ${CFLAGS} -I${INCLUDE} -c src/eaux.c -o eaux.o

clean:
	-- 	rm *.o
	--	rm libeaux.a
	--	rm test
	$(MAKE) -C mosaic/ clean

test: libeaux.a src/test.c mosaic
	${CC} ${CFLAGS} -I${INCLUDE} src/test.c -o test -L. -leaux -L./mosaic -lmosaic -lm


