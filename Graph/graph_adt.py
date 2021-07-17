#function def
def screen() :
    print("\n\t");
    print("====================================================")
    print("\n	    	    FUNCTION")
    print("\n ****CAPITALIZE all the COMMANDSs")
    print(" ****Do not use space bar")
    print("----------------------------------------------------")
    print(" G			create graph")
    print(" +n			insert node\t")
    print(" -n			delete node")
    print(" En1n2			add edge between n1 and n2")
    print(" Dn1n2			delete edge between n1 and n2")
    print(" X			number of vertex")
    print(" H			number of edge")
    print(" Vn			degree of vertex")
    print(" An			adjacent vertex")#
    print(" N			check if graph is empty")
    print(" C			check if graph is connected")
    print(" pn1n2			check if they are connected")
    print(" Rn1n2			rename n1 to n2")#
    print(" Sn1n2			swap n1 and n2")#기능#
    print(" O			sort by key")#기능
    print(" I			sort by key(reverse)")#기능
    print(" L			print graph")
    print(" T			print vertex")#기능
    print(" K			clear")#
    print("----------------------------------------------------\t")
    print(" Q			quit\t")#기능
    print("====================================================")


global vertex_cnt

class node:
    def __init__(self,vertex_data):
        self.visit=False
        self.data=vertex_data

def printf(self):
    if vertex_cnt==0:
        print("{}")
        return
    else:
        print("{",end='')
        for key, value in self.items():
            print(key.data,":[",end='')
            for i in range(len(self[key])):
                print(self.get(key)[i].data,end=',')
            print("]",end=',')
        print("}")

def add(self, data):
    global vertex_cnt
    vertex=node(data)
    self[vertex]=[]
    vertex_cnt+=1

def search(self,data):
    for key in self:
        if data==key.data:
            return key
    return None

def change_lower(self):
    for key in self:
        if key.upper()==True:
            rename_vertex(self,key,key.lower())

def change_upper(self):
    for key in self:
        if key.lower()==True:
            rename_vertex(self,key,key.upper())
        
def delete_vertex(self,data):
    global vertex_cnt
    for key in self:
        if path_exist(self, key,data)==True:
            delete_edge(self,key,data)
    del self[data]
    vertex_cnt-=1

def degree_of_vertex(self,data):
    return len(self[data])    

def adjacent(self, data):
    print("[",end='')
    for i in range(len(self[data])):
        print(self.get(data)[i].data,end=',')
    print("]")

def rename_vertex(self,vertex,dataa):
    for key in self:
        if key.data==vertex.data:
            key.data=dataa
            return

def swap(self,data1, data2):
    tmp1=data1.data
    tmp2=data2.data
    rename_vertex(self,data1,'*')
    rename_vertex(self,data2,tmp1)
    data=search(self,'*')
    rename_vertex(self,data,tmp2)

def edge_exist(self, data1,data2):
    if data2 in self[data1]:
        return True
    return False

def add_edge(self,data1, data2):
    self[data1].append(data2)
    self[data2].append(data1)

def delete_edge(self, data1,data2):
    self[data1].remove(data2)
    self[data2].remove(data1)
    
def print_vertex(self):
    print("{",end='')
    for key in self:
        print(key.data,end=',')
    print("}")

def num_of_vertex(self):
    cnt=0
    for key in self:
        cnt+=1
    return cnt

def num_of_edge(self):
    cnt=0
    for key in self:
        cnt+=len(self[key])
    return int(cnt/2)
    
def is_empty(self):
    global vertex_cnt
    if vertex_cnt==0:
        return True
    return False

def is_connected(self):
    reset_visited(self)
    visited(graph, list(self.keys())[0])
    for key in self:
        if key.visit==False:
            return False
    return True

def path_exist(self,data1,data2):
    reset_visited(self)
    visited(graph, data1)
    for key in self:
        if key.data==data2.data:
            if key.visit==False:
                return False
            else:
                return True

def visited(graph, key):
    if key.visit==True:
        return
    key.visit=True
    for i in range(len(graph[key])):
        value=search(graph,graph.get(key)[i].data)
        if value!=None:
            visited(graph,value)

def reset_visited(self):
    for key in self:
        key.visit=False


def sort_by_key(self):
    return dict(sorted(graph.items(), key=lambda x: x[0].data))

def sort_by_key_reverse(self):
    return dict(sorted(graph.items(), key=lambda x: x[0].data,reverse=True))
    
def clear(self):
    global vertex_cnt
    self.clear()
    vertex_cnt=0


#main
graph={}
vertex_cnt=0
screen()

create=False
while True:
    if create==False:
        print("This graph is not created yet. Please create graph first")
    else :
        printf(graph)
    order=input(">>> ")
    if order[0]=='Q':
        print("\n-End-\n\n")
        break
    for i in range(len(order)):
        if order[0]=='G':
            i=0
            if create==False:
                create=True
            else :
                print("This graph is already created.")
            break
        elif create==False:#error handling
            break
        elif order[0]=='+':
            if search(graph,order[1])==None:
                add(graph,order[1])
            else:
                print("{%c} is already in graph"%order[1])
            break
        elif order[0]=='N':
            print(is_empty(graph))
            break
        elif order[0]=='H':
            print(num_of_edge(graph))
            break
        elif order[0]=='X':
            print(num_of_vertex(graph))
            break
        elif vertex_cnt==0:
            break
        elif order[0]=='-':
            v1=search(graph,order[1])
            if v1==None:
                print("{%c} is not in graph"%order[1])
            else:
                delete_vertex(graph,v1)
            break
        elif order[0]=='V':
            v1=search(graph,order[1])
            if v1==None:
                print("{%c} is not in graph"%order[1])
            else:
                print(degree_of_vertex(graph,v1))
            break
        elif order[0]=='A':
            v1=search(graph,order[1])
            if v1==None:
                print("{%c} is not in graph"%order[1])
            else:
                adjacent(graph,v1)
            break
        elif order[0]=='R':
            v1=search(graph,order[1])
            v2=search(graph,order[2])
            if v1==None:
                print("{%c} is not in graph"%order[1])
            elif v2!=None:
                print("{%c} is already in graph"%order[2])
            else:
                rename_vertex(graph,v1,order[2])
            break
        elif order[0]=='S':
            v1=search(graph,order[1])
            v2=search(graph,order[2])
            if v1==None:
                print("{%c} is not in graph"%order[1])
            elif v2==None:
                print("{%c} is not in graph"%order[2])
            else:
                swap(graph,v1,v2)
            break
        elif order[0]=='P':
            v1=search(graph,order[1])
            v2=search(graph,order[2])
            if v1==None:
                print("{%c} is not in graph"%order[1])
            elif v2==None:
                print("{%c} is not in graph"%order[2])
            else:
                print(path_exist(graph,v1,v2))
            break
        elif order[0]=='E':
            v1=search(graph,order[1])
            v2=search(graph,order[2])
            if v1==None:
                print("{%c} is not in graph"%order[1])
            elif v2==None:
                print("{%c} is not in graph"%order[2])
            else:
                path=edge_exist(graph,v1,v2)
                if path==True:
                    print("{%c}and{%c} are already connected"%(order[1],order[2]))
                else: add_edge(graph,v1,v2)
            break
        elif order[0]=='D':
            v1=search(graph,order[1])
            v2=search(graph,order[2])
            if v1==None:
                print("{%c} is not in graph"%order[1])
            elif v2==None:
                print("{%c} is not in graph"%order[2])
            else:
                path=edge_exist(graph,v1,v2)
                if path==False:
                    print("{%c}and{%c} are not connected"%(order[1],order[2]))
                else: delete_edge(graph,v1,v2)
            break
        elif order[0]=='T':
            print_vertex(graph)
            break
        elif order[0]=='U':
            change_lower(graph)
            break
        elif order[0]=='W':
            change_upper(graph)
            break
        elif order[0]=='O':
            graph=sort_by_key(graph)
            break
        elif order[0]=='I':
            graph=sort_by_key_reverse(graph)
            break
        elif order[0]=='C':
            print(is_connected(graph))
            break
        elif order[0]=='K':
            clear(graph)
            break
        elif order[0]=='L':
            break
        else:
            break
        
        
                
    











        
