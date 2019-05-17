#/bin/bash

: '
server_files=$(ls $server*.cpp)
for filename in $server_files
do
       g++ -g -o server  $filename
done

client_files=$(ls $client*.cpp)

for filename in $server_files
do
           g++ -g -o client  $filename
done
'
server_name=$1.cpp
client_name=$2.cpp
g++ -g -o server $server_name
g++ -g -o client $client_name
