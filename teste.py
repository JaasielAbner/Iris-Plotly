#use teste function to v1.out

f = open('IrisDataset.csv', 'r')
c = f.read()
types = []
x = 0

for l in (c.split('\n'))[1:] :
   t = (l.split(','))[-1]
   types.append(t.strip('"'))
   x+=1
f = open('v1.out', 'r')
c = f.read().splitlines()

acertos = 0
erros = 0

for i in range(150):
   x = c[i].split()
   for j in range(150-i-1):
      if x[j]=="1": 
         if ((i<=49 and j<=49) or (i<100 and i>=50 and j<100 and j>=50) or (i>=100 and j>=100)):
            acertos+=1
         else:
            erros+=1
print(acertos, erros)
         