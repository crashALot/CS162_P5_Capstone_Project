#target: dependencies
#	rule to build

# Work cited: https://askubuntu.com/questions/433943/how-to-clean-executable-using-make-clean
# 	      https://www.cs.bu.edu/teaching/cpp/writing-makefiles/

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -g
CXXFLAGS += -Wall 
#CXXFLAGS += -O3
#CXXFLAGS += -pedantic-errors
#LDFLAGS = -lboost_date_time
OBJS = aGuy.o createRooms.o fightSpace.o itemSpace.o mainSpace.o menuNarration.o menuValidate.o space.o spaceMenu.o startSpace.o warpSpace.o
SRCS = aGuy.cpp createRooms.cpp fightSpace.cpp itemSpace.cpp mainSpace.cpp menuNarration.cpp menuValidate.cpp space.cpp spaceMenu.cpp startSpace.cpp warpSpace.cpp
HEADERS = aGuy.hpp createRooms.hpp fightSpace.hpp itemSpace.hpp menuNarration.hpp menuValidate.hpp space.hpp spaceMenu.hpp startSpace.hpp warpSpace.hpp
runForYourLife: ${OBJS}
	${CXX} ${CXXFLAGS} -o runForYourLife aGuy.o createRooms.o fightSpace.o itemSpace.o mainSpace.o menuNarration.o menuValidate.o space.o spaceMenu.o startSpace.o warpSpace.o
mainSpace.o: mainSpace.cpp ${HEADERS}
	${CXX} ${CXXFLAGS} -c aGuy.cpp createRooms.cpp fightSpace.cpp itemSpace.cpp mainSpace.cpp menuNarration.cpp menuValidate.cpp space.cpp spaceMenu.cpp startSpace.cpp warpSpace.cpp

clean: ${OBJS}
	-rm *.o ${OBJS} runForYourLife
