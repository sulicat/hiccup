
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
		/home/sulicat/git/sulicat/src/file_utils.cpp

all:
	mkdir -p bin
	g++ ${SRC} -o bin/hiccup ${LIBS} ${INCLUDE}