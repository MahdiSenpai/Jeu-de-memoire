/**
 * Fichier : carte.h
 * But : entête du module Carte immplémentant le Type Abstrait de Données (TAD) Carte
 * Date de dernière modification : 09/01/2023     
 * Auteurs : El Mahdi Dirchaoui / Laborde Romain
    Nous certifions être les auteurs de ce code source et attestons ne pas avoir utilisé d'extraits de code
    provenant d'internet. Ce code source s'appuie uniquement sur les notions de programmation vues dans le
    cadre du module R1.01 - Initiation au développement.
 */ 

#ifndef CARTE_H
#define CARTE_H

#include <iostream>
using namespace std;

struct Carte 
{
	string face; // La valeur de la face de la carte
	string dos; // La valeur du dos de la carte
};
/* -------------------------------------------------------------------------------------------
   Getters et setters (accès et Modification individuelle) de chaque chmap de l'enregistrement 
   -------------------------------------------------------------------------------------------*/ 
string getFace (const Carte& pCarte);
string getDos (const Carte& pCarte);
/* But : retourne respectivement la face et le dos du paramètre pCarte */

void setFace (Carte& pCarte, string pFace);
void setDos (Carte& pCarte, string pDos);
/* But : Affecte la valeur du second paramètre au champ correspondant du paramètre pCarte */

/* --------------
   Initialisation 
   --------------*/
void init (Carte& pCarte, string pFace, string pDos);
/* But : initialise les champs du paramètre pCarte avec les paramètres qui suivent */
void init (Carte& pCarte, const Carte& pModele);
/* But : initialise tous les champs du paramètre pCarte à partir des champs du paramètre pModele */

/* --------------
   Modificateur 
   --------------*/
void echanger2Cartes(Carte& pCarte1, Carte& pCarte2);
/* But : echange les valeurs des cartes de pCarte1 avec celles de pCarte2 */

/* ------------------
   Entrées / Sorties 
   ------------------*/
void afficherDosCarte(const Carte& pCarte);
/* But : affiche à l'écran la valeur du dos de pCarte */
void afficherFaceCarte(const Carte& pCarte);
/* But : affiche à l'écran la valeur de la face de pCarte */

#endif