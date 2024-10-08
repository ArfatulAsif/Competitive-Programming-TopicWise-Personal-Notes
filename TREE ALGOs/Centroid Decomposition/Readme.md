
# Centroid Decomposition

# What is Centroid Decomposition?

Centroid decomposition is a divide and divide and conquer technique used in the analysis of trees, where the tree is repeatedly divided into subtrees by identifying centroids. A **centroid** of a tree is a node such that when it is removed, no resulting subtree has more than half the total nodes of the original tree. This decomposition splits the tree in a balanced way, allowing efficient processing of problems involving paths, distances, and more.

# Properties of Centroid Decomposition

## **1.Balanced Partition**: 

The centroid of a tree ensures that each subtree formed after its removal has at most half the number of nodes, which makes the decomposition highly balanced.

## **2.Centroid Tree**:

The centroid tree constructed from a tree has a depth of \( O(\log N) \), where \( N \) is the number of nodes in the original tree. **sort of like segment tree**

## **3.Unique Path Property**: 

In the centroid tree, any path between two nodes in **different** subtrees of a centroid must pass through the centroid in real tree.

<img src = "1.jpeg">

**keep in mind that the subtrees must be different, if we are considering two nodes in the same subtree of the centroid tree, we cannot say that, in real tree it will go through the centroid, there might be direct/short edge connection between these two nodes that does not pass through the centroid, [see the lower half of the above picture]**

<img src="2.jpeg" >

# Applications of Centroid Decomposition

Centroid decomposition is useful in solving tree-related problems where path-based queries are involved, and you need efficient updates and queries.

## 1. Path Queries of \( O(N^2) \) can be calculated in  O(N log N) :
   Centroid decomposition can be used to count or sum properties of paths between pairs of nodes in a tree. Since any path between nodes in different subtrees passes through the centroid, the tree can be efficiently processed in \( O(N \log N) \).
   
**Centroid decomposition is particularly useful for problems involving path counting in trees. Because, Once we have computed all the path-related information for a node 'v', we can safely disregard any paths that include 'v'. This allows us to remove 'v' from the tree and apply the same decomposition strategy to the remaining subtrees. By intelligently choosing 'v' as the centroid at each stage, we ensure that each operation takes at most O(NlogN) time, making it a highly efficient approach for solving path-related problems in trees.**

## 2. Distance Problems:
   If we need to compute distances between nodes or find the shortest paths, centroid decomposition helps break down the problem by removing centroids and solving the problem recursively.

## 3. Fixed-Length Paths:
   When tasked with finding paths of a fixed length in a tree, centroid decomposition can reduce the complexity by ensuring that each decomposition step only processes a subtree of size at most half the original.


---

# Some common problems

## Problem: Fixed-Length Paths I:  
[Link to problem](https://cses.fi/problemset/task/2080)

*Given a tree of `n` nodes, your task is to count the number of distinct paths that consist of exactly `k` edges.*

**Main Theory:**  
For each node `v`, calculate all the paths of length `k` that contain `v`. Once we have computed all the path-related information for a node `v`, we can safely disregard any paths that include `v`. This allows us to remove `v` from the tree and apply the same decomposition strategy to the remaining subtrees. By intelligently choosing `v` as the centroid at each stage, we ensure that each operation takes at most \(O(N \log N)\) time, making it a highly efficient approach for solving path-related problems in trees.

---

**Solution:**

```cpp


const int N = 2e5 + 100;

class CentroidDecomposition {
private:
    int n, k;
    set<int> graph[N];
    int cnt[N];    // cnt[i] = number of i-length path from the centroid/root
    int subtree[N];
    int mx_depth;
    int parent[N];

public:
    long long int ans; // ans = total count of exactly k-length paths

    CentroidDecomposition() {
        this->n = 0;
        this->k = 0;
    }

    void addEdge(int u, int v) {
        graph[u].insert(v);
        graph[v].insert(u);
    }

    int dfs(int s, int p) {
        subtree[s] = 1;
        for (auto child: graph[s]) {
            if (child == p) {
                continue;
            }
            subtree[s] += dfs(child, s);
        }
        return subtree[s];
    }

    int centroid(int s, int p, int n) {
        for (auto child: graph[s]) {
            if (child == p) {
                continue;
            }
            if (subtree[child] > n / 2) {
                return centroid(child, s, n);
            }
        }
        return s;
    }

    void build(int s, int p, int k) {
        this->k = k;
        int n = dfs(s, p);
        int c = centroid(s, p, n);

        vector<int> temp(graph[c].begin(), graph[c].end());

        do_for_centroid(c);

        for (auto child: temp) {
            graph[c].erase(child); // tearing apart the graph
            graph[child].erase(c);
            build(child, c, k);
        }
    }

    void do_for_centroid(int c) { // Here, we will calculate how many paths that contain the centroid C
        cnt[0] = 1; // for computation, we consider Centroid to Centroid, zero length path

        mx_depth = 0;

        for (auto child: graph[c]) {
            // current depth = 1, since they are children
            dfs2(child, c, 1, true);  // flag = true, means compute k-length path for this subtree.
            dfs2(child, c, 1, false); // flag = false means calculate cnt[i], for each i-length path from the centroid to subtree node.

            // For each child, we get a different subtree,
            // We know that if we go from one subtree node to another subtree node, we must visit the centroid.
            // Since we are calculating the k-length path that goes through the centroid, we must process each subtree differently.
            // Also, to avoid recomputation, we must use two different dfs2() calls, so that for each i, we don't count cnt[k-i] of the same subtree, which wouldn't visit through the centroid.
        }

        for (int i = 0; i <= mx_depth + 1; i++) {
            cnt[i] = 0; // clearing
        }
    }

    void dfs2(int s, int p, int depth, bool flag) {
        if (k - depth < 0) {
            return;
        }

        if (flag) { // calculate k-length path
            ans += cnt[k - depth];  // from all the visited different subtrees, we get the count of k-depth path,
                                    // from this subtree we take the current path, whose length is depth, so total length of each path = k - depth + depth = k
        } else { // flag = false
            cnt[depth]++;
        }

        mx_depth = max(depth, mx_depth);

        for (auto child: graph[s]) {
            if (child == p) {
                continue;
            }

            dfs2(child, s, depth + 1, flag);
        }
    }

} CD;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        CD.addEdge(a, b);
    }

    CD.build(1, 1, k);

    cout << CD.ans << endl;
}
```

---

**Above solution will give TLE, but its easier for understanding, use this solution:**
**for faster, use processed[i] to mark which node is already removed, like this implementation**

```cpp
const int N = 2e5 + 100;

class CentroidDecomposition {
private:
    int n, k;
    vector<int> graph[N];
    bool processed[N]; // processed[i] = i-th node has been removed from the graph
    int cnt[N];    // cnt[i] = number of i-length paths from the centroid/root
    int subtree[N];
    int mx_depth;
    int parent[N];

public:
    long long int ans; // ans = total count of exactly k-length paths

    CentroidDecomposition() {
        this->n = 0;
        this->k = 0;
        fill(processed, processed + N, false);
    }

    void addEdge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int dfs(int s, int p) {
        subtree[s] = 1;
        for (auto child : graph[s]) {
            if (child == p || processed[child]) {
                continue;
            }
            subtree[s] += dfs(child, s);
        }
        return subtree[s];
    }

    int centroid(int s, int p, int n) {
        for (auto child : graph[s]) {
            if (child == p || processed[child]) {
                continue;
            }
            if (subtree[child] > n / 2) {
                return centroid(child, s, n);
            }
        }
        return s;
    }

    void build(int s, int p, int k) {
        this->k = k;
        int n = dfs(s, p);
        int c = centroid(s, p, n);

        processed[c] = true;

        do_for_centroid(c);

        for (auto child : graph[c]) {
            if (processed[child]) {
                continue;
            }
            build(child, c, k);
        }
    }

    void do_for_centroid(int c) { // Calculate how many paths contain the centroid C
        cnt[0] = 1; // for computation, we consider Centroid to Centroid, zero length path

        mx_depth = 0;

        for (auto child : graph[c]) {
            if (processed[child]) {
                continue;
            }

            // Current depth = 1, since they are children
            dfs2(child, c, 1, true);  // flag = true, compute k-length path for this subtree.
            dfs2(child, c, 1, false); // flag = false, calculate cnt[i], for each i-length path from centroid to subtree node.

            // For each child, we get a different subtree.
            // We know that if we go from one subtree node to another subtree node, we must visit the centroid.
            // Since we are calculating the k-length path that goes through the centroid, we must process each subtree differently.
            // To avoid recomputation, we use two different dfs2() calls.
        }

        for (int i = 0; i <= mx_depth + 1; i++) {
            cnt[i] = 0; // Clearing
        }
    }

    void dfs2(int s, int p, int depth, bool flag) {
        if (k - depth < 0) {
            return;
        }

        if (flag) { // Calculate k-length path
            ans += cnt[k - depth];  // From all the visited different subtrees, we get the count of k-depth path,
                                    // from this subtree we take the current path, whose length is depth, so total length of each path = k - depth + depth = k
        } else { // flag = false
            cnt[depth]++;
        }

        mx_depth = max(depth, mx_depth);

        for (auto child : graph[s]) {
            if (child == p || processed[child]) {
                continue;
            }

            dfs2(child, s, depth + 1, flag);
        }
    }
} CD;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        CD.addEdge(a, b);
    }

    CD.build(1, 1, k);

    cout << CD.ans << endl;
}
```



## Problem: [Xenia and Tree](https://codeforces.com/contest/342/problem/E)

Xenia has a tree with `n` nodes. Initially, node 1 is painted red, while others are blue. She needs to handle two types of queries:

1. **Paint a blue node red**.
2. **Find the shortest distance from a node to the nearest red node**.

### Approach

For each centroid , we store the distance of the closest red node within its subtree from the centroid. When processing a query, we use this information to determine the shortest distance to the nearest red node by traversing the centroid tree. Since the tree is divided into subtrees with at most NlogN depth levels, this allows us to answer queries efficiently with only a few jumps up (at most logN) the tree hierarchy.  

#### Steps:

1. **Centroid Decomposition**: We recursively divide the tree, calculating distances for centroids and storing them.
2. **Update Query**: When painting a node red, update its distance to the centroids.
3. **Distance Query**: For a given node, check the nearest red node by using the stored centroid distances.

---

### Code Implementation

```cpp

const int inf = 1e9;

class CentroidDecomposition {
private:
    const static int N = 1e5 + 5;
public:
    set<int> graph[N];
    map<int, int> dis[N];
    int subtree[N], parent[N], ans[N];

    CentroidDecomposition(int n) {
        for(int i = 0; i <= n; i++) {
            graph[i].clear();
            subtree[i] = 0;
            parent[i] = 0;
            ans[i] = inf;
        }
    }

    void addEdge(int x, int y) {
        graph[x].insert(y);
        graph[y].insert(x);
    }

    int dfs(int s, int p) {
        subtree[s] = 1;
        for(auto child : graph[s]) {
            if(child == p) continue;
            subtree[s] += dfs(child, s);
        }
        return subtree[s];
    }

    int centroid(int s, int p, int n) {
        for(auto child : graph[s]) {
            if(child == p) continue;
            if(subtree[child] > n / 2)
                return centroid(child, s, n);
        }
        return s;
    }

    void dfs2(int s, int p, int c, int d) {
        dis[c][s] = d;
        for(auto child : graph[s]) {
            if(child == p) continue;
            dfs2(child, s, c, d + 1);
        }
    }

    void build(int s, int p) {
        int n = dfs(s, p);
        int c = centroid(s, p, n);

        if(p == -1) p = c;
        parent[c] = p;

        dfs2(c, p, c, 0);

        vector<int> temp(graph[c].begin(), graph[c].end());
        for(auto child : temp) {
            graph[c].erase(child);
            graph[child].erase(c);
            build(child, c);
        }
    }

    void modify(int s) {
        for(int c = s; c != 0; c = parent[c]) {
            ans[c] = min(ans[c], dis[c][s]);   //For each centroid, we have stored the information of the closest red node among all the nodes its subtree, Then we jump above the centroid tree to reach upper centroid, to compare it to the closest red nodes of other subtrees.
        }
    }

    int query(int s) {
        int mn = inf;
        for(int c = s; c != 0; c = parent[c]) {
            mn = min(mn, ans[c] + dis[c][s]);   
        }
        return mn;
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    CentroidDecomposition cd(n);

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        cd.addEdge(u, v);
    }

    cd.build(1, 0);
    cd.modify(1); // Initially, node 1 is red

    while(q--) {
        int a, v;
        cin >> a >> v;
        if(a == 1) {
            cd.modify(v); // Paint node v red
        } else {
            cout << cd.query(v) << endl; // Query closest red node
        }
    }
}
```

---

Here's a well-structured explanation of the problem and its solution:

---


## Problem Type: Count the number of distinct paths with at least \( k1 \) and at most \( k2 \) edges.

**Link:** [Codeforces Problem A](https://codeforces.com/gym/101991/problem/A)

**Context:** Fouad is in a city represented as an undirected tree. To acquire a magical oven for his shawarma, he needs to satisfy two conditions:

1. Add one extra edge to join two different nodes in the tree.
2. The number of bridges (edges whose removal disconnects the tree) after adding this new edge should be between [L, R] inclusively.

**Objective:** Count the number of ways to add an edge such that the above conditions are met.

**this problem essentially comes down to at least \( k1 \) and at most \( k2 \) edges problem**

---

**Code Implementation:**

```cpp

const int NN = 1e5+10;
int n;

class CentroidDecomposition {
private:
    set<int> graph[NN];
    int subtree[NN];
    int cnt[NN];
    int BIT[NN];
    int mx_depth;
    int N;

public:
    int k1, k2;
    int ans;

    CentroidDecomposition() {}

    void clear() {
        for (int i = 0; i <= n; i++) {
            graph[i].clear();
            subtree[i] = 0;
            cnt[i] = 0;
            BIT[i] = 0;
        }
        N = n;
        mx_depth = 0;
    }

    void addEdge(int u, int v) {
        graph[u].insert(v);
        graph[v].insert(u);
    }

    int dfs(int s, int p) {
        subtree[s] = 1;
        for (auto child : graph[s]) {
            if (child == p) continue;
            subtree[s] += dfs(child, s);
        }
        return subtree[s];
    }

    int centroid(int s, int p, int n) {
        for (auto child : graph[s]) {
            if (child == p) continue;
            if (subtree[child] > n / 2) {
                return centroid(child, s, n);
            }
        }
        return s;
    }

    void build(int s, int p) {
        int n = dfs(s, p);
        int c = centroid(s, p, n);
        vector<int> temp(graph[c].begin(), graph[c].end());

        do_for_centroid(c);

        for (auto child : temp) {
            graph[child].erase(c);
            graph[c].erase(child);
            build(child, c);
        }
    }

    void do_for_centroid(int c) {
        mx_depth = 0;
        for (auto child : graph[c]) {
            dfs2(child, c, 1, true);
            dfs2(child, c, 1, false);
        }
        for (int i = 1; i <= mx_depth; i++) {
            int val = query(i) - query(i - 1);
            update(i, -val);
        }
    }

    void dfs2(int s, int p, int depth, bool flag) {
        if (k2 - depth < 0) return;
        if (flag) {
            int l1 = k1 - depth;
            int l2 = k2 - depth;
            ans += query(l2) - query(l1 - 1);
            if (l1 <= 0 && l2 >= 0) {
                ans += 1;
            }
        } else {
            update(depth, 1);
        }
        mx_depth = max(mx_depth, depth);
        for (auto child : graph[s]) {
            if (child == p) continue;
            dfs2(child, s, depth + 1, flag);
        }
    }

    void update(int x, int val) {
        for (; x < N; x += (x & -x)) {
            BIT[x] += val;
        }
    }

    int query(int x) {
        int sum = 0;
        for (; x > 0; x -= (x & -x)) {
            sum += BIT[x];
        }
        return sum;
    }
} CD;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("awesome.in", "r", stdin);

    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        CD.clear();
        int l, r;
        cin >> l >> r;

        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            CD.addEdge(a, b);
        }

        CD.ans = 0;
        int eg = n - 1;
        CD.k1 = eg - r;
        CD.k2 = eg - l;

        CD.build(1, 1);

        cout << CD.ans << endl;
    }
}
```

---

Here is a well-organized problem description and solution for the CodeChef problem "Count of Occurrence of Each Length Paths":

---

## Problem: Count of Occurrence of Each Length Paths

**Link:** [CodeChef Problem PRIMEDST](https://www.codechef.com/problems/PRIMEDST)

**Description:** You are given a tree. If we select two distinct nodes uniformly at random, what is the probability that the distance between these two nodes is a prime number?

**Objective:** Compute the probability that the distance between two randomly chosen nodes is a prime number.


```cpp
// Count of occurrence of each length paths
// all possible length, exists how many times.
// all_cnt[i] = how many i-length paths exist.

const int N = 5e4 + 100;

class CentroidDecomposition
{
private:
    // Private members can be added here

public:
    int n, k;
    vector<int> graph[N];
    int cnt[N];    
    int subtree[N];
    int mx_depth;
    int parent[N];
    bool processed[N];
    long long int ans; 
    int mx;
    int all_cnt[N];

    CentroidDecomposition()
    {
        this->n = 0;
        this->k = 0;
    }

    void addEdge(int u, int v)
    {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int dfs(int s, int p)
    {
        subtree[s] = 1;
        for (auto child : graph[s])
        {
            if (child == p || processed[child])
            {
                continue;
            }
            subtree[s] += dfs(child, s);
        }
        return subtree[s];
    }

    int centroid(int s, int p, int n)
    {
        for (auto child : graph[s])
        {
            if (child == p || processed[child])
            {
                continue;
            }
            if (subtree[child] > n / 2)
            {
                return centroid(child, s, n);
            }
        }
        return s;
    }

    void build(int s, int p)
    {
        int n = dfs(s, p);
        int c = centroid(s, p, n);

        processed[c] = true;

        do_for_centroid(c);

        for (auto child : graph[c])
        {
            if (processed[child])
            {
                continue;
            }
            build(child, c);
        }
    }

    void do_for_centroid(int c) // Here, we will calculate how many paths contain the centroid C
    {
        cnt[0] = 1; // For computation, we consider Centroid to Centroid, zero length path

        mx_depth = 0;

        for (auto child : graph[c])
        {
            if (processed[child])
            {
                continue;
            }

            // Current depth = 1, since they are children
            dfs2(child, c, 1, true);  // Flag = true means compute k-length path for this subtree
            dfs2(child, c, 1, false); // Flag = false means calculate cnt[i], for each i-length path from the centroid to subtree node
        }

        for (int i = 0; i <= mx_depth + 1; i++)
        {
            cnt[i] = 0; // Clearing
        }
    }

    void dfs2(int s, int p, int depth, bool flag)
    {
        mx_depth = max(depth, mx_depth);

        if (flag)
        {
            for (int i = 1; i <= mx_depth; i++)
            {
                all_cnt[i + depth] += cnt[i]; // Increasing the count of (i+depth)-length paths
            }
        }
        else // flag = false 
        {
            cnt[depth]++;
            all_cnt[depth]++;
        }

        for (auto child : graph[s])
        {
            if (child == p || processed[child])
            {
                continue;
            }
            dfs2(child, s, depth + 1, flag);
        }
    }
} CD;

vector<int> primes;
bool sieve[N];

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 2; i < N; i++)
    {
        if (!sieve[i])
        {
            primes.push_back(i);
            for (int j = i + i; j < N; j += i)
            {
                sieve[j] = true;
            }
        }
    }

    int n;
    cin >> n;

    vector<pair<int, int>> P;

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        CD.addEdge(a, b);
    }

    CD.build(1, 1);

    int ans = 0;

    for (int i = 0; i < primes.size(); i++)
    {
        int k = primes[i];
        ans += CD.all_cnt[k];
    }

    double total = n * 1LL * (n - 1) / 2.0;

    cout << setprecision(18) << ((ans * 1.00) / total) << endl;

    return 0;
}
```

---
