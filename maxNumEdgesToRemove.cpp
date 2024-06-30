#include <bits/stdc++.h>
using namespace std;

class UnionFind{
private:
    vector<int> parent;
    vector<int> rank;
public:
    UnionFind(int n){
        parent.resize(n);
        rank.resize(n, 0);
        for(int i=0; i<n; ++i){
            parent[i] = i;
        }
    }

    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void UnionSets(int x, int y){
        int rootX = find(x);
        int rootY = find(y);
        if(rootX != rootY){
            if(rank[rootX] > rank[rootY]){
                parent[rootY] = rootX;
            } else if(rank[rootX] < rank[rootY]){
                parent[rootX] = rootY;
            } else{
                parent[rootY] = rootX;
                ++rank[rootX];
            }
        }
    }
};

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        UnionFind ufAlice(n + 1);
        UnionFind ufBob(n + 1);
        UnionFind ufBoth(n + 1);
        int ans = 0;
        for(const auto &e : edges){
            if(e[0] == 3){
                if(ufBoth.find(e[1]) != ufBoth.find(e[2])){
                    ufBoth.UnionSets(e[1], e[2]);
                    ufBob.UnionSets(e[1], e[2]);
                    ufAlice.UnionSets(e[1], e[2]);
                    ++ans;
                }
            }
        }
        for(const auto &e : edges){
            if(e[0] == 1){
                if(ufAlice.find(e[1]) != ufAlice.find(e[2])){
                    ufAlice.UnionSets(e[1], e[2]);
                    ++ans;
                }
            } else if(e[0] == 2){
                if(ufBob.find(e[1]) != ufBob.find(e[2])){
                    ufBob.UnionSets(e[1], e[2]);
                    ++ans;
                }
            }
        }
        for(int i=1; i<=n; ++i){
            if(ufAlice.find(i) != ufAlice.find(1) || ufBob.find(i) != ufBob.find(1)){
                return -1;
            }
        }
        return edges.size() - ans;
    }
};
