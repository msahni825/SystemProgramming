# SystemProgramming
Shell Scripting

CLIENT

//reaching the required folders
cd Downloads
cd ClientServerCode

//compiling the c file and creating an output file "client"
gcc -o client client.c

//loop back address 
./client 127.0.0.1

O/P:
Enter string: 
HITHERE
EREHTIH


SERVER

//reaching the required folders
cd Downloads
cd ClientServerCode

//compiling the c file and creating an output file "client"
gcc -o server server.c

./server

O/P:
Server listening for connections
Accepted a string
string from client: HITHERE
Reversed string sent to client!

