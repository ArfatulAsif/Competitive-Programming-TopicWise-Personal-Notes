Here is your corrected text with mathematical expressions formatted using `$$` or `$` for LaTeX:

---

Terminology:

**Flow Network:** A flow network $N$ is a weighted directed graph $G$, where the weight of edges is called capacity. Two distinguished vertices $s$ (no incoming edges) and $t$ (no outgoing edges) are called source and sink.

**Flow:** The value of a flow $f$, denoted $|f|$, is the total flow from the source $s$, which is equal to the total flow coming into the sink $t$.

**Maximum Flow:** The maximum flow problem involves finding the maximum flow from the source $s$ to the sink $t$ in a flow network $N$.

**Cut:** A cut of a flow network $N$ is a partition of vertices $X = (V_s, V_t)$, where $V_s$ is the set of vertices that includes the source $s$, and $V_t$ is the set of vertices that includes the destination $t$.

**Forward edge of a cut $X$:** Origin in $V_s$ and destination in $V_t$.  
**Backward edge of a cut $X$:** Origin in $V_t$ and destination in $V_s$.

**Capacity of a cut $C(X)$:** Total capacity of forward edges.  
**Flow of a cut $f(X)$:** Total flow of forward edges minus the total flow of backward edges.

**Theorem:** The flow value across the network $N$, $|f|$, is equal to the flow of any cut $f(X)$.  
**Theorem:** The value of any flow (flow of a cut or the entire network) is less than or equal to the capacity of any cut.

**Minimum Cut:** A minimum cut is the cut whose capacity is the smallest among all possible cuts.  

In a graph, there can be multiple minimum cuts.

**Theorem (Max-Flow Min-Cut):** The value of the maximum flow is equal to the capacity of the minimum cut.

If we can find the capacity of the minimum cut, then we have found the maximum flow. However, finding the capacity of the minimum cut is more difficult than finding the maximum flow using max flow algorithms.

---

**Residual capacity of edge and path:**

[Include image of slide 7]

**Augmenting Path:**  
[Include image of slide 7, only with the part "A path $p$ from $s$ to $t$ is an augmenting path if $Df(p) > 0$."]

**Residual Network:** If we replace the flow/capacity of the edges with the residual capacity of the edges, then the flow network we get is called the residual network.

[Image of slide 8]

---

**Flow Augmentation:** This is the key iteration in all flow algorithms when finding the maximum flow.

While running the max flow algorithm, in each DFS or BFS iteration, it involves increasing the flow along an augmenting path.  

**Flow augmentation involves:**  
**Forward edges:** Increasing the flow of each by the amount of the residual capacity of the augmenting path.  
**Backward edges:** Decreasing the flow of each edge by the amount of the residual capacity of the augmenting path. [This is very important to understand.] [We can think of it as undoing some flow.]

---

**Why decrease backward edges flow?** Let’s understand it with an example:  

[Include "my khata" photo]  

Let’s say the current flow considered is [image description]. By direct observation, if we don't undo $v \to w$ flow $5$ and consider flow $5$ towards $v \to t$, there is no way to increase the max flow of the network.

So, let’s consider an augmenting path in the flow $s \to u \to w \to v \to t$.  

Look at the $w \to v$ edge. It is reversed, i.e., $v \to w$ exists but not $w \to v$. But we have to consider $w \to v$ because there might be the possibility of undoing $v \to w$ flow. How? Let’s look.

If we perform flow augmentation along $s \to u \to w \to v \to t$, the network becomes [third photo].

Previously, $s \to v$ flow was $5$, which went through $v \to w$ and then $w \to t$. Now $v \to w$ is $0$, and $v \to t$ is $5$.

Now the question is: does this mean a flow is happening in this path $s \to u \to w \to v \to t$? The answer is NO. What actually happened was, initially, we considered flow $s \to v \to w \to t$, but it blocked any flow from $s \to u$ in that direction.  

So, we needed to cancel out or undo $v \to w$ flow, which we did by considering $w \to v$ along $s \to u \to w \to v \to t$.  

Thus, the flow is actually happening along $s \to v \to t (5)$ and $s \to u \to w \to t (5)$.

---

If we don’t consider flow undoing (sending flow through reverse edges), we would have to find an algorithm that always chooses augmenting paths intelligently. This is an NP-Hard problem.

However, if we consider flow undoing (sending flow through reverse edges), we can arbitrarily choose any augmenting path without worry. If the current path was not ideal, in a later iteration, we can undo the flow of edges.

This is exactly what max flow algorithms do, which is why they have polynomial complexity.

For a max flow algorithm, we need to add a reverse edge for each edge.

[Last image]

**Capacity of edge:** Equal to the capacity of the edge.  
**Capacity of reverse edge:** Equal to the flow of the edge. [Why? Because that is the maximum amount of flow we can cancel or undo for this edge.]

[That’s it. Now you are ready for all algorithms.]

---
