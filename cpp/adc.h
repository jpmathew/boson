#ifndef ADC_H
#define ADC_H
#include "cdac.h"

class adc
{
	private:
		cdac *cdacP,*cdacM;
		int add[12],sub[12];
		int ea[12],eb[12];
		int g;
		const static double refp=0.9;
		const static double refm=0.0;
	public:
		adc();
		void sample(double vinp,double vinm);
		void calibSample(int prcode);
		int convert();
		int calibConvert(int bitUnderCal,int config);
		double residue(int bitPosition);
		void autoCapCalib();
		void printCoe();
		void setCoe(int type,int pos,int val);
		~adc();
};

		
#endif
