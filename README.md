# extended-unsigned-datatype
This a repository that has an extension userdefined datatype for dealing with larger unsigned numbers in c++

ulli is the unsigned data type that is used to handle larger numbers in form of arrays of ulli

for testing and development basis , ulli is typedef as a unsigned char

to reach the highest bit number it should be typedef to unsigned long long int

ulliarrayfunctions.cpp contains the functions necessary to add, sub, multiply, check eqaul, check greaterthan, leftshift,rightshift ,move data array, and print larger numbers when handled as arrays of ulli data type 

charnum.cpp and charnum.h provides necessary gluecode to actually handle these large numsigned numbers.

charnum class  (c++11 compiler) provides dynamic array memory handling and operator overloading to the unsigned number

at present 
A=B<<C
operator will make A number a combination of B and C as a cocatenation

it works only for unsigned numbers presently but can be easily extended for signed , and fractions using definitions in ulliarrayfunctions.h

certain abbreivation

NOB => Number Of Bits
NOE => Number Of Elements (of the array)

dest => refers to pointer to destination array
data1 / data2 => refers to pointers to input data arrays
