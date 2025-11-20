import heapq
from random import randint, random


class DirectedGraph:
    def __init__(self, v=None, in_edges=None, out_edges=None, costs=None):
        if in_edges is None and out_edges is None and costs is None:
            self._out_edges = {}
            self._in_edges = {}
            self._costs = {}
            if v is None:
                v = []
            if isinstance(v, int):
                for i in range(v):
                    self._out_edges[i] = []
                    self._in_edges[i] = []
            else:
                for i in v:
                    self._out_edges[i] = []
                    self._in_edges[i] = []
        else:
            self._out_edges = out_edges
            self._in_edges = in_edges
            self._costs = costs

    def get_in_edges(self):
        return self._in_edges

    def get_out_edges(self):
        return self._out_edges

    def get_costs(self):
        return self._costs

    def number_of_vertices(self):
        return len(self._in_edges.keys())

    def parse_vertices(self):
        return self._out_edges.keys()

    def is_edge(self, x, y):
        if not self.valid_vertex(x):
            raise ValueError("Vertex {} does not exist.".format(x))
        if not self.valid_vertex(y):
            raise ValueError("Vertex {} does not exist.".format(y))
        return y in self._out_edges[x]

    def inout_degree(self, x):
        if not self.valid_vertex(x):
            raise ValueError("Vertex {} does not exist.".format(x))
        return len(self._in_edges[x]), len(self._out_edges[x])

    def parse_out(self, x):
        if not self.valid_vertex(x):
            raise ValueError("Vertex {} does not exist.".format(x))
        return list(self._out_edges[x])

    def parse_in(self, y):
        if not self.valid_vertex(y):
            raise ValueError("Vertex {} does not exist.".format(y))
        for x in self._in_edges[y]:
            yield x

    def get_cost(self, v1, v2):
        if not self.valid_vertex(v1):
            raise ValueError('vertex {} not in graph'.format(v1))
        if not self.valid_vertex(v2):
            raise ValueError('vertex {} not in graph'.format(v2))
        if not self.is_edge(v1, v2):
            raise ValueError(f'Edge ({v1}, {v2}) not in graph')
        return self._costs[(v1, v2)]

    def update_cost(self, v1, v2, cost):
        if not self.valid_vertex(v1):
            raise ValueError('vertex {} not in graph'.format(v1))
        if not self.valid_vertex(v2):
            raise ValueError('vertex {} not in graph'.format(v2))
        if not self.is_edge(v1, v2):
            raise ValueError(f'Edge ({v1}, {v2}) not in graph')
        self._costs[(v1, v2)] = cost

    def append_edge(self, x, y, c):
        if not self.valid_vertex(x):
            raise ValueError("Vertex {} does not exist.".format(x))
        if not self.valid_vertex(y):
            raise ValueError("Vertex {} does not exist.".format(y))
        if self.is_edge(x, y):
            raise ValueError("Edge already exists")
        self._out_edges[x].append(y)
        self._in_edges[y].append(x)
        self._costs[(x, y)] = c
        return True

    def delete_edge(self, x, y):
        if not self.valid_vertex(x):
            raise ValueError("Vertex {} does not exist.".format(x))
        if not self.valid_vertex(y):
            raise ValueError("Vertex {} does not exist.".format(y))
        if not self.is_edge(x, y):
            raise ValueError("Edge does not exist")
        self._costs.pop((x, y))
        self._out_edges[x].remove(y)
        self._in_edges[y].remove(x)

    def append_vertex(self, x):
        if self.valid_vertex(x):
            raise ValueError("Vertex {} already exists.".format(x))
        self._out_edges[x] = []
        self._in_edges[x] = []

    def delete_vertex(self, x):
        if not self.valid_vertex(x):
            raise ValueError("Vertex {} does not exist.".format(x))
        for e in list(self.parse_out(x)):
            self.delete_edge(x, e)
        for e in list(self.parse_in(x)):
            self.delete_edge(e, x)
        del self._in_edges[x]
        del self._out_edges[x]

    def valid_vertex(self, v):
        return v in self._in_edges.keys()

    def __str__(self):
        res = []
        res.append("Outbound:")
        for x in self.parse_vertices():
            res.append(f"{x}: " + " ".join(map(str, self.parse_out(x))))
        res.append("Inbound:")
        for x in self.parse_vertices():
            res.append(f"{x}: " + " ".join(map(str, self.parse_in(x))))
        return "\n".join(res)

    def copy(self):
        in_copy = self._in_edges.copy()
        out_copy = self._out_edges.copy()
        costs_copy = self._costs.copy()
        return DirectedGraph(None, in_copy, out_copy, costs_copy)

    def bfs(self, end):
        '''
        Performs a backwards BFS (starting from the end node) to build a parent map.
        parameter end: The destination node in the graph.
        return: parent (dictionary): A mapping of each node to its parent in the BFS tree,where parent[end] = None.
        '''
        idx = 0  # current position in the queue
        queue = [end]  # initializing queue with the end node
        parent = {}  # dictionary to store each node's parent in BFS tree
        parent[end] = None  # end has no parent since it's the root of the BFS tree
        while idx < len(queue):
            current = queue[idx]  # get current node from queue
            # Traverse all nodes that point to current (hence parse_in)
            for node in self.parse_in(current):
                if node not in parent:  # If the node hasn't been visited yet
                    parent[node] = current  # Set its parent
                    queue.append(node)  # Add node to the queue
            idx += 1
        return parent

    def shortest_path(self, start, end):
        '''
        Finds the shortest path from start to end using BFS.
        This uses the bfs(end) function which performs a reverse BFS from end
        parameter start: Starting node.
        parameter end: Ending node.
        return path: the list of nodes from start to end,or None if the path does not exist.
        '''
        if not self.valid_vertex(start):
            raise ValueError("Vertex {} does not exist.".format(start))
        if not self.valid_vertex(end):
            raise ValueError("Vertex {} does not exist.".format(end))
        tree = self.bfs(end)  # get the BFS tree rooted at end
        if start not in tree:
            return None  # no path
        path = []
        current = start
        #reconstruct path by walking through the parent dict from start to end
        while current is not None:
            path.append(current)
            current = tree[current]
        return path

    def cheapest_walk(self, start, end):
        """
        Finds the lowest cost path from start to end using Bellman-Ford algorithm
        :param start:the starting vertex
        :param end:the ending vertex
        :return: (list of vertices in the path, total cost), or (None, None) if unreachable
        raises an exception if there are negative cost cycles accessible from the starting vertex or if the vertices do not exist
        """
        if not self.valid_vertex(start):
            raise ValueError("Vertex {} does not exist.".format(start))
        if not self.valid_vertex(end):
            raise ValueError("Vertex {} does not exist.".format(end))
        dist={} # dist[x]=the cost of the minimum cost walk from start to x at one point
        prev={} # prev[x]=the vertex just before x in the walk
        vertices=self.parse_vertices()
        for node in vertices:#O(vertices)
            dist[node] = float("inf") #initialize dist[node] with infinity in order to compare and find the cheapest walk
        dist[start] = 0 #the cost of the walk from start to itself is 0
        #relaxing all edges max no of vertices-1 times
        #because the shortest possible path between any two nodes can only have (no of vertices-1) edges
        changed=True
        max_iter=len(vertices)-1
        index=0
        while changed and index < max_iter :
            changed = False
            for (x,y) in self._costs.keys():
                if dist[x]!=float("inf"):
                    if dist[x]+self.get_cost(x,y) < dist[y]:
                        dist[y] = dist[x]+self.get_cost(x,y)
                        prev[y]=x
                        changed = True
            index+=1
        #O(v*e)
        #check for negative cost cycles
        #if one more relax can be done it means we have a negative cycle
        for (x, y) in self._costs.keys():
            if dist[x] != float("inf"):
                if dist[x] + self.get_cost(x, y) < dist[y]:
                    raise ValueError("Negative weight cycle detected from vertex", start)
        #check if the end is reachable
        if dist[end] == float('inf'):
            return (None, None)
        else:
            #retrive walk
            walk = []
            current = end
            while current is not None:
                walk.append(current)
                if current == start:
                    break
                current = prev[current]  # move one step back
            walk.reverse()  # reverse the list to show path from start to end
            return walk, dist[end]

    def min_spanning_tree(self, start):
        """
        Finds the minimum spanning tree starting at vertex start using Prim's algorithm.
        :return: the list of edges in the minimum spanning tree and the cost of it.Throws an error if the starting vertex does not exist.
        """
        if not self.valid_vertex(start):
            raise ValueError("Vertex {} does not exist.".format(start))
        q = []  #priority queue: list of tuples (cost, node)
        prev = {}  #stores the parent of each node
        dist = {}  #stores the minimum cost to reach each node
        edges = []  #edges in the mst
        total_cost = 0  #total cost of the mst
        vertices = {start}  #nodes in the mst

        #initialize distances for neighbors of start
        for x in self.parse_out(start):
            dist[x] = self.get_cost(start, x)#distance up to node x is the cost of the edge
            prev[x] = start#prev of node x is start
            heapq.heappush(q, (dist[x], x))#nodes to visit next prioritized by cost

        # for x in self.parse_in(start):
        #     dist[x] = self.get_cost(x, start)
        #     prev[x] = start
        #     heapq.heappush(q, (dist[x], x))

        #build mst
        while q:#repeat while there are still
            cost_x, x = heapq.heappop(q)#pop the node with the smallest cost
            if x not in vertices:#if the node is not already in the mst
                edges.append((prev[x], x))#add the edge to the mst
                total_cost += cost_x#increase the total cost
                vertices.add(x)#mark node as visited
                for y in self.parse_out(x):#get all the neighbours of node that was just added to the mst
                    cost_xy = self.get_cost(x, y)
                    if y not in dist or cost_xy < dist[y]:#if the neighbour is not visited yet or we found a cheaper edge to get to it
                        dist[y] = cost_xy#the distance is updated
                        prev[y] = x#the prev of y is x
                        heapq.heappush(q, (dist[y], y))#add it to the queue
                # for y in self.parse_in(x):
                #     cost_xy = self.get_cost(y, x)
                #     if y not in dist or cost_xy < dist[y]:
                #         dist[y] = cost_xy
                #         prev[y] = x
                #         heapq.heappush(q, (dist[y], y))
        return edges, total_cost

    def min_vertex_cover_version1(self):
        """
        Approximation algorithm.
        Returns: (size of cover, set of vertices in the cover)
        """
        edges = set()
        for u in self._out_edges:
            for v in self._out_edges[u]:
                edges.add((u, v))
        vertices = set()
        while edges:
            u, v= edges.pop()#select an edge
            vertices.add(u)#add the two of them to the solution
            vertices.add(v)
            #remove all edges incident to u or v
            new_edges = set()
            for e in edges:
                if u not in e and v not in e:
                    new_edges.add(e)
            edges = new_edges
        return len(vertices), vertices

    def min_vertex_cover_version2(self):
        """
        Greedy heuristic.
        Returns: (size of cover, set of vertices in the cover)
        """
        edges = set()
        for x in self._out_edges:
            for y in self._out_edges[x]:
                edges.add((x, y))
        vertices = set()
        while edges:
            #for all the edges left count how many times each vertex appears
            degree_count = {}
            for u, v in edges:
                degree_count[u] = degree_count.get(u, 0) + 1
                degree_count[v] = degree_count.get(v, 0) + 1
            #pick the one with the maximum degree
            best_vertex = max(degree_count, key=degree_count.get)
            #add it to the solution
            vertices.add(best_vertex)
            #remove all edges incident to best_vertex
            edges = {(u, v) for (u, v) in edges if u != best_vertex and v != best_vertex}
        return len(vertices), vertices

# ----------------------------------------------------------------------------------------------------
def read_graph_from_file(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
        form = lines[0].strip()
        if form == 'special':
            nov = lines[1].strip().split()[0]
            noe = lines[1].strip().split()[1]
            isolated = lines[2].strip().split()
            li = []
            for i in isolated:
                i = int(i)
                li.append(i)
            edges = []
            for line in lines[3:]:
                line = line.strip()
                if line == "":
                    continue
                parts = line.split()
                vertex1 = int(parts[0])
                vertex2 = int(parts[1])
                if vertex1 not in li:
                    li.append(vertex1)
                if vertex2 not in li:
                    li.append(vertex2)
                cost = int(parts[2])
                try:
                    edges.append((vertex1, vertex2, cost))
                    edges.append((vertex2, vertex1, cost))
                except:
                    continue
            g=DirectedGraph(li)
            for e in edges:
                g.append_edge(e[0], e[1], e[2])
        else:
            l = lines[0].strip().split()
            g = DirectedGraph(int(l[0]))
            for line in lines[1:]:
                line = line.strip()
                if line == "":
                    continue
                parts = line.split()
                vertex1 = int(parts[0])
                vertex2 = int(parts[1])
                cost = int(parts[2])
                try:
                    g.append_edge(vertex1,vertex2,cost)
                    g.append_edge(vertex2, vertex1, cost)
                except:
                    continue
    return g


def write_graph_to_file(g, filename):
    with open(filename, "w") as f:
        f.write("special\n")
        isolated = []
        for v in g.parse_vertices():
            if g.inout_degree(v)[0] == 0 and g.inout_degree(v)[1] == 0:
                isolated.append(v)
        f.write(str(g.number_of_vertices()) + " ")
        no_edges = len(g.get_costs())
        f.write(str(no_edges) + "\n")
        vertices = ""
        for x in isolated:
            vertices = vertices + f"{x} "
        f.write(vertices + "\n")
        for vertex1 in g.parse_vertices():
            for vertex2 in g.parse_out(vertex1):
                f.write(f"{vertex1} {vertex2} {g.get_cost(vertex1, vertex2)}\n")


def random_graph(n, m):
    if m > n ** 2:
        raise ValueError("m must be smaller than n^2")
    g = DirectedGraph(n)
    for i in range(m):
        x = randint(0, n - 1)
        y = randint(0, n - 1)
        c = randint(0, n - 1)
        while g.is_edge(x, y):
            x = randint(0, n - 1)
            y = randint(0, n - 1)
            c = randint(0, n - 1)
        g._out_edges[x].append(y)
        g._in_edges[y].append(x)
        g._costs[(x, y)] = c
    return g
