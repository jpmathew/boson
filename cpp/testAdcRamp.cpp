#include "adc.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ofstream dataOut("data.dat",ios::out);
	ofstream resOut("resa.dat",ios::out);
	adc *iAdc = new adc();
	double input,residue;
	long code;
	int rampTest=1;
	if(rampTest==1)
	{
		for(input=-0.9;input<0.9;input+=0.0001)
		{
			iAdc->sample(.45+input/2,.45-input/2);
			code=iAdc->convert();
			residue=iAdc->residue(0);
			dataOut<<code<<endl;
			resOut<<residue<<endl;
		}
	}
	else if(rampTest == 2)
	{
		cout<<"Input :";
		cin>>input;
		iAdc->sample(.45+input/2,.45-input/2);
		code=iAdc->convert();
	}
	else
	{
		iAdc->sample(0.1,0.80);
		code=iAdc->convert();
		cout<<code<<endl;
	}
	delete iAdc;
	return 1;
}
