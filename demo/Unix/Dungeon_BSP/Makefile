all: translate  compile

translate: dungeon.xc
	java -Xss6M -jar ../../../ableC.jar dungeon.xc --show-lifted-pp > dungeon.generated.h

compile: dungeon.generated.h  main.cpp  macro.h  DungeonSpace.cpp  DungeonSpace.h
	g++ -std=c++11 -O3 -I../../../include/ *.cpp ../../../include/common/*.cpp -lSDL2 -lSDL2main -lGL -o dungeon.exe

clean:
	rm -rf build *.i *.o *.exe *.out *.generated.h
