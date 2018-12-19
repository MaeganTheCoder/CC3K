CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -g -D DEBUG
EXEC = cc3k 
SRC = ${shell find . -name '*.cc'}
OBJ = ${SRC:.cc=.o}
DEPENDS = ${OBJ:.o=.d}

${EXEC}: ${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJ} ${EXEC} ${DEPENDS}

.PHONY: g

g: ${EXEC}
	./${EXEC} 2> log.txt
