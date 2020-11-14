#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <string.h>
#include "func.h"
float readNum(int *i,char str[]){//func that read number and make him
	// a float number ;
	int j=0;
	char strN[80];
	while (str[*i]!='*'&&str[*i]!='\0'){
		strN[j]=str[*i];
		(*i)++;
		j++;
	}
	float f=atof(strN);
	int t;
	for (t=0;str[t]!='\0';t++)
		strN[t]='\0';
	return f;
}

void cleanBuffer(){
	int c;
	do{
		c=getchar();
	}while(c!=EOF&&c!='\n');
}
Equation* dealEquation(int count){//divide the equation
	//to numbers and
	//and variables ,and return equation.
	Equation* e;
	e=(Equation*) malloc(sizeof(Equation));
	e->A=(float*) malloc(count* sizeof(float));
	e->count=count;
	int x=0,y=1,z=2;
	if (e->count==3)//default 0;
		{
		*((e->A)+x)=0;
		*((e->A)+y)=0;
		*((e->A)+z)=0;
		}else if (e->count==2){
			*((e->A)+x)=0;
			*((e->A)+y)=0;
		}else *((e->A)+x)=0;



	float ans;

	char str[80];
	cleanBuffer();
	printf ("enter equation: ");
	gets(str);




	int i=0;
	while (str[i]!='\0'){
		if (str[i]=='+')
			i++;
		if ((str[i]!='x')&&(str[i]!='y')&&str[i]!='z')
			ans=readNum(&i,str);
		if (str[i]=='x')
			*((e->A)+x)=ans;
		else if (str[i]=='y')
			*((e->A)+y)=ans;
		else if (str[i]=='z')
			*((e->A)+z)=ans;
		if (str[i+1]=='='){
			i+=2;
			e->B=readNum(&(i),str);//get the answer to b vec
			break;
		}
    i++;
	}
	return e;
}
void printMatrix(Solver f){//print the matrix
	int i,j;
	printf("matrix A : \n");
	for (i=0;i<f.count;i++){
		for(j=0;j<f.count;j++)
			printf("  %.3f  ",*((*(f.A_Mat+i))+j));
		printf("\n");
	}

}

void printBVec(Solver f){//print B vec
	int i;
	printf("vector B: \n");
	for (i=0;i<f.count;i++){
		printf("  %.3f \n",*(f.B_Vec+i));
	}
}

float determin(Solver f){//calculate the determinent of any case .
	if (f.count==3){
		float a1,a2,a3,b1,b2,b3,c1,c2,c3;
		a1=f.A_Mat[0][0];
		a2=f.A_Mat[1][0];
		b1=f.A_Mat[0][1];
		b2=f.A_Mat[1][1];
		a3=f.A_Mat[2][0];
		b3=f.A_Mat[2][1];
		c1=f.A_Mat[0][2];
		c2=f.A_Mat[1][2];
		c3=f.A_Mat[2][2];
		return ((a1*((b2*c3)-(c2*b3)))-(b1*((a2*c3)-
				(c2*a3)))+(c1*((a2*b3)-(b2*a3))));
	}else if (f.count==2){
		float a1,a2,b1,b2;
		a1=f.A_Mat[0][0];
	    a2=f.A_Mat[0][1];
	    b1=f.A_Mat[1][0];
	    b2=f.A_Mat[1][1];
		return (a1 * b2)-(a2 * b1);

	}
      return *((*(f.A_Mat+0))+0);
}
void findXVec(Solver* f,int numEqu){//find the oposite of the matrix by
	//calculate the minor of each ,and solve the equations.
		if(numEqu==3){
			float inverseMat[3][3];
			for(int i=0;i<numEqu;i++){
				for(int j=0;j<numEqu;j++){
					inverseMat[i][j]=((f->A_Mat[(j+1)%3][(i+1)%3] * f->A_Mat[(j+2)%3][(i+2)%3]) -
							(f->A_Mat[(j+1)%3][(i+2)%3] * f->A_Mat[(j+2)%3][(i+1)%3]))/ f->determin;
				}
			}
			for(int i=0;i<numEqu;i++){
				for(int j=0;j<numEqu;j++){
					f->X_Vec[i]+=inverseMat[i][j]*f->B_Vec[j];
				}
			}
		}
		if(numEqu==1){
			f->X_Vec[0]=f->B_Vec[0]/f->A_Mat[0][0];
		}
		if(numEqu==2){
			float tmp=f->A_Mat[0][0]/f->determin;
			f->A_Mat[0][0]=f->A_Mat[1][1]/f->determin;
			f->A_Mat[1][1]=tmp;
			f->A_Mat[0][1]=0-f->A_Mat[0][1]/f->determin;
			f->A_Mat[1][0]=0-f->A_Mat[1][0]/f->determin;
			for(int i=0;i<numEqu;i++){
				for(int j=0;j<numEqu;j++)
					f->X_Vec[i]+=f->A_Mat[i][j]*f->B_Vec[j];
			}
		}
	}
