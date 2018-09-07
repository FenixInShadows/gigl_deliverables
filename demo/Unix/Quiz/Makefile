all: translate  compile

translate: quiz.xc
	java -Xss6M -jar ../../../ableC.jar quiz.xc --show-lifted-pp > quiz.generated.h

compile: quiz.generated.h  main.cpp
	g++ -std=c++11 -O3 -I../../../include/ *.cpp ../../../include/common/*.cpp -o quiz.exe

clean:
	rm -f *.i *.o *.exe *.out *.generated.h
