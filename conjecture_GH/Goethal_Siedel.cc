#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdio.h>      /* printf */
#include <math.h>
#include"/home/soundap9/Documents/Bush_Hadamard/make_Bush_matrices.cc"
using namespace std;
//This function generates a Goethal Seidel matrix of order 12, given the matrices B,C,D of order 3. Matrix A of order 3 is assumed to be the all ones matrix.
int** goethal_seidel(int** b, int** c, int** d);
int** goethal_seidel_I(int** b, int** c, int** d);


int main()
{
 int** d = new int*[3];
 int** b = new int*[3];
 int** c = new int*[3];
for(int i=0;i<3;i++)
{
	d[i] = new int[3];
	b[i] = new int[3];
	c[i] = new int[3];
}

b[0][0]=1; b[0][1]=-1;b[0][2]=-1;
b[1][0]=-1;b[1][1]=1;b[1][2]=-1;
b[2][0]=-1;b[2][1]=-1;b[2][2]=1;

c[0][0]=-1;c[0][1]=1;c[0][2]=-1;
c[1][0]=-1;c[1][1]=-1;c[1][2]=1;
c[2][0]=1;c[2][1]=-1;c[2][2]=-1;

d[0][0]=-1;d[0][1]=-1;d[0][2]=1;
d[1][0]=1;d[1][1]=-1;d[1][2]=-1;
d[2][0]=-1;d[2][1]=1;d[2][2]=-1;
int** gs = goethal_seidel(b,c,d);
cout<<"b ="<<endl;
print(b,3);
cout<<"c ="<<endl;
print(c,3);
cout<<"d ="<<endl;
print(d,3);
cout<<"______________________________"<<endl;
print(gs,12);
cout<<"______________________________"<<endl;
cout<<check_Hadamard(gs,12);
gs = goethal_seidel_I(b,c,d);
cout<<"b ="<<endl;
print(b,3);
cout<<"c ="<<endl;
print(c,3);
cout<<"d ="<<endl;
print(d,3);
cout<<"______________________________"<<endl;
print(gs,12);
cout<<"______________________________"<<endl;
cout<<check_Hadamard(gs,12);
}

int** goethal_seidel(int** b, int** c, int** d)
{
	int** gs = new int*[12];
	
	for(int i=0;i<12;i++)
	{
		gs[i] = new int[12];
	}
	// A
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			gs[i][j] = 1;
		}
	}
	// BR
	for(int i=0;i<3;i++)
	{
		for(int j=3;j<6;j++)
		{
			gs[i][j] = b[i][5-j];
		}
	}
	// CR
	for(int i=0;i<3;i++)
	{
		for(int j=6;j<9;j++)
		{
			gs[i][j]= c[i][8-j];
		}
	}
	//DR
	for(int i=0;i<3;i++)
	{
		for(int j=9;j<12;j++)
		{
			gs[i][j] = d[i][11-j];
		}
	}
	/*
	//-BR
	for(int i=3;i<6;i++)
	{
		for(int j=0;j<3;j++)
		{
			gs[i][j] = -b[i-3][2-j];
		}
	}
	*/
	// A
	for(int i=3;i<6;i++)
	{
		for(int j=3;j<6;j++)
		{
			gs[i][j]=1;
		}
	}
	// D_tR
	for(int i=3;i<6;i++)
	{
		for(int j=6;j<9;j++)
		{
			gs[i][j]=d[2-(j-6)][(i-3)];
		}
	}
	// -C_tR
	for(int i=3;i<6;i++)
	{
		for(int j=9;j<12;j++)
		{
			gs[i][j]=-c[2-(j-9)][(i-3)];
		}
	}
	// A
	for(int i=6;i<9;i++)
	{
		for(int j=6;j<9;j++)
		{
			gs[i][j] = 1;
		}
	}

	// B_tR
	for(int i=6;i<9;i++)
	{
		for(int j=9;j<12;j++)
		{
			gs[i][j]= b[2-(j-9)][(i-6)];
		}
	}
	// A
	for(int i=9;i<12;i++)
	{
		for(int j=9;j<12;j++)
		{
			gs[i][j] = 1;
		}
	}
	//Rest of the matrix
         // -BR
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        gs[i+3][j] = -gs[i][j+3];
                }
        }
        // -CR
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        gs[i+6][j]= -gs[i][j+6];
                }
        }
        //-DR
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        gs[i+9][j] = -gs[i][j+9];
                }
        }
        // -D_tR
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        gs[i+6][j+3]=-gs[i+3][j+6];
                }
        }
        // -C_tR
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        gs[i+9][j+3]=-gs[i+3][j+9];
                }
        }
        // -B_tR
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        gs[i+9][j+6]= -gs[i+6][j+9];
                }
        }
	return gs;
}

int** goethal_seidel_I(int** b, int** c, int** d)
{
        int** gs = new int*[12];

        for(int i=0;i<12;i++)
        {
                gs[i] = new int[12];
        }
        // A
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        gs[i][j] = 1;
                }
        }
        // BR
        for(int i=0;i<3;i++)
        {
                for(int j=3;j<6;j++)
                {
                        gs[i][j] = b[i][j-3];
                }
        }
        // CR
        for(int i=0;i<3;i++)
        {
                for(int j=6;j<9;j++)
                {
                        gs[i][j]= c[i][j-6];
                }
        }
        //DR
        for(int i=0;i<3;i++)
        {
                for(int j=9;j<12;j++)
                {
                        gs[i][j] = d[i][j-9];
                }
        }

	// A
        for(int i=3;i<6;i++)
        {
                for(int j=3;j<6;j++)
                {
                        gs[i][j]=1;
                }
        }
        // D_tR
        for(int i=3;i<6;i++)
        {
                for(int j=6;j<9;j++)
                {
                        gs[i][j]=d[(j-6)][(i-3)];
                }
        }
        // -C_tR
        for(int i=3;i<6;i++)
        {
                for(int j=9;j<12;j++)
                {
                        gs[i][j]=-c[(j-9)][(i-3)];
                }
        }
        // A
        for(int i=6;i<9;i++)
        {
                for(int j=6;j<9;j++)
                {
                        gs[i][j] = 1;
                }
        }

        // B_tR
        for(int i=6;i<9;i++)
        {
                for(int j=9;j<12;j++)
                {
                        gs[i][j]= b[(j-9)][(i-6)];
                }
        }

	// A
        for(int i=9;i<12;i++)
        {
                for(int j=9;j<12;j++)
                {
                        gs[i][j] = 1;
                }
        }
        //Rest of the matrix
         // -BR
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        gs[i+3][j] = -gs[i][j+3];
                }
        }
        // -CR
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        gs[i+6][j]= -gs[i][j+6];
                }
        }
        //-DR
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        gs[i+9][j] = -gs[i][j+9];
                }
        }
        // -D_tR
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        gs[i+6][j+3]=-gs[i+3][j+6];
                }
        }
	// -C_tR
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        gs[i+9][j+3]=-gs[i+3][j+9];
                }
        }
        // -B_tR
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        gs[i+9][j+6]= -gs[i+6][j+9];
                }
        }
        return gs;
}
