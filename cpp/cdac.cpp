#include "cdac.h"
#include "simpleFunctions.h"

cdac::cdac()
{
	capCount=24;
	samplingCapCount=12;
	//msb Array
	capWeight=new double[24];
	capWeight[0]=1.0/double(pow(2,0+2));
	capWeight[1]=1.0/double(pow(2,0+2));
	capWeight[2]=1.0/double(pow(2,1+2));
	capWeight[3]=1.0/double(pow(2,1+2));
	capWeight[4]=1.0/double(pow(2,2+2));
	capWeight[5]=1.0/double(pow(2,2+2));
	capWeight[6]=1.0/double(pow(2,3+2));
	capWeight[7]=1.0/double(pow(2,3+2));
	capWeight[8]=1.0/double(pow(2,4+2));
	capWeight[9]=1.0/double(pow(2,4+2));
	capWeight[10]=1.0/double(pow(2,4+2));
	capWeight[11]=1.0/double(pow(2,4+2));
	//lsb array
	capWeight[12]=1.0/double(pow(2,0+7));
	capWeight[13]=1.0/double(pow(2,0+7));
	capWeight[14]=1.0/double(pow(2,1+7));
	capWeight[15]=1.0/double(pow(2,1+7));
	capWeight[16]=1.0/double(pow(2,2+7));
	capWeight[17]=1.0/double(pow(2,2+7));
	capWeight[18]=1.0/double(pow(2,3+7));
	capWeight[19]=1.0/double(pow(2,3+7));
	capWeight[20]=1.0/double(pow(2,4+7));
	capWeight[21]=1.0/double(pow(2,4+7));
	capWeight[22]=1.0/double(pow(2,4+7));
	capWeight[23]=1.0/double(pow(2,4+7));
	//bottompaltes
	totSamplingCap=0;
	capVoltage=new double[24];
	for(int iter=0;iter<capCount;iter++)
	{
		capVoltage[iter]=0.0;
		totSamplingCap+=capWeight[iter];
	}
}

cdac::cdac(int errCount,double* err)
{
	capCount=24;
	samplingCapCount=12;
	//msb Array
	capWeight=new double[24];
	capWeight[0]=1.0/double(pow(2,0+2));
	capWeight[1]=1.0/double(pow(2,0+2));
	capWeight[2]=1.0/double(pow(2,1+2));
	capWeight[3]=1.0/double(pow(2,1+2));
	capWeight[4]=1.0/double(pow(2,2+2));
	capWeight[5]=1.0/double(pow(2,2+2));
	capWeight[6]=1.0/double(pow(2,3+2));
	capWeight[7]=1.0/double(pow(2,3+2));
	capWeight[8]=1.0/double(pow(2,4+2));
	capWeight[9]=1.0/double(pow(2,4+2));
	capWeight[10]=1.0/double(pow(2,4+2));
	capWeight[11]=1.0/double(pow(2,4+2));
	//lsb array
	capWeight[12]=1.0/double(pow(2,0+7));
	capWeight[13]=1.0/double(pow(2,0+7));
	capWeight[14]=1.0/double(pow(2,1+7));
	capWeight[15]=1.0/double(pow(2,1+7));
	capWeight[16]=1.0/double(pow(2,2+7));
	capWeight[17]=1.0/double(pow(2,2+7));
	capWeight[18]=1.0/double(pow(2,3+7));
	capWeight[19]=1.0/double(pow(2,3+7));
	capWeight[20]=1.0/double(pow(2,4+7));
	capWeight[21]=1.0/double(pow(2,4+7));
	capWeight[22]=1.0/double(pow(2,4+7));
	capWeight[23]=1.0/double(pow(2,4+7));
	//Add error
	for(int iter=0;iter<errCount;iter++)
	{
		capWeight[iter]+=err[iter];
	}
	//bottompaltes
	capVoltage=new double[24];
	totSamplingCap=0;
	for(int iter=0;iter<capCount;iter++)
	{
		capVoltage[iter]=0.0;
		totSamplingCap+=capWeight[iter];
	}
}

cdac::cdac(int capCount,int samplingCapCount,double *capWeight)
{
	this->capCount=capCount;
	this->samplingCapCount=samplingCapCount;
	for(int iter=0;iter<capCount;iter++)
	{
		this->capWeight[iter]=capWeight[iter];
	}
	for(int iter=0;iter<capCount;iter++)
	{
		capVoltage[iter]=0.0;
	}
}

void cdac::sample(double vin,double refp,double refm)
{
	topPlateVoltage=0.0;
	for(int iter=0;iter<samplingCapCount;iter++)
	{
		capVoltage[iter]=vin;
	}
	for(int iter=samplingCapCount;iter<capCount;iter++)
	{
		if(iter%2==0)
		{
			capVoltage[iter]=refm;
		}
		else
		{
			capVoltage[iter]=refp;
		}
	}
}

void cdac::calibSample(double refp,double refm,int prcode)
{
	topPlateVoltage=0.0;
	for(int iter=0;iter<capCount;iter++)
	{
		if(iter%2==0)
		{
			capVoltage[iter]=refm;
		}
		else
		{
			capVoltage[iter]=refp;
		}
	}
	capVoltage[22]=double(prcode)/32.0*(refp-refm);
}

double cdac::changeBotPlateVoltage(double botVoltage,int botPosition)
{
	topPlateVoltage+=(botVoltage-capVoltage[botPosition])*capWeight[botPosition];
	capVoltage[botPosition]=botVoltage;
	return topPlateVoltage;
}

double cdac::getTopPlateVoltage()
{
	return topPlateVoltage;
}

void cdac::printBotstat()
{
	for(int iter=0;iter<capCount;iter++)
	{
		cout<<capVoltage[iter]<<"\t";
	}
	cout<<endl;
}

cdac::~cdac()
{
	delete [] capVoltage;
	delete [] capWeight;
}

	






	





