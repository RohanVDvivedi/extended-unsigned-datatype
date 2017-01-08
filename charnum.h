#ifndef CHARNUM_H
#define CHARNUM_H

#include <iostream>
#include <string>
#include "ulliarrayfunctions.h"
using namespace std;

class charnum
{
	private :
		void ChangeSize(charnum& C,ulli NEWNOE);

		ulli* data;
        ulli NOB =0 ;
        ulli NOE =0;

        charnum* temp = NULL;

	public:

		charnum(string number,ulli NOB);
		~charnum();

		bool getbool();

		charnum operator+(charnum& parama);
		charnum operator-(charnum& parama);
		charnum operator*(charnum& parama);
		charnum operator&(charnum& parama);
		charnum operator|(charnum& parama);
		charnum operator~();
		void operator=(const charnum& parama);
		charnum operator<<(charnum& parama);
		friend ostream& operator<<(ostream& out,const charnum& C);
		bool operator==(charnum& parama);
		bool operator!=(charnum& parama);
		bool operator>(charnum& parama);
		bool operator<(charnum& parama);
		bool operator>=(charnum& parama);
		bool operator<=(charnum& parama);
		bool operator&&(charnum& parama);
		bool operator||(charnum& parama);
};

#endif // CHARNUM_H
