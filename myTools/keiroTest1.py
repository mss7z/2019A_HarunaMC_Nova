from matplotlib import pyplot as plt

fig=plt.figure()
ax=fig.add_subplot(1,1,1)

class point:
	def __init__(self,xa=0,ya=0):
		self.x=xa
		self.y=ya
		self.p,=ax.plot(self.x,self.y,"ro")
	def update(self):
		self.p.set_data(self.x,self.y)
	def set(self,xa,ya):
		self.x=xa
		self.y=ya
		self.update()
	def distSq(self,xa,ya):
		return (self.x-xa)**2 + (self.y-ya)**2
	
	
points={"from":point(), "p1":point(), "p2":point(), "to":point()}

def frange(f,t,j):
	v=f
	while v<t:
		yield v
		v += j

def func(t):
	x=(1-t)**3*points["from"].x + 3*(1-t)**2*t*points["p1"].x + 3*(1-t)*t**2*points["p2"].x + t**3*points["to"].x
	y=(1-t)**3*points["from"].y + 3*(1-t)**2*t*points["p1"].y + 3*(1-t)*t**2*points["p2"].y + t**3*points["to"].y
	return (x,y)

def writeC(detail=0.1):
	ys=[]
	xs=[]
	for i in frange(0,1,detail):
		(x,y)=func(i)
		xs.append(x)
		ys.append(y)
	lines.set_data(xs,ys)

dragP=None
def click(event):
	global dragP,points
	print("button={} x={} y={}".format(event.button,event.xdata,event.ydata))
	min=points["from"].distSq(event.xdata,event.ydata)
	minP=points["from"]
	for p in points.values():
		now=p.distSq(event.xdata,event.ydata)
		if now<min:
			min=now
			minP=p
	dragP=minP
	
def motion(event):
	global dragP
	print("motion x={} y={}".format(event.xdata,event.ydata))
	if dragP==None:
		return
	if event.xdata==None or event.ydata==None:
		return
	dragP.set(event.xdata,event.ydata)
	writeC()

def release(event):
	global dragP
	print("release")
	dragP=None
	writeC(0.01)

def key(event):
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
key.nowDragSetting=False

lines,=ax.plot(0,0)

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