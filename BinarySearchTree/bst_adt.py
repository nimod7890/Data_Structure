
#function def

def screen() :
    print("\n\t");
    print("========================================================")
    print("\n	    	    FUNCTION")
    print("\n ****CAPITALIZE all the COMMANDSs")
    print(" ****Do not use space bar")
    print("-------------------------------------------------------")
    print(" first +n                   insert root node")#확인
    print(" +n                         insert node")#확인
    print(" -n                         delete node")#확인
    print(" Fn                         search node")#확인
    print(" Gn                         get right child node")#확인
    print(" Ln                         get left child node")#확인
    print(" I                          sort (start min)")#확인
    print(" R                          sort (start max)")#확인
    print(" N                          get minimum")#확인
    print(" X                          get maximum")#확인
    print(" P                          print tree(default)")#확인
    print(" A                          hide node data")#확인
    print(" B                          reveal node data")#확인
    print(" D                          degree of tree")#
    print(" Dn                         degree of node")#
    print(" H                          height of tree (start with 0)")
    print(" Hn                         level of node (start with 0)")#
    print(" #                          count all node")#확인
    print(" C                          clear (delete all node)")#확인
    print("-------------------------------------------------------")
    print(" Q                          quit")#
    print("=======================================================")

class Node:
    def __init__(self,data=None,left=None,right=None):
        self.data=data
        self.left=left
        self.right=right

class _tree:
    def __init__(self):
        newf=Node(None)
        
        self.root=newf
        self.root.left=None
        self.root.right=None
        self.cnt=0








def printf(pnode,cnode):
    crr=cnode.left
    if pnode==cnode:
        print("%d"%pnode.data,end='')
    if cnode.left !=None:
        print("(%d"%crr.data,end='')
        printf(pnode,crr)
        if cnode.right !=None:
            print(",%d"%cnode.right.data,end='')
            printf(pnode,cnode.right)
            print(")",end='')
        else:
            print(",)",end='')
    elif cnode.right !=None:
        print("(,%d"%cnode.right.data,end='')
        printf(pnode,cnode.right)
        print(")",end='')

def hide(pnode,cnode):
    crr=cnode.left
    if pnode==cnode:
        print("*",end='')
    if cnode.left !=None:
        print("(*",end='')
        hide(pnode,crr)
        if cnode.right !=None:
            print(",*",end='')
            hide(pnode,cnode.right)
            print(")",end='')
        else:
            print(",)",end='')
    elif cnode.right !=None:
        print("(,*",end='')
        hide(pnode,cnode.right)
        print(")",end='')

def count(tree):
    print("\ntall node count : %d"%tree.cnt)

def is_left_child(node):
    if node==None:return False
    if node.left==None: return False
    else :return True

def is_right_child(node):
    if node==None:return False
    if node.right==None: return False
    else :return True

def get_parent(root, data):
    cur=root
    parent=None
    while cur!=None:
        if cur.data==data: return parent
        elif cur.data>data:
            parent=cur
            cur=cur.left
        else:
            parent=cur
            cur=cur.right
    return None

def get_left_child(node):
    if node==None: return None
    n=is_left_child(node)
    if n==True:return node.left
    else: return None

def get_right_child(node):
    if node==None: return None
    n=is_right_child(node)
    if n==True:return node.right
    else: return None

def level_of_node(tree,cnode):
    tmp=cnode
    cnt=0
    while tmp!=None:
        pnode=get_parent(tree.root,tmp.data)
        if pnode !=None: cnt+=1
        tmp=pnode
    return cnt

def level_of_tree(tree,p1,p2):
    if p1==None:return None
    
    if level_of_node(tree,p1)>level_of_node(tree,p2):
        deeper=p1
    else :
        deeper=p2
    
    if level_of_tree(tree,p1.left,deeper)!=None:
        deeper=level_of_tree(tree,p1.left,deeper)
    if level_of_tree(tree,p1.right,deeper)!=None:
        deeper=level_of_tree(tree,p1.right,deeper)

    return deeper

def find(tree,node,data,path):
    if node==None:return 
    if data==node.data:return None
    
    leftchild=get_left_child(node)
    rightchild=get_right_child(node)
    
    if leftchild==None and rightchild ==None : return node

    if data<node.data:#넣을 데이터가 부모보다 작으면
        path.append('L')#왼쪽으로 들어감
        if leftchild!=None:#왼쪽 있으면
            if leftchild.data==data:return None#왼쪽이랑 같으면 return null
            elif data<leftchild.data:#넣을 데이터가 왼쪽보다 작으면
                if leftchild.left!=None:#왼쪽 차있으면
                    path.append('L')
                    baby=find(tree,leftchild.left,data,path)
                    return baby
                else :return leftchild#비어 있으면
            elif data>leftchild.data:
                if leftchild.right !=None:
                    path.append('R')
                    baby=find(tree,leftchild.right,data,path)
                    return baby
                else :return leftchild
            else :return leftchild
        else: #왼쪽 없으면
            return node
    elif data>node.data:#오른쪽
        path.append('R')
        if rightchild!=None:
            if rightchild.data==data:return None
            elif data<rightchild.data:
                if rightchild.left!=None:
                    path.append('L')
                    baby=find(tree,rightchild.left,data,path)
                    return baby
                else :return rightchild
            elif data>rightchild.data:
                if rightchild.right !=None:
                    path.append('R')
                    baby=find(tree,rightchild.right,data,path)
                    return baby
                else :return rightchild
            else :return rightchild
        else: return node
    else:return node

def search(pnode,data):
    if pnode==None: return None
    if pnode.data==data:return pnode
    new=search(pnode.left,data)
    if new!=None :
        return new
    new=search(pnode.right,data)
    if new!=None:
        return new
    return new

def inorder(node):
    leftchild=get_left_child(node)
    if leftchild!=None:
        inorder(leftchild)
    print(node.data,end=' ')
    rightchild=get_right_child(node)
    if rightchild !=None:
        inorder(rightchild)

def rightmost_inorder(node):
    rightchild=get_right_child(node)
    if rightchild!=None:
        rightmost_inorder(rightchild)
    print(node.data,end=' ')
    leftchild=get_left_child(node)
    if leftchild !=None:
        rightmost_inorder(leftchild)

def get_min(root):
    if root==None: return None
    while root.left!=None:
        root=root.left
    return root

def get_max(root):
    if root==None: return None
    while root.right!=None:
        root=root.right
    return root

def degree_of_node(parent):
    if is_left_child(parent)==False and is_right_child(parent) ==False :return 0
    elif is_left_child(parent)==False or is_right_child(parent) ==False :return 1
    else :return 2
            
def degree_of_tree(p1,p2):
    if p1==None:return None

    if degree_of_node(p1)>degree_of_node(p2):
        deeper=p1
    else :deeper=p2

    if degree_of_tree(p1.left,deeper)!=None:
        degree_of_tree(p1.left,deeper)
        
    if degree_of_tree(p1.right,deeper)!=None:
        degree_of_tree(p1.right,deeper)

        
    return deeper




def insert(tree,putposition,data):
    new=Node(data)
    if data<putposition.data:
        putposition.left=new
    elif data>putposition.data:
        putposition.right=new
    
    new.left=None
    new.right=None
    tree.cnt+=1

def delete_node(tree,node):
    if node==None :return
    n=degree_of_node(node)
    if node==tree.root:
        if n==0 : tree.root==None
        elif n==1:
            tree.root=tree.root.left!=None and tree.root.left or tree.root.right
        else :
            maxi=get_max(tree.root.left)
            maxparent=get_parent(tree.root,maxi.data)
            if maxi==tree.root.left:
                maxi.right=tree.root.right
                tree.root=maxi
            else :
                maxi.right=tree.root.right
                if maxi.left!=None:
                    tmp=maxi
                    while tmp.left!=None:
                        tmp=tmp.left
                    tmp.left=tree.root.left
                else:
                    maxi.left=tree.root.left
                tree.root.left=None
                tree.root.right=None
                maxparent.right=None
                tree.root=maxi
    else :
        parent=get_parent(tree.root,node.data)
        if n==0:
            if node==get_left_child(parent) :
                parent.left=None
            else :parent.right=None
        elif n==1:
            if node==get_left_child(parent):
                if node.left!=None :
                    parent.left=node.left
                else :
                    parent.left=node.right
            else :
                if node.left!=None :
                    parent.right=node.left
                else :
                    parent.right=node.right
        else:
            maxi=get_max(node.left)
            maxparent=get_parent(tree.root,maxi.data)
            if maxi==node.left:
                if node==get_left_child(parent):
                    parent.left=node.left
                else : parent.right=node.left
                maxi.right=node.right
            else :
                if maxi.left!=None:
                    tmp=maxi
                    while tmp.left!=None:
                        tmp=tmp.left
                    tmp.left=node.left
                else:
                    maxi.left=node.right
                max.right=node.right
                if node==get_left_child(parent): 
                    parent.left=max
                else :parent.right=max
                maxparent.right=None
    tree.cnt-=1

def clear(tree):
    while tree.cnt!=0:
        delete_node(tree,tree.root)
            









#main
tree=_tree()
screen()

reveal=True
while True:
    print("\n",end='')
    if tree.cnt==0:
        print("This tree is empty. Please create root node first",end='')
    elif reveal==True:
        printf(tree.root,tree.root)
    else :
        hide(tree.root,tree.root)
    
    order=input("\n>>> ")
    if order[0]=='Q': break
    num=0
    i=0
    data=0
    path=[]
    index=0
    new=Node(None)
    found=Node(None)
    while i<len(order): 
        if len(order)!=1 and num==0:
            if '0' <= order[1] <= '9' :
                j=1
                while j<len(order):
                    data*=10
                    data+=int(order[j])
                    j+=1
                i=0
                num+=1  
        if order[0]=='+':
            if data!=0:
                if tree.cnt==0:
                    new=Node(data)
                    tree.root=new
                    tree.cnt+=1
                else:
                    new=find(tree,tree.root,data,path)
                    if new!=None:
                        insert(tree,new,data)
                    else :
                        print("\n중복 값은 입력할 수 없습니다.")
                        print("search path of same data %d : root "%data,end=' ')
                        j=0
                        for i in path: print("->",i,end=' ')
                break
        elif order[0]=='N':
            if tree.cnt==0:
                print("\nThis tree is empty")
                break
            new=get_min(tree.root)
            print("\nminimum data : %d "%new.data,end='')
            if tree.cnt == 1:
                print("(root node)")
            break
        elif order[0]=='X':
            if tree.cnt==0:
                print("\nThis tree is empty")
                break
            new=get_max(tree.root)
            print("\nmaximum data : %d "%new.data,end='')
            if tree.cnt == 1:
                print("(root node)")
            break
        elif order[0]=='F':
            if tree.cnt==0:
                print("\nThis tree is empty")
                break
            if data!=0:
                new=find(tree,tree.root,data,path)
                if new==None:
                    print("\n[SUCCESS] ",end='')
                else :
                    print("[FAILED] ",end='')
                print("\nsearch path of %d : root"%data,end='')
                j=0
                for i in path: print("->",i,end=' ')
            break
        elif order[0]=='-':
            if tree.cnt==0:
                print("\nThis tree is empty")
                break
            elif data!=0:
                new=find(tree,tree.root,data,path)
                if new==None:
                    found=search(tree.root,data)
                    delete_node(tree,found)
                else :
                    print("\nNot Found")
                    print("failed search path of %d: root "%data,end=' ')
                    for i in path: print("->",i,end=' ')
                    print(" (탐색 실패)")
            break
        elif order[0]=='H':
            if tree.cnt==0:
                print("\nThis tree is empty")
                break
            if data==0:
                new=level_of_tree(tree,tree.root,tree.root)
                print("\nheight of tree : %d"%(level_of_node(tree, new)))
            else :
                new=find(tree,tree.root,data,path)
                if new==None:
                    found=search(tree.root,data)
                    print("\nlevel of node : %d"%(level_of_node(tree, found)))
                else :
                    print("\nNot Found")
            break
        elif order[0]=='D':
            if tree.cnt==0:
                print("\nThis tree is empty")
                break
            if data==0:
                new=degree_of_tree(tree.root,tree.root)
                print("\ndegree of tree : %d"%(degree_of_node(new)))
            else:
                new=find(tree,tree.root,data,path)
                if new==None:
                    found=search(tree.root,data)
                    print("\ndegree of node : %d"%(degree_of_node(found)))
                else :
                    print("Not Found")
            break
        elif order[0]=='G':
            if tree.cnt==0:
                print("\nThis tree is empty")
                break
            if data!=0:
                new=find(tree,tree.root,data,path)
                if new==None:
                    found=search(tree.root,data)
                    right=get_right_child(found)
                    if right!=None:
                        print("\nright child data : %d"%right.data)
                    else: print("\nNot Found")
                else :
                    print("\nNot Found")
            break
        elif order[0]=='L':
            if tree.cnt==0:
                print("\nThis tree is empty")
                break
            if data!=0:
                new=find(tree,tree.root,data,path)
                if new==None:
                    found=search(tree.root,data)
                    left=get_left_child(found)
                    if left!=None:
                        print("\nleft child data : %d"%left.data)
                    else :print("\nNot Found")
                else :
                    print("\nNot Found")
            break

        
        elif order[0]=='A':
            reveal=False
            break
        elif order[0]=='B':
            reveal=True
            break
        elif order[0]=='P':
            break
        elif order[0]=='I':
            if tree.cnt==0:
                print("\nThis tree is empty")
                break
            print("\nsort (start minimum) : ",end='')
            inorder(tree.root)
            break
        elif order[0]=='R':
            if tree.cnt==0:
                print("\nThis tree is empty")
                break
            print("\nsort (start maximum) : ",end='')
            rightmost_inorder(tree.root)
            break
        
        elif order[0]=='C':
            clear(tree)
            break
        
        elif order[0]=='#':
            count(tree)
            break

            











            
                         
            

