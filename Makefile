
SRC_DIR = src

LIBS = 	-L third_party/lib/linux_x86 \
		-l SDL3 \
		-l GL \
		-l imgui

INCLUDE = 	-I include \
			-I third_party/include \
			-I /home/sulicat/git/sulicat/include/ \
			-I third_party/include/imgui \

SRC = 	$(wildcard $(SRC_DIR)/*.cpp ) \
		/home/sulicat/git/sulicat/src/sync_vector.cpp \
		/home/sulicat/git/sulicat/src/file_utils.cpp \
		/home/sulicat/git/sulicat/src/general_utils.cpp \
		/home/sulicat/git/sulicat/src/term.cpp

all:
	mkdir -p bin
	g++ ${SRC} -g -o bin/hiccup ${LIBS} ${INCLUDE}