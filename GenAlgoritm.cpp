#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
using namespace std;
 
double myfunction(double x, double y)
{
	double z = cos(x)*cos(y)*exp(y / 2);
	return z;
}

double randomaiser()
{
	double q;
	q = rand() % 10000 / 1000. - 7.;
	if (q < -2.)
	{
		while (q < -2)
			q += 1;
	}
	if (q > 2.)
	{
		while (q > 2)
			q -= 1;
	}
	return q;
}

void mutation(double X[4], double Y[4])
{
	double E = 0.05;
	int i;
	i = rand() % 4;
	double p;
	p = rand() % 2;
	if (p <= 0.5)
		if (p <= 0.5)
			X[i] += E;
		else
			X[i] -= E;
	else
		if (p <= 0.5)
			Y[i] += E;
		else
			Y[i] -= E;
}

void GenAlgoritm()
{
	int k = 1;
	double X[4];
	double Y[4];
	double Z[4];
	double Z_SR = 0.;
	double P[4];
	double MaxZn;
	double Hit;
	int flag1, flag2;
	double Sum = 0.;
	X[0] = randomaiser();
	Y[0] = randomaiser();
	Z[0] = myfunction(X[0], Y[0]);
	X[1] = randomaiser();
	Y[1] = randomaiser();
	Z[1] = myfunction(X[1], Y[1]);
	X[2] = randomaiser();
	Y[2] = randomaiser();
	Z[2] = myfunction(X[2], Y[2]);
	X[3] = randomaiser();
	Y[3] = randomaiser();
	Z[3] = myfunction(X[3], Y[3]);
	cout << "      X          Y        FIT      Макс. зн.   Ср. зн."<<endl;
	cout << "=========================================================";
	for(int u=0; u<10; u++)
	{		
		Z_SR = 0.000;
		for (int i = 0; i < 4; i++)
		{
			Z_SR += Z[i];
		}
		Z_SR /= 4;
		for (int i = 0; i < 4; i++)
		{
			Sum += Z[i];
		}
		for (int i = 0; i < 4; i++)
		{
			P[i] = Z[i] / Sum*100;
			P[i] = 100 - P[i];
		}
		Hit = rand() % (int)(P[0] + P[1] + P[2] + P[3]) + 1;
		for (int i = 0; i < 4; i++)
		{
			if (Hit > P[i])
			{
				P[i + 1] = P[i] + P[i + 1];
			}
			if (Hit <= P[i])
			{
				flag1 = i;
			}
		}
		MaxZn = -999999;
		for (int i = 0; i < 4; i++)
		{
			if (i == flag1)
			{
				continue;
			}
			else
			{
				if (MaxZn < Z[i])
				{
					MaxZn = Z[i];
					flag2 = i;
				}
			}
		}
		
		for (int i = 0; i < 4; i++)
		{
			cout << endl;
			if (X[i] < 0)
				cout << fixed << setprecision(6) << " |" << X[i]/* << " | "*/;
			else
				cout << fixed << setprecision(6) << " | " << X[i] /*<< " |*/;
			if (Y[i] < 0)
				cout << fixed << setprecision(6) << " |" << Y[i] /*<< " | "*/;
			else
				cout << fixed << setprecision(6) << " | " << Y[i] /*<< " |"*/;
			if (Z[i] < 0)
				cout << fixed << setprecision(6) << " |" << Z[i] /*<< " | "*/;
			else
				cout << fixed << setprecision(6) << " | " << Z[i] /*<< " |"*/;
			
		}
		cout << " | " << fixed << setprecision(6) << MaxZn << " | " << fixed << setprecision(6) << Z_SR;
		cout << "\n=========================================================";
		cout << endl;
		k++;
		int n = 0;
		double pop[3][2] = { 0, 0, 0, 
		                     0, 0, 0 };
		for (int i = 0; i < 4; i++)
		{
			if (i == flag2)
			{
				pop[0][0] = X[i];
				pop[0][1] = Y[i];
			}
			else 
				if (i == flag1)
				{
					n += 1;
					pop[n][0] = X[i];
					pop[n][1] = Y[i];
				}
		}
		X[0] = pop[1][0];
		X[1] = pop[2][0];
		X[3] = pop[0][0];
		X[2] = pop[2][0];
		Y[0] = pop[2][1];
		Y[1] = pop[0][1];
		Y[2] = pop[1][1];
		Y[3] = pop[2][1];
		for (int i = 0; i < 4; i++)
		{
			Z[i] = myfunction(X[i], Y[i]);
		}
		double p;
		p = rand() % 100;
		if (p <= 25)
		{
			mutation(X, Y);
		}
		else
			continue;
		Z_SR = 0.000;
	}
	Z_SR = 0.000;
	for (int i = 0; i < 4; i++)
	{
		Z_SR += Z[i];
	}
	Z_SR /= 4;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	GenAlgoritm();
	system("pause");
	return 0;
}
