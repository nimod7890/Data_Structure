class NODE:
    def init(self,data=None,left_child=None,right_sibling=None):
        self.data=data
        self.left_child=left_child
        self.right_sibling=right_sibling

class T:
    def init(self):
        new=Node(None)
        self.root=new
        self.cnt=0
        
def insertchild(self,parent,data):
    node=NODE()
    node.data=data
    node.left_child=None
    node.right_sibling=None
    tmp=pnode.left_child
    if parent.left_child==None:
        parent.left_child=node
    elif parent.left_child==None:
        parent.right_sibling=node
    else:
        while tmp.right_sibling !=None:
            tmp=tmp.right_sibling
        tmp.right_sibling=node
    self.cnt+=1

def search(pnode,data):
    if pnode==None: return None
    if pnode.data==data: return pnode
    new=search(pnode.left_child,data)
    if new!=None: return new
    new=search(pnode.right_sibling,data)
    if new!=None: return new
    return None

def get_parent(pnode,data):
    if pnode==None: return None
    if pnode.left_child==None:return None
    child =pnode.left_child
    if child==None: return None
    if child.data==data: return pnode
    new=get_parent(child,data)
    if new!=None: return new
    while child.right_sibling!=None:
        if child.right_sibling.data==data:return pnode
        new2=get_parent(child.right_sibling,data)
        if new2 !=None : return new2
        child=child.right_sibling
    return None

def path(self,node1,node2):
    hap=0
    if node1==self.root:#root에서 node2까지
        hap+=node2.data
        parent=get_parent(self.root,node2.data)
        while parent !=None:
            hap+=parent.data
            parent=get_parent(self.root,parent.data)
    elif node2==self.root:#root에서 node1까지
        hap+=node1.data
        parent=get_parent(self.root,node1.data)
        while parent !=None:
            hap+=parent.data
            parent=get_parent(self.root,parent.data)
    else :
        level1=int(levelofnode(self,node1))
        level2=int(levelofnode(self,node2))
        parent1=get_parent(self.root,node1.data)
        parent2=get_parent(self.root,node2.data)
        hap=int(node1.data)+int(node2.data)
        n=level1-level2
        if n>0:
            while n!=0:
                if parent1==node2:
                    return hap;
                hap+=int(parent1.data)
                parent1=get_parent(self.root,parent1.data)
                n-=1;
        else :
            while n!=0:
                if parent2==node1:
                    return hap;
                hap+=int(parent2.data)
                parent2=get_parent(self.root,parent2.data)
                n+=1;
        while True:
            if parent1==parent2:#겹치면
                hap+=int(parent1.data)
                break
            else:
                hap+=int(parent1.data)
                hap+=int(parent2.data)
            parent1=get_parent(self.root,parent1.data)
            parent2=get_parent(self.root,parent2.data)
    return hap
            
                            

def levelofnode(self,cnode):
    tmp=cnode
    cnt=0
    while tmp!=None:
        pnode=get_parent(self.root,tmp.data)
        if pnode!=None: cnt+=1
        else :break
        tmp=pnode
    return cnt

def printf(pnode,cnode):
    crr=cnode.left_child
    if pnode==cnode: print("%d"%pnode.data,end=' ')
    if pnode.left_child==None: return
    print("(",end=' ')
    while crr !=None:
        print("%d"%crr.data,end=' ')
        if crr.left_child !=None: printf(pnode,crr)
        if crr.right_sibling != None: print(",",end=' ')
        crr=crr.right_sibling
    print(")",end=' ')

#main
tree=T()
ndata=NODE()
print("tree making")
ndata.data=int(input("root node data : "))
tree.root=ndata
tree.cnt=1;
tree.root.left_child=None
tree.root.right_sibling=None

while True:
    print()
    if tree.cnt !=0:
        print("tree : ",end='')
        printf(tree.root,tree.root)
        print()
    pnode=int(input("if you want to quit, input 0 \nparent node : "))
    if pnode==0 :break
    p=pnode
    pnode=search(tree.root,pnode)
    if pnode ==None :
        print("%d is not in tree"%p)
    else :
        cnode= int(input("if you want to quit, input minus data(ex. -1)\nchild node : "))
        if cnode==0 :break
        c=search(tree.root,cnode)
        if c==None:
            insertchild(tree,pnode,cnode)
        else :
            print("%d is already in tree"%cnode)


go=True
while go:
    while True:
        print()
        print("Tree Path")
        p1=int(input("start node : "))
        p2=int(input("finish node : "))
        start=search(tree.root,p1)
        finish=search(tree.root,p2)
        if start ==None :
            print("%d is not in tree"%p1)
        elif finish ==None :
            print("%d is not in tree"%p2)
        else: break
    print("tree path : %d"%path(tree,start,finish))
    go=int(input("Do you want to quit? (yes=0 no=1) >>> "))

    
