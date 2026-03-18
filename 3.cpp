#include <iostream>
#include <cmath>

using namespace std;


int main()
{
	setlocale(LC_ALL, "rus"); 
	//double x1, x2, x3;
	double A[3][3];
	//double X[3][1];
	//double B[3][1];

	for(int i=0;i<3;i++)
		for (int j = 0; j < 3; j++)
		{
			if (j == 1) A[i][j] = 1.00;
			A[1][2] = 0.80;
			A[2][2] = 0.90;
			A[3][2] = 1.10;
			A[1][3] = 0.64;
			A[2][3] = 0.81;
			A[3][3] = 1.21;
		}

	for (int i = 0; i < 3; i++) {
		cout << endl;
		for (int j = 0; j < 3; j++)
			cout << A[i][j] << " ";
	}
}