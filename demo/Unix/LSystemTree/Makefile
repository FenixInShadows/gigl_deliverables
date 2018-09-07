all: translate  compile

translate: l_tree.xc
	java -Xss6M -jar ../../../ableC.jar l_tree.xc --show-lifted-pp > l_tree.generated.h

compile: l_tree.generated.h  main.cpp  macro.h  TreeSegment.cpp  TreeSegment.h
	g++ -std=c++11 -O3 -I../../../include/ *.cpp ../../../include/common/*.cpp -lSDL2 -lSDL2main -lGL -o l_tree.exe

clean:
	rm -rf build *.i *.o *.exe *.out *.generated.h
