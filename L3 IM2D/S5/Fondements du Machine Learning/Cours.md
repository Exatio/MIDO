## Décomposition en valeurs singulières (singular value decomposition - SVD)

On a un jeu de données $X \in R^{m \times n}$, on veut comprendre sa structure pour le représenter avec moins de coefficients. On va alors l'analyser en tant qu'application linéaire.

### Sous-espaces fondamentaux

> [!info] Définition
>Pour toute matrice $X \in R^{m \times n}$, on définit :
 >- le **noyau** de X : $Ker X = \{ v \in R^n , Xv = 0\}$
 >- l'**image** de X : $Im X = \{ u \in R^m , \exists v \in R^n \text{ tel que } u = Xv\}$


> [!info] Définition
> Le **rang** de X est la dimension de $Im X$.

Théorème du rang : $\forall X \in R^{n*m}, dim(Ker X) + rg(X) = n$

### Cas des matrices symétriques
Dans cette partie, on suppose que $m=n$ et $X^T = X$.
Alors, il existe une décomposition spectrale de X de la forme $X=PAP^T$ avec : 
- $P \in R^{m \times n}$ orthogonale ($P^T=P^{-1}$)

- $A = \begin{pmatrix}   \lambda_1 & ... & 0\\ 0 & \lambda_i & 0 \\  0 & ... & \lambda_n   \end{pmatrix}$, avec $\lambda_1 \ge ... \ge \lambda_n$ des réels

P permet de transformer X en une matrice diagonale
Les valeurs propres nous disent comment X transforme les colonnes de P. 
Le rang de X est le nombre de valeurs propres non nulles
Le noyau de X est engendré par les colonnes de p correspondant aux valeurs propres nulles.
Pour $\lambda_1 \neq 1$, si $|\lambda_i| \ge 1$, alors X a un effet d'augmentation dans la dimension de la i-ème colonne de p.
Si $|\lambda_i| \ge 1$, alors il a un effet de réduction.

...

A valeur propre nulle $\implies rg X = 1$
	On dit que la matrice n'est pas de rang plein, ce qui signifie qu'elle contient moins d'informations que sa capacité
A valeurs propre égale ) 1 $\implies$ conservation des vecteurs colinéaires à $p_1 = \begin{pmatrix} \frac{1}{\sqrt{2}} \\ \frac{1}{\sqrt{2}} \end{pmatrix}$
Avec la bonne base P, X s'écrit $P\begin{pmatrix} 2 & 0 \\ 0 & 1 \end{pmatrix}P^T$

### Cas général
On revient au cas $X \in R^{m \times n}$ avec m, n quelconques ($\ge 1$)
Existe-t-il un analogue de la décomposition spectrale dans ce cas général ?

> [!info] Propriétés des matrices $XX^T$ et $X^TX$
> 
- $Ker (X^TX) = Ker (X)$ et $Ker (XX^T) = Ker (X^T)$
- $Im (X^TX) = Im (X^T)$ et $Im (XX^T) = Im (X)$
- $rg (X^TX) = rg (X)$ et $rg (XX^T) = rg (X^T)$

L'étude de X via ses 4 sous-espaces fondamentaux se ramène à l'étude des matrices symétriques $XX^T$ et $X^TX$, qui ont chacune 2 sous-espaces fondamentaux.
Cela revient à dire que l'on peut étudier X via les décompositions spectrales de $XX^T$ et $X^TX$
Les valeurs propres de $XX^T$ et $X^TX$ sont positives ou nulles ($XX^T \ge 0$ et $X^TX \ge 0$)


> [!info] Théorème (SVD)
> Soit $X \in R^{m \times n}$. Cette matrice admet une décomposition en valeurs singulières de la forme $X = U\Sigma V^T$  avec :
> - $U \in R^{m \times m}$, orthogonale ($U^T = U^{-1}$)
> - $V \in R^{n \times n}$, orthogonale ($V^T = V^{-1}$)
> - $\Sigma = \begin{bmatrix} \sigma_1 & 0 & 0 \\ 0 & \sigma_{\min(n,m)} & 0 \\ 0 & 0 & 0\end {bmatrix} \in R^{m \times n}$
> - $\Sigma = (\sigma_{ij})$ avec $\sigma_{ij} = 0$ si $i \neq j$ et $\sigma_{ii} = \sigma_{i} \ge 0$
> 
> Colonnes de U : vecteurs singuliers à gauche
> Colonnes de V : vecteurs singuliers à droite
> Coefficients diagonaux de $\Sigma$ : $\sigma_1$, ..., $\sigma_n$ (en général on les ordonne : $\sigma_1 \ge ... \ge \sigma_n$)


> [!info] Propriétés (SVD)
> i) Le rang de X est le nombre de valeurs singulières non nulles ($rg(X) \leq min(m,n)$)
> 
ii) Les carrés des valeurs singulières de X ($\sigma_{1}^2 \geq \dots \geq \sigma_{min(m,n)}$) sont valeurs propres de $X^TX$ et $XX^T$
>
iii) Si $X=U\Sigma V^T$ est une SVD de X, alors $U^T\Sigma^TV$ est une SVD de $X^T$


TD: preuve constructive de la SVD.

Calcul pratique de la SVD: 
- Efficace grâce à l'algorithme de Golub-Kahan
- Stable numériquement

### SVD et réduction de dimension
Soit $X \in \mathbb{R}^{m\times n}$ et $X=U\Sigma V^T$ une SVD de X, avec :
- $$
\Sigma = \begin{bmatrix}
\sigma_{1} & 0 & 0 \\
0 & .. & 0 \\
0 & 0 & ..
\end{bmatrix}
$$
- $U = [u_{1}, \dots, u_{m}]$ avec $u_{i} \in \mathbb{R}^m, \forall i$
- $V = [v_{1}, \dots, v_{n}]$ avec $v_{j} \in \mathbb{R}^n, \forall j$

 Alors, la SVD réduite de X est :
$$
 X = [u_{1}, \dots, u_{r}] \begin{bmatrix}
\sigma_{1} & \dots & 0  \\
0  & \sigma_{i} & 0 \\
0 & \dots & \sigma_{r}
\end{bmatrix}
\begin{bmatrix}
v_{1}^T \\
\dots \\
v_{r}^T
\end{bmatrix}
$$avec $r = rg(X)$

Et la SVD tronquée de X est :
$$
X = [u_{1}, \dots, u_{k}] \begin{bmatrix}
\sigma_{1} & \dots & 0  \\
0  & \sigma_{i} & 0 \\
0 & \dots & \sigma_{k}
\end{bmatrix}
\begin{bmatrix}
v_{1}^T \\
\dots \\
v_{k}^T
\end{bmatrix}
$$
avec $k \leq rg(X)$

Si $r\leq min(m,n)$ alors la SVD réduite permet de représenter X avec $n \times m$ moins de coefficients.
Si $k \leq min(m, n)$, alors le k-SVD permet d'approcher X avec moins de $m \times n$ coefficients.