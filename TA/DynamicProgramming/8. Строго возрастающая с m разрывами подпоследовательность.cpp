#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>


using namespace std;

int getMid(int a, int b)
{
    return a + (b - a) / 2;
}

int getMax_process(int* tree, int tl, int tr, int l,
                   int r, int v)
{
    if (l > r) return 0;
    if (l <= tl && r >= tr)
        return tree[v];


    if (tr < l || tl > r)
        return -1;

    int mid = getMid(tl, tr);

    return max(getMax_process(tree, tl, mid, l, r,
                              2 * v + 1),
               getMax_process(tree, mid + 1, tr, l,
                              r, 2 * v + 2));
}


int getMax(int* tree, int n, int l, int r)
{

    return getMax_process(tree, 0, n - 1, l, r, 0);
}


int build_tree_process(int tl, int tr,
                       int* tree, int v)
{

    if (tl == tr)
    {
        tree[v] = 0;
        return 0;
    }

    int mid = getMid(tl, tr);

    tree[v] = max(build_tree_process(tl, mid, tree,
                                     v * 2 + 1),
                  build_tree_process(mid + 1, tr,
                                     tree, v * 2 + 2));

    return tree[v];
}

int* build_tree(int n)
{
    int x = (int)(ceil(log2(n)));

    int max_size = 2 * (int)pow(2, x) - 1;

    int* tree = new int[max_size];

    build_tree_process(0, n - 1, tree, 0);

    return tree;
}

void add_tree_process(int* tree, int v, int tl, int tr, int pos, int a)
{
    if (tl > tr) return;
    if (tl == tr) {
        tree[v] = a;
        return;
    }


    int mid = getMid(tl, tr);

    if (pos <= mid) add_tree_process(tree, v * 2 + 1, tl, mid, pos, a); else {
        add_tree_process(tree, v * 2 + 2, mid + 1, tr, pos, a);
    }

    tree[v] = max(tree[v * 2 + 1], tree[v * 2 + 2]);
}

void add_tree(int* tree, int n, int pos, int a)
{
    add_tree_process(tree, 0, 0, n - 1, pos, a);
}


int main()

{

    int n, m = 0;
    FILE *fin = fopen("m-gaps.in", "r");
    fscanf(fin, "%d%d", &n, &m);
    int* arr = new int[n];
    pair<int, int>* arrpos = new pair<int, int>[n];
    int* pos = new int[n];


    int** dp = new int*[m + 1];



    for (int i = 0; i < m + 1; i++) {
        dp[i] = new int[n];

    }
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d", &arr[i]);
        arrpos[i] = { arr[i], i };
    }

    sort(arrpos, arrpos + n);
    int id = 0;
    int o = -1e9;
    for (int i = 0; i < n; i++) {
        if (arrpos[i].first != o) {
            o = arrpos[i].first;
            id++;
        }
        pos[arrpos[i].second] = id;
    }

    int* tree2;
    int maxdp;

    for (int i = 0; i < n; i++) {
        dp[0][i] = 1;
    }

    for (int i = 0; i <= m; i++)
    {

        maxdp = 0;
        tree2 = build_tree(n);
        for (int j = 0; j < n; j++)
        {


            if (i != 0 && j != 0) maxdp = max(maxdp, dp[i - 1][j - 1]);
            dp[i][j] = max(maxdp, getMax(tree2, n, 0, pos[j] - 1)) + 1;
            add_tree(tree2, n, pos[j], dp[i][j]);

        }




    }
    int l = 0;

    for (int i = 0; i < n; i++) l = max(l, dp[m][i]);
    FILE *fout = fopen("m-gaps.out", "w");
    fprintf(fout, "%d", l);
    fclose(fin);
    fclose(fout);


}
