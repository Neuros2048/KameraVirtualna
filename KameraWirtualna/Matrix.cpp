#include "Matrix.h"
#include <iostream>
# define M_PI 3.14159265358979323846
Matrix::Matrix(int n,int m){
	this->n = n;
	this->m = m;
	pola = static_cast<double**>(malloc(sizeof(double*) * n));
	for (int i = 0; i < n; i++) {
		pola[i] = static_cast<double*>(malloc(sizeof(double) * m));
		for(int j =0 ; j < m ; j++)
		{
			pola[i][j] = 0;
		}
	}
}
Matrix::~Matrix(){
	for (int i = 0; i < n; i++) {
		free(pola[i]);
	}
	free(pola);
}

int Matrix::get_n() const
{
	return n;
}

auto Matrix::get_m() const -> int
{
	return m;
}

void Matrix::operator+=(const Matrix &B) const
{
	if(n!= B.get_n() && m != B.get_m())
	{
		return ;
	}
	for(int i = 0 ; i< n ; i++)
	{
		for (int j = 0 ; j < m ; j++)
		{
			this->operator[](i)[j] += B[i][j];
		}
	}
}

void Matrix::operator-=(const Matrix &B) const
{
	if(n!= B.get_n() && m != B.get_m())
	{
		return ;
	}
	for(int i = 0 ; i< n ; i++)
	{
		for (int j = 0 ; j < m ; j++)
		{
			this->operator[](i)[j] -= B[i][j];
		}
	}
}

void Matrix::operator*=(const Matrix &B)
{
	if(m!= B.get_n())
	{
		return ;
	}
	Matrix matrix {n,B.get_m()};
	for(int i = 0 ; i< n ; i++)
	{
		for (int j = 0 ; j < B.get_m() ; j++)
		{
			for(int k =0 ; k < m;k++)
			{
				matrix[i][j] += this->operator[](i)[k] * B[k][j];
			}
			
		}
	}
	this->free_pola(n,B.get_m());
	for(int i = 0 ; i< n ; i++)
	{
		for (int j = 0 ; j < B.get_m() ; j++)
		{
			this->operator[](i)[j] = matrix[i][j];
		}
	}
}


void Matrix::multiplication(const Matrix& A, const Matrix& B)
{
	if(A.get_m() != B.get_n() && this->get_n() != A.get_n()&&this->get_m() != B.get_m())
	{
		return ;
	}
	for(int i = 0 ; i< A.get_n() ; i++)
	{
		for (int j = 0 ; j < B.get_m() ; j++)
		{
			pola[i][j] = 0;
			for(int k =0 ; k < A.get_m();k++)
			{
				this->pola[i][j] += A[i][k] * B[k][j];
			}
			
		}
	}
	
}

void Matrix::addition(const Matrix& A, const Matrix& B)
{
	if(A.get_m() != B.get_m()&& A.get_n() != B.get_n() && this->get_n() != A.get_n()&&this->get_m() != B.get_m())
	{
		return ;
	}
	for(int i = 0 ; i< A.get_n() ; i++)
	{
		for (int j = 0 ; j < B.get_m() ; j++)
		{
			this->pola[i][j] = A[i][j] + B[i][j];
		}
	}
}

void Matrix::subtraction(const Matrix& A, const Matrix& B)
{
	if(A.get_m() != B.get_m()&& A.get_n() != B.get_n() && this->get_n() != A.get_n()&&this->get_m() != B.get_m())
	{
		return ;
	}
	for(int i = 0 ; i< A.get_n() ; i++)
	{
		for (int j = 0 ; j < B.get_m() ; j++)
		{
			this->pola[i][j] = A[i][j] - B[i][j];
		}
	}
}

void Matrix::dot_prodact(const Matrix& A, const Matrix& B)
{
	if( !(A.get_m() == 1 && B.get_m()  == 1 && A.get_n() == B.get_n()) )
	{
		return;
	}
	for(int i =0 ; i< A.get_n(); i++)
	{
		this->pola[i][0] = A[i][0] * B[i][0];
	}
}

std::ostream& operator<<(std::ostream& os, Matrix const& A)
{
	for(int i =0 ; i< A.get_n() ; i++)
	{
		for(int j = 0 ; j<A.get_m() ; j++)
		{
			os << A[i][j] << " ";
		}
		os << '\n';
	}
	return os;
}

double* Matrix::operator[](int i) const
{
	return pola[i];
}

void Matrix::free_pola(int n , int m)
{
	for (int i = 0; i < this->n; i++) {
		free(pola[i]);
	}
	free(pola);
	this->n = n;
	this->m = m;
	pola = static_cast<double**>(malloc(sizeof(double*) * n));
	for (int i = 0; i < n; i++) {
		pola[i] = static_cast<double*>(malloc(sizeof(double) * m));
		for(int j =0 ; j < m ; j++)
		{
			pola[i][j] = 0;
		}
	}
}


void Matrix::set_matrix_4_to(MatrixType type, double val)
{
	if(this->n != 4 || this->m != 4) return;
	for (int i = 0; i < n; i++) {
		for(int j =0 ; j < m ; j++)
		{
			pola[i][j] = 0;
		}
		pola[i][i] = 1;
	}
	
	switch (type)
	{
		case Jednostkowa:
			break;
		case obrotPrawo:
			pola[0][0] = cos(M_PI*val/180);
		    pola[2][2] = cos(M_PI*val/180);
			pola[0][2] = sin(M_PI*val/180);
			pola[2][0] = -sin(M_PI*val/180);
			break;
		case obrotLewo:
			val*=-1;
			pola[0][0] = cos(M_PI*val/180);
			pola[2][2] = cos(M_PI*val/180);
			pola[0][2] = sin(M_PI*val/180);
			pola[2][0] = -sin(M_PI*val/180);
			break;
		case ruchprawo:
			pola[0][3] = val;
			break;
		case ruchlewo:
			pola[0][3] = -val;
			break;
		case ruchgora:
			pola[1][3] = val;
			break;
		case ruchdol:
			pola[1][3] = -val;
			break;
		case ruchprzod:
			pola[2][3] = val;
			break;
		case ruchtyl:
			pola[2][3] = -val;
			break;
		case obrotdol:
			val*=-1;
			pola[1][1] = cos(M_PI*val/180);
			pola[2][2] = cos(M_PI*val/180);
			pola[1][2] = -sin(M_PI*val/180);
			pola[2][1] = sin(M_PI*val/180);
			break;
		case obrotgora:
			pola[1][1] = cos(M_PI*val/180);
			pola[2][2] = cos(M_PI*val/180);
			pola[1][2] = -sin(M_PI*val/180);
			pola[2][1] = sin(M_PI*val/180);
			break;
		case obrotZlewo:
			val*=-1;
			pola[0][0] = cos(M_PI*val/180);
			pola[1][1] = cos(M_PI*val/180);
			pola[0][1] = -sin(M_PI*val/180);
			pola[1][0] = sin(M_PI*val/180);
			break;
		case obrotZprawo:
			pola[0][0] = cos(M_PI*val/180);
			pola[1][1] = cos(M_PI*val/180);
			pola[0][1] = -sin(M_PI*val/180);
			pola[1][0] = sin(M_PI*val/180);
			break;
	}
}

void Matrix::swap(Matrix& A)
{
	if(n!= A.get_n() && m != A.get_m())
	{
		return ;
	}
	double** tmpp;
	tmpp = this->pola;
	this->pola = A.pola;
	A.pola = tmpp;
	return;
	double tmp;
	for(int i = 0 ; i< n ; i++)
	{
		for (int j = 0 ; j < m ; j++)
		{
			tmp =  pola[i][j];
			pola[i][j] = A[i][j];
			A[i][j] = tmp;
		}
	}
}

void Matrix::normalize()
{
	if(m!= 1) return;
	double nor = pola[n-1][0];
	for(int i = 0 ; i < n ; i++)
	{
		pola[i][0]/= nor;
	}
}

// niepotrzeby kod rodzacy problemyu
/*
Matrix operator+(const Matrix &A, const Matrix &B)
{
	if(A.get_n()!= B.get_n() && A.get_m() != B.get_m())
	{
		Matrix zero(0,0);
		return zero;
		//return {0,0};
	}
	Matrix matrix {A.get_n(),B.get_m()};
	for(int i = 0 ; i< A.get_n() ; i++)
	{
		for (int j = 0 ; j < A.get_m() ; j++)
		{
			matrix[i][j] = A[i][j] + B[i][j];
		}
	}
	matrix.prepare_for_copy();
	return matrix;
}

Matrix operator-(const Matrix &A, const Matrix &B)
{
	if(A.get_n()!= B.get_n() && A.get_m() != B.get_m())
	{
		return {0,0};
	}
	Matrix matrix {A.get_n(),B.get_m()};
	for(int i = 0 ; i< A.get_n() ; i++)
	{
		for (int j = 0 ; j < A.get_m() ; j++)
		{
			matrix[i][j] = A[i][j] - B[i][j];
		}
	}
	matrix.prepare_for_copy();
	return matrix;
}

Matrix operator*(const Matrix &A, const Matrix &B)
{
	if(A.get_m() != B.get_n())
	{
		return {0,0};
	}
	Matrix matrix {A.get_n(),B.get_m()};
	for(int i = 0 ; i< A.get_n() ; i++)
	{
		for (int j = 0 ; j < B.get_m() ; j++)
		{
			for(int k =0 ; k < A.get_m();k++)
			{
				matrix[i][j] += A[i][k] * B[k][j];
			}
			
		}
	}
	matrix.prepare_for_copy();
	return matrix;
}
*/

/*
Matrix& Matrix::operator=( Matrix& A) const
{
	A.prepare_for_copy();
	std::cout << this->to_clear << " sss\n";
	return A;
}

Matrix& Matrix::operator=(const Matrix& A)
{
	
	std::cout << this->to_clear << " ss#@s\n";
	return *this;
}*/
/*
void Matrix::prepare_for_copy()
{
	this->to_clear =false;
}

void Matrix::prepare_for_delete()
{
	this->to_clear =true;
}*/