#include <iostream>
#include <fstream>
using namespace std;

class Matrix {
	int row_count;
	int col_count;
	int** data;

public:
	Matrix(int x, int y) {
		row_count = x;
		col_count = y;
		data = new int* [row_count];
		for (int i = 0; i < row_count; i++) {
			data[i] = new int[col_count];
		}
	}

	void set(int* a) {
		for (int i = 0; i < row_count; i++) {
			for (int j = 0; j < col_count; j++) {
				data[i][j] = a[j + ((i)* col_count)];
			}
		}
	}

	void out() {
		for (int i = 0; i < row_count; i++) {
			for (int j = 0; j < col_count; j++) {
				cout << data[i][j] << ' ';
			}
			cout << endl;
		}
	}

	void trp() {
		// Vertausche Spalten und Zeilenanzahl
		int temp = row_count;
		row_count = col_count;
		col_count = temp;

		// Erstelle eine neue transponierte Matrix
		int ** transp = new int* [row_count];
		for (int i = 0; i < row_count; i++) {
			transp[i] = new int[col_count];
		}

		// Uebertrage die Werte der alten Matrix in die neue Matrix
		for (int i = 0; i < row_count; i++) {
			for (int j = 0; j < col_count; j++) {
				transp[i][j] = data[j][i];
			}
		}

		// Uebernehme die Daten
		data = transp;
		return;
	}

	void add(Matrix& m) {
		if (col_count == m.col_count && row_count == m.row_count) {
			for (int i = 0; i < row_count; i++) {
				for (int j = 0; j < col_count; j++) {
					data[i][j] += m.data[i][j];
				}
			}
		}
		else {
			cout << "Diese Matrizen koennen nicht addiert werden." << endl;
		}
		return;
	}

	void mul(Matrix& m) {
		if (col_count == m.row_count) {
			// Erstelle eine neue Ergebnismatrix
			int ** mul = new int* [row_count];
			for (int i = 0; i < row_count; i++) {
				mul[i] = new int[m.col_count];
			}

			for (int i = 0; i < row_count; i++) {
				for (int j = 0; j < m.col_count; j++) {
					int value = 0;
					for (int x = 0; x < row_count; x++) {
						for (int y = 0; y < m.col_count; y++) {
							value += data[x][i] * m.data[j][y];
						}
					}
					mul[i][j] = value;
				}
			}
			data = mul;
			col_count = m.col_count;
		}
		else {
			cout << "Diese Matrizen koennen nicht multipliziert werden." << endl;
		}
		return;
	}
};

Matrix* convertInput(char* path) {
	int rows;
	int cols;
	ifstream inFile;
	inFile.open(path);
	inFile >> rows;
	inFile >> cols;
	int* a = new int[rows * cols];

	int counter = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			inFile >> a[counter];
			counter++;
		}
	}

	Matrix* new_mat = new Matrix(rows,cols);
	new_mat->set(a);
	return new_mat;
}

int main(int argc, char* argv[]) {
	if (argc > 2) {
		Matrix* m1 = convertInput(argv[1]);
		Matrix* m2 = convertInput(argv[2]);
		// Aufgabenablauf
		cout << "Matrix 1:" << endl;
		m1->out();
		cout << "Matrix 2:" << endl;
		m2->out();
		cout << "Matrix 1 und 2 addiert:" << endl;
		m1->add(*m2);
		m1->out();
		cout << "Matrix 2 und 1 multipliziert:" << endl;
		m2->mul(*m1);
		m1->trp();
		m1->out();
	}
	else {
		cout << "Keine oder zu wenig Parameter angegeben." << endl;
		return -1;
	}
	return 0;
}
