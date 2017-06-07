import sys
import re
import time
import math

graphRE=re.compile("(\\d+)\\s(\\d+)")
edgeRE=re.compile("(\\d+)\\s(\\d+)\\s(-?\\d+)")

vertices=[]
edges=[]

class Edge:
    u = 0
    v = 0
    w = 0.0
    def __init__(self,u,v,w):
        self.u = u
        self.v = v
        self.w = w

    def __repr__(self):
        return "((%s,%s),%s)"%(self.u,self.v,self.w)

def BellmanFord(G):
    pathPairs=[]
    # Fill in your Bellman-Ford algorithm here
    # The pathPairs list will contain the list of vertex pairs and their weights [((s,t),w),...]
    
    # Enumerate edges from the dataset.
    edges = []
    for i in range(len(vertices)):
        for j in range(len(vertices)):
            if not math.isinf(float(G[1][i][j])):
                curr_edge = Edge(int(i),int(j),float(G[1][i][j]))
                edges.append(curr_edge)
    for m in range(len(vertices)):
        distance = []
        for n in range(len(vertices)):
            distance.append(float("inf"))
            if n == m:
                distance[n] = 0;
        for i in range(len(vertices) - 1):
            for j in range (len(edges)):
                if distance[edges[j].v] > distance[edges[j].u] + edges[j].w:
                        distance[edges[j].v] = distance[edges[j].u] + edges[j].w
        for i in range(len(edges)):
            if distance[edges[i].v] > distance[edges[i].u] + edges[i].w:
                print("Negatice circle.")
                return 0
        for i in range(len(G[0])):
            curr_edge = Edge(i,j,distance[i])
            pathPairs.append(curr_edge)
    return pathPairs

def FloydWarshall(G):
    pathPairs=[]
    # Fill in your Floyd-Warshall algorithm here
    # The pathPairs list will contain the list of vertex pairs and their weights [((s,t),w),...]
    
    distance = []
    for i in range(len(G[0])):
        new = []
        for j in range(len(G[0])):
            new.append(float(edges[i][j]))
        distance.append(new)
        distance[i][i] = 0
    for k in range(len(G[0])):
        for i in range(len(G[0])):
            for j in range(len(G[0])):
                if distance[i][j] > (distance[i][k] + distance[k][j]):
                    distance[i][j] = distance[i][k] + distance[k][j]
    for i in range(len(G[0])):
        for j in range(len(G[0])):
            e = Edge(i,j,distance[i][j]);
            pathPairs.append(e)
            
    return pathPairs

def readFile(filename):
    global vertices
    global edges
    # File format:
    # <# vertices> <# edges>
    # <s> <t> <weight>
    # ...
    inFile=open(filename,'r')
    line1=inFile.readline()
    graphMatch=graphRE.match(line1)
    if not graphMatch:
        print(line1+" not properly formatted")
        quit(1)
    vertices=list(range(int(graphMatch.group(1))))
    edges=[]
    for i in range(len(vertices)):
        row=[]
        for j in range(len(vertices)):
            row.append(float("inf"))
        edges.append(row)
    for line in inFile.readlines():
        line = line.strip()
        edgeMatch=edgeRE.match(line)
        if edgeMatch:
            source=edgeMatch.group(1)
            sink=edgeMatch.group(2)
            if int(source) > len(vertices) or int(sink) > len(vertices):
                print("Attempting to insert an edge between "+source+" and "+sink+" in a graph with "+vertices+" vertices")
                quit(1)
            weight=edgeMatch.group(3)
            edges[int(source)-1][int(sink)-1]=weight
    #Debugging
    #for i in G:
        #print(i)
    return (vertices,edges)

def printResult(result):
    for i in range(len(result)):
        sys.stdout.write(str(result[i]))
        sys.stdout.write(" ")
    print(" ")

def main(filename,algorithm):
    algorithm=algorithm[1:]
    G=readFile(filename)
    # G is a tuple containing a list of the vertices, and a list of the edges
    # in the format ((source,sink),weight)
    if algorithm == 'b' or algorithm == 'B':
        resultb = BellmanFord(G)
        printResult(resultb)
    if algorithm == 'f' or algorithm == 'F':
        resultf = FloydWarshall(G)
        printResult(resultf)
    if algorithm == "both":
        start=time.clock()
        resultb = BellmanFord(G)
        end=time.clock()
        BFTime=end-start
        resultf = FloydWarshall(G)
        start=time.clock()
        end=time.clock()
        FWTime=end-start
        print("Bellman-Ford pairs:")
        printResult(resultb)
        print("Floyd-Warshall pairs")
        printResult(resultb)
        print("Bellman-Ford timing: "+str(BFTime))
        print("Floyd-Warshall timing: "+str(FWTime))

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("python bellman_ford.py -<f|b> <input_file>")
        quit(1)
    main(sys.argv[2],sys.argv[1])
