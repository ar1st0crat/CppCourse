CXX = g++
CXXFLAGS = -std=c++14 -Wall

SRCS = $(wildcard Controller/*.cpp Controller/Rules/*.cpp Controller/Rules/Misc/*.cpp Controller/GameStates/*.cpp Model/*.cpp View/*.cpp)

all:
	$(CXX) $(CXXFLAGS) main.cpp $(SRCS) -o ../bin/blackjack
