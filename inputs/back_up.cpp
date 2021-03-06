#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <list>
#define BFS 0
#define DFS 1

using namespace std;

class Node
{
    private:
        int name_;
        map<int, int> neighbours_;
        friend class Graph;
        friend class bfs_iterator;
        
    public:
        //default constructor
        Node()
        :name_()
        {}

        //parametrized constructor
        Node(int name, const vector<int>& v)
        : name_(name)
        {
            for(int i=0; i<v.size(); i++)
            {
                if(v[i] > 0)
                {
                    neighbours_.insert(make_pair(i, v[i]));
                }
            }
        }
        
        //destructor
        ~Node()
        {
        }
        
        //copy constructor
        Node(const Node& rhs)
        {
            name_ = rhs.name_;
            for(auto k : rhs.neighbours_)
            {
                neighbours_.insert(k);
            }
        }
        
        //copy assignment
        Node& operator=(const Node& rhs)
        {
            if(this != &rhs)
            {
                name_ = rhs.name_;
                neighbours_.clear();
                for(auto k : rhs.neighbours_)
                {
                    neighbours_.insert(k);
                }
            }
            return *this;
        }
        
        //move constructor
        Node(Node&& rhs)
        : name_(rhs.name_), neighbours_(rhs.neighbours_)
        {
            rhs.name_ = -1;
            //rhs.neighbours_ = NULL;
        }
        
        //move assignment
        Node& operator=(Node&& rhs)
        {
            if(this != &rhs)
            {
                name_ = rhs.name_;
                neighbours_ = rhs.neighbours_;
                rhs.name_ = -1;
                //rhs.neighbours_ = NULL;
            }
            return *this;
        }
        
};

class Graph
{
    private:
        vector<Node> graph_;
        vector<string> node_names_;
        map<string, int> name_index_;
        
    public:
        //default ctor
        Graph()
        {}

        //constructor
        Graph(const vector<vector<int>>& matrix,
                vector<string> node_names) 
        {
            for(int i=0; i<matrix.size(); i++)
            {
                Node tmp(i, matrix[i]);
                graph_.push_back(tmp);
            }
            for(int i=0; i<node_names.size(); i++)
            {
                node_names_.push_back(node_names[i]);
                name_index_[node_names[i]] = i;
            }
        }
        
        //destructor
        ~Graph()
        { }
        
        //copy constructor
        Graph(const Graph& rhs)
        {
            for(auto k : rhs.graph_)
            {
                graph_.push_back(k);
            }
            for(auto k : rhs.node_names_)
            {
                node_names_.push_back(k);
            }
        }
        
        //copy assignment
        Graph& operator=(const Graph& rhs)
        {
            if(this != &rhs)
            {
                graph_.clear();
                node_names_.clear();
                for(auto k : rhs.graph_)
                {
                    graph_.push_back(k);
                }
                for(auto k : rhs.node_names_)
                {
                    node_names_.push_back(k);
                }
            }
            return *this;
        }
        
        //move constructor
        Graph(Graph&& rhs)
        {
            graph_ = move(rhs.graph_);
            node_names_ = move(rhs.node_names_);
        }
        
        //move assignment
        Graph& operator=(Graph&& rhs)
        {
            if(this != &rhs)
            {
                graph_ = move(rhs.graph_);
                node_names_ = move(rhs.node_names_);
            }
            return *this;
        }
        
        
        class iterator
        {
            private:
            Node* pt_;
            vector<Node> graph_temp_;   
            bool* visited;
            list<int> cont;
            bool last = false;
            vector<string> node_names_;
            int check;
    
            public:
            iterator(Node* sc, vector<Node> graph_temp, vector<string> node_names,int c)
            :visited(new bool[graph_temp.size()]), pt_(sc), graph_temp_(graph_temp),check(c)
            {
                for(int i=0; i<graph_temp.size(); i++)
                {
                    visited[i] = false;
                }
                    
                for(int i=0; i<node_names.size(); i++)
                {
                    node_names_.push_back(node_names[i]);
                }
            }
            string operator *()
            {
                return node_names_[pt_->name_];
            }
            bool operator==(const iterator& rhs)
            {
                return pt_->name_ == rhs.pt_->name_;
            }
            bool operator!=(const iterator& rhs)
            {
                if(last)
                {
                    return false;
                }
                else
                {
                    if(*this == rhs)
                    {
                        last = true;
                    }
                    return true;
                }
            }

            iterator& operator++() // pre
            {
                if(! visited[pt_->name_])
                {
                    visited[pt_->name_] = true;
                }

                vector<int> temp;
                for(auto k : pt_->neighbours_)
                {
                        temp.push_back(k.first);
                }
        
                for(int i : temp) 
                {
                    if(! visited[i])
                        cont.push_back(i);
                }
                if(! cont.empty())
                {
                    if(check == 1)
                    {
                        pt_ = &graph_temp_[cont.back()];
                        cont.pop_back();
                    }

                    else
                    {
                        pt_ = &graph_temp_[cont.front()];
                        cont.pop_front();
                    }
                }
                return *this;
            }   

            iterator operator++(int) // post
            {                
                iterator temp (*this);
                ++*this;
                return temp;
            }
            
        };
        

        iterator begin_bfs(string str)
        {
            return begin(BFS, str);
        }
        iterator end_bfs(string str)
        {
            return end(BFS, str);
        }
        iterator begin_dfs(string str)
        {
            return begin(DFS, str);
        }
        iterator end_dfs(string str)
        {
            return end(DFS, str);
        }
        iterator begin(int c, string str)
        {
            return iterator(&graph_[name_index_[str]], graph_, node_names_, c);
        }
        iterator end(int c, string str)
        {
            return iterator(&graph_[name_index_[str]], graph_, node_names_, c);
        }
};

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
    cout << "BFS : ";
    disp(g.begin_bfs("Mumbai"), g.end_bfs("Delhi"));
    cout << "DFS : ";
    disp(g.begin_dfs("Mumbai"), g.end_dfs("Delhi"));
    return 0;
}

/*if(last || counter_ == graph_temp_.size()-1)
{
    return false;
}
else
{
    ++counter_;
    if(*this == rhs)
    {
        last = true;
    }
    return true;
}*/
