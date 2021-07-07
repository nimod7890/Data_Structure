#function def
def screen() :
    print("\n\t");
    print("====================================================")
    print("\n	    	    FUNCTION")
    print("\n ****CAPITALIZE all the COMMANDSs")
    print(" ****Do not use space bar")
    print("----------------------------------------------------")
    print(" + (data)		push\t")
    print(" = (data)		replace data\t")
    print(" - (data)		pop\t")
    print(" H			hide all data\t")#
    print(" R			reveal all data\t")#
    print(" T			return (top index, data)\t")
    print(" P			peek //return top data\t")
    print(" L			print all data except cursor\t")
    print(" E			is empty\t")
    print(" F			is full\t")
    print(" C			be empty\t")
    print(" #			all data count\t")
    print(" @ (data)		a data count\t")#
    print(" ? (data)		this data is member\t")
    print("----------------------------------------------------\t")
    print(" Q			quit\t")#
    print("====================================================")

   
class Node:
    def __init__(self,data=None,next=None):
        self.data=data
        self.next=next

class _stack:
    def __init__(self):
        new=Node(None)
        self.top=new
        self.len=0

def printf(self,prnt):
    if is_empty(self)==True:
        print("This stack is empty")
        return
    if prnt.next !=None:printf(self,prnt.next)
    if prnt==self.top :print('(',prnt.data,')',end=' ')
    else:print(prnt.data,end=' ')
        
def printL(self,prnt):
    print()
    if is_empty(self)==True:
        print("This stack is empty")
        return
    if prnt.next !=None:printf(self,prnt.next)
    print(prnt.data,end=' ')
    print()

def hide(self,prnt):
    if is_empty(self)==True:
        print("This stack is empty")
        return
    if prnt.next !=None:hide(self,prnt.next)
    if prnt==self.top :print('(_)',end=' ')
    else:print('_',end=' ')

def push(self,DATA):
    if self.len==0:
        self.top.data =DATA

    else :
        new=Node(DATA)
        new.next=self.top
        self.top=new
    self.len+=1
  
def is_empty(self):
    if self.len==0:
        return True
    else :return False

def pop(self):
    print()
    if is_empty(self)==True:
        print("This stack is empty")
        return
    print("pop : ",self.top.data)
    if self.len==1:
        self.top.data=None
    else :
        rmv=self.top
        rmv.next=self.top.next
        self.top=self.top.next
    self.len-=1

def delete(self):
    if is_empty(self)==True:
        print("\nThis stack is empty")
        return
    if self.len==1:
        self.top.data=None
    else :
        rmv=self.top
        rmv.next=self.top.next
        self.top=self.top.next
    self.len-=1

def datacount(self):
    print("all stack data : ",self.len)

def adatacount(self,DATA):
    print()
    crnt=self.top
    cnt=0
    while crnt!=None:
        if crnt.data==DATA : cnt+=1;
        crnt=crnt.next
    print(DATA," : ",cnt,"개")

def top(self):
    print()
    if is_empty(self)==True:
        print("Not Found")
        return
    print("( ",self.len,", ",self.top.data,")")

def peek(self):
    print()
    if is_empty(self)==True:
        print("Not Found")
        return
    print("top data : ",self.top.data)

def is_member(self,DATA):
    print()
    if is_empty(self)==True:
        print("Not Found")
        return
    crnt =self.top
    i=0
    k=0
    while crnt!=None:
        if crnt.data==DATA :
            print(DATA,"위치 :",self.len-i)
            k=1
        i+=1
        crnt=crnt.next
    if k==0 :
        print("Not Found")
        return

def replace(self,DATA):
    self.top.data=DATA

def empty(self):
    while self.len!=0:
        delete(self)


#main
stack=_stack()
screen()
nhide=False
while True:
    print()
    prnt=stack.top
    if nhide == False : printf(stack,prnt)
    else : hide(stack,prnt) 
    if stack.len!=0 : print()
    order=input(">>> ")
    if order[0]=='Q': break
    num=0
    i=0
    index=0

    while i<len(order): 
        if '0' <= order[i] <= '9':
            while '0' <= order[i] <= '9':
                index*=10
                index+=int(order[i])
                i+=1
            i-=1
        elif order[i]=='+':
            push(stack,order[i+1])
            i+=1
            num+=1
        elif order[i]=='-':
            if index!=0 :
                for i in range(index):
                    pop(stack)
            else :pop(stack)
        elif order[i]=='T':
            top(stack)  
        elif order[i]=='P':
            peek(stack)
        elif order[i]=='@':
            adatacount(stack,order[i+1])
            i+=1
        elif order[i]=='=':
            replace(stack,order[i+1])
            i+=1
        elif order[i]=='L':
            printL(stack,prnt)
        elif order[i]=='#':
            datacount(stack)
        elif order[i]=='C':
            empty(stack)
        elif order[i]=='E':
            print(is_empty(stack))
        elif order[i]=='F':
            print("\n해당 스택의 메모리 할당 방식 : dynamic")
            print("So this stack is not full")
        elif order[i]=='?':
            is_member(stack,order[i+1])
            i+=1
        elif order[i]=='H':
            nhide = True
        elif order[i]=='R':
            nhide = False
        i+=1
