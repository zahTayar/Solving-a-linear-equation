
/*
 * main.c
 *
 *
 *  Author: Zah Tayar
 *  
 */
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <string.h>
#include "func.h"	
int main(void) {


		AllEquations all;
		Solver s;
		// gete number of equations

		printf ("enter number of equations: (1-3)\n");
		scanf("%d",&all.count);
		if (all.count<1||all.count>3){
			printf("wrong number \n please try again \n");
			printf ("enter number of equations: (1-3)\n");
					scanf("%d",&all.count);

		}


		int i;
		s.count=all.count;
		s.A_Mat=(float**) malloc(all.count * sizeof(float*));//make place in the memory
		s.B_Vec=(float*) malloc((3)* sizeof(float));//make place in the memory
		s.X_Vec=(float*) malloc((3)* sizeof(float));//make place in the memory
		all.eqArr=(Equation**) malloc(all.count*sizeof(Equation*));//make place in the memory
		for (i=0;i<all.count;i++){//get equation and B vec
			*(all.eqArr+i)=dealEquation(all.count);
			*(s.B_Vec+i)=((*(all.eqArr+i))->B);
			*(s.A_Mat+i)=((*(all.eqArr+i))->A);
		}
		printMatrix(s);
		printBVec(s);
		s.determin=determin(s);
		printf ("Determinant : %.3f\n",s.determin);
		findXVec(&s,s.count);
		if (s.determin==0)
			printf("the matrix don't have solution or there is many solutions\n");
		else      { printf("Vector X : \n");
        for(int i=0;i<s.count;i++)
            printf("\t%.3f\n",s.X_Vec[i]);
    }
		free(s.A_Mat);
		free(s.B_Vec);
		free(s.X_Vec);
		free(all.eqArr);




	}

