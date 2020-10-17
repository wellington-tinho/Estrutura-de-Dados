# python3
# coding: utf-8

g = {'s':{'t':10,'y':5},
    't':{'y':2,'x':1},
    'x':{'z':4},
     'y':{'t':3,'z':2},
    'z':{'s':7,'x':6}
    }


start = 's'
S=[]
d = {}
prev = {}
Q = list(g.keys())

for k in Q:
    d[k] = float('inf')
    prev[k] = None
    
d[start] = 0

def extract_min(d,q):
    min_ = q[0]
    for i in q:
        if d[i]<d[min_]:
            min_ = i
    q.remove(min_)
    return min_

def relax(u,v,d,prev,g):
        soma = g[u][v]+d[u]
        if d[v] > soma:
            d[v] = soma
            prev[v] = u
            
while Q:
    u = extrac_min(d,Q)
    S.append(u)
    for v in g[u].keys():
    

print(d)
print(prev) 
print(S)

