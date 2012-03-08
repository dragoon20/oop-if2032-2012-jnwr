all1: bin/Point.o bin/main2.o
	g++ -o bin/main2 bin/Point.o bin/main2.o
	
all2: bin/Point.o bin/main3.o
	g++ -o bin/main3 bin/Point.o bin/main3.o	
	
bin/Point.o: src/Point/point.cpp
	g++ -c src/Point/point.cpp -o bin/Point.o

bin/main2.o: src/main2.cpp
	g++ -c src/main2.cpp -o bin/main2.o

bin/main3.o: src/main3.cpp
	g++ -c src/main3.cpp -o bin/main3.o
	
run1: bin/main2
	./bin/main2

run2: bin/main3
	./bin/main3

clean:
	rm -rf bin/*
