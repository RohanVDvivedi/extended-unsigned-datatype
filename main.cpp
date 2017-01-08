#include <iostream>
#include <bitset>
#include "charnum.h"
using namespace std;

int main()
{
	/*ulli data1[4] = { 255, 100,96,125 };
	ulli data2[4] = { 122, 255,250,150 };
	ulli dest[8] = {};
	unsigned long long int demo1,demo2;

	cout<<"data1 : ";
	demo1=printulli(data1,4);
	cout<<"data2 : ";
	demo2=printulli(data2,4);

	cout<<"multiplying"<<endl;
	MUL(data1,data2,dest,4);
	cout<<"multiplying complete"<<endl;
	demo1 = demo1*demo2;
	demo2 = printulli(dest,8);

	cout<<"ans gott :"<<demo2<<endl;
	cout<<"real ans :"<<demo1<<endl;
    return 0;*/

	charnum A("0d9999",16);
	charnum B("0xFFFF1234",32);
	charnum C("0b101111011111",12);
	charnum D("0xffff",16);
	cout<<A<<endl;
	cout<<B<<endl;
	cout<<C<<endl;
	cout<<D<<endl<<endl;
	C=C<<B<<A;
	cout<<A<<endl;
	cout<<B<<endl;
	cout<<C<<endl;
	cout<<D<<endl<<endl;
	cout<<(D+C)<<endl<<(C+D)<<endl;
	cout<<A<<endl;
	cout<<B<<endl;
	cout<<C<<endl;
	cout<<D<<endl<<endl;
	D=B*D;
	cout<<A<<endl;
	cout<<B<<endl;
	cout<<C<<endl;
	cout<<D<<endl<<endl;
	D=C;
	cout<<A<<endl;
	cout<<B<<endl;
	cout<<C<<endl;
	cout<<D<<endl<<endl;
	D=D+A+C;
	cout<<A<<endl;
	cout<<B<<endl;
	cout<<C<<endl;
	cout<<D<<endl<<endl;

    return 0;
}
