from matplotlib import pyplot as plt
import math
import pickle

mmPerPixcel=10

lineFileName="linev5.pkl"
fieldImageName="redFieldSH.png"

def frange(f,t,j):
	v=f
	while v<t:
		yield v
		v += j

class point:
	points=[]
	@classmethod
	def addPoints(cls,obj):
		#append で参照を追加
		cls.points.append(obj)
	@classmethod
	def delPoints(cls,obj):
		cls.points.remove(obj)
	@classmethod
	def nearPoint(cls,xa,ya):
		minP=cls.points[0]
		min=minP.distSq(xa,ya)
		for p in cls.points:
			now=p.distSq(xa,ya)
			if now<min:
				min=now
				minP=p
		return (min,minP)
	
	def __init__(self,xa=0,ya=0,belong=None,marker="o"):
		self.x=xa
		self.y=ya
		self.belong=belong
		self.p=ax.scatter(self.x,self.y,s=10,marker=marker)
		self.addPoints(self)
	def update(self):
		self.p.set_offsets((self.x,self.y))
		if self.belong!=None:
			self.belong.draw()
			if self.belong.nextLine!=None:
				self.belong.nextLine.draw()
	def set(self,val):
		self.x,self.y=val
		self.update()
	def get(self):
		return (self.x,self.y)
	def distSq(self,xa,ya):
		return (self.x-xa)**2 + (self.y-ya)**2
	def selected(self,isv):
		if isv:
			self.p.set_sizes((30,))
		else:
			self.p.set_sizes((10,))
	def delete(self):
		self.delPoints(self)
		self.p.remove()

class lineClass:
	def __init__(self,val):
		self.nextLine=None
		self.preLine=None
		if val!=None:
			self.set(val)
	def draw(self,detail=0):
		pass
	def delete(self):
		pass
	def len(self):
		self.calcedLen=0
		return 0
	def drawC(self,detail=0.1):
		self.draw(detail)
		if self.nextLine!=None:
			self.nextLine.drawC(detail)
	def lenC(self):
		if self.nextLine==None:
			return self.len()
		else:
			return self.len()+self.nextLine.lenC()
	def fl(self,l):
		return self.f(l/self.calcedLen)
	def flC(self,l):
		"""すべてのライン長を計算するために自分の次のラインも計算に入れる"""
		#self.len()
		#print("l is"+str(l))
		if l<=self.calcedLen or self.nextLine==None:
			return self.fl(l)
		else:
			return self.nextLine.flC(l-self.calcedLen)
	def genGet(self,val):
		"""generator"""
		return (self.__class__.__name__,val)
		
	def addLine(self,new):
		if self.nextLine==None:
			self.nextLine=new(self.end)
			self.nextLine.preLine=self
			self.nextLine.draw()
			return self.nextLine
		else:
			return None
	def delC(self):
		if self.nextLine!=None:
			self.nextLine.delC()
			#参照を含むのでそのままだと消されない、そのためにまず手動で参照を消す
			self.nextLine.delete()
			del self.nextLine
			self.nextLine=None
	def getC(self):
		vals=list()
		self.getCinternal(vals)
		return vals
	def getCinternal(self,list):
		list.append(self.get())
		if self.nextLine!=None:
			self.nextLine.getCinternal(list)
		return list
	def setC(self,list):
		line=list.pop(0)
		self.set(line[1])
		if len(list)!=0:
			#print(list[0])
			self.addLine(eval(list[0][0]))
			self.nextLine.setC(list)


class startl(lineClass):
	def __init__(self,frma=None,val=None):
		self.end=point(belong=self,marker="*")
		super().__init__(val)
	def delete(self):
		raise ValueError("この点は消せません")
	def f(self,t=0):
		return (self.end.x,self.end.y)
	def fl(self,l=0):
		return self.f()
	def get(self):
		return self.genGet((self.end.get(),))
	def set(self,val):
		end,=val
		self.end.set(end)
	
class bazier(lineClass):
	def __init__(self,frma,val=None):
		self.frm=frma
		self.p1=point(belong=self)
		self.p2=point(belong=self)
		self.end=point(belong=self)
		self.len()
		self.line,=ax.plot(0,0)
		super().__init__(val)
	def f(self,t):
		x=(1-t)**3*self.frm.x + 3*(1-t)**2*t*self.p1.x + 3*(1-t)*t**2*self.p2.x + t**3*self.end.x
		y=(1-t)**3*self.frm.y + 3*(1-t)**2*t*self.p1.y + 3*(1-t)*t**2*self.p2.y + t**3*self.end.y
		return (x,y)
	
	def len(self):
		prex,prey=self.f(0)
		ans=0
		for i in frange(0,1,0.01):
			nowx,nowy=self.f(i)
			ans+=math.sqrt((nowx-prex)**2+(nowy-prey)**2)
			prex=nowx
			prey=nowy
		self.calcedLen=ans
		return self.calcedLen
	def draw(self,detail=0.1):
		ys=[]
		xs=[]
		for i in frange(0,1,detail):
			(x,y)=self.f(i)
			xs.append(x)
			ys.append(y)
		self.line.set_data(xs,ys)
	def delete(self):
		self.p1.delete()
		self.p2.delete()
		self.end.delete()
		self.line.remove()
	def get(self):
		return self.genGet((self.p1.get(),self.p2.get(),self.end.get()))
	def set(self,val):
		p1,p2,end=val
		self.p1.set(p1)
		self.p2.set(p2)
		self.end.set(end)

class straight(lineClass):
	def __init__(self,frma,val=None):
		self.frm=frma
		self.end=point(belong=self)
		self.len()
		self.line,=ax.plot(0,0)
		super().__init__(val)
	def f(self,t):
		x=(1-t)*self.frm.x+t*self.end.x
		y=(1-t)*self.frm.y+t*self.end.y
		return (x,y)
	def len(self):
		self.calcedLen=math.sqrt((self.frm.x-self.end.x)**2 + (self.frm.y-self.end.x)**2)
		return self.calcedLen
	def draw(self,detail=0):
		ys=(self.frm.y,self.end.y)
		xs=(self.frm.x,self.end.x)
		self.line.set_data(xs,ys)
	def delete(self):
		self.end.delete()
		self.line.remove()
	def get(self):
		return self.genGet((self.end.get(),))
	def set(self,val):
		end,=val
		self.end.set(end)

class memory:
	def __init__(self,fileName):
		self.fileName=fileName
		self.lineList=[self.defoVal() for i in range(10)]
	def defoVal(self):
		return [("startl",((0,0),)),]
	def write(self):
		with open(self.fileName,"wb") as file:
			print("write")
			print(self.lineList)
			pickle.dump(self.lineList,file)
	def read(self):
		with open(self.fileName,"rb") as file:
			
			self.lineList=pickle.load(file)
			print("read")
			print(self.lineList)
	def recall(self,line,number):
		line.delC()
		list=self.lineList[number].copy()
		line.setC(list)
	def memorize(self,line,number):
		self.lineList[number]=line.getC()

def click(event):
	global dragP,slctP
	#print("button={} x={} y={}".format(event.button,event.xdata,event.ydata))
	if slctP != None:
		slctP.selected(False)
	dist,dragP=point.nearPoint(event.xdata,event.ydata)
	slctP=dragP
	slctP.selected(True)
	
def motion(event):
	global dragP,slctP
	#print("motion x={} y={}".format(event.xdata,event.ydata))
	if dragP==None:
		return
	if event.xdata==None or event.ydata==None:
		return
	dragP.set((event.xdata,event.ydata))

def release(event):
	global dragP
	dragP=None
	line.drawC(0.01)


def delLine(line):
	print("line del")
	#参照を含むのでそのままだと消されない、そのためにまず手動で参照を消す
	line.delete()
	line.preLine.nextLine=None
	del line

"""
def addLine(line,new):
	line.nextLine=new(line.end)
	line.nextLine.preLine=line
	line.nextLine.draw()"""

def genSlope(x):
	#return (math.sin((x-0.5)*math.pi)+1.0)/2.0
	return (math.sin((x)*(math.pi/2.0)))

def genSpeed(now,total):
	tagSpd=5
	tagSpdH=150
	if total<(tagSpdH*2):
		mult=total/(tagSpdH*2)
		tagSpd*=mult
		tagSpdH*=mult
	byEnd=total-now
	if now<tagSpdH:
		return genSlope(now/tagSpdH)*tagSpd
	elif byEnd<tagSpdH:
		return genSlope(byEnd/tagSpdH)*tagSpd
	else:
		return tagSpd

def printaCoord(i):
	x,y=line.flC(i)
	print("{{{},{}}},".format(int(x*mmPerPixcel),int(y*mmPerPixcel)),end="")

def genCoord():
	total=line.lenC()
	i=0
	while i<=total:
		printaCoord(i)
		i+=genSpeed(i,total)+0.1
	pass
def genCoordReverse():
	total=line.lenC()
	i=total
	while i>=0:
		printaCoord(i)
		i-=genSpeed(i,total)+0.1
	pass

def setDrag(isv):
	if isv:
		setDrag.clickCid=fig.canvas.mpl_connect('button_press_event',click)
		setDrag.motionCid=fig.canvas.mpl_connect('motion_notify_event',motion)
		setDrag.releaseCid=fig.canvas.mpl_connect('button_release_event',release)
		print("マウス入力を受付しています")
	else:
		fig.canvas.mpl_disconnect(setDrag.clickCid)
		fig.canvas.mpl_disconnect(setDrag.motionCid)
		fig.canvas.mpl_disconnect(setDrag.releaseCid)
		print("マウス入力の受付を中止しました")

def key(event):
	global slctP,line,mem,killFlg
	if event.key=='w':
		setDrag(key.nowDragSetting)
		key.nowDragSetting=not key.nowDragSetting
	elif event.key=='a':
		if slctP!=None:
			if slctP.belong != None:
				slctP.belong.addLine(bazier)
	elif event.key=='z':
		if slctP!=None:
			if slctP.belong != None:
				slctP.belong.addLine(straight)
	elif event.key=='d':
		if slctP!=None:
			if slctP.belong != None:
				if slctP.belong.nextLine == None:
					delLine(slctP.belong)
					slctP=None
				else:
					print("次のラインがあるため消せない")
	elif event.key=='i':
		genCoord()
		print("\n正転再生終了")
	elif event.key=='u':
		genCoordReverse()
		print("\n逆転再生終了")
	elif event.key=='t':
		pass
	elif '0'<=event.key and event.key<='9':
		switchLine(int(event.key))
	elif event.key=='x':
		killFlg=True
key.nowDragSetting=False

def switchLine(number):
	global mem,line,nowMem
	mem.memorize(line,nowMem)
	mem.recall(line,number)
	nowMem=number
	print(str(number)+"がリコールされました")

def killProgram():
	global line
	mem.memorize(line,nowMem)
	mem.write()
	plt.close()
	print("プログラムを停止します")
	exit(0)

#スタート

print("自動機経路生成支援プログラム  Starway Alpha  by mss7z")

#matplotlibへ設定
fig=plt.figure()
ax=fig.add_subplot(1,1,1)
ax.imshow(plt.imread(fieldImageName))
ax.invert_yaxis()
fig.canvas.mpl_connect('key_press_event',key)

#基本点生成
line=startl()

killFlg=False

#保存システム初期化
mem=memory(lineFileName)
nowMem=0
try:
	mem.read()
except:
	print(lineFileName+" が無いようだ")
mem.recall(line,0)

#マウス操作
dragP=None
slctP=None
setDrag(True)

while True:
	try:
		plt.pause(0.05)
	except:
		print("警告:メインループに例外発生!")
		killProgram()
	if killFlg:
		killProgram()