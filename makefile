CXXFLAGS = -std=c++11

OBJ = Inventory.o Item.o Character.o Monster.o Battle.o Map.o functions.o main.o
OBJ2 = Inventory.o Item.o Character.o Monster.o Battle.o Map.o functions.o main2.o

game: $(OBJ)
	g++ -o game $(OBJ)

game2: $(OBJ2)
	g++ -o game2 $(OBJ2)

Inventory.o: Inventory.h
Item.o: Item.h
Character.o: Character.h
Monster.o: Monster.h
Battle.o: Battle.h
Map.o: Map.h
functions.o: functions.h
main2.o:
main.o:

.PHONY : clean
clean:
	rm game $(OBJ)
