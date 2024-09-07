## Exercice 1

![[Exo1.png]]

1. La relation "Personne" pourrait avoir, en tant que clés primaires :
   - Num (clé artificielle)
   - Prenom (clé matérielle)
   - DateNaissance (clé matérielle)
   - (Nom, Prenom) (clé matérielle, je parle ici du couple des deux attributs)
   - (Prenom, DateNaissance)
   - ...
   En analysant uniquement les instances, il y a beaucoup de possibilités de clé primaires, notamment en faisant intervenir des couples uniques.
   En revanche, on peut noter qu'il est impossible que les attributs Nom et Sexe soient individuellement des clés primaires, car ils ont des valeurs qui se répètent plusieurs fois dans la relation.
   
   La relation "Parente" ne peut avoir que deux clés primaires possibles : IDEnfant et le couple (IDParent, IDEnfant). En effet, IDParent se répète, il ne peut donc pas être un clé primaire.
   
2. En analysant uniquement la sémantique sous-jacente du schéma, on voit facilement que l'on souhaiterait définir Num comme clé primaire pour la relation Personne et IDEnfant pour la relation Parente.
   
3.  La relation "Personne" ne possède (à priori) pas de clés étrangères. En revanche, IDParent et IDEnfant sont des clés étrangères faisant référence à Num dans la relation Personne.
   
4. Sexe $\in \{ M , F \}$
   
5. Personne.IDParent.DateNaissance < Personne.IDEnfant.DateNaissance
   

## Exercice 3

![[BDD/TD/TD1 - Modèle relationnel/Exo3.png]]

Le SGBD va refuser l'inserttion du nuplet car ClientID est une clé étrangère faisant référence à la relation Client, qui ne contient pas de client dont le ClientID est de valeur 4.i
## Exercice 4

![[Exo4.png]]

1. On ne peut pas insérer de nuplet (3, 'MIAGE-IF', 2, 1) dans la relation Master dans la mesure où MasterID est une clé primaire est on ne peut pas avoir de doublons, sachant qu'il y a déjà un master dont le MasterID vaut 3.
2. Oui, on peut l'insérer. Il n'existe pas déjà de master d'identifiant 5, le nom ne devrait pas poser de problèmes, il existe bien un enseignant d'identifiant 4, et le département 1 existe également puisque déjà utilisé. 
3. On ne peut pas directement supprimer le nuplet correspondant à l'enseignant 'Khalid Belhajjame' dans la relation Enseignant car ce nuplet est référencé par sa clé primaire (EnseignantID valant 3) en tant que clé étrangère dans la relation Master.
   Il faudrait d'abord supprimer cette clé étrangère où mettre sa valeur à NULL avant de pouvoir supprimer ce nuplet.
## Exercice 6

![[Exo6.png]]
La raison de ce problème est que la clé primaire de la relation "Travailler" est le couple (CodeMb, CodeEnt). C'est-à-dire que ce couple doit être unique, et donc impossible de mettre plusieurs postes pour la même personne dans une entreprise.
La solution serait de modifier la clé primaire pour qu'elle puisse être unique tout en ayant plusieurs postes dans la même entreprise: par exemple le triplet (CodeMb, CodeEnt, PosteOccupé) ou bien on peut créer un nouvelle attribut TravailID qui correspondrait donc à un poste pour une personne dans une entreprise 