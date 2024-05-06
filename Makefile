##########################

INCDIR    = src
TARGDIR	  = bin
COMPILER  = g++

# Using C++ 2017 standard:
PREFLAGS  = -std=c++17

# PREFLAGS  += -c -g -Wall -O3


##############################
##
## Targets:
##

# targets which don't actually refer to files
.PHONY : all clean makedirs


all: makedirs
	@echo [CC] $@
	@$(COMPILER) example/example.cpp $(PREFLAGS) -o $(TARGDIR)/example


clean:
	@echo target files:
	-rm -f $(TARGDIR)/*
	-rm -rf $(TARGDIR)


makedirs:
	@-mkdir -p $(TARGDIR)

