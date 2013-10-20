// beautifulcode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//start
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <iomanip>
using namespace std;
int main(int argc, char* argv[])
{
	int T;
	cin >> T;
	int a,b,c,d,e,temp;
	double p,s,ca,sp;
	for(int iCase = 1; iCase <= T;++iCase)
	{
		cin >>a>>b>>c>>d>>e;
		p = (double(a)+b+e)/2;
		s = p*(p-a)*(p-b)*(p-e);
		s = sqrt(s);
		//cout << "s: " << s << endl;
		if(a<b) {temp=a;a=b;b=temp;}
		ca = (b*b-e*e+a*a)*1.0/(2*b*a);
		ca = acos(ca);
		//cout << "ca" << ca/3.14*180 << "sca" << sin(ca) << "cca" << cos(ca)<< endl;
		sp = b*sin(ca)*b*cos(ca)/2;
		//cout << "sp" << sp << endl;
		//s = 2*(s-sp);
    s = 2*s+sp-a*b*sin(ca)/2;
		cout << "Case #" << iCase <<":"; //记得冒号后面的空格
		cout << " " <<fixed << setprecision(4)<< s << endl;
	}
	return 0;
}

