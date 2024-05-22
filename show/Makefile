export INCLUDE_PATH
CXXFLAGS = -I$(INCLUDE_PATH) -O2 --std=c++2a -Wall -lstdc++fs

all: judger chk communicator

% : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
