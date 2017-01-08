#ifndef ULLIARRAYFUNCTIONS_H_INCLUDED
#define ULLIARRAYFUNCTIONS_H_INCLUDED

#include <iostream>
#include <bitset>
using namespace std;

//typedef unsigned long long int ulli;
typedef unsigned char ulli;
/*
	ulli unsigned long long int
	NOB = number of bits to be considered
	NOE = number of elements in the array
*/
void MOVE(ulli* data1,ulli* dest,ulli NOE);
void PRINTbin(ulli* data1,ulli NOE);
void PRINThex(ulli* data1,ulli NOE);
void NOT(ulli* data,ulli* dest,ulli NOE);
void AND(ulli* data1,ulli* data2,ulli* dest,ulli NOE);
void OR(ulli* data1,ulli* data2,ulli* dest,ulli NOE);
void EX_OR(ulli* data1,ulli* data2,ulli* dest,ulli NOE);
void ADD(ulli* data1,ulli* data2,ulli* dest,ulli NOE);
void SUB(ulli* data1,ulli* data2,ulli* dest,ulli NOE);
void LEFTSHIFT(ulli* data,ulli* dest,ulli LS,ulli NOE);
void RIGHTSHIFT(ulli* data,ulli* dest,ulli RS,ulli NOE);
void mululli(ulli* A,ulli* B,ulli* ans,ulli* carryin,ulli* carryout);
void MUL(ulli* data1,ulli* data2,ulli* dest,ulli NOE);
bool ISEQUAL(ulli* data1,ulli* data2,ulli NOE);
bool ISGREATERTHAN(ulli* data1,ulli* data2,ulli NOE);
void ZERO(ulli* data,ulli NOE);
#endif // ULLIARRAYFUNCTIONS_H_INCLUDED
