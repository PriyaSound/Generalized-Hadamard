#include<iostream>
using namespace std;

// Global variable declarations. Put them all here.

//The Generalized Hadamard matrix we're constructing.
int GH[8][8]={{1,1,1,1,1,1,1,1}};
//Each row has 8 possibilities. These possibilities are put in 8 matrices numbered di, where i is the row number.
int d0[8][9]={{1,1,1,1,1,1,1,1,1}};
int d1[8][9]={{1,1,2,3,4,5,6,7,8}}; // Row 1 and 2 are not needed I guess
int d2[8][9]={{1,1,3,7,5,2,4,8,6},{1,1,3,5,7,6,8,2,4},{1,1,3,7,5,6,8,4,2},{1,1,3,5,7,4,2,8,6},{1,1,3,8,6,7,5,2,4},{1,1,3,6,8,7,5,4,2},{1,1,3,6,8,2,4,5,7},{1,1,3,8,6,4,2,5,7}};
int d3[8][9]={{1,1,4,6,7,8,5,3,2},{1,1,4,7,6,8,5,2,3},{1,1,4,6,7,3,2,8,5},{1,1,4,7,6,2,3,8,5},{1,1,4,8,5,3,2,6,7},{1,1,4,5,8,2,3,6,7},{1,1,4,5,8,6,7,2,3},{1,1,4,8,5,6,7,3,2}};
int d4[8][9]={{1,1,5,7,3,8,4,2,6},{1,1,5,7,3,4,8,6,2},{1,1,5,6,2,8,4,3,7},{1,1,5,2,6,4,8,3,7},{1,1,5,4,8,7,3,6,2},{1,1,5,4,8,3,7,2,6},{1,1,5,6,2,3,7,8,4},{1,1,5,2,6,7,3,8,4}};
int d5[8][9]={{1,1,6,8,3,7,4,2,5},{1,1,6,8,3,4,7,5,2},{1,1,6,2,5,3,8,4,7},{1,1,6,5,2,8,3,4,7},{1,1,6,5,2,4,7,8,3},{1,1,6,2,5,7,4,8,3},{1,1,6,4,7,8,3,5,2},{1,1,6,4,7,3,8,2,5}};
int d6[8][9]={{1,1,7,2,8,6,4,5,3},{1,1,7,4,6,2,8,3,5},{1,1,7,4,6,8,2,5,3},{1,1,7,8,2,6,4,3,5},{1,1,7,5,3,2,8,6,4},{1,1,7,5,3,8,2,4,6},{1,1,7,2,8,3,5,4,6},{1,1,7,8,2,3,5,6,4}};
int d7[8][9]={{1,1,8,4,5,6,3,7,2},{1,1,8,5,4,6,3,2,7},{1,1,8,4,5,7,2,6,3},{1,1,8,5,4,2,7,6,3},{1,1,8,6,3,7,2,4,5},{1,1,8,3,6,2,7,4,5},{1,1,8,3,6,4,5,2,7},{1,1,8,6,3,4,5,7,2}};


int group_product[8][8];
const int n=8;
bool inserted_rows[8]={true,false,false,false,false,false,false,false};


// Function prototypes.
void insert_GH_row(int,int);
void assign_incompatible_choices(int,int);




  //Create two matrices h, k whose Kronecker product you must find. Generate the bigger Hadamard matrix and use that to find the group products. Right now I'm just going to input values directly. 
void generalized_kronecker_product()
{
}

//This function computes the group product for the rows 0-7.
void assign_group_product()
{
		  group_product[0][0]=group_product[1][1]=group_product[2][2]=group_product[3][3]=group_product[4][4]=group_product[5][5]=group_product[6][6]=group_product[7][7]=1;
		for(int i=0;i<=7;i++)
		{
		  group_product[0][i]=i+1;
		  group_product[i][0]=i+1;
		}

		group_product[2][3]=group_product[4][5]=group_product[6][7]=2;
		group_product[5][7]=group_product[4][6]=group_product[1][3]=3;
		group_product[4][7]=group_product[5][6]=group_product[1][2]=4;
		group_product[3][7]=group_product[2][6]=group_product[1][5]=5;
		group_product[3][6]=group_product[1][4]=group_product[2][7]=6;
		group_product[1][7]=group_product[2][4]=group_product[3][5]=7;
		group_product[1][6]=group_product[2][5]=group_product[3][4]=8;
       
        for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
				{
						group_product[j][i]=group_product[i][j];
				}




}

void print_group_product()
{
		for(int i=0;i<8;i++)
		{
				for(int j=0;j<8;j++)
				{
						cout<<group_product[i][j]<<" ";
				}
				cout<<endl;
		}
}

//This class contains an array. The array has 8 blocks. Each block represents the element that cannot appear at that matrix position in the GH matrix. 
class incompatible_choices
{
 public:
 bool a[8];
 incompatible_choices()
 {
 a[0]=true; 
 for(int i=1;i<8;i++)
  {
    a[i]=false;
  }

 }

};

incompatible_choices p[6][6];
int (*di)[9];
void return_row(int i)
{

 if(i==0)
 di = d0;

 else if(i==1)
 di = d1;

 else if(i==2)
  di = d2;
else if(i==3)
  di = d3;
 else if(i==4)
  di = d4;
 else if(i==5)
  di = d5;
else if(i==6)
  di = d6;
else if(i==7)
  di = d7;

} 

  

//Checks if there are any remaining possibilities for row i. If there are none, returns true, otherwise false.
bool check_if_possibility_stack_empty(int i)
{
   return_row(i);	
	for(int j=0;j<8;j++)
	{
		if(di[j][0]==1)
			{
               cout<<di[j][0]<<" ";
               return false;
			
            
		    }
	}
	return true;
}

//Removes possibility number k from row i.
void remove_possibility(int k, int i)
{
   return_row(i);	
	
   di[k][0]=-1;
}


void print_possibility(int a[8][9])
{
  for(int i=0;i<8;i++)
  {
		 for(int j=0;j<9;j++)
		 {
				cout<<a[i][j]<<" ";
		 }
	 cout<<endl;
  }
cout<<endl;
}

void print_compatibility()
{
		for(int i=0;i<6;i++)
		{
				for(int j=0;j<6;j++)
				{
						for(int k=0;k<8;k++)
						{
						     cout<<p[i][j].a[k]<<" ";
						}
						cout<<"___";
				}
				cout<<endl;
		}
}
//Goes through each possibility stack and checks to see if any of the possibilities are incompatible after the recent computation of the incompatibility matrix p. 
bool check_possibilities()
{
  bool c;
  for(int i=0;i<6;i++)
  {
		  if(inserted_rows[i+2]==false)
		  { 
				  return_row(i+2);
				   for(int j=0;j<6;j++)
					{
							  for(int k=0;k<8;k++)
							  { 
								  
								if(di[k][0]==1)
								{
								   if(p[i][j].a[di[k][j+3]-1]==true)
									 { 
										    cout<<" Possibility "<<k<<" of row "<<i+2<<endl;
											 remove_possibility(k,i+2);
										 
									 }
								}

							  }
								print_compatibility();						 
							  //Check if possibility stack is empty, if so return false.
							  c = check_if_possibility_stack_empty(i+2);
							  cout<<"Is stack empty?"<<c<<endl;
							  if(c==true)
								{
									return false;
								}
						   
					}
		  }
 }
return true;
}
//Checks if the possibility stack has only one value remaining.
int check_if_possibility_stack_onevalue(int i)
{
		int count=0,pos=0;
        return_row(i);				
		for(int j=0;j<8;j++)
		{
				if(di[j][0]==1)
				{
						count++;
						pos=j;
				}
		}
		if(count==1)
				return pos;
		else
				return -1;
}

//Inserts the kth possibility of the ith row in the Generalized Hadamard matrix.
void print_GH_matrix()
{
 for(int i=0;i<8;i++)
 {
  for(int j=0;j<8;j++)
  {
		  cout<<GH[i][j]<<" ";
  }
  cout<<endl;
 }
}



//This initializes p.
void initialize_p()
{
  for(int i=0;i<6;i++)
  {
		  for(int j=0;j<6;j++)
		  {
				  p[i][j].a[i+2]=true;
				  p[i][j].a[j+2]=true;
		  }
  }

}

void array_incompatible_choices(int ins, int k)
{
  int value,rem;
          return_row(ins);
		  for(int i=0;i<6;i++)
		  { 
			if(inserted_rows[i+2]==false)
			{
				  value=group_product[i+2][di[k][2]-1];	
				  for(int j=0;j<6;j++)
					 {
					   rem = group_product[value-1][di[k][3+j]-1];
					   p[i][j].a[rem-1] = true;
					   if(i==5) cout<<"rem "<<rem<<endl;
					   p[i][j].a[di[k][3+j]-1] = true; 
					   //remove those elements that belong to that row in the first two column and the first two rows of that column
					 }
		  //I must create a stack that represents all the rows that have been added. These rows need not be touched later on.
			}


		  }

                  bool check = check_possibilities();
				   if(check == false)
					{
					 cout<<"This row cannot be inserted"<<endl;
					 return;
					}
                     print_possibility(d0);
										
								        print_possibility(d1);

								        print_possibility(d2);
								        print_possibility(d3);

								        print_possibility(d4);


								        print_possibility(d5);


								        print_possibility(d6);

								        print_possibility(d7);


		  cout<<"Possibilities have been checked"<<endl;

//Somewhere I must check for the rows that have only one possibility remaining. In that case, that possibility
//has to be inserted.
  int c;
  for(int k=2;k<8;k++)
  {
       if(inserted_rows[k]==false)
	   {
		  c = check_if_possibility_stack_onevalue(k);
		  if(c!=-1)
		  {
			      cout<<"Something"<<endl;
				  insert_GH_row(k,c);
		  }
	   }
  }

  print_possibility(d1);

}

           
void insert_GH_row(int i,int k)
{
 return_row(i);
 for(int j=0;j<8;j++)
 {
    GH[i][j] = di[k][j+1];
 }
 inserted_rows[i]=true;
 print_GH_matrix();
 array_incompatible_choices(i,k);
 //Print the GH matrix.

}



int main()
{
int c=1;

initialize_p();

assign_group_product();

print_group_product();

insert_GH_row(1,0);

return 0;
}


