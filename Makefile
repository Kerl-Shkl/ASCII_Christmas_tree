#linker flags
LDFLAGS := -lncurses

#used compiler
CC 		:= gcc

#object files path
OBJPATH := obj

#source path
SRCPATH := source

#header path
HPATH 	:= header

#binary path
BINPATH := bin

#binary name
BINNAME := Tree

#build project and documentation
run: build
	./$(BINPATH)/$(BINNAME)

#build project only
build: $(BINPATH)/$(BINNAME)

clean:
	-rm -rf $(OBJPATH)/*
	-rm -rf $(BINPATH)/*

#Collect files
_CFILES := $(wildcard $(SRCPATH)/*.c)
_HFILES := $(wildcard $(HPATH)/*.h) 
_OFILES := $(patsubst $(SRCPATH)/%.c, $(OBJPATH)/%.o, $(_CFILES))

$(OBJPATH)/%.o: $(SRCPATH)/%.c
	mkdir -p $(OBJPATH)
	$(CC) -c $< -o $@ 

$(BINPATH)/$(BINNAME): $(_OFILES)
	mkdir -p $(BINPATH)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: all clean build
