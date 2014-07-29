#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <stdio.h>      /* printf */
#include <math.h>
using namespace std;

const int s=32;//size of our matrix in the form of 2^k
const int s2 = s*s;
const int k=5;//k

//This program takes a GH matrix of order 2^n, converts each entry to its binary equivalent, then makes n different Hadamard matrices by splitting the n entries
//and checks if the product of any two/three of the Hadamard matrices is Hadamard.

class polynomial
{
        public:
        int coeff[k];
        int index;
        void compute_index()
        {
                int c=1;
                for(int i=0;i<k;i++)
                {
                        c = c + coeff[i]*pow(2,i);
                }
                index = c;
        }
	void compute_coeff()
	{
		int c = index;
		int i=0,binary;
		while(i<k)
		{
			binary = c%2;
			coeff[i] = binary;
			c=c/2;
			i++;
		}
	}

};

polynomial p[s][s];
polynomial row[s];
int c1[s][s] = {{1,1,1,1,1,1,1,1},{1,2,3,4,5,6,7,8},{1,3,5,7,4,2,8,6},{1,4,7,6,8,5,2,3},{1,5,4,8,7,3,6,2},{1,6,2,5,3,8,4,7},{1,7,8,2,6,4,3,5},{1,8,6,3,2,7,5,4}};
int c2[s][s] = {{1,1,1,1,1,1,1,1},{1,2,3,4,5,6,7,8},{1,3,5,7,6,8,2,4},{1,4,7,6,2,3,8,5},{1,5,6,2,8,4,3,7},{1,6,8,3,4,7,5,2},{1,7,2,8,3,5,4,6},{1,8,4,5,7,2,6,3}};
int c3[s][s] = {{1,1,1,1,1,1,1,1},{1,2,3,4,5,6,7,8},{1,3,7,5,6,8,2,4},{1,4,5,8,2,3,6,7},{1,5,6,2,3,7,8,4},{1,6,8,3,7,4,2,5},{1,7,4,6,8,2,5,3},{1,8,2,7,4,5,3,6}};

void fill_p()
{
	for(int i=0;i<s;i++)
	{
		for(int j=0;j<s;j++)
		{
			p[i][j].index = (c3[i][j]-1);
			p[i][j].compute_coeff();
		}
	}
}

void print_p_coeff()
{
	for(int i=0;i<s;i++)
	{
		for(int j=0;j<s;j++)
		{
			for(int l=0;l<k;l++)
			{
				cout<<p[i][j].coeff[l]<<" ";
			}
			cout<<"    ";
		}
		cout<<endl;
	}
}

void print_p_index()
{
	for(int i=0;i<s;i++)
	{
		for(int j=0;j<s;j++)
		{
			cout<<p[i][j].index<<" ";
		}
		cout<<endl;
	}
}
void fill_row()
{
        int n;
        bool binary;
        int i;
        for(int ind=0;ind<s;ind++)
        {
                i=0;
                n=ind;
                while(i<=k)
                {
                   binary = n%2;
                   n=n/2;
                   row[ind].coeff[i]=binary;
                   i++;
                }
        }
}


int** generate_Hadamard_from_triple(int n)
{
	int**c = new int*[s];
	for(int i=0;i<s;i++)
	{
		c[i] = new int[s];
	}
	for(int j=0;j<s;j++)
	{
		for(int k=0;k<s;k++)
		{
			if(p[j][k].coeff[n]==0)
				c[j][k]=1;
			else if(p[j][k].coeff[n]==1)
				c[j][k]=-1;
		}
	}
	return c;
}


int inner_product(int* a,int* b, int n)
{
  int sum=0;
  for(int i=0;i<n;i++)
   {
        sum = sum + a[i]*b[i];
   }
  return(sum);
}
bool check_symmetric(int** p, int n)
{
        for(int i=0;i<n;i++)
        {
                for(int j=0;j<n;j++)
                {
                        if(p[i][j]!=p[j][i])
                                return false;
                }
        }
        return true;
}


bool check_Hadamard(int** a, int n)
{
        int value = a[0][0];
        for(int i=0;i<n;i++)
        {
                for(int j=0;j<n;j++)
                {
                        if(a[i][j]!=value && a[i][j]!=-value)
                                return false;
                }
        }
        for(int i=0;i<n;i++)
        {
                for(int j=i+1;j<n;j++)
                {
                        if(inner_product(a[i],a[j],n)!=0)
                        {
                               return false;
                        }
                }
        }
        return true;
}

int** matrix_multiplication(int** a,int** b)
{

   int** c =new int*[s];
   for(int i=0; i < s; i++)
   {
      c[i] = new int[s];
   }
   for(int i = 0; i < s; i++)
   {
      for(int j = 0; j < s; j++)
      {

          c[i][j]=a[i][j]*b[i][j];
      }
   }
   return (c);
}



void generat_GH()
{
   int c;
   if(s!=2)
   {
   for(int ind_i=0;ind_i<s;ind_i++)
   {
      for(int ind_j=0;ind_j<s;ind_j++)
      {
         for(int i=0;i<k;i++)
         {
            for(int j=0;j<k;j++)
            {
               c = row[ind_i].coeff[i]*row[ind_j].coeff[j];
               if((i+j)<k)
                  p[ind_i][ind_j].coeff[i+j]=(p[ind_i][ind_j].coeff[i+j]+c)%2;
               else
               {
                  p[ind_i][ind_j].coeff[(i+j)-k+1] = (p[ind_i][ind_j].coeff[(i+j)-k+1] + c)%2;
                  p[ind_i][ind_j].coeff[(i+j)-k] = (p[ind_i][ind_j].coeff[(i+j)-k] +c)%2;
               }
            }
         }
         p[ind_i][ind_j].compute_index();
      }
   }
   }
   else
   {
      p[0][0].index=1;
      p[0][1].index=1;
      p[1][0].index=1;
      p[1][1].index=2;
   }

}

//Print functions
/*
void print(const int a[s][s])
{
     for(int i=0;i<s;i++)
   {
      for(int j=0;j<s;j++)
         cout<<a[i][j]<<" ";
      cout<<endl;
   }
}
void print(int b[s][s][s])
{
   for(int l=0; l < s; l++)
   {
   for(int i=0;i<s;i++)
   {
      for(int j=0;j<s;j++)
         cout<<b[l][i][j]<<" ";
      cout<<endl;
   }
   cout<<endl;
   cout<<"______________"<<endl;
   }
}

void print(int b[s][s2][s2])
{
   for(int l=0; l <s ; l++)
   {
   for(int i=0;i<s2;i++)
   {
      for(int j=0;j<s2;j++)
         cout<<b[l][i][j]<<" ";
      cout<<endl;
   }

   cout<<"_________________________________________________________________________"<<endl;
     cout<<endl;
   }
}


void print(int b[s][s2][s2], int y)
{

   for(int i=0;i<s2;i++)
   {
      for(int j=0;j<s2;j++)
         cout<<b[y][i][j]<<" ";
      cout<<endl;
   }


}

void print1(int a[2*s][2*s])
{
     for(int i=0;i<2*s;i++)
   {
      for(int j=0;j<2*s;j++)
         cout<<a[i][j]<<" ";
      cout<<endl;
   }
}
*/

void print(int** a)
{
    for(int i=0;i<s;i++)
   {
      for(int j=0;j<s;j++)
      {
             
	      cout<<a[i][j]<<" ";
	     
	    	 }
      cout<<endl;
   }
}
int** Trans(int** a,const  int n)
{
int** c =new int*[n];
   for(int i=0; i < n; i++)
   {
      c[i] = new int[n];
   }
   for(int i = 0; i < n; i++)
   {
      for(int j = 0; j < n; j++)
      {
         c[i][j]= a[j][i];
      }
   }

   return c;
}


int main()
{
   fill_row();
   generat_GH();
   // fill_p();
   //print_p();
   int count=0;
   int** c= new int*[s];
   for(int i=0;i<s;i++)
   {
	   c[i] = new int[s];
   }
	for(int i=0;i<s;i++)
	{
		for(int j =0;j<s;j++)
		{
			c[i][j]=1;
		}
	}
/*
   for(int i=0;i<k;i++)
   {
	   for(int j=i+1;j<k;j++)
	   {
		 
		  if(check_Hadamard(generate_Hadamard_from_triple(i)) && check_Hadamard(generate_Hadamard_from_triple(j)))
		  {
			  cout<<"Matrix "<<i<<endl;
		  	  print((generate_Hadamard_from_triple(i)));
			  cout<<"*"<<endl;
		  	  cout<<"Matrix "<<j<<endl;
			  print((generate_Hadamard_from_triple(j)));
		  	  cout<<"       = "<<endl;
		  	  print(matrix_multiplication(generate_Hadamard_from_triple(i),generate_Hadamard_from_triple(j)));
		 
		  if( check_Hadamard(matrix_multiplication(generate_Hadamard_from_triple(i),generate_Hadamard_from_triple(j))))
		  {
			  cout<<"True"<<endl;
		  }
		  else
		  {
			  cout<<"False"<<endl;
		  }
		  }
		  else
			  cout<<"Either Matrix "<<i<<" or Matrix "<<j<<" is not Hadamard"<<endl;
	         
		   if(check_Hadamard(generate_Hadamard_from_triple(i)) && check_Hadamard(generate_Hadamard_from_triple(j)) && check_Hadamard(matrix_multiplication(generate_Hadamard_from_triple(i),generate_Hadamard_from_triple(j))))
		   {
			   ++count;
		   }
		  
	   }
   }
  */
	int** prod1;
	int** prod2;
	for(int i=0;i<k;i++)
	{
		prod1=generate_Hadamard_from_triple(i);
		for(int j=i+1;j<k;j++)
		{
			prod2 = generate_Hadamard_from_triple(j);
			cout<<check_Hadamard(matrix_multiplication(prod1,Trans(prod2,s)),s);
		//	print(matrix_multiplication(prod1,Trans(prod2,s)));
			cout<<endl;
			
		}

	}
cout<<"______________________________"<<endl;		
   for(int i=0;i<k;i++)
   {
	   c = matrix_multiplication(c,generate_Hadamard_from_triple(i));
   }
   print(c);
   cout<<endl;
   if(check_Hadamard(c,s)==true)
   {
	   cout<<"The product of all the Hadamard matrices is Hadamard"<<endl;
   }

   cout<<"Count for s = "<<s<<" and k = "<<k<<" is "<<count<<endl;
}

