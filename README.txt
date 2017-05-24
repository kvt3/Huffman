# Huffman
File Compression and Decompression using Huffman Algorithm
### FOR HUFFMAN PROJECT ### (use gcc version 4.9 and above)

Use command to check version :
gcc --vesrion

if vesrion is less than 4.9
Use comman to load module:
module load gcc/4.9.2 
or 
module load gcc/5.4.0

Errors:
NO BUGS
Note: 1) if heap memory not available may give you memory related error
      2) if your using gcc version less than 4.9, program will give you pointer assigment related warning

For compiling files use following command:
gcc henc4514.c -o henc4514 
gcc hdec4514.c -o hdec4514

To run file use following command:
To encodefile:
./henc4514 filename
To decodefile:
./hdec4514 filename
