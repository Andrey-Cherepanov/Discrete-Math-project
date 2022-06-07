#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<vector<int>> read_matrix(int n, int m, ifstream* in);
short is_Euler(int n, int m, vector<vector<int>> matrix);
string Chain(int n, int m, vector<vector<int>> matrix);
string Cycle(int n, int m, vector<vector<int>> matrix);
bool is_bridge(int n, int m, vector<vector<int>> matrix, int v);

int main() {
	ofstream fout;
	ifstream fin("input.txt");
	fout.open("output.txt");
	int n, m;
	fin >> n; fin >> m;
	fin.close();
	ifstream* in = &fin;
	vector<vector<int>> matrix = read_matrix(n, m, in);
	short f = is_Euler(n, m, matrix);
	if (f == 0) {
		fout << "Nothing";
	}
	else if (f == 1) {
		fout << "Cycle";
	}
	else {
		fout << "Chain";
	}
}

vector<vector<int>> read_matrix(int n, int m, ifstream* in)
{
	int buf;
	*in >> buf; *in >> buf;
	vector<vector<int>> matrix(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) *in >> matrix[i][j];
	}
	return matrix;
}

short is_Euler(int n, int m, vector<vector<int>> matrix)
{
	short f = 0; int sum;
	for (int i = 0; i < n; i++) {
		sum = 0;
		for (int j = 0; j < m; j++) sum += matrix[i][j];
		if (sum % 2 != 0) f++;
		if (f > 2) return 0;
	}
	if (f == 0)
		return 1;
	else if (f == 2)
		return 2;
	else return 0;
}

string Chain(int n, int m, vector<vector<int>> matrix)
{
	return "";
}

string Cycle(int n, int m, vector<vector<int>> matrix)
{
	return "";
}

bool is_bridge(int n, int m, vector<vector<int>> matrix, int v)
{
	for (int i = 0; i < m; i++) {
		//Удаляем изграфа все ребра, инцидентные указанной вершине
		if (matrix[v][i] == 1) {
			for (int j = 0; j < n; j++) matrix[j][i] = 0;
		}
	}

	return false;
}
