#include "Matrices.h"
#include <iostream>
#include <cmath>

namespace Matrices {


	Matrix::Matrix (int _rows, int _cols) {

		rows = _rows;
		cols = _cols;

		a.resize(rows);
		for (int i = 0; i < a.size(); i++) {
			a[i].resize(cols);
		}

	}


	Matrix operator+(const Matrix& a, const Matrix& b) {
		Matrix c(a.getRows(), a.getCols());


		if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
			throw runtime_error("Error: dimensions must agree");

		for (int i = 0; i < a.getRows(); i++) {

			for (int j = 0; j < a.getCols(); j++) {
				c(i, j) = a(i, j) + b(i, j);
			}

		}
		return c;
	}

	Matrix operator*(const Matrix& a, const Matrix& b) {
		
		if (a.getCols() != b.getRows())
			throw runtime_error("Error: dimensions must agree");

		int rows = a.getRows();
		int cols = b.getCols();
		
		Matrix c(rows, cols);

		double sum;
		for (int i = 0; i < a.getRows(); i++ ) {

			for (int k = 0; k < b.getCols(); k++) {
				sum = 0;
				for (int j = 0; j < a.getCols(); j++) {
					sum += a(i, j) * b(j, k);
				}
				c(i, k) = sum;
			}

		}

		return c;

	}

	bool operator==(const Matrix& a, const Matrix& b) {

		if (a.getRows() != b.getRows() || a.getCols() != b.getCols() )
			return false;
		double bounds = 0.001;

		for (int i = 0; i < a.getRows(); i++) {
			for (int j = 0; j < a.getCols(); j++) {
				if (abs(a(i, j) - b(i, j)) > bounds)
					return false;

			}
		}

		return true;

	}

	bool operator!=(const Matrix& a, const Matrix& b) {
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols() )
			return true;
		double bounds = 0.001;

		for (int i = 0; i < a.getRows(); i++) {
			for (int j = 0; j < a.getCols(); j++) {
				if(abs(a(i, j) - b(i, j)) < bounds)
					return false;
			}
		}

		return true;
	}

	ostream& operator<<(ostream& os, const Matrix& a) {


		for (int i = 0; i < a.getRows(); i++) {
			for (int j = 0; j < a.getCols(); j++) {
				os << setw(10) << a(i, j) << " ";
			}
			
			os << "\n\n";
		}

		os << '\n';

		return os;
	}


}
