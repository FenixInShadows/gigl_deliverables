all: translate  compile

translate: hello_world.xc
	java -Xss6M -jar ../../../ableC.jar hello_world.xc --show-lifted-pp > hello_world.generated.h

compile: hello_world.generated.h  main.cpp
	g++ -std=c++11 -O3 -I../../../include/ *.cpp ../../../include/common/*.cpp -o hello_world.exe

clean:
	rm -f *.i *.o *.exe *.out *.generated.h
