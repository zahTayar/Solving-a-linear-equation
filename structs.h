//zah tayar	
//203133681
#pragma once
typedef struct
{
	int count;//number of coefficient
	float* A ;//coefficient x,y,z
	float B; //the number in the right side
}Equation;
typedef struct
{
	int count ;//number of equations
	Equation **eqArr;
}AllEquations;
typedef struct
{
	int count ;
	float ** A_Mat;
	float* B_Vec;
	float determin;
	float* X_Vec;
}Solver;
