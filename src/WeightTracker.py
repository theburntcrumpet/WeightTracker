import os

def CreateFileIfNotExists(strFile):
	if(os.path.isfile(strFile))
		return True
	try:
		f = open(strFile,"w")
		f.write("")
		f.close()
	except Exception as e:
		return False
	return True

class WeightData:
	def __init__(self,strFileName):
		self.strFileName = strFileName
		self.weights = []

	def ReadWeights(self):
		if(!CreateFileIfNotExists(self.strFileName)):
			print("Failed to create file")
			return False
		f = None
		try:
			f = open(self.strFileName,"r")
		except Exception as e:
			print("Failed to open file for reading")
			return False

		for l in f:
			try:
				n = int(l)
				self.weights.append(n)
			except Exception as e:
				pass
		f.close()
		return True

	def IsValidWeight(self, nSt, nLbs):
		return nSt > 0 and nLbs >= nLbs and nLbs < 14

	def RemoveWeight(self,nIndex):
		if nIndex < 1 or nIndex > len(self.weights):
			print("Enter a valid index!")
			return False
		del self.weights[nIndex-1]
		f = None
		try:
			f = open(self.strFileName,"w")
			for i in weights:
				f.write(i)
			f.close()
		except Exception as e:
			print("There was a problem writing the data file")
			return False
		return True
