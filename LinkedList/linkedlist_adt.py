#function def
def screen() :
    print("\n\t");
    print("====================================================")
    print("\n	    	    FUNCTION")
    print("\n ****CAPITALIZE all the COMMANDSs")
    print(" ****Do not use space bar")
    print("----------------------------------------------------")
    print(" + (data)		insert\t")
    print(" ~ (data)		addtail\t")
    print(" = (data)		replace data\t")
    print(" - (data)		delete\t")
    print(" G			print present data\t")
    print(" L			print all data\t")
    print(" E			is empty\t")
    print(" C			be empty\t")
    print(" R			reverse list\t")#
    print(" #			all data count\t")
    print(" @ (data)		a data count\t")#
    print(" ? (data)		this data is member\t")
    print(" <			go to first index\t")
    print(" >			go to last index\t")
    print(" N			go to next index\t")
    print(" P			go to previous index\t")#
    print(" (index)		go to (numberth) index\t")#
    print("----------------------------------------------------\t")
    print(" Q			quit\t")#
    print("====================================================")

class Node:
    def __init__(self,data=None,next=None,back=None):
        self.data=data
       # self.next=next
        self.back=back

class _list:
    def __init__(self):
        new=Node(None)
        self.head=new
        self.len=0
        self.pos=self.head

def addtail(self,DATA):
    new=Node(DATA)
    if self.pos==self.head or self.pos.next==None:
        new.next=None
        self.pos.next=new
        new.next=None
        self.pos.next=new
        self.pos=new
        self.len+=1
        return
    elif(self.pos.next!=None):
        cnt=list.head
        while cnt.next!=none:
            cnt=cnt.next
        self.pos=cnt
    new.next=None
    self.pos.next=new
    self.pos=new

    self.len+=1

def add(self,DATA):
    new=Node(DATA)
    if self.pos==self.head or self.pos.next==None:
        new.next=None
        self.pos.next=new
    else:
        new.next=self.pos.next
        self.pos.next=new
    self.pos=new
    self.len+=1

def addfront(self,DATA):
    new=Node(DATA)
    before=self.head
    while before.next!=self.pos:
        before=before.next
    new.next=self.pos
    before.next=new
   # new.back=self.pos.back
   # self.pos.back.next=new
    self.pos=new
    self.len+=1

def is_empty(self):
    if self.len==0:
        return True
    else :return False

def reverse(self):
    if is_empty(self)==True:return
    first=self.head.next
    last=self.pos
    while last.next !=None:
        last=last.next
    for i in range(int(self.len/2)):
        first.data,last.data=last.data,first.data
        first=first.next
        before=self.head
        while before.next!=last:
            before=before.next
        last=before
    while self.pos.next !=None:
        self.pos=self.pos.next
        
def delete(self):
    if is_empty(self)==True:return
    before=self.head
    while before.next!=self.pos:
        before=before.next
    if self.pos.next==None:#마지막
        before.next=None
        if self.len==1:
            self.pos=self.head
            self.pos.next=None
        else:
            self.pos=self.head.next
    else:
        delete=self.pos
        before.next=self.pos.next
        self.pos=self.pos.next
        delete=None
    self.len-=1

def empty(self):
    while self.len!=0:
        delete(self)

def datacount(self):
    print("data : ",self.len)

def adatacount(self,DATA):
    crnt=self.head.next
    cnt=0
    while crnt!=None:
        if crnt.data==DATA : cnt+=1;
        crnt=crnt.next
    print(DATA," : ",cnt,"개")


def is_member(self,DATA):
    if is_empty(self)==True:
        print("Not Found")
        return
    crnt =self.head.next
    i=1
    k=0
    while crnt!=None:
        if crnt.data==DATA :
            print(DATA,"위치 : ",i)
            self.pos=crnt
            k=1
        i+=1
        crnt=crnt.next
    if k==0 :
        print("Not Found")
        return
    

def getdata(self):
    if is_empty(self)==True:return
    print("current data : ",self.pos.data)

def gonext(self):
    if is_empty(self)==True or self.pos.next==None :return
    self.pos=self.pos.next

def goback(self):
    if is_empty(self)==True or self.head.next==self.pos :return
    before=self.head
    while before.next!=self.pos:
        before=before.next
    before.next=self.pos
    self.pos=before


def gofirst(self):
    if is_empty(self)==True:return
    else :self.pos=self.head.next
    
def golast(self):
    if is_empty(self)==True:return
    else:
        crnt=self.head.next
        while crnt.next !=None:
            crnt=crnt.next
        crnt.next=None
        self.pos=crnt
    
def goindex(self,index):
    if is_empty(self)==True:return
    else :
        crnt=self.head
        for i in range(index):
            crnt=crnt.next
        self.pos=crnt

def replace(self,DATA):
    if is_empty(self)==True:return
    self.pos.data=DATA

def printf(self):
    if is_empty(self)==True:
        print("This list is empty")
        return
    pnt=self.head.next
    while pnt != None:
        if pnt==self.pos:print('(',pnt.data,')',end=' ')
        else : print(pnt.data,end=' ')
        pnt=pnt.next
    print()

def printL(self):
    if is_empty(self)==True:
        print("This list is empty")
        return
    pnt=self.head.next
    while pnt != None:
        print(pnt.data,end=' ')
        pnt=pnt.next
    print()


#main
list=_list()
screen()

while True:
    printf(list)
    order=input(">>> ")
    if order[0]=='Q': break
    num=0
    '''if '0' < order[0] and order[0]<= str(list.len):
        goindex(list,int(order[0]))
        num+=1'''
    i=0
    while i<len(order): #for 문으로 작동 안 됨 >>> 이유 : ???
        if '0' <= order[i] <= '9':
            index=0
            while '0' <= order[i] <= '9':
                index*=10
                index+=int(order[i])
                i+=1
            i-=1
            goindex(list,index)
        elif order[i]=='~':
            if order[i+1]=='\0' : break
            addtail(list,order[i+1])
            i+=1
            num+=1
            continue
        elif order[i]=='<':
            gofirst(list)
        elif order[i]=='>':
            golast(list)
        elif order[i]=='N':
            gonext(list)
        elif order[i]=='P':
            goback(list)
        elif order[i]=='+':
            if num==0 and list.len!=0 :
                addfront(list,order[i+1])
            else : add(list,order[i+1])
            i+=1
            num+=1
        elif order[i]=='-':
            delete(list)
        elif order[i]=='G':
            getdata(list)
        elif order[i]=='@':
            adatacount(list,order[i+1])
            i+=1
        elif order[i]=='=':
            replace(list,order[i+1])
            i+=1
        elif order[i]=='L':
            printL(list)
        elif order[i]=='#':
            datacount(list)
        elif order[i]=='C':
            empty(list)
        elif order[i]=='E':
            print(is_empty(list))
        elif order[i]=='?':
            is_member(list,order[i+1])
            i+=1
        elif order[i]=='R':
            reverse(list)
        i+=1
