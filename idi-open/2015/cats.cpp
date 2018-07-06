/**
 * This problem simply asks to compute the cost of a minimum spanning of a graph.
 * Build a graph which vertices are the cats. There is a edge between each pair of cats.
 * The cost of an edge is the distance between the two cats that the edge connects.
 * We have:
 *  - T, the cost of a minimum spanning spanning tree.
 *  - C, the number of cats.
 *  - M, milk amount.
 * We can feed all the cats iff T + C <= M.
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

typedef struct edge {
    int u, v, w;
    edge(int u, int v, int w): u(u), v(v), w(w) {}
} edge;

bool operator <(const edge &e, const edge &o)
{
    return e.w < o.w;
}

typedef struct union_find {
    vector<int> parents;
    vector<int> queue;

    union_find(int n): parents(n, 0) {
        queue.reserve(2 * n);
        iota(parents.begin(), parents.end(), 0);
    }

    int find(int u) {
        int p = parents[u];
        while (u != p) {
            queue.push_back(u);
            u = p;
            p = parents[p];
        }
        for (const auto &j: queue) {
            parents[j] = p;
        }
        queue.clear();
        return p;
    }

    void unite(int u, int v) {
        parents[find(u)] = find(v);
    }
} union_find;

int main()
{
    vector<edge> edges;
    int m, c, t, p;
    int u, v, w;
    int cost;

    cin >> t;
    while (t != 0) {
        cin >> m >> c;
        if (m <= c) {
            cout << "no" << endl;
            --t;
            continue;
        }

        p = (c * (c - 1)) / 2;
        for (int j = 0; j < p; ++j) {
            cin >> u >> v >> w;
            edges.emplace_back(u, v, w);
        }

        sort(edges.begin(), edges.end());
        union_find uf(c);
        cost = 0;
        for (const auto &e: edges) {
            int pu = uf.find(e.u);
            int pv = uf.find(e.v);
            if (pu != pv) {
                cost += e.w;
                uf.unite(pu, pv);
            }
        }

        cout << (m >= c + cost ? "yes" : "no") << endl;
        edges.clear();
        --t;
    }

    return 0;
}

