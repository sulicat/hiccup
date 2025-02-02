
LIBS = 	-L third_party/lib/linux_x86 \
		-l SDL3 \
		-l GL \
		-l imgui

INCLUDE = 	-I include \
			-I third_party/include \
			-I /home/sulicat/git/sulicat/sulicat/ \
			-I third_party/include/imgui \

SRC = 	src/main.cpp \
		src/parser.cpp \
		src/gui.cpp

all:
	mkdir -p bin
	g++ ${SRC} -o bin/hiccup ${LIBS} ${INCLUDE}