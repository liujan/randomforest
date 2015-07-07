obj = Node.o Tree.o RandomForest.o main.o
target=random

$(target):$(obj)
	g++ -o $(target) $(obj)

Node.o:Node.h
	g++ -c Node.cpp
Tree.o:Node.h Tree.h
	g++ -c Node.cpp Tree.cpp
RandomForest.o:RandomForest.h Tree.h Node.h
	g++ -c Tree.cpp Node.cpp  RandomForest.cpp
main.o:main.cpp RandomForest.h Tree.h Node.h
	g++ -c main.cpp RandomForest.cpp Tree.cpp Node.cpp

clean:
	rm -rf $(obj)
