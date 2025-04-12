#ifndef DISJOINTSET_H
#define DISJOINTSET_H

using namespace std;

class DisjointSet {

    public:
        explicit DisjointSet(int n);
        ~DisjointSet();
        int find(int a);
        void join(int a, int b);

    private:
        int* parent;
        int* rank;
        int size;
};

#endif