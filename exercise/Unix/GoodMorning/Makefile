all: translate  compile

translate: good_morning.xc
	java -Xss6M -jar ../../../ableC.jar good_morning.xc --show-lifted-pp > good_morning.generated.h

compile: good_morning.generated.h  main.cpp
	g++ -std=c++11 -O3 -I../../../include/ *.cpp ../../../include/common/*.cpp -o good_morning.exe

clean:
	rm -f *.i *.o *.exe *.out *.generated.h
