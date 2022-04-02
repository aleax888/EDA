#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;

bool sortByFirst(const pair<int, int>& a, const pair<int, int>& b)
{
    return (a.first < b.first);
}

struct point
{
    vector<int> data;
    int dim = 0;
    point(vector<int> v)
    {
        for (int i = 0, s = v.size(); i < s; ++i)
            data.push_back(v[i]);
        dim = v.size();
    }

    point(const point &p)
    {
        for (int i = 0, s = p.dim; i < s; ++i)
            data.push_back(p.data[i]);
        dim = p.dim;
    }

    void print()
    {
        cout << "dim: " << dim << endl;
        for (int i = 0; i < dim; ++i)
            cout << data[i] << " ";
        cout << endl;
    }
};

int intRand(int max, int min)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

point pointRand(int dim) 
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 1000);
    vector<int> ans;
    for (int i = 0; i < dim; ++i)
        ans.push_back(distrib(gen));
    return point(ans);
}

vector<point> dataRand(int n, int dim)
{
    vector<point> ans;
    for (int i = 0; i < n; ++i)
        ans.push_back(pointRand(dim));
    return ans;
}

int euclideanDistance(point a, point b)
{
    int ans = 0;
    for (int i = 0; i < a.dim; ++i)
        ans += pow(a.data[i] - b.data[i], 2);
    return sqrt(ans);
}

int findPII(vector<pii> vec, int e)
{
    for (int j = 0, s = vec.size(); j < s; ++j)
        if (vec[j].first == e)
            return j;
    return -1;
}

vector<pii> makeHistogram(int n, int dim)
{
    vector<point> data(dataRand(n, dim));
    /*for (int i = 0, s = data.size(); i < s; ++i)
        data[i].print();*/
    
    int datoE = intRand(0, n-1);
    vector<pii> ans;

    for (int i = 0; i < n; ++i)
    {
        int ed = euclideanDistance(data[i], data[datoE]);
        int pos = findPII(ans, ed);
        if (pos == -1)
            ans.push_back(pii{ ed, 1 });
        else
            ans[pos].second++;
    }
    sort(ans.begin(), ans.end(), sortByFirst);
    return ans;
}

int main()
{
    int dataN = 20;
    vector<int> dims({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 });

    vector<pii> h(makeHistogram(dataN, dims[0]));
    for (int i = 0, s = h.size(); i < s; ++i)
        cout << h[i].first << " " << h[i].second << endl;
}
