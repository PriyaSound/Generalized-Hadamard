#include<iostream>
#include<math.h>
using namespace std;
const int s=8;
const int k=3;
class polynomial
{
	public:
	int coeff[k];
	int index;
	void compute_index()
	{
		int c=0;
		for(int i=0;i<k;i++)
		{
			c = c + coeff[i]*pow(2,i);
		}
	        index = c;
	}
};
polynomial p[s][s];
polynomial row[s];

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



void print_row()
{
	for(int i=0;i<s;i++)
	{
		for(int j=0;j<k;j++)
		{
		 	cout<<row[i].coeff[j]<<"T^"<<j<<" + ";
		}
		cout<<"|";
	}
}



void generate_GH()
{
  int c;
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



void print_matrix()
{
	cout<<endl;
	cout<<"_________________________________"<<endl;
	for(int ind_i=0;ind_i<s;ind_i++)
	{
		for(int ind_j=0;ind_j<s;ind_j++)
			{
					
			cout<<p[ind_i][ind_j].index<<" ";
			//		for(int j=0;j<k;j++)
			//		{	
		 	//			cout<<p[ind_i][ind_j].coeff[j]<<"T^"<<j<<" + ";
			//		}
			//		cout<<"|";
			}
		cout<<endl;
	}

}
			
		
int main()		
{
	fill_row();
	print_row();
	generate_GH();
	print_matrix();
}

