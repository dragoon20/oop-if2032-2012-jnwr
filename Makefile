all1: bin/Point.o bin/Sel.o bin/matrix.o bin/latar.o bin/bidang.o bin/main2.o
	g++ -o bin/main2.exe bin/Point.o bin/Sel.o bin/matrix.o bin/latar.o bin/bidang.o bin/main2.o
	
all2: bin/Point.o bin/Sel.o bin/matrix.o bin/latar.o bin/bidang.o bin/main3.o
	g++ -o bin/main3.exe bin/Point.o bin/Sel.o bin/matrix.o bin/latar.o bin/bidang.o bin/main3.o	
	
bin/Point.o: src/Point/Point.cpp
	g++ -c src/Point/Point.cpp -o bin/Point.o

bin/Sel.o: src/Sel/Sel.h
	g++ -c src/Sel/Sel.h -o bin/Sel.o

bin/matrix.o: src/Matrix/matrix.h
	g++ -c src/Matrix/matrix.cpp -o bin/matrix.o

bin/latar.o: src/Latar/latar.h
	g++ -c src/Latar/latar.h -o bin/latar.o
	
bin/bidang.o: src/Bidang/bidang.h
	g++ -c src/Bidang/bidang.h -o bin/bidang.o
	
bin/main2.o: src/main2.cpp
	g++ -c src/main2.cpp -o bin/main2.o

bin/main3.o: src/main3.cpp
	g++ -c src/main3.cpp -o bin/main3.o
	
run1: bin/main2.exe
	./bin/main2.exe

run2: bin/main3.exe
	./bin/main3.exe

clean:
	rm -rf bin/*