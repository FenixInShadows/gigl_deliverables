all: translate  compile

translate: monster.xc
	java -Xss6M -jar ../../../ableC.jar monster.xc --show-lifted-pp > monster.generated.h

compile: monster.generated.h  main.cpp
	g++ -std=c++11 -O3 -I../../../include/ *.cpp ../../../include/common/*.cpp -o monster.exe

clean:
	rm -f *.i *.o *.exe *.out *.generated.h
