CC=g++
DEPS = circuit.hpp ui.hpp ui_graphics.hpp ui_math.hpp graph.hpp
CFLAGS=-std=c++17 -Wall

ODIR=obj

_OBJ = circuit.o ui.o ui_graphics.o ui_math.o graph.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: kirchhoff 

$(ODIR)/%.o: %.cpp $(DEPS)
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

kirchhoff: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -rf obj