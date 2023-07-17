/**
 * Fichier : carte.cpp
 * But : corps du module Carte
 * Date de dernière modification : 09/01/2023     
 * Auteurs : El Mahdi Dirchaoui / Laborde Romain
    Nous certifions être les auteurs de ce code source et attestons ne pas avoir utilisé d'extraits de code
    provenant d'internet. Ce code source s'appuie uniquement sur les notions de programmation vues dans le
    cadre du module R1.01 - Initiation au développement.
 */ 

#include "carte.h"

/* -------------------------------------------------------------------------------------------
   Getters et setters (accès et Modification individuelle) de chaque chmap de l'enregistrement 
   -------------------------------------------------------------------------------------------*/ 
string getFace (const Carte& pCarte)
{
    return pCarte.face;
}
string getDos (const Carte& pCarte)
{
    return pCarte.dos;
}

void setFace (Carte& pCarte, string pFace)
{
    pCarte.face = pFace;
}
void setDos (Carte& pCarte, string pDos)
{
    pCarte.dos = pDos;
}

/* --------------
   Initialisation 
   --------------*/
void init (Carte& pCarte, string pFace, string pDos)
{
    setFace(pCarte, pFace);
    setDos(pCarte, pDos);
}
void init (Carte& pCarte, const Carte& pModele)
{
    setFace(pCarte, getFace(pModele));
    setDos(pCarte, getDos(pModele));
}

/* --------------
   Modificateur 
   --------------*/
void echanger2Cartes(Carte& pCarte1, Carte& pCarte2)
{
    Carte carteAuxiliaire;
    init(carteAuxiliaire, pCarte1);
    init(pCarte1, pCarte2);
    init(pCarte2, carteAuxiliaire);
}

/* ------------------
   Entrées / Sorties 
   ------------------*/
void afficherDosCarte(const Carte& pCarte)
{
    cout << getDos(pCarte);
}

void afficherFaceCarte(const Carte& pCarte)
{
    cout << getFace(pCarte);
}
