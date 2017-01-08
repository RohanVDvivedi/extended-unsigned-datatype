#include "charnum.h"

ulli getbineq(char c)
{
    if(c=='0')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
ulli gethexeq(char c)
{
	if(c>='0' && c<='9')
	{
		c = c-'0';
	}
	else if(c>='A' && c<='F')
	{
		c = c-'A'+10;
	}
	else if(c>='a' && c<='f')
	{
        c = c-'a'+10;
	}
	return ((ulli)c);
}
ulli getdeceq(char c)
{
	return gethexeq(c);
}

charnum::charnum(string number,ulli NOB):NOB(NOB)
{
	char base = 'd';
	ulli iter = 0;

	if(number.length()>0)
	{
		if(number[0]=='0')
		{
			if(number[1]=='x' || number[1]=='X')
			{
				base = 'x';
				iter+=2;
			}
			else if(number[1]=='b' || number[1]=='B')
			{
				base = 'b';
				iter+=2;
			}
			else if(number[1]=='d' || number[1]=='D')
			{
				iter+=2;
			}
		}
	}

    NOE = NOB/(sizeof(ulli)*8);
    if(NOE*sizeof(ulli)*8 < NOB)
	{
        NOE++;
	}
    data = new ulli[NOE];
    ZERO(data,NOE);

    if(number.length()>0)
	{
		ulli* temp = new ulli[NOE];
		ulli* temp210 = new ulli[NOE];

		ZERO(temp,NOE);
		ZERO(temp210,NOE);
		temp210[0]=10;

		for(;iter<number.length();iter++)
		{
			switch(base)
			{
				case 'd':
					{
						temp210[0]=10;ZERO(temp,NOE);
						MUL(data,temp210,temp,NOE);
						//PRINThex(temp,NOE);

						temp210[0]=getdeceq(number[iter]);
						ADD(temp,temp210,data,NOE);
						//PRINTbin(data,NOE);
						break;
					}
				case 'b':
					{
						LEFTSHIFT(data,temp,1,NOE);
						MOVE(temp,data,NOE);
						data[0]=data[0] | getbineq(number[iter]);
						break;
					}
				case 'x':
					{
						LEFTSHIFT(data,temp,4,NOE);
						MOVE(temp,data,NOE);
						data[0]=data[0] | gethexeq(number[iter]);
						break;
					}
			}

		}

		delete [] temp;
		delete [] temp210;
	}
}

charnum::~charnum()
{
	delete [] data;
}


void charnum::ChangeSize(charnum& C,ulli NEWNOE)
{
    if(C.NOE > NEWNOE)
	{
        ulli* datanew = new ulli[NEWNOE];
        MOVE(C.data,datanew,NEWNOE);
        delete [] C.data;
        C.data = datanew;
        C.NOE = NEWNOE;
	}
	else if(C.NOE < NEWNOE)
	{
		ulli* datanew = new ulli[NEWNOE];
		ZERO(datanew,NEWNOE);
        MOVE(C.data,datanew,C.NOE);
        delete [] C.data;
        C.data = datanew;
        C.NOE = NEWNOE;
	}
	C.NOB = NEWNOE * sizeof(ulli) * 8;
}

charnum charnum::operator+(charnum& parama)
{
	charnum Self("",this->NOB);
    MOVE(this->data,Self.data,this->NOE);

    charnum C("",parama.NOB);
    MOVE(parama.data,C.data,parama.NOE);

	if(C.NOE > Self.NOE)
	{
		ChangeSize(Self,C.NOE);
	}
	else if(C.NOE < Self.NOE)
	{
		ChangeSize(C,Self.NOE);
	}

    charnum Ans("",Self.NOB);
    ADD(C.data,Self.data,Ans.data,Self.NOE);
	return Ans;
}

charnum charnum::operator-(charnum& parama)
{
	charnum Self("",this->NOB);
    MOVE(this->data,Self.data,this->NOE);

    charnum C("",parama.NOB);
    MOVE(parama.data,C.data,parama.NOE);

	if(C.NOE > Self.NOE)
	{
		ChangeSize(Self,C.NOE);
	}
	else if(C.NOE < Self.NOE)
	{
		ChangeSize(C,Self.NOE);
	}
    charnum Ans("",Self.NOB);
    SUB(Self.data,C.data,Ans.data,Self.NOE);
	return Ans;
}

charnum charnum::operator*(charnum& parama)
{

	charnum Self("",this->NOB);
    MOVE(this->data,Self.data,this->NOE);

    charnum C("",parama.NOB);
    MOVE(parama.data,C.data,parama.NOE);

    bool needtochangesize;

	if(C.NOE > Self.NOE)
	{
		ChangeSize(Self,C.NOE);
		needtochangesize = true;
	}
	else if(C.NOE < Self.NOE)
	{
		ChangeSize(C,Self.NOE);
		needtochangesize = true;
	}
    charnum Ans("",2*(Self.NOE*sizeof(ulli)*8) );
    MUL(Self.data,C.data,Ans.data,Self.NOE);
    if(needtochangesize)
	{
		Ans.ChangeSize(Ans,this->NOE + parama.NOE);
	}
	Ans.NOB = this->NOB + parama.NOB;
	return Ans;
}

charnum charnum::operator&(charnum& parama)
{
	charnum Self("",this->NOB);
    MOVE(this->data,Self.data,this->NOE);

    charnum C("",parama.NOB);
    MOVE(parama.data,C.data,parama.NOE);

	if(C.NOE > Self.NOE)
	{
		ChangeSize(Self,C.NOE);
	}
	else if(C.NOE < Self.NOE)
	{
		ChangeSize(C,Self.NOE);
	}
    charnum Ans("",Self.NOB);
    AND(C.data,Self.data,Ans.data,Self.NOE);
	return Ans;
}

charnum charnum::operator|(charnum& parama)
{
	charnum Self("",this->NOB);
    MOVE(this->data,Self.data,this->NOE);

    charnum C("",parama.NOB);
    MOVE(parama.data,C.data,parama.NOE);

	if(C.NOE > Self.NOE)
	{
		ChangeSize(Self,C.NOE);
	}
	else if(C.NOE < Self.NOE)
	{
		ChangeSize(C,Self.NOE);
	}
    charnum Ans("",Self.NOB);
    OR(C.data,Self.data,Ans.data,Self.NOE);
	return Ans;
}

charnum charnum::operator~()
{
    charnum Ans("",this->NOB);
    NOT(this->data,Ans.data,this->NOE);
	return Ans;
}

charnum charnum::operator<<(charnum& C)
{
    charnum Ans("",this->NOB + C.NOB);
    charnum temp("",this->NOB + C.NOB);
    MOVE(this->data,temp.data,this->NOE);
    LEFTSHIFT(temp.data,Ans.data,C.NOB,Ans.NOE);
    OR(Ans.data,C.data,Ans.data,C.NOE);
    return Ans;
}

void charnum::operator=(const charnum& C)
{
	this->NOE = C.NOE;
	this->NOB = C.NOB;
	delete [] this->data;
	this->data = new ulli[this->NOE];
	MOVE(C.data,this->data,this->NOE);
}

string getproperhex(ulli a)
{
    ulli siz = sizeof(a) * 2;
    ulli temp = 0xf;
    ulli ans;
    string number;
    char c;
    for(ulli i=siz; i>0 ;i--)
    {
        ans = temp & a;
        a=a>>4;
        if(ans<=9)
        {
            c = ans + '0';
        }
        else
        {
            c = (ans-10) + 'a';
        }
        number = c + number;
    }
    return number;
}

ostream& operator<<(ostream& out,const charnum& C)
{
	bool start = false;
	for(ulli i=C.NOE;i>0;i--)
	{
		if(C.data[i-1] == 0 && start==false )
		{
			continue;
		}
		else
		{
			start = true;
		}
		out<<getproperhex(C.data[i-1]);
	}
	return out;
}

bool charnum::getbool()
{
    charnum temp("",this->NOB);
    if( ISEQUAL(temp.data,this->data,this->NOE) )
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool charnum::operator==(charnum& parama)
{
	charnum Self("",this->NOB);
    MOVE(this->data,Self.data,this->NOE);

    charnum C("",parama.NOB);
    MOVE(parama.data,C.data,parama.NOE);

	if(C.NOE > Self.NOE)
	{
		ChangeSize(Self,C.NOE);
	}
	else if(C.NOE < Self.NOE)
	{
		ChangeSize(C,Self.NOE);
	}
    bool Ans=ISEQUAL(C.data,Self.data,Self.NOE);
	return Ans;
}
bool charnum::operator!=(charnum& parama)
{
	charnum Self("",this->NOB);
    MOVE(this->data,Self.data,this->NOE);

    charnum C("",parama.NOB);
    MOVE(parama.data,C.data,parama.NOE);

	if(C.NOE > Self.NOE)
	{
		ChangeSize(Self,C.NOE);
	}
	else if(C.NOE < Self.NOE)
	{
		ChangeSize(C,Self.NOE);
	}
    bool Ans=ISEQUAL(C.data,Self.data,Self.NOE);
	return !Ans;
}
bool charnum::operator>(charnum& parama)
{
	charnum Self("",this->NOB);
    MOVE(this->data,Self.data,this->NOE);

    charnum C("",parama.NOB);
    MOVE(parama.data,C.data,parama.NOE);

	if(C.NOE > Self.NOE)
	{
		ChangeSize(Self,C.NOE);
	}
	else if(C.NOE < Self.NOE)
	{
		ChangeSize(C,Self.NOE);
	}
	//cout<<Self<<" "<<(int)Self.NOE<<endl;
	//cout<<C<<" "<<(int)C.NOE<<endl;
    bool Ans=ISGREATERTHAN(Self.data,C.data,Self.NOE);
	return Ans;
}
bool charnum::operator<(charnum& parama)
{
	charnum Self("",this->NOB);
    MOVE(this->data,Self.data,this->NOE);

    charnum C("",parama.NOB);
    MOVE(parama.data,C.data,parama.NOE);

	if(C.NOE > Self.NOE)
	{
		ChangeSize(Self,C.NOE);
	}
	else if(C.NOE < Self.NOE)
	{
		ChangeSize(C,Self.NOE);
	}
    bool Ans=ISGREATERTHAN(C.data,Self.data,Self.NOE);
	return !(ISEQUAL(C.data,Self.data,Self.NOE)) && Ans;
}
bool charnum::operator>=(charnum& parama)
{
    return ( this->operator>(parama) || this->operator==(parama) ) ;
}
bool charnum::operator<=(charnum& parama)
{
    return !(this->operator>(parama));
}
bool charnum::operator&&(charnum& parama)
{
	return this->getbool() && parama.getbool();
}
bool charnum::operator||(charnum& parama)
{
	return this->getbool() || parama.getbool();
}
