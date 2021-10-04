#ifndef _PHYSICS_MATRIX_
#define _PHYSICS_MATRIX_

#pragma once

#include "Vector.h"

PHYSICS_NAMESPACE_BEGIN(collections)

template<const unsigned int rows, const unsigned int columns>
class Matrix {
private:
	Vector<columns> matrix[rows];

public:
	Matrix(FloatType fill = (FloatType)0) {
		for (unsigned int iRow = 0; iRow != rows; iRow++) {
			for (unsigned int iColumn = 0; iColumn != columns; iColumn++) {
				this->matrix[iRow][iColumn] = fill;
			}
		}
	}

	Matrix(const std::initializer_list<std::initializer_list<FloatType>>& initMatrixLists) {
		// no size check :(
		for (unsigned int iRow = 0; iRow != rows; iRow++) {
			for (unsigned int iColumn = 0; iColumn != columns; iColumn++) {
				this->matrix[iRow][iColumn] = *((initMatrixLists.begin() + iRow)->begin() + iColumn);
			}
		}
	}

	static Matrix<rows, columns> identity() {
		Matrix<rows, columns> identityMatrix;
		if (rows == columns) {
			for (unsigned int i = 0; i != rows; i++) {
				identityMatrix.at(i, i) = (FloatType)1;
			}

		}
		return identityMatrix;
	}

public:
	Vector<columns>& rowAt(const unsigned int iRow) {
		return this->matrix[iRow];
	}

	const Vector<columns>& rowAt(const unsigned int iRow) const {
		return this->matrix[iRow];
	}

	FloatType& at(const unsigned int iRow, const unsigned int iColumn) {
		return this->rowAt(iRow)[iColumn];
	}

	const FloatType& at(const unsigned int iRow, const unsigned int iColumn) const {
		return this->rowAt(iRow)[iColumn];
	}

	Vector<columns> getRow(const unsigned int iRow) const {
		return this->matrix[iRow];
	}

	Vector<rows> getColumn(const unsigned int iColumn) const {
		Vector<rows> column;
		for (unsigned int iRow = 0; iRow != rows; iRow++) {
			column[iRow] = this->at(iRow, iColumn);
		}
		return column;
	}

private:
	Matrix<rows, columns>& rowSwap(const unsigned int iRow1, const unsigned int iRow2) {
		Vector<columns> tmpRow = this->getRow(iRow1);
		this->matrix[iRow1] = this->matrix[iRow2];
		this->matrix[iRow2] = tmpRow;
		return *this;
	}

	// adds `iRow2` row into `iRow1` row
	Matrix<rows, columns>& rowAdd(const unsigned int iRow1, const unsigned int iRow2) {
		this->matrix[iRow1] += this->matrix[iRow2];
		return *this;
	}

	Matrix<rows, columns>& rowSubtract(const unsigned int iRow1, const unsigned int iRow2) {
		this->matrix[iRow1] -= this->matrix[iRow2];
		return *this;
	}

	Matrix<rows, columns>& rowMultiply(const unsigned int iRow, FloatType modder) {
		this->matrix[iRow] *= modder;
		return *this;
	}

	Matrix<rows, columns>& rowDivide(const unsigned int iRow, FloatType modder) {
		this->matrix[iRow] /= modder;
		return *this;
	}

public:

	Matrix<rows, columns>& add(const Matrix<rows, columns>& modder) {
		for (unsigned int iRow = 0; iRow != rows; iRow++) {
			this->matrix[iRow] += modder.matrix[iRow];
		}
		return *this;
	}

	Matrix<rows, columns>& subtract(const Matrix<rows, columns>& modder) {
		for (unsigned int iRow = 0; iRow != rows; iRow++) {
			this->matrix[iRow] -= modder.matrix[iRow];
		}
		return *this;
	}

	Matrix<rows, columns>& multiply(FloatType modder) {
		for (unsigned int iRow = 0; iRow != rows; iRow++) {
			this->matrix[iRow] *= modder;
		}
		return *this;
	}

	Matrix<rows, columns>& divide(FloatType modder) {
		for (unsigned int iRow = 0; iRow != rows; iRow++) {
			this->matrix[iRow] /= modder;
		}
		return *this;
	}


	Matrix<rows, columns>& toREF() {
		unsigned int pivotRow, pivotColumn = 0;

		for (; pivotColumn != columns; pivotColumn++) {
			for (pivotRow = 0; pivotRow != rows; pivotRow++) {
				if (this->at(pivotRow, pivotColumn) != (FloatType)0) {
					if (pivotRow != 0) {
						this->rowSwap(pivotRow, 0);
						pivotRow = 0;
					}
					goto pivotInitOut;
				}
			}
		}
		return *this;

	pivotInitOut:


		for (; pivotColumn != columns; pivotColumn++) {
			if (this->at(pivotRow, pivotColumn) != (FloatType)1) {
				this->rowAt(pivotRow) /= this->at(pivotRow, pivotColumn);
			}

			Vector<columns> pivotRowVect = this->getRow(pivotRow);

			for (unsigned int iRow = pivotRow + 1; iRow != rows; iRow++) {
				if (this->at(iRow, pivotColumn) < (FloatType)0) {
					this->rowAt(iRow) += pivotRowVect * abs(this->at(iRow, pivotColumn));
				}
				else if (this->at(iRow, pivotColumn) > (FloatType)0) {
					this->rowAt(iRow) -= pivotRowVect * this->at(iRow, pivotColumn);
				}
			}

			if (++pivotRow == rows) {
				break;
			}
		} 

		return *this;
	}

	// using Gause - Jordan method
	Matrix<rows, columns>& inverse() {
		if (rows != columns) {
			// error
			return *this;
		}

		Matrix<rows, columns> identityMatrix = Matrix<rows, columns>::identity();



		return *this;
	}

	template<const unsigned int modderColumns>
	Matrix<rows, modderColumns> dotMultiplied(const Matrix<columns, modderColumns>& modder) const {
		Matrix<rows, modderColumns> product;

		for (unsigned int iProdRow = 0; iProdRow != rows; iProdRow++) {
			for (unsigned int iProdColumn = 0; iProdColumn != modderColumns; iProdColumn++) {
				product.at(iProdRow, iProdColumn) = this->getRow(iProdRow) * modder.getColumn(iProdColumn);
			}
		}

		return product;
	}

	Matrix<columns, rows> transposed() const {
		Matrix<columns, rows> transposed;

		for (unsigned int iRow = 0; iRow != rows; iRow++) {
			for (unsigned int iColumn = 0; iColumn != columns; iColumn++) {
				transposed.at(iColumn, iRow) = this->at(iRow, iColumn);
			}
		}

		return transposed;
	}

public:

	FloatType* operator[](size_t offset) {
		return this->matrix[offset];
	}

	template<const unsigned int rows, const unsigned int columns>
	friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& outStream, const Matrix<rows, columns>& matrixRef);

public:

	template<const unsigned int rows, const unsigned int columns>
	friend bool operator==(const Matrix<rows, columns>& leftMatrixRef, const Matrix<rows, columns>& rightMatrixRef);

	template<const unsigned int rows, const unsigned int columns>
	friend bool operator==(const Matrix<rows, columns>& leftMatrixRef, const FloatType value);

};

template<const unsigned int rows, const unsigned int columns>
std::basic_ostream<char>& operator<<(std::basic_ostream<char>& outStream, const Matrix<rows, columns>& matrixRef) {
	outStream.put('[');
	outStream.put(' ');

	for (unsigned int iRows = 0; iRows != rows; iRows++) {
		if (iRows) {
			outStream.put(',');
			outStream.put(' ');
		}

		outStream.put('[');

		for (unsigned int iColumns = 0; iColumns != columns; iColumns++) {
			if (iColumns) {
				outStream.put(',');
				outStream.put(' ');
			}

			outStream << matrixRef.matrix[iRows][iColumns];
		}

		outStream.put(']');
	}

	outStream.put(' ');
	outStream.put(']');

	return outStream;
}

template<const unsigned int rows, const unsigned int columns>
bool operator==(const Matrix<rows, columns>& leftMatrixRef, const Matrix<rows, columns>& rightMatrixRef) {
	return memcmp(
		&leftMatrixRef.at(0, 0), &rightMatrixRef.at(0, 0), (rows * columns * sizeof(FloatType))
	) == 0;
}

template<const unsigned int rows, const unsigned int columns>
bool operator==(const Matrix<rows, columns>& leftMatrixRef, const FloatType value) {
	for (unsigned int iRow = 0; iRow != rows; iRow++) {
		for (unsigned int iColumn = 0; iColumn != columns; iColumn++) {
			if (leftMatrixRef.at(iRow, iColumn) != value) {
				return false;
			}
		}
	}
	return true;
}

PHYSICS_NAMESPACE_END

#endif