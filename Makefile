CC = gcc
CFLAGS = -Wall -Werror
CPPFLAGS = -MMD
SrcDir = src
BinDir = bin
ObjDir = obj
	
MainSrc = $(wildcard $(SrcDir)/geometry/*.c)
LibSrc = $(wildcard $(SrcDir)/libgeometry/*.c)

LibTarget = $(ObjDir)/libgeometry/libgeometry.a
Target = $(BinDir)/main

all: $(Target)

$(Target): $(ObjDir)/geometry/main.o $(LibTarget)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(LibTarget): $(ObjDir)/libgeometry/circle.o
	ar rcs $@ $^

$(ObjDir)/geometry/main.o: $(MainSrc)
	$(CC) -c $(CFLAGS) $< $(CPPFLAGS) -o $@ -I $(SrcDir)/libgeometry/  

$(ObjDir)/libgeometry/circle.o: $(LibSrc)
	$(CC) -c $(CFLAGS) $< $(CPPFLAGS) -o $@ -I $(SrcDir)/libgeometry

.PHONY: clean

run:
	./$(Target)

clean:
	rm -rf $(ObjDir)/libgeometry/*.o $(ObjDir)/geometry/*.o $(Target)
	rm -rf $(ObjDir)/libgeometry/*.d $(ObjDir)/geometry/*.d
	rm -rf $(LibTarget)
-include $(ObjDir)/geometry/%.d $(ObjDir)/libgeometry/%.d