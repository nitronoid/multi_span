################################################################################
#                                                                              #
# This file is a basic unix makefile which runs all the multi_span tests.      #
# Prefer to use the bazel build setup.                                         #
# Usage:  make -f unix_makefile.mk                                             #
#                                                                              #
################################################################################

EXE_NAME = tests

SRC_DIR = src
OBJ_DIR = obj

SRC_FILES = $(wildcard ${SRC_DIR}/*.cpp)
OBJ_FILES = $(patsubst ${SRC_DIR}/%.cpp, ${OBJ_DIR}/%.o,${SRC_FILES})

INCLUDES += -I../include
INCLUDES += -ICatch2/single_include

CXXFLAGS += -g -std=c++14 -O3 -DMULTI_SPAN_THROW_ON_CONTRACT_VIOLATION
CXXFLAGS += -Wall -Wextra -pedantic -Wno-array-bounds

LDFLAGS += -g -DMULTI_SPAN_THROW_ON_CONTRACT_VIOLATION

.PHONY: directories

all: directories ${EXE_NAME}

directories: ${OBJ_DIR}

$(OBJ_DIR):
	mkdir -p ${OBJ_DIR}

$(EXE_NAME): ${OBJ_FILES}
	${CXX} ${LDFLAGS} -o $@ $^

$(OBJ_DIR)/%.o: ${SRC_DIR}/%.cpp
	${CXX} ${CXXFLAGS} ${INCLUDES} -c -o $@ $<

clean:
	rm -rf ${EXE_NAME} ${OBJ_DIR}/*.o

