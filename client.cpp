#include "graph.h"

vector<vector<int>> input_matrix(int N)
{
    vector<vector<int>> v; 
    for(int i=0; i<N; i++)
    {
        vector<int> tmp;
        for(int j=0; j<N; j++)
        {
            int value;
            cin >> value;
            tmp.push_back(value);
        }
        v.push_back(tmp);
    }
    return v;
}

vector<string> input_string(int N)
{
    vector<string> v;
    string ch;
    for(int i=0; i<N; i++)
    {
        ch = new char[100];
        cin >> ch;
        v.push_back(ch);
    }
    return v;
}

template<typename ptr>
void disp(ptr first, ptr last)
{
    while(first != last)
    {
        cout << *first << "   ";
        ++first;
    }
    cout << endl;
}

template<typename ptr>
void disp2(ptr first, ptr last)
{
    while(first != last)
    {
        cout << *first << "   ";
        first++;
    }
    cout << endl;
}

int main()
{
    int N;
    cin >> N;
    vector<string> vertex_names = input_string(N);
    vector<vector<int>> adjacency_matrix = input_matrix(N);
    Graph g(adjacency_matrix, vertex_names);
    #if 0
    cout << "BFS : ";
    disp(g.begin_bfs("Mumbai"), g.end_bfs("Belgaum"));
    cout << "DFS : ";
    disp(g.begin_dfs("Mumbai"), g.end_dfs("Belgaum"));
    #endif
    
    #if 0
    cout << "BFS : ";
    disp(g.begin_bfs("Belgaum"), g.end_bfs("Mumbai"));
    cout << "DFS : ";
    disp(g.begin_dfs("Belgaum"), g.end_dfs("Mumbai"));
    #endif
    
    #if 0
    cout << "BFS : ";
    disp(g.begin_bfs("Belgaum"), g.end_bfs("Chennai"));
    //cout << "DFS : ";
    //disp(g.begin_dfs("Belgaum"), g.end_dfs("Mumbai"));
    #endif
    
    #if 1
    cout << "BFS : ";
    disp(g.begin_bfs("Belgaum"), g.end_bfs("Chennai"));
    cout << "DFS : ";
    disp(g.begin_dfs("Belgaum"), g.end_dfs("Chennai"));
    #endif
    
    return 0;
}
