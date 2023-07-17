/**
 * Fichier : case.h
 * But : entête du module Case immplémentant le Type Abstrait de Données (TAD) Case
 * Date de dernière modification : 09/01/2023     
 * Auteurs : El Mahdi Dirchaoui / Laborde Romain
    Nous certifions être les auteurs de ce code source et attestons ne pas avoir utilisé d'extraits de code
    provenant d'internet. Ce code source s'appuie uniquement sur les notions de programmation vues dans le
    cadre du module R1.01 - Initiation au développement.
 */

#ifndef CASE_H
#define CASE_H

#include "carte.h"

enum Etat { libre, occupe }; // Les états possible d'une case

const Carte vide = {"   ", "   "}; // La valeur de la carte d'une case vide

struct Case 
{
	unsigned short int etat; // L'etat de la case soit libre soit occupe
    unsigned short int coordonnee; // La coordonnee de la case
	Carte carte; // La valeur d'une carte
};

/* -------------------------------------------------------------------------------------------
   Getters et setters (accès et Modification individuelle) de chaque chmap de l'enregistrement 
   -------------------------------------------------------------------------------------------*/ 
Etat getEtat (const Case& pCase);
unsigned short int getCoordonnee(const Case& pCase);
Carte getCarte (const Case& pCase);
/* But : retourne respectivement l'etat, la coordonnee et la carte du paramètre pCase */

void setEtat (Case& pCase, Etat pEtat);
void setCoordonnee(Case& pCase, unsigned short int pCoordonnee);
void setCarte (Case& pCase, Carte pCarte);
/* But : Affecte la valeur du second paramètre au champ correspondant du paramètre pCase */

/* --------------
   Initialisation 
   --------------*/
void init (Case& pCase, Etat pEtat, unsigned short int pCoordonnee, Carte pCarte);
/* But : initialise les champs du paramètre pCase avec les paramètres qui suivent */
void init (Case& pCase, const Case& pModele);
/* But : initialise tous les champs du paramètre pCase à partir des champs du paramètre pModele */

/* ------------------
   Comparateur 
   ------------------*/
bool contientLaMemeCarte(const Case& pCase1, const Case& pCase2);
/* But : Retourne vrai si pCase1 possède la même carte que pCase2, sinon faux */

#endif