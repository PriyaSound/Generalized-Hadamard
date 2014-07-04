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

// This function finds the 2 matrices H and H_dash by using the recursive method mentioned in the paper:"Recursive Construction for New Symmetric Designs", Ionin and Kharaghani, and finds if their Hadamard_product is Hadamard or not
 bool Had_4x3n_generate(int** a_n,const int order_a_n, int** b_n,const int order_b_n, int** J,const int order_J, int** Q,const int order_Q,int** I,const int order_I);

int main()
{

int** Q = new int*[3];  int q[3][3] = {{0,-1,1},{1,0,-1},{-1,1,0}};//Normalized
int** J3= new int*[3]; int j3[3][3]={{1,1,1},{1,1,1},{1,1,1}};
int** I3= new int*[3]; int i3[3][3] ={{1,0,0},{0,1,0},{0,0,1}};
int** A0= new int*[4]; int a0[4][4] = {{-1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
int** B0= new int*[4]; int b0[4][4] = {{0,1,1,1},{1,0,-1,1},{1,1,0,-1},{1,-1,1,0}};

for(int i=0;i<3;i++)
{
        Q[i] = new int[3];
        J3[i] = new int[3];
        I3[i] = new int[3];
        for(int j=0;j<3;j++)
        {
                Q[i][j] = q[i][j];
                J3[i][j] = j3[i][j];
                I3[i][j] = i3[i][j];
        }
}

for(int i=0;i<4;i++)
{
        A0[i] = new int[4];
        B0[i] = new int[4];
        for(int j=0;j<4;j++)
        {
                A0[i][j] = a0[i][j];
                B0[i][j] = b0[i][j];
        }
}




const int order_a_1 = 4;
const int order_b_1 = 4;
const int order_J = 3;
const int order_I = 3;
const int order_Q = 3;
bool c;
c = Had_4x3n_generate(A0,order_a_1,B0,order_b_1,J3,order_J,Q,order_Q,I3,order_I);
cout<<c<<endl;
}

bool Had_4x3n_generate(int** a_n,const int order_a_n, int** b_n,const int order_b_n, int** J,const int order_J, int** Q,const int order_Q,int** I,const int order_I)
{
  int** a_n_1;
 int**  b_n_1;
 print(a_n, order_a_n);
 print(b_n, order_b_n);
a_n_1 = Kronecker(b_n,I,order_b_n,order_I);

	print(a_n_1,(order_b_n*order_I));

	cout<<"_________"<<endl;
b_n_1 = Add(Kronecker(a_n,J,order_a_n,order_J),Kronecker(b_n,Q,order_b_n,order_Q),(order_a_n*order_J),(order_b_n*order_Q));

	print(b_n_1,(order_b_n*order_I));

	cout<<"_________"<<endl;



int **H;
int **H_dash;
int order=0;
if((order_b_n*order_I) != (order_a_n*order_J))
{
        cout<<"Something's wrong with the orders"<<endl;
        return 0;
}
else
{
        order = order_b_n*order_I;
        H= Add(a_n_1,b_n_1,order,order);
        H_dash = Add(a_n_1,negative_matrix(b_n_1,order),order,order);
	print(H,order);
	cout<<"________________________"<<endl;
	print(H_dash,order);
	bool check = check_Hadamard(Hadamard_product(H,H_dash,order),order);
        return check;
}

}

