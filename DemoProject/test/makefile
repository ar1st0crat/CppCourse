CXX = g++
CXXFLAGS = -std=c++14 -Wall -lgtest -lgmock -lgtest_main -lgmock_main -lpthread

SUT_SRC = $(wildcard ../src/Controller/*.cpp ../src/Controller/Rules/*.cpp ../src/Controller/GameStates/*.cpp ../src/Model/*.cpp ../src/View/*.cpp)
TEST_SRC = $(wildcard *.cpp)

all:
	$(CXX) $(TEST_SRC) $(CXXFLAGS) $(SUT_SRC) -o runtests
