#include <vector>
#include <stack>

class Graph{
private:
    std::vector<std::vector<int>>  adj, adj_t;
    std::stack<int> order;
    std::vector<int> scc, scc_size;
    int n_scc;

    void dfs(int cur_node);
    void dfs_t(int cur_node, int component);

public:
    Graph(int n); 
    void add_edge(int from, int to);
    
    // where the magic happens 
    void run();

    // getters
    int get_n_scc();
    int get_largest_scc();
    int get_comp(int i);
    void print_all_scc();
};