all: translate  compile

translate: fancy_monster.xc
	java -Xss6M -jar ../../../ableC.jar fancy_monster.xc --show-lifted-pp > fancy_monster.generated.h

compile: fancy_monster.generated.h  main.cpp
	g++ -std=c++11 -O3 -I../../../include/ *.cpp ../../../include/common/*.cpp -o fancy_monster.exe

clean:
	rm -f *.i *.o *.exe *.out *.generated.h
