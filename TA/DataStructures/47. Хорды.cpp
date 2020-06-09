/*
 Problem 47. Хорды
Input file name: chords.in
Output file name: chords.out
Time limit: 1 s
Memory limit: 64 MB
На окружности отмечено 2n различных точек, пронумерованных от 1 до 2n против часовой стрелки. Петя нарисовал n хорд, i-я из которых соединяет точки с номерами ai и bi. При этом каждая точка является концом ровно одной хорды.



Теперь Петя заинтересовался, сколько пар хорд пересекаются. Помогите ему найти это число.

Input
Первая строка содержит число n проведённых хорд (1 ≤ n ≤ 300 000). Следующие n строк содержат по два целых числа — ai и bi (1 ≤ ai, bi ≤ 2n, ai ≠ bi).
Output
Выведите число пар хорд, которые пересекаются.
Examples
chords.in	
3
1 4
2 5
3 6
chords.out
3
chords.in
2
1 2
3 4
chords.out
0
chords.in
2
1 4
2 3
chords.out
0
*/
#include <iostream>
#include <fstream>
#include <cmath>

long long getMid(long long a, long long b)
{
	return a + (b - a) / 2;
}


long long build_tree_process(long long tl, long long tr,
	long long* tree, long long v)
{

	if (tl == tr)
	{
		tree[v] = 0;
		return 0;
	}

	long long mid = getMid(tl, tr);

	tree[v] = build_tree_process(tl, mid, tree,
		v * 2 + 1) +
		build_tree_process(mid + 1, tr,
			tree, v * 2 + 2);

	return tree[v];
}

long long* build_tree(long long n)
{
	long long x = (long long)(ceil(log2(n)));

	long long max_size = 2 * (long long)pow(2, x) - 1;

	long long* tree = new long long[max_size];

	build_tree_process(0, n - 1, tree, 0);

	return tree;
}

void add_tree_process(long long* tree, long long v, long long tl, long long tr, long long pos, long long a)
{
	if (tl > tr) return;
	if (tl == tr) {
		tree[v] = a;
		return;
	}


	long long mid = getMid(tl, tr);

	if (pos <= mid) add_tree_process(tree, v * 2 + 1, tl, mid, pos, a); else {
		add_tree_process(tree, v * 2 + 2, mid + 1, tr, pos, a);
	}

	tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
}

void add_tree(long long* tree, long long n, long long pos, long long a)
{
	add_tree_process(tree, 0, 0, n - 1, pos, a);
}

long long get_sum_process(long long *tree, long long tl, long long tr, long long l, long long r, long long v)
{

	if (l <= tl && r >= tr)
		return tree[v];


	if (tr < l || tl > r)
		return 0;

	long long mid = getMid(tl, tr);
	return get_sum_process(tree, tl, mid, l, r, 2 * v + 1) +
		get_sum_process(tree, mid + 1, tr, l, r, 2 * v + 2);
}

long long getSum(long long *tree, long long n, long long l, long long r)
{

	// Check for erroneous input values
	if (l < 0 || r > n - 1 || l > r)
	{

		return 0;
	}

	return get_sum_process(tree, 0, n - 1, l, r, 0);
}




int main() {

	long long n, intersections = 0;
	std::ifstream fin("chords.in");
	std::ofstream fout("chords.out");
	fin >> n;
	long long *endpoints = new long long[2 * n + 1];
	bool *seen = new bool[n + 1];
	long long * tree = build_tree(n + 1);
	for (long long i = 1; i < n + 1; i++) {
		long long e1, e2;
		fin >> e1 >> e2;
		endpoints[e1] = endpoints[e2] = i;
		seen[i] = false;

	}
	long long i = 1;
	long long j;



	long long *E = new long long[n + 1];
	while (i <= 2 * n) {
		j = endpoints[i];
		if (!seen[j]) {
			seen[j] = true;
			add_tree(tree, n + 1, j, 1);
		}
		else {
			intersections += getSum(tree, n + 1, j + 1, n);
			add_tree(tree, n + 1, j, 0);

		}
		i++;


	} fout << intersections;
	fout.close();
	return 0;
}
