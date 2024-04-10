#pragma once
#include <ostream>
enum MatrixType
{
	Jednostkowa,
	obrotPrawo,
	obrotLewo,
	obrotdol,
	obrotgora,
	obrotZlewo,
	obrotZprawo,
	ruchprawo,
	ruchlewo,
	ruchgora,
	ruchdol,
	ruchprzod,
	ruchtyl
};
class Matrix
{
public:
	Matrix(int n, int m);
	~Matrix();
	int get_n() const;
	int get_m() const;
	double* operator [] (int i) const;
	void operator+=(const Matrix &B) const;
	void operator-=(const Matrix &B) const;
	void operator*=(const Matrix &B);
	void multiplication(const Matrix &A, const Matrix &B);
	void addition(const Matrix &A, const Matrix &B);
	void subtraction(const Matrix &A, const Matrix &B);
	friend std::ostream &operator<<(std::ostream &os, Matrix const &A);
	void set_matrix_4_to(MatrixType type,double val);
	void swap(Matrix& A);
	void normalize();
	//friend Matrix operator+(const Matrix &A, const Matrix &B);
	//friend Matrix operator-(const Matrix &A, const Matrix &B);
	//friend Matrix operator*(const Matrix &A, const Matrix &B);
	//Matrix& operator=(Matrix & A ) const;
	//Matrix& operator=(const Matrix & A );
	//void prepare_for_copy();
	//void prepare_for_delete();
private:
	double** pola;
	int n;
	int m;
	void free_pola(int n,int m);
	//bool to_clear = true;
};

