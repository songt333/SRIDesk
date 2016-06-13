
CFLAG+=$(shell pkg-config --cflags cairo)
LIBS+=$(shell pkg-config --libs cairo)

all:	xt.c
	gcc xt.c -lX11 -lXtst -o xt $(CFLAG) $(LIBS)

