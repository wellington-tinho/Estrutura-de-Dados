import threading, time, random


class Filosofo(threading.Thread):
	def __init__(self,name,garfoD,garfoE):
		threading.Thread.__init__(self)
		self.garfoD = garfoD
		self.garfoE = garfoE
		self.name = name

	def Pensar(self):
		tempo = random.randint(1,5)
		print(f'{self.name} esta pensando por {tempo}s')
		time.sleep(tempo)

	def Comer(self):
		print('tentando pegar o garfo esquerdo')
		g1 = self.garfoE.acquire(timeout=1)
		if g1:
			print(f'{self.name} Pegando o garfo esquerdo')
			print(f'{self.name} Tentando pegar o garfo direito')			
			g2 = self.garfoD.acquire(timeout=1)
			if g2:
				print(f'{self.name} Pegando o garfo direito')
				print(f'{self.name} Conseguiu comer e largou os garfos')
				tempo = random.randint(1,8)
				print(f'{self.name} esta comendo por {tempo}s')
				time.sleep(tempo)
				self.garfoD.release()
			else:
				print(f'{self.name} nao conseguiu pegar o garfo direito')
			self.garfoE.release()
		else:
			print(f'{self.name} nao conseguiu pegar o garfo esquerdo e foi dormir')
				
			
	def Dormir(self):
		tempo = random.randint(1,5)
		print(f'{self.name} esta Dormindo por {tempo}s')
		time.sleep(tempo)
	def run(self):
		while True:
			self.Pensar()
			self.Comer()
			self.Dormir()

garfos = []
nomes = ['piton','karl max','platao','snoop dog','tirirca']
for i in range(5):
	garfos.append(threading.RLock())

for i in range(5):
	f = Filosofo(nomes[i],garfos[i],garfos[(i+1)%5])
	f.start()

	 
		

		
		
		
