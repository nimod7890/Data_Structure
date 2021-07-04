

def screen():
	print("\n\t")
	print(" =================================================")
	print("\n\t\tFUNCTION\n")
	print(" *** CAPITALIZE all the COMMANDSs")
	print(" **** Enter all DATA in LOWERCASE")
	print(" **** Do not use space bar")
	print(" -------------------------------------------------")
	print(" + (data)		insert")
	print(" - (data)		delete"); 
	print(" = (data)		replace data") 
	print(" E			be empty") 
	print(" @			print present position")
	print(" A			length of array") #create
	print(" L			print array")
	print(" R			reverse array")#create
	print(" S			sort");#create
	print(" V			sort(reverse)"); #create
	print(" <			go to first index")
	print(" >			go to last index")
	print(" N			go to next index")
	print(" P			go to previous index")
	print(" M (index)		Move (numberth) index") 
	print(" MN			move forward one")
	print(" MP			move backward one")
	print(" Mn			move to end of list ")
	print("\n Q			quit")
	print(" =================================================")

def printarr(array): #L
	if (length == 0) :
		print(" This array is empty")
	else :
		for i in range(0,length,1):
			if ((i == position or (position == -1 and length != 0))): print('('+array[i]+')',end=' ')
			else: print(array[i],end=' ')
		print()

def insert(array, data):#+
	global position
	position+=1
	length=len(array)
	array.insert(position,data)

def delete(array,index):#-
	global position
	del my_array[position]
	if position == length-1 : position=0

def move(array,index):
	global position
	if position > index:
		for i in range(position,index,-1):
			temp = array[i - 1]
			array[i - 1] = array[i]
			array[i] = temp
	elif position < index:
		for i in range(position,index,+1):
			temp = array[i + 1]
			array[i + 1] = array[i]
			array[i] = temp



#main function
screen()
position = -1
length = 0
my_array = []

while True:
	length=len(my_array)
	printarr(my_array) 
	type=[]
	type=input(" >>> ")
	if type[0] == 'Q':
		print("- The end -")
		break
	for i in range(len(type)):
		if type[i]=='E':
			my_array.clear()
			position=-1
			break
		if type[i] == 'S':
			my_array.sort()
			position=length-1
			break
		if type[i] == 'V':
			my_array.sort(reverse=True)
			position=length-1
			break
		if type[i] == 'R':
			my_array.reverse()
			position=length-1
			break
		if type[i] == '=':
			my_array[position]=type[i+1]
			i+=1
		if type[i] == 'L':
			if (length == 0) :
				print(" This array is empty")
			else :
				print(" my_array : ", my_array)
			break
		if type[i] == '@':
			print(" my_array[",position,"] = ",my_array[position])
		if type[i] == 'A':
			print(" length :",length)
			break
		if type[i]=='+':
			if position>30: break
			insert(my_array,type[i+1])
			i+=1
		if type[i]=='-':
			if length==0: break
			delete(my_array,position)
		if type[i]=='<':
			position=0
		if type[i]=='>':
			position=length-1
		if type[i]=='N':
			if position>=30: break
			position+=1
		if type[i]=='P':
			if position<0 : break
			position-=1
		if type[i]=='M':
			if type[i+1]=='N':
				move(my_array, position + 1)
			elif type[i + 1] == 'P':
				move(my_array, position - 1)
			elif type[i + 1] == 'n':
				move(my_array, length - 1)
				position=length-1
			else :
				move(my_array, int(type[i+1]))
				position=int(type[i+1])
			i+=1
