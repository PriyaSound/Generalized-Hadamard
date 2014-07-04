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

//Four circulant matrices of order 3.
int** circulant1 = new int*[3];
int** circulant2 = new int*[3];
int** circulant3 = new int*[3];
int** circulant4 = new int*[3];



//Produces the Kronecker product of circulant matrix and random matrix a.
int** new_constr(int** circulant,int order_circ, int** a,int order_a);
const int n = 4;

int** a;
int** b;
int** c;
int** d;
int main()
{
	
	int circ1[3][3] ={{1,1,-1},{-1,1,1},{1,-1,1}};
	int circ2[3][3] ={{-1,1,-1},{-1,-1,1},{1,-1,-1}};
	int circ3[3][3] ={{1,1,1},{1,1,1},{1,1,1}};
	int circ4[3][3] ={{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}};
	int a_source[n][n]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
	int b_source[n][n]={{0,1,0,0},{-1,0,0,0},{0,0,0,1},{0,0,-1,0}};
	int c_source[n][n]={{0,0,1,0},{0,0,0,-1},{-1,0,0,0},{0,1,0,0}};
	int d_source[n][n]={{0,0,0,1},{0,0,1,0},{0,-1,0,0},{-1,0,0,0}};

	circulant1 = initialize_matrix(&circ1[0][0],3,3);
	circulant2 = initialize_matrix(&circ2[0][0],3,3);
	circulant3 = initialize_matrix(&circ3[0][0],3,3);
	circulant4 = initialize_matrix(&circ4[0][0],3,3);
	a = initialize_matrix(&a_source[0][0],n,n);
	b = initialize_matrix(&b_source[0][0],n,n);
	c = initialize_matrix(&c_source[0][0],n,n);
	d = initialize_matrix(&d_source[0][0],n,n);

	int** matrix;
	int** matrix1;
	int** matrix2;	
	matrix = new_constr(circulant3,3,a,4);
	matrix = Add(matrix,new_constr(circulant2,3,b,4),3*n,3*n);
	matrix = Add(matrix,new_constr(circulant2,3,c,4),3*n,3*n);
	matrix = Add(matrix,new_constr(circulant2,3,d,4),3*n,3*n);
	matrix1 = matrix;
	int perm_array[12] ={1,0,3,2,5,4,7,6,9,8,11,10};
	matrix1 = matrix_multiplication(permutation(perm_array,12,1),matrix1,12);
	print(matrix1,3*n);
	cout<<"__________________"<<endl;
	cout<<(check_Hadamard(matrix1,3*n))<<endl;

	matrix = new_constr(circulant3,3,a,4);
        matrix = Add(matrix,new_constr(circulant1,3,b,4),3*n,3*n);
        matrix = Add(matrix,new_constr(circulant1,3,c,4),3*n,3*n);
        matrix = Add(matrix,new_constr(circulant1,3,d,4),3*n,3*n);
        print(matrix,3*n);
	cout<<"_________________"<<endl;
        cout<<(check_Hadamard(matrix,3*n))<<endl;
	matrix2 = matrix;

	
	polynomial** p;
	p = make_GH_from_H(matrix1, matrix2, 3*n, 2);
	print_p(p,3*n);
	cout<<check_Hadamard(Hadamard_product(matrix1,matrix2,3*n),3*n);
	return 0;
}

int** new_constr(int** circulant,int order_circ,int** a, int order_a)
{
	return(Kronecker(circulant,a,order_circ,order_a));
}



