#include "adc.h"
#include <iostream>
#include <fstream>
#include "xnlCompute.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	int code1,code2,code3,code4;
	double residue,input;
	srand(time(0));
	adc* iAdc;
	iAdc = new adc();
	ofstream dataOut1("data1.dat",ios::out);
	ofstream dataOut2("data2.dat",ios::out);
	ofstream resOut("resa.dat",ios::out);
	xnlCompute *linTest = new xnlCompute(12);
	
	for(input=-0.8;input<0.8;input+=0.0001)
	{
		iAdc->sample(.45+input/2,.45-input/2);
		code1=iAdc->convert();
		residue=iAdc->residue(0);
		dataOut1<<code1<<endl;
		resOut<<residue<<endl;
	}
	//linTest->computeLin("data1.dat");
	//iAdc->autoIndCapCalibDither(5,1);
	//iAdc->autoIndCapCalibDither(5,0);
	//iAdc->autoIndCapCalibDither(4,0);
	//iAdc->autoIndCapCalibDither(4,1);
	iAdc->autoCapCalib();
	for(input=-0.8;input<0.8;input+=0.0001)
	{
		iAdc->sample(.45+input/2,.45-input/2);
		code1=iAdc->convert();
		residue=iAdc->residue(0);
		dataOut2<<code1<<endl;
		resOut<<residue<<endl;
	}
	linTest->computeLin("data1.dat","a");
	linTest->computeLin("data2.dat","b");
	delete iAdc;
	delete linTest;
	return 1;
}
