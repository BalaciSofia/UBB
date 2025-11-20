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
        Performs BFS in graph ending at `end`.
        Returns the tree as a dictionary mapping each vertex to its parent; parent[start] = None
        '''
        idx = 0
        queue = [end]
        parent = {}
        parent[end] = None
        while idx < len(queue):
            current = queue[idx]
            for node in self.parse_in(current):
                if node not in parent.keys():
                    parent[node] = current
                    queue.append(node)
            idx += 1
        return parent

    def shortest_path(self, start, end):
        '''
            Finds the shortes (min length) path from start to dest in graph g.
            Precond: start and dest are vertices in g.
            Returns the path as a list of vertices along it. Returns None if no path exists.
        '''
        tree=self.bfs(end)
        if start not in tree:
            return None
        path = []
        current = start
        while current is not None:
            path.append(current)
            current = tree[current]
        return path

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
                edges.append((vertex1, vertex2, cost))
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
                g.append_edge(vertex1, vertex2, cost)
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
