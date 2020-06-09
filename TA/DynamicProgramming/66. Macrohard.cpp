#include <iostream>
#include <fstream>


int main() {
    int n, k = 0;
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    fin >> n;
    fin >> k;
    int* arr = new int[k];
    for (int i = 0; i < k; i++)
    {
        fin >> arr[i];
    }

    int x;
    for (int i = 0; i < k; i++) {
        for (int j = k - 1; j > i; j--) {
            if (arr[j - 1] > arr[j]) {
                x = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = x;
            }
        }
    }

    const int p = 1;
    int* q = new int[k + 1];
    q[0] = arr[0] - 1;
    if (n > arr[k - 1])
        q[k] = n - arr[k - 1];
    else
        q[k] = 0;
    for (int i = 1; i < k; i++)
    {
        q[i] = arr[i] - arr[i - 1] - 1;
    }


    int** e = new int* [k + 1];
    int** w = new int* [k + 1];
    for (int i = 0; i < k + 1; i++) {
        e[i] = new int[k + 1];
        w[i] = new int[k + 1];
    }

    for (int i = 0; i <= k; i++)
        for (int j = 0; j <= k; j++) w[i][j] = e[i][j] = 0;

    for (int i = 0; i < k; i++)
    {
        w[i][i] = e[i][i] = q[i] + 1 + q[i + 1];

    }

    for (int i = 0; i < k; i++)
        for (int j = i + 1; j < k; j++) w[i][j] = w[i][j - 1] + q[j + 1] + 1;



    for (int l = 1; l < k; l++)
    {
        for (int i = 0; i < k - l; i++)
        {
            int j = i + l;
            int minSum = INT_MAX;
            int m;
            for (int h = i; h <= j; h++)
            {

                int sum = w[i][j];

                if (j >= h + 1) sum += e[h + 1][j];
                if (i <= h - 1) sum += e[i][h - 1];


                if (minSum >= sum)
                {
                    minSum = sum;
                    m = h;
                }
            }

            e[i][j] = minSum;
        }
    }

    fout << e[0][k - 1];

}
