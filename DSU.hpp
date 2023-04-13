#include <algorithm>
#include <vector>

class DSU {
  private: 
    int* par;
    int* rank;

  public:
    int size;
    
    DSU(int n) : size{n}{
        par = new int[n];
        rank = new int[n]();
        for(int i = 0; i < n; ++i) par[i] = i;
    }
    int find(int a){
        if(par[a] == a) return a;
        return par[a] = find(par[a]);
    }

    void join(int a, int b){
        a=find(a), b=find(b);
        if(a != b) size--;
        if(rank[a] < rank[b]) std::swap(a,b);
        par[a] = b;
        rank[b] += rank[a];
    }

    void set_parent(int a, int label){
      par[a] = label;
    }
}; 