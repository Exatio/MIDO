# Un exemple d'assembleur 

Une instruction CPU est un code numérique (souvent exprimé en hexadécimal) aussi écrit mmh un équivalent symbolique

___Exemple :___
Compris par le CPU -> ``37CAB3FO`` (base 16) = ``XOR r10, r0, #B3F0`` <- Compris par les humains

La traduction entre code assembleur et code numérique est faite par l'assembleur.

## Exemple de CPU
### Registres
- registre PC sur 32 bits (-> 4 Go)
- 32 registres généraux sur 32 bits chacun : r0 à r31
- un registre d'état avec les bits Z, C, V, N
- 
## Instructions
### Transfert de données

- ``mov rx, ry`` rx <- ry
- ``mvi rx, #i`` rx <- valeur i en décimal, en général en assembleur -> hexa

- ``ldb rx, (ry)`` *load byte :* rx <- (ry) sur un octet
- ``ldh rx, (ry)`` *load half :* rx <- (ry) sur la moitié du registre (registre 32 bits -> moitié = 16 bits = 2 octets)
- ``ldw rx, (ry)`` *load word :* rx <- (ry) sur 4 octets
  
- ``stb (rx), ry`` *store byte :* (rx) <- ry sur 1 octet. rx est un registre qui pointe sur une ??
- ``sth (rx), ry`` *store half :* (rx) <- ry sur 2 octets
- ``stw (rx), ry`` *store word :* (rx) <- ry sur 4 octets

### Opérations arithmétique et logique

- ``ADD rx,ry,rz`` rx <- ry + rz
- ``ADD rx,ry,#i`` rx <- ry + valeur i  

La même chose avec :
- ``SUB``(soustraction)
- ``MUL`` (multiplication)
- ``DIV`` (division)
- ``AND`` (ET logique)
- ``OR`` (OU logique)
- ``XOR`` (OU exclusif logique)

La multiplication travaille sur les 16 bits de poids faible de ry et rz

- ``NOT rx,rz`` rx <- !rz
- ``NOT rx,#i`` rx <- !#i
- ``NEG rx,rz`` rx <- - rz
- ``NEG rx,#i`` rx <- - #i

### Décalage / Rotation

- ``LRT rx,ry,rz`` *left rotate :* rx <- ry décalé par rotation rz fois vers la gauche
- ``LLS rx,ry,rz`` *logical left shift :* rx <- ry décalé rz fois à gauche

### Sauts (rupture de séquences)

- ``JMP Adr`` PC <- Adr

- ``JZ rx,Adr`` *Jump if zero :* PC <- Adr si rx = 0
- ``JNZ rx,Adr`` *Jump if not zero :* PC <- Adr si rx != 0

De même :
- ``JGT rx,Adr`` >
- ``JLT rx,Adr`` <
- ``JGE rx,Adr`` >=
- ``JLE rx,Adr`` <=

On peut mettre une étiquette à la place de l'adresse ; elle sera associée à une autre instruction.
Par exemple : 
```
JMP ici

...
...

ici: ADD r0,r1,r2
```
