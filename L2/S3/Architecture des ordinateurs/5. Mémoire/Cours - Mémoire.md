Mémorisation de l’information 
- Registres
- Mémoire cache
- Mémoire principale (RAM)
- Mémoire de masse (disquette, disque dur, SSD + Clé USB, CD + DVD, bande magnétique)

## 1. Caractéristiques
### a) Localisation
Dans le CPU : registres, mémoire cache
Proche du CPU : mémoire principale
Relié via E/S : mémoire de masse
Relié via réseau : serveur, cloud

### b) Capacité
Ordre de grandeur non arbitraire :
- Registres : ordre de l’octet à 1 ko
- Cache L1 : 32ko à 128ko
- Cache L2 : 512 ko à 8 mo
- Cache L3 : 8 mo à 32 mo
- RAM : 1 Go à 32 Go
- HDD : 1 To à 20 To  
- SSD : 25 Go à 2 To
- CD : 700 mo
- DVD : 4 Go à 25 Go
- Bande : ~10 Go
  
### c) Méthodes d'accès

- **Accès séquentiel** : parcours de toutes les cases jusqu’à celle la case voulu
  Exemple : bandes magnétiques + schéma
  
- **Accès semi-direct** : Mémoire sous la forme d’un tableau à 2 dimensions : On choisit directement la ligne puis on la parcourt 
  Exemple : HDD, CD, DVD
  
- **Accès direct ou aléatoire** : Adresse envoyée à un décodeur qui sélectionne la bonne case

![[Pasted image 20231211110420.png]]
### d) Performances
#### i.) Mémoire à accès aléatoire

**Temps d'accès** : temps entre l'envoi de l'adresse et la réception de la donnée.
Exemples: 
- Registre (1 ns)
- Cache (3-10 ns)
- Mémoire principale (~30 ns)
- SSD (~$50 \mu s$)

**Temps de cycle** : temps mini entre deux accès (= temps d'accès + temps de latence des circuits)

Des dispositifs permettent d'accélérer les transferts.

#### ii.) Mémoires à accès semi-direct (ex: disque dur)

- Temps de positionnement de la tête de lecture sur la bonne piste (= temps d'accès)
  $\approx$ 5 à 10 ms
- Temps de latence : temps d'attente avant arrivée de la donnée sous la tête de lecture.
  qq ms
- Taux de transfert de données 
  $\approx$ 100 Mo/s

### e.) Caractéristiques physiques

Support :
- électronique : registre, cache, RAM, SSD
- magnétique : disque dur, bande magnétique
- optique : CD, DVD

## 2.) Mémoires à semi-conducteurs

### a.) Types

**RAM** : 
- mémoire de travail contenant programmes et données en cours d'exécution.
- volatile : informations perdues sans courant

**ROM** : 
- **R**ead**O**nly **M**emory 
- mémoire non volatile, mémorise l'information de manière permanente et non modifiable (ou presque)
- utilité : programme de démarrage (aller chercher le reste du système sur le disque et le mettre en RAM)

### b. Organisations internes

-> cf poly


## 3. Mémoire cache

### a.) Hiérarchie mémoire

Plusieurs types de mémoires mais souvent plus la capacité est grande, plus le temps d'accès l'est également.

![[Pasted image 20231211113740.png]]

### b.) Principe

-> Le cache est une mémoire plus rapide que la RAM et qui contient un sous ensemble de celle-ci
-> Quand le CPU demande de l'information (instructions ou données), il regarde si elle est dans le cache et si oui, elle est rapidement disponible, sinon le CPU la récupère en RAM.









