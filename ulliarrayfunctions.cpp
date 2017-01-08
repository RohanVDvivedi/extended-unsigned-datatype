//typedef unsigned long long int ulli;
#include <iostream>
#include <bitset>
#include "ulliarrayfunctions.h"
using namespace std;
typedef unsigned char ulli;
/*
	ulli unsigned long long int
	NOB = number of bits to be considered
	NOE = number of elements in the array
*/
ulli firsthalf = 0xF0;
/*ulli firsthalf = 0hFFFFFFFF00000000;*/
ulli secondhalf = ~firsthalf;

void MOVE(ulli* data1,ulli* dest,ulli NOE)
{
    for(ulli i=0;i<NOE;i++)
	{
		dest[i]=data1[i];
	}
}

void PRINThex(ulli* data1,ulli NOE)
{
    for(ulli i=NOE;i>0;i--)
	{
		cout<<std::hex<<((unsigned long long int)data1[i-1]);
	}
	cout<<endl;
}

void PRINTbin(ulli* data1,ulli NOE)
{
	ulli j;
	for(j=NOE-1;j>0;j--)
	{
		cout<<bitset<(sizeof(data1[j])*8)>(data1[j])<<" ";
	}
	cout<<bitset<(sizeof(data1[j])*8)>(data1[j])<<" "<<endl;
}

void NOT(ulli* data,ulli* dest,ulli NOE)
{
    for(ulli i=0;i<NOE;i++)
	{
        dest[i]=~(data[i]);
	}
}

void AND(ulli* data1,ulli* data2,ulli* dest,ulli NOE)
{
	for(ulli i=0;i<NOE;i++)
	{
        dest[i]=(data2[i] & data1[i]);
	}
}

void OR(ulli* data1,ulli* data2,ulli* dest,ulli NOE)
{
	for(ulli i=0;i<NOE;i++)
	{
        dest[i]=(data2[i] | data1[i]);
	}
}

void EX_OR(ulli* data1,ulli* data2,ulli* dest,ulli NOE)
{
	for(ulli i=0;i<NOE;i++)
	{
        dest[i]=(data2[i] ^ data2[i]);
	}
}

void ADD(ulli* data1,ulli* data2,ulli* dest,ulli NOE)
{
	ulli carry = 0;
	ulli temp = 0;
	ulli nextcarry = 0;
	for(ulli i=0;i<NOE;i++)
	{
        temp=(data2[i] + data1[i]);
        if(temp<data2[i] || temp<data1[i])
		{
            nextcarry = 1;
		}
		else
		{
			nextcarry = 0;
		}
		dest[i]=(temp + carry);
        if(dest[i]<temp || dest[i]<carry)
		{
            nextcarry += 1;
		}
		else
		{
			nextcarry += 0;
		}
		carry = nextcarry;
	}
}

void SUB(ulli* data1,ulli* data2,ulli* dest,ulli NOE)
{
    NOT(data2,data2,NOE);
	ulli carry = 1;
	ulli nextcarry = 0;
	ulli temp;
	for(ulli i=0;i<NOE;i++)
	{
        temp=(data2[i] + data1[i]);
        if(temp<data2[i] || temp<data1[i])
		{
            nextcarry = 1;
		}
		else
		{
			nextcarry = 0;
		}
		dest[i]=(temp + carry);
        if(dest[i]<temp || dest[i]<carry)
		{
            nextcarry += 1;
		}
		else
		{
			nextcarry += 0;
		}
		carry = nextcarry;
	}
	NOT(data2,data2,NOE);
}

void LEFTSHIFT(ulli* data,ulli* dest,ulli LS,ulli NOE)
{
    ulli siz = sizeof(ulli)*8;
    ulli baseshift = LS/siz;
    ulli minorshift = LS%siz;
    for(ulli i=0;i<NOE;i++)
	{
        if(i<baseshift)
		{
			dest[i]=0;
		}
		else
		{
			dest[i]=data[i-baseshift];
		}
	}
	ulli carry = 0;
	ulli nextcarry = 0;
    for(ulli i=baseshift;i<NOE;i++)
	{
		nextcarry = dest[i]>>(siz-minorshift);
        dest[i]=(dest[i]<<minorshift) | carry;
        carry = nextcarry;
	}
}

void RIGHTSHIFT(ulli* data,ulli* dest,ulli RS,ulli NOE)
{
    ulli siz = sizeof(ulli)*8;
    ulli bs = RS/siz;
    ulli baseshift = NOE - 1 - bs;
    ulli minorshift = RS%siz;
    //cout<<(int)baseshift<<" "<<(int)minorshift<<endl;
    for(ulli i=0;i<NOE;i++)
	{
        if(i>baseshift)
		{
			dest[i]=0;
		}
		else
		{
			dest[i]=data[i+bs];
		}
	}
	ulli carry = 0;
	ulli nextcarry = 0;
	ulli i;
    for(i=baseshift;i>0;i--)
	{
		nextcarry = dest[i]<<(siz-minorshift);
        dest[i]=(dest[i]>>minorshift) | carry;
        carry = nextcarry;
	}
	nextcarry = dest[i]<<(siz-minorshift);
	dest[i]=(dest[i]>>minorshift) | carry;
	carry = nextcarry;
}

void mululli(ulli* A,ulli* B,ulli* ans,ulli* carryin,ulli* carryout)
{
	ulli bitwid = sizeof(ulli) * 4;
    ulli t1,t2,t3,t4;
    t1 = ((*A) & secondhalf) * ((*B) & secondhalf);
	t2 = (((*A) & firsthalf)>>bitwid) * ((*B) & secondhalf);
	t4 = ((*A) & secondhalf) * (((*B) & firsthalf)>>bitwid);
	t3 = (((*A) & firsthalf)>>bitwid) * (((*B) & firsthalf)>>bitwid);

	*carryout = t2 + t4;
	if(*carryout<t2 || *carryout<t4)
	{
		t3 = t3 + (1<<bitwid);
	}
    t2 = *carryout;
    *carryout = 0;
	t4 = t1 + *carryin;
	if(t4<t1 || t4<(*carryin))
	{
		t2 = t2 + (1<<bitwid);
	}
	t1 = t4;
	*ans = 0;
	*ans = (t1 & secondhalf);
	t4 = t2 + (t1>>bitwid);
	if(t4<t2 || t4<(t1>>bitwid) )
	{
		t3 = t3 + (1<<bitwid);
	}
	t2 = t4;
	*ans = *ans | (t2<<bitwid);
	t3 = t3 + (t2>>bitwid);
	*carryout = t3;
}


void MUL(ulli* data1,ulli* data2,ulli* dest,ulli NOE)
{
	ulli carry;
	ulli nextcarry;
	ulli solsize = 2*NOE;
	ulli* tempsolution = new ulli[solsize];
	ulli* tempsolution2 = new ulli[solsize];
	ulli tempvar;

    for(ulli i=0;i<NOE;i++)
	{
		tempvar = data1[i];
		carry = 0;
		nextcarry = 0;
		ulli j;

		ZERO(tempsolution,solsize);
		ZERO(tempsolution2,solsize);

		for(j=0;j<NOE;j++)
		{
            mululli(&tempvar,&(data2[j]),&(tempsolution[i+j]),&carry,&nextcarry);
            carry = nextcarry;
		}
		tempsolution[i+j] = carry;
		ADD(dest,tempsolution,tempsolution2,solsize);
		MOVE(tempsolution2,dest,solsize);
	}
	//PRINThex(dest,solsize);
	delete [] tempsolution;
	delete [] tempsolution2;
}

bool ISEQUAL(ulli* data1,ulli* data2,ulli NOE)
{
    for(ulli i=0;i<NOE;i++)
	{
		if(data1[i]!=data2[i])
		{
			return false;
		}
	}
	return true;
}

bool ISGREATERTHAN(ulli* data1,ulli* data2,ulli NOE)
{
    for(ulli i=NOE;i>0;i--)
	{
		if(data1[i-1]>data2[i-1])
		{
			return true;
		}
		else if(data1[i-1]<data2[i-1])
		{
			return false;
		}
	}
	return false;
}

void ZERO(ulli* data,ulli NOE)
{
    for(ulli i =0;i<NOE;i++)
	{
        data[i] = 0;
	}
}
