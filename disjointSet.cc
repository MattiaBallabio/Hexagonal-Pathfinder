#include "disjointSet.h"

using namespace std;

DisjointSet::DisjointSet(int n){
    size = n;
    parent = new int[n];
    rank = new int[n];
    for(int i = 0; i < n; i++){
        parent[i] = i;
        rank[i]   = 0;
    }
}

DisjointSet::~DisjointSet() {
    delete[] parent;
    delete[] rank;
}

int DisjointSet::find(int a) {
    if(parent[a] != a) {
        parent[a] = find(parent[a]);
    }
    return parent[a];
}

void DisjointSet::join(int a, int b) {
    int numA = find(a);
    int numB = find(b);
    
    if(numA != numB) {
        if(rank[numA] < rank[numB]) {
            parent[numA] = numB;
            
        } else if(rank[numA] > rank[numB]) {
            parent[numB] = numA;

        } else {
            parent[numB] = numA;
            rank[numA]++;

        }
    }
}