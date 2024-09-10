## Exercice 1

![[Exercice 1.png]]

1. On a $AV = U\Sigma V^TV = U\Sigma$
   Et on a $V = (v_{1},\dots,v_{n})$ d'où $AV = (Av_{1}, \dots, Av_{n})$
   Donc $Av_{i}$ est la i-ème colonne de $U\Sigma$
   
   Or, $U\Sigma = (u_{1}, \dots, u_{n}) \begin{pmatrix} \sigma_{1} & \dots & \dots \\ 0 & \dots & \dots \\ 0 & \dots & \sigma_{min(m,n)}\end{pmatrix}$
   D'où la i-ème colonne de $U\Sigma$ est $\sigma_{i}u_{i}$.
   Donc $Av_{i} = \sigma_{i}u_{i}$
   
   _Pour la 2ème égalité, on utilise $A^T = V\Sigma^T U^T$ et on applique le même raisonnement_
   
2. D'après la 1ère égalité, on a $Av_{i} = \sigma_{i}u_{i}$.
   Donc $A^TAv_{i}=\sigma_{i}A^Tu_{i} = \sigma_{i}^2v_{i}$
   Donc $v_{i}$ est un vecteur propre ($vi \neq 0$ car V est orthogonale donc inversible) de $AA^T$ associé à la valeur propre $\sigma_{i}^2$.
   De plus, V est orthogonale donc les $(v_{i})_{i \in [|1,n|]}$ forment une base de $\mathbb{R}^n$.
   Donc on a toutes les valeurs propres de $A^TA$, ainsi $Sp(A^TA) = \{ \sigma_{i}^2, i \in [|1,n|]\}$
   Ainsi, les valeurs singulières de A sont les racines des valeurs propres de $A^TA$.

3. On a $rg(A) = rg(A^TA) = r$.
   Donc $A^TA$ possède $r$ valeurs propres non nulles. Donc, par _b.)_ A admet $r$ valeurs singulières non nulles.

## Exercice 2
![[Exercice 2.png]]

1. On a $A = P\Lambda P^T$ avec P orthogonale de $\Lambda$ qui sont $\geq 0$.
   On choisit alors $U=P$, $\Sigma = \Lambda$, $V=P$. C'est une SVD de A.

2. B est symétrique réelle donc $\exists Q \in O_{n}(\mathbb{R})$ et $D = (d_{1}, \dots, d_{n})$ diagonale tel que $B=QDQ^T$.
   Donc $B^2=QDQ^TQDQ^T=QD^2Q^T=A=P\Lambda P^T$.
   D'où $P=Q$ et $D^2=\Lambda$.
   Les valeurs propres de B sont les $\sqrt{ \lambda_{i} }$.
   D'où $B=P\Lambda^{1/2}P^T$
   Alors, une SVD de B est $U'= P$, $\Sigma'=\Lambda^{1/2}$, $V'=P$
   
3. $B^TB=B^2=A$
   D'où les valeurs propres de $B^TB$ sont les valeurs propres de A, c'est-à-dire les $\sqrt{ \lambda_{i} }$
   Or, les valeurs singulières de B sont les $\sqrt{ \lambda_{i} }$.
   On retrouve bien le lien de l'exercice _1.b)_

## Exercice 3
![[Exercice 3.png]]
1. On considère la SVD de X suivante : $X = U\Sigma V^T$.
   D'où $CX = CU\Sigma V^T$
   Or $CU$ est orthogonale car $(CU) (CU^T) = CUU^TC^T=\mathrm{Im}$
   Une SVD de $CX$ est $CX = U_{C}\Sigma V^T$ où $U_{C} = CU$
2. a rattraper