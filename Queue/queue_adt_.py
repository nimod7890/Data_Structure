#function def
def screen() :
    print("\n\t");
    print("============================================")
    print("\n	    	    FUNCTION")
    print("\n ****CAPITALIZE all the COMMANDSs")
    print(" ****Do not use space bar")
    print("----------------------------------------------------")
    print("+ (data)			enqueue")
    print(" = (data)		replace rear data")
    print("- (data)			dequeue")
    print(" D			hide all data")#
    print(" R			reveal all data")#
    print(" H			return (front index, data)")#front index== always 1
    print(" T			return (rear index, data)")#rear index==queue.len
    print(" P			peek //return front data")
    print(" L			print all data")
    print(" E			is empty")
    print(" F			is full")
    print(" C			be empty")
    print(" #			all data count")
    print(" @ (data)		a data count")#
    print(" ? (data)			this data is member")
    print("----------------------------------------------------")
    print(" Q			quit")#
    print("===========================================")


class Node:
    def __init__(self,data=None,next=None):
        self.data=data
        self.next=next

class _queue:
    def __init__(self):
        newf=Node(None)
        newr=Node(None)
        
        self.front=newf
        self.rear=newr
        self.front.next=self.rear
        self.len=0

def printf(self):
    if is_empty(self)==True:
        print("This queue is empty")
        return
    new=self.front
    if queue.len==1:
        print(new.data)
        return
    while new!=None:
        print(new.data,end=' ')
        new=new.next

def printL(self):
    if is_empty(self)==True:
        print("This queue is empty")
        return
    new=self.front
    if queue.len==1:
        print(new.data)
        return
    print("print all data : ",end=' ')
    while new!=None:
        print(new.data,end=' ')
        new=new.next

def hide(self):
    if is_empty(self)==True:
        print("This queue is empty")
        return
    new=self.front
    if queue.len==1:
        print("_")
        return
    while new!=None:
        print('_',end=' ')
        new=new.next

def enqueue(self,DATA):
    if queue.len==0 :
        queue.front.data=DATA
    elif queue.len==1:
        queue.rear.data=DATA
    else:
        new=Node(None)
        new.data=DATA
        queue.rear.next=new
        queue.rear=new
        queue.rear.next=None

    queue.len+=1

def is_empty(self):
    if queue.len==0 :return True
    else :return False

def dequeue(self):
    if is_empty(self)==True:
        print("This queue is empty")
        return
    print("dequeue : %c"%(queue.front.data))
    if queue.len==1:
        queue.front.data=None
    elif queue.len==2:
        queue.rear.data=queue.front.data
        queue.rear.data=None
    else:
        queue.front=queue.front.next
    queue.len-=1

def delete(self):
    if is_empty(self)==True:
        print("This queue is empty")
        return
    if queue.len==1:
        queue.front.data=None
    elif queue.len==2:
        queue.rear.data=queue.front.data
        queue.rear.data=None
    else:
        queue.front=queue.front.next
    queue.len-=1    

def a_data_count(self,DATA):
    if is_empty(self)==True:
        print("This queue is empty")
        return
    crnt=queue.front
    cnt=0
    while crnt!=None:
        if crnt.data==DATA: cnt+=1
        crnt=crnt.next
    if cnt==0: print("queue 내 data '%c'가 존재하지 않습니다."%(DATA))
    else :print("%c data : %d개"%(DATA,cnt))

def data_count(self):
    print("all data : %d개"% queue.len)

def peek(self):
    print()
    if is_empty(self)==True:
        print("Not Found")
        return
    print("front data : ",self.front.data)

def is_member(self,DATA):
    print()
    if is_empty(self)==True:
        print("Not Found")
        return
    crnt =self.front
    i=1
    k=0
    while crnt!=None:
        if crnt.data==DATA :
            print(DATA,"위치 :",i)
            k=1
        i+=1
        crnt=crnt.next
    if k==0 :
        print("Not Found")
        return

def replace(self,DATA):
    self.rear.data=DATA

def empty(self):
    while self.len!=0:
        delete(self)

#main
queue=_queue()
screen()
nhide=False
while True:
    print()
    if nhide == False : printf(queue)
    else : hide(queue) 
    if queue.len!=0 : print()
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
            enqueue(queue,order[i+1])
            i+=1
            num+=1
        elif order[i]=='-':
            if index!=0 :
                for i in range(index):
                    dequeue(queue)
            else :dequeue(queue)
        elif order[i]=='H':
            print("Front : (1,%c)"%queue.front.data)
        elif order[i]=='T':
            print("rear : (%d,%c)"%(queue.len,queue.rear.data))
        elif order[i]=='P':
            peek(queue)
        elif order[i]=='@':
            a_data_count(queue,order[i+1])
            i+=1
        elif order[i]=='=':
            replace(queue,order[i+1])
            i+=1
        elif order[i]=='L':
            printL(queue)
        elif order[i]=='#':
            data_count(queue)
        elif order[i]=='C':
            empty(queue)
        elif order[i]=='E':
            print(is_empty(queue))
        elif order[i]=='F':
            print("\n해당 스택의 메모리 할당 방식 : dynamic")
            print("So this stack is not full")
        elif order[i]=='?':
            is_member(queue,order[i+1])
            i+=1
        elif order[i]=='D':
            nhide = True
        elif order[i]=='R':
            nhide = False
        i+=1
 
