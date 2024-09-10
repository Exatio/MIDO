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
   
   1. 