#include "graph.h"
#define MAX_VAL 999
#include <typeinfo>

//default ctor
Graph::Graph()
{}

//constructor
Graph::Graph(const vector<vector<int>>& matrix,
        vector<string> node_names) 
{
    for(int i=0; i<matrix.size(); i++)
    {
        Node tmp(i, matrix[i]);
        graph_.push_back(tmp);
    }
    //dummy @end
    graph_.push_back(Node(-1,vector<int>()));

    for(int i=0; i<node_names.size(); i++)
    {
        node_names_.push_back(node_names[i]);
        name_index_[node_names[i]] = i;
    }
}

//destructor
Graph::~Graph()
{ }

//copy constructor
Graph::Graph(const Graph& rhs)
{
    for(auto k : rhs.graph_)
    {
        graph_.push_back(k);
    }
    for(auto k : rhs.node_names_)
    {
        node_names_.push_back(k);
    }
    for(auto k : rhs.name_index_)
    {
    	name_index_.insert(k);
    }
}

//copy assignment
Graph& Graph::operator=(const Graph& rhs)
{
    if(this != &rhs)
    {
        graph_.clear();
        node_names_.clear();
        name_index_.clear();
        for(auto k : rhs.graph_)
        {
            graph_.push_back(k);
        }
        for(auto k : rhs.node_names_)
        {
            node_names_.push_back(k);
        }
        for(auto k : rhs.name_index_)
    	{
    		name_index_.insert(k);
    	}
    }
    return *this;
}

//move constructor
Graph::Graph(Graph&& rhs)
{
    graph_ = move(rhs.graph_);
    node_names_ = move(rhs.node_names_);
    name_index_ = move(rhs.name_index_);
}

//move assignment
Graph& Graph::operator=(Graph&& rhs)
{
    if(this != &rhs)
    {
        graph_ = move(rhs.graph_);
        node_names_ = move(rhs.node_names_);
        name_index_ = move(rhs.name_index_);
    }
    return *this;
}


Graph::iterator::iterator(Node* sc, vector<Node> graph_temp, vector<string> node_names,int c)
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

Graph::iterator::~iterator()
{
    delete [] visited;
}

string Graph::iterator::operator *()
{
    return node_names_[pt_->name_];
}
bool Graph::iterator::operator==(const iterator& rhs)
{
    return pt_->name_ == rhs.pt_->name_;
}
bool Graph::iterator::operator!=(const iterator& rhs)
{
	return ! (*this == rhs);
}

Graph::iterator& Graph::iterator::operator++() // pre
{
    if(! visited[pt_->name_])
    {
        visited[pt_->name_] = true;
    }
    for(auto k : pt_->neighbours_)
    {
        if(! visited[k.first] && find(cont.begin(), cont.end(), k.first) == cont.end())
        {
            cont.push_back(k.first);
        }
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
    else
    {
        counter_++;
        for(int i=0; i<graph_temp_.size(); i++)
        {
            if(! visited[i])
            {
                pt_ = &graph_temp_[i];
                visited[i] = true;
                break;
            }
        }
    }
    return *this;
}   

Graph::iterator Graph::iterator::operator++(int) // post
{                
    iterator temp (*this);
    ++*this;
    return temp;
}
    
Graph::iterator Graph::begin_bfs(string str)
{
    return make_itr(BFS, str);
}
Graph::iterator Graph::end_bfs(string str)
{
    return make_itr(BFS, str);
}
Graph::iterator Graph::begin_dfs(string str)
{
    return make_itr(DFS, str);
}
Graph::iterator Graph::end_dfs(string str)
{
    return make_itr(DFS, str);
}
Graph::iterator Graph::make_itr(int c, string str)
{
    if(str.compare("$$$") == 0)
    {
        return iterator(&graph_[graph_.size()-1], graph_, node_names_, c);
    }
    else
    {
        return iterator(&graph_[name_index_[str]], graph_, node_names_, c);
    }

}

vector<string> Graph::topo_sort(Graph::iterator start_pt,Graph::iterator end_pt)
{
    vector<string> sorted;
    while(start_pt != end_pt)
    {
        sorted.push_back(*start_pt);
        ++start_pt;
    }
    reverse(sorted.begin(),sorted.end()); 

    return sorted;
}

Graph::iterator myfind(Graph::iterator first, Graph::iterator last, string val)
{	
	while(first != last)
	{
		if(val.compare(*first) == 0)
		{
			break;
		}
		++first;
	}

	return first;
}


int Graph::get_number_of_components(string city)
{	
    auto it = begin_bfs(city);
    int num = 0;
    cout << "num : " << it.counter_ << endl;
    cout << (it == end_bfs()) << endl;
    for(; it != end_bfs(); it++)
    {
        num = it.counter_;
        cout << "num : " << it.counter_ << endl;
    }
    return num;
}


bool comp_graphs(Graph::iterator st1,Graph::iterator en1,Graph::iterator st2,Graph::iterator en2)
{
	while(st1 != en1 && st2 != en2)
	{
		if(st1 != st2)
			break;
		++st1;
		++st2;
	}

	if(st1 == en1 and st2 == en2)
		return true;
	else
		return false;
}


void Graph::djikstra(string src, int N)
{
	int src_ = name_index_[src];
	int distances[N];
	bool shortest_path_set[N];
	for(int i=0; i<N; i++)
	{
		distances[i] = MAX_VAL;
		shortest_path_set[i] = false;		
	}
	distances[src_] = 0;
	int min_v;
	for(int i=0; i<N; i++)
	{
		int min = MAX_VAL;
		min_v = -1;
		for(int i=0; i<N; i++)
		{
			if(distances[i] < min && shortest_path_set[i] == false)
			{
				min_v = i;
				min = distances[i];
			}
		}	
		shortest_path_set[min_v] = true;
		//update dists of all nbrs of min_v
				for(auto k : graph_[min_v].neighbours_)
		{
			if(shortest_path_set[k.first]==false && distances[min_v]!=MAX_VAL 
				&& distances[k.first] > distances[min_v]+k.second)
			{
				distances[k.first] = distances[min_v]+k.second;
			}
		}
	}
	for(int i=0; i<N; i++)
	{
		cout << node_names_[src_] << " To " << node_names_[i] << " --> " << distances[i] << "\n";
	}
	cout << "\n";	
}
