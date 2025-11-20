from graph import *
def print_menu():
    print("1: Get number of vertices")
    print("2: Display the set of vertices")
    print("3: Check if there is an edge between 2 vertices")
    print("4: Get in/out degree of a vertice")
    print("5: Display the set of outbound edges of a specified vertex")
    print("6: Display the set of inbound edges of a specified vertex")
    print("7: Modify the cost attached to a specified edge.")
    print("8: Get cost attached to a specified edge.")
    print("9: Add edge")
    print("10: Remove edge")
    print("11: Add vertex")
    print("12: Remove vertex")
    print("13: Read graph from file")
    print("14: Write graph to file")
    print("15: Create random graph")
    print("16: Print graph")
    print("17: Copy graph and write to file")
    print("18: Second assignment(2.lowest length path between 2 given vertices,by using a backward breadth-first search from the ending vertex)")
    print("19: Third assignment(3.lowest cost walk between the given vertices, using Fords Algorithm)")
    print("20: Fourth assignment(6.constructs a minimal spanning tree using the Prim's algorithm)")
    print("21: Fifth assignment(7.find a covering of edges by vertices with no more than twice the optimal number of vertices in O(n+m) time.")
    print("22: Fifth assignment -version 2")
    print("e: Exit")
    print("==================================================================================")


def main():
    g = DirectedGraph()
    commands = {
        '1': number_vertices,
        '2': display_vertices,
        '3': check_edge,
        '4': get_inout_degree,
        '5': outbound_edges,
        '6': inbound_edges,
        '7': modify_cost,
        '8': get_cost,
        '9': add_edge,
        '10': remove_edge,
        '11': add_vertex,
        '12': remove_vertex,
        '13': read_graph_file,
        '14': write_graph_file,
        '15': create_random_graph,
        '16': print_graph,
        '17': copy_write_graph,
        '18': shortest_length,
        '19': lowest_cost_walk,
        '20': minimum_span_tree,
        '21': minimum_vertex_cover_v1,
        '22': minimum_vertex_cover_v2
    }

    while True:
        print_menu()
        command = input(">>>").strip()

        if command == 'e':
            print("Exiting...")
            break
        elif command in commands:
            if command == '13':
                new_graph = read_graph_file()
                if new_graph:
                    g = new_graph
            elif command == '15':
                new_graph = create_random_graph()
                if new_graph:
                    g = new_graph
            else:
                commands[command](g)
        else:
            print("Invalid command")


def number_vertices(g):
    print("number of vertices:",g.number_of_vertices())

def display_vertices(g):
    vertices=g.parse_vertices()
    for v in vertices:
        print(v)

def check_edge(g):
    x=input("Enter the vertex x >")
    y=input("Enter the vertex y >")
    try:
        x=int(x)
        y=int(y)
        if g.is_edge(x,y):
            print("Edge exists")
        else:
            print("Edge does not exist")
    except ValueError as e:
        print(e)

def get_inout_degree(g):
    x=input("Enter vertex >")
    try:
        x=int(x)
        print("In degree:",g.inout_degree(x)[0])
        print("Out degree:",g.inout_degree(x)[1])
    except ValueError as e:
        print(e)

def outbound_edges(g):
    x = input("Enter vertex >")
    try:
        x = int(x)
        outbounds=g.parse_out(x)
        for o in outbounds:
            print(o)
    except ValueError as e:
        print(e)

def inbound_edges(g):
    x=input("Enter vertex >")
    try:
        x=int(x)
        inbounds=g.parse_in(x)
        for i in inbounds:
            print(i)
    except ValueError as e:
        print(e)

def modify_cost(g):
    x = input("Enter the vertex x >")
    y = input("Enter the vertex y >")
    c = input("Enter new cost >")
    try:
        x = int(x)
        y = int(y)
        c = int(c)
        g.update_cost(x,y,c)
    except ValueError as e:
        print(e)

def get_cost(g):
    print("Enter the edge (x,y)")
    x = input("Enter the vertex x >")
    y = input("Enter the vertex y >")
    try:
        x = int(x)
        y = int(y)
        print(f"The cost of the edge({x},{y}) is {g.get_cost(x,y)}")
    except ValueError as e:
        print(e)

def add_edge(g):
    x = input("Enter the vertex x >")
    y = input("Enter the vertex y >")
    c = input("Enter cost >")
    try:
        x = int(x)
        y = int(y)
        c = int(c)
        g.append_edge(x, y, c)
    except ValueError as e:
        print(e)

def remove_edge(g):
    x = input("Enter the vertex x >")
    y = input("Enter the vertex y >")
    try:
        x = int(x)
        y = int(y)
        g.delete_edge(x, y)
    except ValueError as e:
        print(e)

def add_vertex(g):
    x = input("Enter the vertex x >")
    try:
        x=int(x)
        g.append_vertex(x)
    except ValueError as e:
        print(e)

def remove_vertex(g):
    x = input("Enter the vertex x >")
    try:
        x = int(x)
        g.delete_vertex(x)
    except ValueError as e:
        print(e)

def read_graph_file():
    filename = input("Enter the file name >")
    try:
        new_graph = read_graph_from_file(filename)
        return new_graph
    except Exception as e:
        print(f"Error reading file: {e}")

def write_graph_file(g):
    filename = input("Enter the file name >")
    try:
        write_graph_to_file(g,filename)
        print("Graph successfully written to file.")
    except Exception as e:
        print(f"Error writing to file: {e}")

def create_random_graph():
    n = input("Enter the number of vertices >")
    m = input("Enter the number of edges >")
    try:
        n = int(n)
        m = int(m)
        return random_graph(n, m)
    except ValueError as e:
        print(e)

def print_graph(g):
    print(g)

def copy_write_graph(g):
    copy=g.copy()
    write_graph_file(copy)

def shortest_length(g):
    x = input("Enter starting x >")
    y = input("Enter ending y >")
    try:
        x = int(x)
        y = int(y)
        res=g.shortest_path(x,y)
        if res==None:
            print("Path does not exist")
        else:
            print("The shortest path is: ",res, "and has the length of ",len(res)-1)
    except ValueError as e:
        print(e)

def lowest_cost_walk(g):
    x = input("Enter starting x >")
    y = input("Enter ending y >")
    try:
        x = int(x)
        y = int(y)
        res=g.cheapest_walk(x,y)
        if res[0]==None and res[1]==None:
            print("The vertex",y, "is unreachable starting from vertex ",x)
        else:
            print("The cheapest walk is: ",res[0],"and has a cost of ",res[1])
    except ValueError as e:
        print(e)

def minimum_span_tree(g):
    x = input("Enter starting x >")
    try:
        x = int(x)
        res=g.min_spanning_tree(x)
        print("The minimum spanning tree is: ",res[0],"and has a cost of ",res[1])
    except ValueError as e:
        print(e)

def minimum_vertex_cover_v1(g):
    n,l=g.min_vertex_cover_version1()
    print("The minimum vertex cover is: ",l,"and has a cost of ",n)

def minimum_vertex_cover_v2(g):
    n,l=g.min_vertex_cover_version2()
    print("The minimum vertex cover is: ",l,"and has a cost of ",n)