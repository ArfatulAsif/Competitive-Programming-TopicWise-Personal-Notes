// Ford-Fulkerson:
// Single source, single sink
// Requires integer capacities
// O (E * max flow)
      
const int N = 1000;

struct edge
{
	int v; 			// to
	int rev; 		//Reverse edge index in graph[v]
	int residual_capacity;  // Residual capacity of the edge
	int edge_id;            // Edge ID (optional, if needed)
};

vector<edge>graph[N];

void addEdge(int u, int v, int capacity, int id = -1)
{
	graph[u].push_back({v, (int)graph[v].size(), capacity, id});
	graph[v].push_back({u, (int)graph[u].size()-1, 0, -id});
}


int dfs(int u, int sink, int flow, vector<bool> &visited)
{
	if(u == sink)
	{
		return flow;
	}

	visited[u] = true;

	for(auto &[v, rev, residual_capacity, id] : graph[u])
	{
		if(visited[v] || residual_capacity == 0)
		{
			continue;
		}

		int pathFlow = min(flow, residual_capacity);
		int pushedFlow = dfs(v, sink, pathFlow, visited);

		if(pushedFlow > 0)
		{
			residual_capacity -= pushedFlow;
			graph[v][rev].residual_capacity += pushedFlow;

			return pushedFlow; // we need to find only one augmenting path, so we return after any children who is giving pushFlow > 0
		}

	}

	return 0; // no augmenting path found
}


int FordFulkerson(int source ,int sink)
{
	int maxFlow = 0;
	vector<bool>visited(N,false);

	while(true)
	{
		fill(visited.begin(),visited.end(),false);

		int flow = dfs(source, sink, INT_MAX, visited);

		if(flow == 0) // no augmenting path found
		{
			break; 
		}

		maxFlow += flow;
	}

	return maxFlow;
}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,m;
        cin>>n>>m;

        for(int i=0;i<m;i++)
        {
        	int u,v,c;
        	cin>>u>>v>>c;
        	addEdge(u,v,c);
        }

        cout<<FordFulkerson(1,n)<<endl;

}

// https://cses.fi/problemset/task/1694/
