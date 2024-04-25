##########################

INCDIR    = bloom_filter
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
	@$(COMPILER) bloom_filter/bloom_filter.cpp main.cpp $(PREFLAGS) -o $(TARGDIR)/main


clean:
	@echo target files:
	-rm -f $(TARGDIR)/*


makedirs:
	@-mkdir -p $(TARGDIR)

