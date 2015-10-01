CC = g++
CFLAGS = -Wall
PROG = carrom

SRCS = main.cpp Board.cpp disc.cpp Powermeter.cpp Scoreboard.cpp
LIBS = -lglut -lGL -lGLU

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
