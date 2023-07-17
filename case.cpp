/**
 * Fichier : case.cpp
 * But : corps du module Case
 * Date de dernière modification : 09/01/2023     
 * Auteurs : El Mahdi Dirchaoui / Laborde Romain
    Nous certifions être les auteurs de ce code source et attestons ne pas avoir utilisé d'extraits de code
    provenant d'internet. Ce code source s'appuie uniquement sur les notions de programmation vues dans le
    cadre du module R1.01 - Initiation au développement.
 */ 

#include "case.h"

/* -------------------------------------------------------------------------------------------
   Getters et setters (accès et Modification individuelle) de chaque chmap de l'enregistrement 
   -------------------------------------------------------------------------------------------*/ 
Etat getEtat(const Case& pCase)
{
    return (pCase.etat == 0 ? libre : occupe);   
}

unsigned short int getCoordonnee(const Case& pCase)
{
    return pCase.coordonnee;
}

Carte getCarte (const Case& pCase)
{
    return pCase.carte;
}

void setEtat(Case& pCase, Etat pEtat)
{
    pCase.etat = pEtat;
}

void setCoordonnee(Case& pCase, unsigned short int pCoordonnee)
{
    pCase.coordonnee = pCoordonnee;
}

void setCarte(Case& pCase, Carte pCarte)
{
    pCase.carte = pCarte;
}

/* --------------
   Initialisation 
   --------------*/
void init(Case& pCase, Etat pEtat, unsigned short int pCoordonnee, Carte pCarte)
{
    setEtat(pCase, pEtat);
    setCoordonnee(pCase, pCoordonnee);
    setCarte(pCase, pCarte);
}

void init(Case& pCase, const Case& pModele)
{
    setEtat(pCase, getEtat(pModele));
    setCoordonnee(pCase, getCoordonnee(pModele));
    setCarte(pCase, pModele.carte);
}

/* ------------------
   Comparateur 
   ------------------*/
bool contientLaMemeCarte(const Case& pCase1, const Case& pCase2)
{
    return (getFace(getCarte(pCase1)) == getFace(getCarte(pCase2)) ? true : false);   
}