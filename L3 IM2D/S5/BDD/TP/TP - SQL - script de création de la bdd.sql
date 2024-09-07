-- Suppression des relations si elles sont deja créées 
-- (enlever les tirets de commentaire)
-- L'ordre de suppression des relations doit être respecté 
-- pour ne pas violer les contraintes d'intégrité réferentielles
--DROP VIEW Email_Etudiant;
--DROP TABLE Etudiant;
--DROP TABLE Reservation;
--DROP FUNCTION GetSalleCapaciteSuperieurA(int);
--DROP TABLE Salle;
--DROP TABLE Cours;
--DROP TABLE Enseignant;
--DROP TABLE Departement;

-- Script de création des relations

CREATE TABLE Departement
(
 Departement_id     serial,
 Nom_Departement   varchar(25) NOT NULL,
 CONSTRAINT UN_Nom_Departement UNIQUE (nom_departement),
 CONSTRAINT PK_Departement PRIMARY KEY(Departement_ID)
);

CREATE TABLE Etudiant
(
 Etudiant_ID    serial,
 Nom      	varchar(25) NOT NULL,
 Prenom   	Varchar(25) NOT NULL,
 Date_Naissance date NOT NULL,
 Adresse  	Varchar(50) DEFAULT NULL,
 Ville    	Varchar(25) DEFAULT NULL,
 Code_Postal  	Varchar(9) DEFAULT NULL,
 Telephone      Varchar(10) DEFAULT NULL,
 Fax            Varchar(10) DEFAULT NULL,
 Email          Varchar(100) DEFAULT NULL,
 CONSTRAINT PK_Etudiant PRIMARY KEY (Etudiant_ID));
 
CREATE TABLE Cours
( 
  Cours_ID  integer NOT NULL,
  Departement_ID   integer NOT NULL,
  Intitule         varchar(60) NOT NULL UNIQUE,
  Description      varchar(1000),
  CONSTRAINT PK_Cours PRIMARY KEY (Cours_ID, Departement_ID),
  CONSTRAINT "FK_Cours_Departement" FOREIGN KEY (Departement_ID) REFERENCES Departement (Departement_ID) ON UPDATE RESTRICT ON DELETE RESTRICT
) ;

CREATE TABLE Enseignant
(
 Enseignant_ID     serial,
 Departement_ID    integer NOT NULL,
 Nom        	   varchar(25) NOT NULL,
 Prenom            varchar(25) NOT NULL,
 Grade             varchar(25) 
 CONSTRAINT CK_Enseignant_Grade
 CHECK (Grade IN ('Vacataire', 'Moniteur','ATER', 'MCF', 'PROF')),
 Telephone         varchar(10) DEFAULT NULL,
 Fax               varchar(10) DEFAULT NULL,
 Email             varchar(100) DEFAULT NULL,
 CONSTRAINT PK_Enseignant PRIMARY KEY (Enseignant_ID),
 CONSTRAINT "FK_Enseignant_Departement_ID" FOREIGN KEY (Departement_ID) REFERENCES Departement (Departement_ID) ON UPDATE RESTRICT ON DELETE RESTRICT
);



CREATE TABLE Salle
(
 Batiment     	varchar(1),
 Numero_Salle   varchar(10),
 Capacite  	integer CHECK (Capacite >1),
 CONSTRAINT PK_Salle PRIMARY KEY (Batiment, Numero_Salle)
);

CREATE TABLE Reservation
(
 Reservation_ID     serial,
 Batiment           varchar(1) NOT NULL,
 Numero_Salle       varchar(10) NOT NULL,
 Cours_ID    integer NOT NULL,
 Departement_ID     integer NOT NULL,
 Enseignant_ID      integer NOT NULL, 
 Date_Resa          date NOT NULL DEFAULT CURRENT_DATE,
 Heure_Debut	    time NOT NULL DEFAULT CURRENT_TIME,
 Heure_Fin	    time NOT NULL DEFAULT '23:00:00',
 Nombre_Heures	    integer NOT NULL,
 CONSTRAINT PK_Reservation PRIMARY KEY (Reservation_ID),
 CONSTRAINT "FK_Reservation_Salle" FOREIGN KEY (Batiment,Numero_Salle) REFERENCES Salle (Batiment,Numero_Salle) ON UPDATE RESTRICT ON DELETE RESTRICT,
 CONSTRAINT "FK_Reservation_Cours" FOREIGN KEY (Cours_ID,Departement_ID) REFERENCES Cours (Cours_ID,Departement_ID) ON UPDATE RESTRICT ON DELETE RESTRICT,
 CONSTRAINT "FK_Reservation_Enseignant" FOREIGN KEY (Enseignant_ID) REFERENCES Enseignant (Enseignant_ID) ON UPDATE RESTRICT ON DELETE RESTRICT,
 CONSTRAINT CK_Reservation_Nombre_Heures CHECK (Nombre_Heures >=1),
 CONSTRAINT CK_Reservation_HeureDebFin CHECK (Heure_Debut < Heure_Fin)
);


 
 
CREATE OR REPLACE VIEW Email_Etudiant
AS SELECT Nom, Prenom, Email FROM Etudiant;


-------------------------------------------------------------------------
--Fonction permettant de récuperer la liste des salles ayant une capacité
--supérieure à une certaine valeur
-------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION GetSalleCapaciteSuperieurA(int) RETURNS SETOF Salle AS '
    SELECT * FROM Salle WHERE Capacite > $1;
' LANGUAGE SQL;

SELECT * FROM GetSalleCapaciteSuperieurA(300) ;




------------------------------------------------------------------------
--Fonction permettant de récuperer l'identificateur du département à partir
--de son nom
-------------------------------------------------------------------------


CREATE OR REPLACE FUNCTION GetDepartement_ID(text) RETURNS integer AS
'SELECT Departement_ID FROM Departement WHERE Nom_Departement = $1'
LANGUAGE SQL;

SELECT Nom, Prenom 
 FROM Enseignant 
  WHERE Departement_ID IN (SELECT * FROM GetDepartement_ID('INFO'));


----------------------------------------------------------------------------
--Fonction retournant la ou les identificateurs de reservations existantes
--ne permettant pas de reserver une salle.
--On donne en paramètre de la fonction, la salle (batiment et numéro de salle)
--la date de reservation et l'heure de debut (representée par $4 dans la requête) 
--et de fin de reservation (representée par $5 dans la requête).
--La fonction vérifie que le créneau horaire choisit n'est pas
--contenu dans le créneau horaire d'une reservation existante
--ou ne chevauche pas une le créneau horaire d'une reservation existante
----------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION PossibiliteResa(text,text,date,time,time) RETURNS integer AS
'SELECT Reservation_ID
  FROM Reservation 
   WHERE (Batiment = $1 AND Numero_Salle = $2 AND Date_Resa = $3 AND Heure_Debut < $4  AND $4 < Heure_Fin) 
     OR  (Batiment = $1 AND Numero_Salle = $2 AND Date_Resa = $3 AND $4 < Heure_Debut AND Heure_Debut < $5 AND Heure_Fin > $5)
     OR  (Batiment = $1 AND Numero_Salle = $2 AND Date_Resa = $3 AND Heure_Debut < $4 AND $4 < Heure_Fin AND Heure_Fin < $5)
     OR  (Batiment = $1 AND Numero_Salle = $2 AND Date_Resa = $3 AND Heure_Debut > $4 AND Heure_Fin < $5)
     OR  (Batiment = $1 AND Numero_Salle = $2 AND Date_Resa = $3 AND Heure_Debut = $4 AND Heure_Fin = $5)
     OR  (Batiment = $1 AND Numero_Salle = $2 AND Date_Resa = $3 AND Heure_Debut = $4)
     OR  (Batiment = $1 AND Numero_Salle = $2 AND Date_Resa = $3 AND Heure_Fin = $5)'
LANGUAGE SQL;


SELECT PossibiliteResa('B','022','04/11/2003','09:00:00','18:00:00');



------------------------------------------------------------------------
--Fonction trigger et TRIGGER permettant d'inserer une reservation dans 
--la base, en verifiant que la reservation est possible
-------------------------------------------------------------------------

--**************************************************************************
--Pour activer le langage PL/pgSQL il faut executer la commande
--createlang plpgsql nom_base
--**************************************************************************


CREATE OR REPLACE FUNCTION FunctionTriggerReservation() RETURNS trigger AS
' DECLARE 
  resa Reservation.Reservation_ID%TYPE;
  
  BEGIN
   SELECT INTO resa Reservation_ID
    FROM Reservation 
     WHERE (Batiment = NEW.Batiment AND Numero_Salle = NEW.Numero_Salle AND Date_Resa = NEW.Date_Resa AND Heure_Debut < NEW.Heure_Debut AND NEW.Heure_Debut < Heure_Fin) 
      OR  (Batiment = NEW.Batiment AND Numero_Salle = NEW.Numero_Salle AND Date_Resa = NEW.Date_Resa AND NEW.Heure_Debut < Heure_Debut AND Heure_Debut < NEW.Heure_Fin AND Heure_Fin > NEW.Heure_Fin)
      OR  (Batiment = NEW.Batiment AND Numero_Salle = NEW.Numero_Salle AND Date_Resa = NEW.Date_Resa AND Heure_Debut < NEW.Heure_Debut  AND NEW.Heure_Debut < Heure_Fin AND Heure_Fin < NEW.Heure_Fin)
      OR  (Batiment = NEW.Batiment AND Numero_Salle = NEW.Numero_Salle AND Date_Resa = NEW.Date_Resa AND Heure_Debut = NEW.Heure_Debut  AND Heure_Fin = NEW.Heure_Fin)
      OR  (Batiment = NEW.Batiment AND Numero_Salle = NEW.Numero_Salle AND Date_Resa = NEW.Date_Resa AND Heure_Debut > NEW.Heure_Debut  AND Heure_Fin < NEW.Heure_Fin)
      OR  (Batiment = NEW.Batiment AND Numero_Salle = NEW.Numero_Salle AND Date_Resa = NEW.Date_Resa AND Heure_Debut = NEW.Heure_Debut)
      OR  (Batiment = NEW.Batiment AND Numero_Salle = NEW.Numero_Salle AND Date_Resa = NEW.Date_Resa AND Heure_Fin = NEW.Heure_Fin);

  IF FOUND THEN
    RAISE EXCEPTION ''Reservation impossible, salle occupée à la date et aux horaires demandés'';
  ELSE RETURN NEW;
  END IF;

 END;' 
LANGUAGE 'plpgsql';


--DROP TRIGGER InsertionReservation ON Reservation;

CREATE TRIGGER InsertionReservation
 BEFORE INSERT ON Reservation
  FOR EACH ROW
   EXECUTE PROCEDURE FunctionTriggerReservation();

INSERT INTO Departement(Nom_Departement) VALUES ('MIDO');
INSERT INTO Departement(Nom_Departement) VALUES ('LSO');
INSERT INTO Departement(Nom_Departement) VALUES ('MSO');


INSERT INTO Etudiant(Nom,Prenom,Date_Naissance,Adresse,Ville,Code_Postal,Telephone,Fax,Email) VALUES ('GAMOTTE', 'Albert','1979/02/18','50, Rue des alouettes','PARIS','75021','0143567890',NULL,'gamotal4@etud.dauphine.fr');
INSERT INTO Etudiant(Nom,Prenom,Date_Naissance,Adresse,Ville,Code_Postal,Telephone,Fax,Email) VALUES ('HIBULAIRE', 'Pat','1980/08/23','10, Avenue des marguerites','POUILLON','40000','0678567801',NULL,'pat@yahoo.fr');
INSERT INTO Etudiant(Nom,Prenom,Date_Naissance,Adresse,Ville,Code_Postal,Telephone,Fax,Email) VALUES ('ODENT', 'Jamal','1978/05/12','25, Boulevard des fleurs','PARIS','75022','0145678956','0145678956','odent@free.fr');
INSERT INTO Etudiant(Nom,Prenom,Date_Naissance,Adresse,Ville,Code_Postal,Telephone,Fax,Email) VALUES ('DEBECE', 'Gill','1979/07/15','56, Boulevard des fleurs','PARIS','75022','0678905645',NULL,'deby@hotmail.com');
INSERT INTO Etudiant(Nom,Prenom,Date_Naissance,Adresse,Ville,Code_Postal,Telephone,Fax,Email) VALUES ('DEBECE', 'Aude','1979/08/15','45, Avenue des abeilles','PARIS','75022',NULL,NULL,NULL);

INSERT INTO Enseignant(Departement_ID,Nom,Prenom,Grade,Telephone,Fax,Email)  VALUES((SELECT Departement_id FROM Departement WHERE nom_departement='MIDO') ,'MANOUVRIER','Maude','MCF','4185','4091','maude.manouvrier@dauphine.fr');
INSERT INTO Enseignant (Departement_ID,Nom,Prenom,Grade,Telephone,Fax,Email) VALUES(1,'BELHAJJAME','Khalid ','MCF',NULL,NULL,'khalid.belhajjame[at]dauphine.fr');
INSERT INTO Enseignant(Departement_ID,Nom,Prenom,Grade,Telephone,Fax,Email)  VALUES(1,'NEGRE','Elsa ','MCF',NULL,NULL,'elsa.negre[at]dauphine.fr');
INSERT INTO Enseignant (Departement_ID,Nom,Prenom,Grade,Telephone,Fax,Email) VALUES(1,'MURAT','Cecile ','MCF',NULL,NULL,'cecile.murat[at]dauphine.fr');

INSERT INTO Salle VALUES('B','020','15');
INSERT INTO Salle VALUES('B','022','15');
INSERT INTO Salle VALUES('A','301','45');
INSERT INTO Salle VALUES('C','Amphi 8','500');
INSERT INTO Salle VALUES('C','Amphi 4','200');


INSERT INTO Cours VALUES (1,1,'Bases de Données Relationnelles','Niveau Licence (L3) : Modélisation E/A et UML, Modèle relationnel, Algèbre Relationnelle, Calcul relationel, SQL, dépendances fonctionnelles et formes normales');
INSERT INTO Cours VALUES (2,1,'Langage C++','Niveau Master 1');
INSERT INTO Cours VALUES (3,1,'Mise à Niveau Bases de Données','Niveau Master 2 - Programme Licence et Master 1 en Bases de Données');

INSERT INTO Reservation(Batiment,Numero_Salle,Cours_ID,Departement_ID,Enseignant_ID,Date_Resa,Heure_Debut,Heure_Fin,Nombre_Heures) VALUES ('B','022',1,1,(SELECT Enseignant_id FROM Enseignant WHERE Nom='MANOUVRIER'),'2016/10/15','08:30:00','11:45:00','3');
INSERT INTO Reservation(Batiment,Numero_Salle,Cours_ID,Departement_ID,Enseignant_ID,Date_Resa,Heure_Debut,Heure_Fin,Nombre_Heures) VALUES ('B','022',1,1,2,'2016/11/04','08:30:00','11:45:00','3');
INSERT INTO Reservation(Batiment,Numero_Salle,Cours_ID,Departement_ID,Enseignant_ID,Date_Resa,Heure_Debut,Heure_Fin,Nombre_Heures) VALUES ('B','022',1,1,2,DEFAULT,'08:30:00','11:45:00','3');
INSERT INTO Reservation(Batiment,Numero_Salle,Cours_ID,Departement_ID,Enseignant_ID,Date_Resa,Heure_Debut,Heure_Fin,Nombre_Heures) VALUES ('B','020',1,1,1,DEFAULT,'08:30:00','11:45:00','3');


