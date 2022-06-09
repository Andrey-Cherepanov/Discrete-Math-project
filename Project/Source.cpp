#include <fstream>
#include <vector>
#include <string>

using namespace std;

short is_Euler(int n, int m, vector<vector<int>> matrix);
vector<int> build_chain(int n, int m, vector<vector<int>> matrix, int v);
bool is_bridge(int n, int m, vector<vector<int>> matrix, int edge);
void dfs(int n, vector<vector<int>> matrix, int v, vector<int>* checked_nodes);
vector<vector<int>> create_adj_matrix(int n, int m, vector<vector<int>> matrix);
bool in_array(vector<int> arr, int val);

int main() {
	ofstream fout;
	ifstream fin("input.txt");
	fout.open("output.txt");
	int n, m;
	fin >> n; fin >> m;
	vector<vector<int>> matrix(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) fin >> matrix[i][j];
	}
	fin.close();
	short f = is_Euler(n, m, matrix);
	if (f == 0) {
		fout << "Nothing";
	}
	else if (f == 1) {
		fout << "Cycle\n";
		vector<int> cycle = build_chain(n, m, matrix, 0);
		fout << cycle[0]+1;
		for (int i = 1; i < cycle.size(); i++) fout << " " << cycle[i]+1;
	}
	else {
		fout << "Chain\n";
		int v = 0; int temp = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) temp += matrix[i][j];
			if (temp % 2 == 1) {
				v = i;
				break;
			}
		}
		vector<int> chain = build_chain(n, m, matrix, v);
		fout << chain[0]+1;
		for (int i = 1; i < chain.size(); i++) fout << " " << chain[i]+1;
	}
	fout.close();


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

vector<int> build_chain(int n, int m, vector<vector<int>> matrix, int v)
{
	vector<int> res;

	while (true) {
		res.push_back(v);
		int edge = -1; int k = 0; bool is_b = false;
		for (int i = m-1; i >= 0; i--)
			if (matrix[v][i]) {
				if (is_bridge(n, m, matrix, i)) {
					if (k == 0) edge = i;
				}
				else {
					edge = i;
					k++;
				}
			}
		if (edge == -1) return res;
		for (int i = 0; i < n; i++) {
			if (matrix[i][edge] == 1 && i != v) {
				v = i;
				break;
			}
		}
		for (int i = 0; i < n; i++) {
			matrix[i][edge] = 0;
		}
	}
	
}

bool is_bridge(int n, int m, vector<vector<int>> matrix, int edge)
{
	int u, v;
	int temp[2];
	int f = 0;
	for (int i = 0; i < n; i++) {
		if (matrix[i][edge]) {
			temp[f] = i;
			f++;
		}
	}
	v = temp[0]; u = temp[1];
	for (int i = 0; i < m; i++) {
		if (matrix[v][i] == 1 && matrix[u][i] == 1) {
			matrix[v][i] = 0;
			matrix[u][i] = 0;
			break;
		}
	}
	vector<vector <int>> adj_matrix = create_adj_matrix(n, m, matrix);
	vector<int> checked_nodes;
	dfs(n, adj_matrix, v, &checked_nodes);

	if (in_array(checked_nodes, u)) return false;
	return true;
}

void dfs(int n, vector<vector<int>> adj_matrix, int v, vector<int>* checked_nodes)
{
	(*checked_nodes).push_back(v);
	for (int i = 0; i < n; i++) {
		if (adj_matrix[v][i] && !in_array(*checked_nodes, i)) {
			dfs(n, adj_matrix, i, checked_nodes);
		}
	}
}

vector<vector<int>> create_adj_matrix(int n, int m, vector<vector<int>> matrix)
{
	vector<vector<int>> adj_matrix(n, vector<int>(n, 0));
	for (int i=0; i < n; i++) {
		for (int j=0; j < m; j++) {
			if (matrix[i][j] == 1) {
				for (int c = i+1; c < n; c++) {
					if (matrix[c][j] == 1 && c != i) {
						adj_matrix[i][c] = 1;
						adj_matrix[c][i] = 1;
						matrix[i][j] = 0;
						matrix[c][j] = 0;
						break;
					}
				}
			}
		}
	}
	return adj_matrix;
}

bool in_array(vector<int> arr, int val) {
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] == val) return true;
	}
	return false;
}
