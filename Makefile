CSOURCES = src/model/aiger.c

CPPSOURCES = src/check/BackwardChecker.cpp src/model/AigerModel.cpp src/model/CarSolver.cpp src/model/MainSolver.cpp src/model/InvSolver.cpp src/model/State.cpp src/main.cpp src/model/OverSequence.cpp src/model/Log.cpp\
	src/sat/minisat/core/Solver.cc src/sat/minisat/utils/Options.cc src/sat/minisat/utils/System.cc
#CSOURCES = aiger.c picosat/picosat.c
#CPPSOURCES = bfschecker.cpp checker.cpp carsolver.cpp mainsolver.cpp model.cpp utility.cpp data_structure.cpp main.cpp \
	glucose/core/Solver.cc glucose/utils/Options.cc glucose/utils/System.cc

OBJS = BackwardChecker.o AigerModel.o CarSolver.o State.o main.o aiger.o MainSolver.o InvSolver.o OverSequence.o Log.o\
	Solver.o Options.o System.o 

CFLAG = -I../ -I./src/sat/minisat -I./src/model -I./src/check -I./src/sat/minisat/core -D__STDC_LIMIT_MACROS -D __STDC_FORMAT_MACROS -c -g -fpermissive 
#CFLAG = -I../ -I./glucose -D__STDC_LIMIT_MACROS -D __STDC_FORMAT_MACROS -c -g 

LFLAG = -g -lz -lpthread 

GCC = gcc

GXX = g++

simplecar: $(CSOURCES) $(CPPSOURCES)
	$(GCC) $(CFLAG) $(CSOURCES)
	$(GCC) $(CFLAG) -std=c++11 $(CPPSOURCES)
	$(GXX) -o simplecar $(OBJS) $(LFLAG)
	rm *.o

.PHONY: simplecar

clean: 
	
	rm simplecar
	

