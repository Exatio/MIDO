```python
def parent(T, x, p):  
    if x in p:  
        return p[x]  
    return None  
  
  
def matrice_adjacente(T, r, p):  
    n = len(T)  
    M = [[0] * n for _ in range(n)]  
    for i in T:  
        for j in T:  
            if j in p and i == p[j]:  
                M[i - 1][j - 1] = 1  
            elif i in p and j == p[i]:  
                M[i - 1][j - 1] = -1  
    return M  
  
  
def racine(M):  
    for i in range(len(M)):  
        row = M[i]  
        if -1 not in row:  
            return i+1  


  
T = {1, 2, 3, 4, 5, 6}  
p = {1: 2, 2: 3, 3: 4, 4: 5, 6: 5}  
r = 1  
x = 3  
  
print(f"Le père de {x} est : {parent(T, x, p)}")  
  
M = matrice_adjacente(T, r, p)  
print("Matrice d'adjacence de l'arbre :")  
for row in M:  
    print(row)  
  
print(f'La racine de l\'arbre est {racine(M)}')```