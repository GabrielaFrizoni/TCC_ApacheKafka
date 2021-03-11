#!/bin/sh
ldconfig
mv /json.hpp ./json.hpp 2>/dev/null
g++ -std=c++11 -Wall -fexceptions -g -pthread -I header -c source/main.cpp -o main.o
g++ -std=c++11 -Wall -fexceptions -g -pthread -I header -c source/consumidor.cpp -o consumidor.o
g++ -std=c++11 -o consumer_module main.o consumidor.o -lpthread -lcppkafka
LD_LIBRARY_PATH=/usr/local/lib/x86_64-linux-gnu/ ./consumer_module
