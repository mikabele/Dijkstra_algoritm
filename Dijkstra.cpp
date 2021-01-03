#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <deque>
#include <algorithm>
#include <queue>
#pragma warning(disable:4996)

using namespace std;

class Comparator {
public:
	bool operator()(pair<long long, long long>& a, pair<long long, long long>& b) {
		return a.first > b.first;
	};
};

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	long long n, m;
	cin >> n >> m;
	vector<pair<long long, long long>>* edges = new vector<pair<long long, long long>>[n];//список смежности
	long long u, v, w;
	Comparator comp;
	for (long long i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		edges[u - 1].push_back(make_pair(v - 1, w));
		edges[v - 1].push_back(make_pair(u - 1, w));
	}
	long long* paths = new long long[n] {};//пара-длина пути
	long long* flags = new long long[n] {};//флаги почещения- -1-посещен но не факт что мин, 0-не посещен,1-посещен по мин пути
	paths[0] = 0;
	flags[0] = -1;
	priority_queue<pair<long long, long long>, vector<pair<long long, long long>>,Comparator> s(comp);
	s.push(make_pair(0, 0));
	pair<long long, long long> top;
	while (!s.empty())
	{
		top = s.top();
		if (top.second == n - 1)
			break;
		if (flags[top.second] == -1)
		{
			flags[top.second] = 1;
			long long count = edges[top.second].size();
			long long i = 0;
			for (; i < count; i++)
			{
				if (flags[edges[top.second][i].first] != 1 && (paths[edges[top.second][i].first] == 0 ||
					edges[top.second][i].second + top.first < paths[edges[top.second][i].first]))
				{
					paths[edges[top.second][i].first] = edges[top.second][i].second + top.first;
					flags[edges[top.second][i].first] = -1;
					s.push(make_pair(paths[edges[top.second][i].first], edges[top.second][i].first));
				}
			}
		}
		s.pop();
	}
	cout << paths[n - 1];
}