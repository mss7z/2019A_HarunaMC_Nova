from matplotlib import pyplot as plt
from math import sqrt

fig=plt.figure()
ax=fig.add_subplot(1,1,1)

ax.imshow(plt.imread("redFieldSH.png"))
ax.invert_yaxis()

mmPerPixcel=10

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
	def set(self,xa,ya):
		self.x=xa
		self.y=ya
		self.update()
	def distSq(self,xa,ya):
		return (self.x-xa)**2 + (self.y-ya)**2
	def selected(self,isv):
		if isv:
			self.p.set_sizes((30,))
		else:
			self.p.set_sizes((10,))
	def delete(self):
		print("call delete !!!!!!!")
		self.delPoints(self)
		self.p.remove()

class lineClass:
	def __init__(self):
		self.nextLine=None
		self.preLine=None
		print("line called")
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
			print(self.len())
			return self.len()
		else:
			return self.len()+self.nextLine.lenC()
	def flC(self,l):
		#self.len()
		if l<=self.calcedLen:
			return self.fl(l)
		else:
			return self.nextLine.flC(l-self.calcedLen)

class startl(lineClass):
	def __init__(self):
		super().__init__()
		self.end=point(belong=self,marker="*")
	def delete(self):
		raise ValueError("この点は消せません")
	def f(self,t=0):
		return (self.end.x,self.end.y)
	def fl(self,l=0):
		return self.f()
	
class bazier(lineClass):
	def __init__(self,frma=None):
		super().__init__()
		if frma == None:
			self.frm=point(belong=self)
		else:
			self.frm=frma
		self.p1=point(belong=self)
		self.p2=point(belong=self)
		self.end=point(belong=self)
		self.len()
		self.line,=ax.plot(0,0)
		print("maked bazier")
	def f(self,t):
		x=(1-t)**3*self.frm.x + 3*(1-t)**2*t*self.p1.x + 3*(1-t)*t**2*self.p2.x + t**3*self.end.x
		y=(1-t)**3*self.frm.y + 3*(1-t)**2*t*self.p1.y + 3*(1-t)*t**2*self.p2.y + t**3*self.end.y
		return (x,y)
	def fl(self,l):
		return self.f(l/self.calcedLen)
	def len(self):
		prex,prey=self.f(0)
		ans=0
		for i in frange(0,1,0.01):
			nowx,nowy=self.f(i)
			ans+=(nowx-prex)**2+(nowy-prey)**2
		self.calcedLen=sqrt(ans)
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
	"""
	def __del__(self):
		self.p1.delPoints(self)
		self.p2.delPoints(self)
		self.end.delPoints(self)
		self.line.remove()"""


line=startl()
"""
def writeC(detail=0.1):
	print("writeC")
	global line
	proc=line
	while True:
		proc=proc.nextLine
		if proc is None:
			break
		proc.draw(detail)
def lenC():
	global line
	proc=line
	len=0
	while True:
		proc=proc.nextLine
		if proc is None:
			break
		len+=proc.len()
	return len
"""

dragP=None
slctP=None
def click(event):
	global dragP,slctP
	print("button={} x={} y={}".format(event.button,event.xdata,event.ydata))
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
	dragP.set(event.xdata,event.ydata)

def release(event):
	global dragP
	print("release")
	dragP=None
	line.drawC(0.01)

def delLine(line):
	print("line del")
	#参照を含むのでそのままだと消されない、そのためにまず手動で参照を消す
	line.delete()
	line.preLine.nextLine=None
	del line

def addLine(line,new):
	line.nextLine=new(line.end)
	line.nextLine.preLine=line
	line.nextLine.draw()

def genCoord():
	total=line.lenC()
	for i in frange(0,total,10):
		x,y=line.flC(i)
		print("{{{},{}}},".format(int(x*mmPerPixcel),int(y*mmPerPixcel)))
	pass

def key(event):
	global slctP
	if event.key=='w':
		if key.nowDragSetting:
			fig.canvas.mpl_disconnect(key.clickCid)
			fig.canvas.mpl_disconnect(key.motionCid)
			fig.canvas.mpl_disconnect(key.releaseCid)
		else:
			key.clickCid=fig.canvas.mpl_connect('button_press_event',click)
			key.motionCid=fig.canvas.mpl_connect('motion_notify_event',motion)
			key.releaseCid=fig.canvas.mpl_connect('button_release_event',release)
		key.nowDragSetting=not key.nowDragSetting
	elif event.key=='a':
		if slctP!=None:
			if slctP.belong != None:
				addLine(slctP.belong,bazier)
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
		print("len {}".format(line.lenC()))
		
key.nowDragSetting=False

fig.canvas.mpl_connect('key_press_event',key)


#plt.ion()
"""
for i in frange(0,1,0.01):
	(x,y)=func(i)
	xs.append(x)
	ys.append(y)
	#plt.plot(x,y,'ro')
	#lines.set_data(xs,ys)
	
	#plt.pause(0.1)
	#plt.clf()
	"""



#plt.show()
while True:
	plt.pause(0.05)

"""
plt.plot(xs,ys,"ro")
plt.show()
"""