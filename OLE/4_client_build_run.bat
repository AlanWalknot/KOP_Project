
g++ -c ./client/source/client.cpp -o ./client/build/client.o

g++ ./client/build/client.o -o ./client/build/client.exe -lole32 -loleaut32 -luser32

"./client/build/client.exe"

pause