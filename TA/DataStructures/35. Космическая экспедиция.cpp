#include <iostream>
#include <vector>
#include <fstream>

struct Point
{
    int x;
    int y;
    int z;

};

bool operator == (const Point &c1, const Point &c2)
{
    return (c1.x == c2.x &&
            c1.y== c2.y && c1.z == c2.z);
}


bool operator!= (const Point &c1, const Point &c2)
{
    return !(c1==c2);
}

Point parent[200][200][200];

Point find_set (Point v) {
    if (v == parent[v.x][v.y][v.z])
        return v;
    return find_set (parent[v.x][v.y][v.z]);
}

void union_sets (Point a, Point b) {
    a = find_set (a);
    b = find_set (b);
    if (a != b)
        parent[b.x][b.y][b.z] = a;
}

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int n, m, k, t;
    int x1, y1, z1, x2, y2, z2;
    fin >> n >> m >> k >> t;
    for (int i=1; i<=n; i++)
    {
        for (int j =1; j<=m; j++)
        {
            for (int l = 1; l <=k; l++)
            {
                Point point{};
                point.x = i;
                point.y = j;
                point.z = l;
                parent[i][j][l] = point;
            }
        }
    }

    for (int i=0; i<t; i++)
    {
        fin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        if(x1!=x2)
        {
            int x_min = std::min(x1,x2);
            int x_max= std::max(x1,x2);
            if (x1<x2)
            {
                for (int j = x_min; j<x_max; j++)
                {
                    if(find_set(parent[j][y1][z1])!=find_set(parent[j+1][y1][z1]))
                        union_sets(parent[j][y1][z1],parent[j+1][y2][z1]);
                    else
                        fout << j << ' ' << y1 << ' ' << z1 << ' ' << j + 1 << ' ' << y2 << ' ' << z2 << "\n";

                }


            } else {
                for (int j = x_max; j > x_min; j--) {
                    if(find_set(parent[j][y1][z1])!=find_set(parent[j-1][y1][z1]))
                        union_sets(parent[j][y1][z1],parent[j-1][y1][z1]);
                    else
                        fout << j << ' ' << y1 << ' ' << z1 << ' ' << j-1 << ' ' << y2 << ' ' << z2 << "\n";

                }
            }

        }
        else if(y1!=y2)
        {
            int y_min = std::min(y1,y2);
            int y_max= std::max(y1,y2);
            if (y1<y2)
            {
                for (int j = y_min; j<y_max; j++)
                {
                    if(find_set(parent[x1][j][z1])!=find_set(parent[x1][j+1][z1]))
                        union_sets(parent[x1][j][z1],parent[x1][j+1][z1]);
                    else
                        fout << x1 << ' ' << j << ' ' << z1 << ' ' << x1 << ' ' << j+1 << ' ' << z2 << "\n";
                }

            } else {
                for (int j = y_max; j > y_min; j--) {
                    if(find_set(parent[x1][j][z1])!=find_set(parent[x1][j-1][z1]))
                        union_sets(parent[x1][j][z1],parent[x1][j-1][z1]);
                    else
                        fout << x1 << ' ' << j << ' ' << z1 << ' ' << x1 << ' ' << j-1 << ' ' << z2 << "\n";


                }
            }

        }
        else{
            int z_min = std::min(z1, z2);
            int z_max = std::max(z1, z2);
            if (z1 < z2) {
                for (int j = z_min; j < z_max; j++) {
                    if(find_set(parent[x1][y1][j])!=find_set(parent[x1][y1][j+1]))
                        union_sets(parent[x1][y1][j],parent[x1][y1][j+1]);
                    else
                        fout << x1 << ' ' << y1 << ' ' << j << ' ' << x1 << ' ' << y1 << ' ' << j+1 << "\n";

                }

            } else {
                for (int j = z_max; j > z_min; j--) {
                    if(find_set(parent[x1][y1][j])!=find_set(parent[x1][y1][j-1]))
                        union_sets(parent[x1][y1][j],parent[x1][y1][j-1]);
                    else
                        fout << x1 << ' ' << y1 << ' ' << j << ' ' << x1 << ' ' << y1 << ' ' << j-1 << "\n";

                }
            }
        }
    }
    return 0;
}
