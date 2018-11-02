#include "Fileio.h"
#include  <iostream>
using namespace std;



Fileio::Fileio()
{
}

Fileio::Fileio(int flag)
{
}

string Fileio::File_assign(int flag)
{	
	string KYBfile = "KYB.csv";
	string VWfile = "VW.csv";
	if (flag == 0)
	{
		return KYBfile;
	}
	if (flag == 1)
	{

		return VWfile;
	}
	
}

filecheck::filecheck()

{


}

filecheck::filecheck(int flag)
{
	string me = " me.csv";
	
}


Fileio::~Fileio()
{
}

