#include <iostream>
#include <time.h>
#include <vector>
#include <iomanip>
#include <cassert>
#include <thread>

using namespace std;

const int MX = 1000;

typedef vector<vector<int>> matrix;

void f(int i, matrix &a, matrix &b, matrix &c){
	int sz = a.size();
	for(int j = 0 ;  j < sz ; j++)
		for(int k = 0; k < sz; k++)
			c[i][j] += a[i][k] * b[k][j];
};

void floyd(vector<vector<int>> &m){
    for(auto &v : m) 
        for(auto &elem : v) 
            elem = rand() % MX;
}

void show(matrix &a){
	for(auto v : a){
		for(auto i : v)
			cout << i << " ";
		cout << "\n";
	}
}

void mult(matrix &a, matrix &b, matrix &c){
	assert(a.size() == b.size() );
	int sz = a.size();
	vector<thread> threads(sz);
	int idx = 0;
	for(int i = 0 ; i < sz; i++){
		threads[idx++] = thread(f,i,ref(a), ref(b), ref(c));
	}
		// for(int j = 0 ;  j < sz ; j++)
		// 	for(int k = 0; k < sz; k++)
		// 		c[i][j] += a[i][k] * b[k][j];
	for(auto &t : threads) t.join();
}

int main() {
	clock_t beginnig_time = clock();
	srand(time(0));
	int n; cin >> n;
	vector<vector<int>> a(n, vector<int>(n));
	vector<vector<int>> b(n, vector<int>(n));
	vector<vector<int>> c(n, vector<int>(n));
    floyd(a);
    floyd(b);
	mult(a,b,c);
	show(c);
	clock_t end_time = clock();
	cout << n << ": " << fixed << setprecision(6) << (end_time - beginnig_time) * 1.0 / CLOCKS_PER_SEC << endl;
	return 0;
}