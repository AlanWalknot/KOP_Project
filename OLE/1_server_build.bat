g++ -c ./server/source/component.cpp -o ./server/build/component.o
g++ -c ./server/source/main.cpp -o ./server/build/main.o

g++ -shared ./server/build/component.o ./server/build/main.o -o ./server/build/main.dll -lole32 -loleaut32 -luser32 -Wl,--kill-at

g++ -c ./server2/source/component.cpp -o ./server2/build/component.o
g++ -c ./server2/source/main.cpp -o ./server2/build/main.o

g++ -shared ./server2/build/component.o ./server2/build/main.o -o ./server2/build/main.dll -lole32 -loleaut32 -luser32 -Wl,--kill-at

pause