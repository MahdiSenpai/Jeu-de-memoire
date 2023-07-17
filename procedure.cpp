/**
 * Fichier : procedure.cpp
 * But : contient les définitions des procédures
 * Date de dernière modification : 09/01/2023     
 * Auteurs : El Mahdi Dirchaoui / Laborde Romain
    Nous certifions être les auteurs de ce code source et attestons ne pas avoir utilisé d'extraits de code
    provenant d'internet. Ce code source s'appuie uniquement sur les notions de programmation vues dans le
    cadre du module R1.01 - Initiation au développement.
 */ 

#include "procedure.h"

void verifChaineCarac(const string tableauChaineCarac[], unsigned short int nbChaineCarac, string ChaineAComparer, bool& valTrouvee)
{
    // Initialiser la recherche
    unsigned short int posCourante = 0;
    valTrouvee = false;

    // Effectuer la recherche
    while (posCourante < nbChaineCarac && !valTrouvee)
    {
        if (tableauChaineCarac[posCourante] == ChaineAComparer)
        {
            valTrouvee = true;
        }
        
        posCourante ++;
    }
}

void rechercherCoordDansTableauCase(const Case tableauCase[], unsigned short int nbCases, unsigned short int val, unsigned short int& pos, bool& valTrouvee)
{   
    // Variables
    unsigned short int milieu;

    // Initialiser la recherche
    // partieJoueur >> Calcul bInf et bSup >> bInf, bSup
    unsigned short int bSup = static_cast<unsigned short int>(nbCases - 1);
    unsigned short int bInf = 0;
    
    valTrouvee = false;

    // choixSaisi, bInf, bSup, tableJeu, partieJoueur.nbCartes >> Effectuer la recherche >> trouve, [pos]
    while (bInf <= bSup)
    {
        // bInf, bSup >> Calcul milieu >> milieu
        milieu = static_cast<unsigned short int>((bSup + bInf)/2);

        if (tableauCase[milieu].etat == 1 && tableauCase[milieu].coordonnee == val)
        {
            valTrouvee = true;
            pos = milieu;
            break;
        }

        // choixSaisi, milieu, tableJeu, partieJoueur.nbCartes, bInf, bSup >> Progresser dans espace recherche >> bSup, bInf
        if (tableauCase[milieu].coordonnee > val)
        {
            bSup = static_cast<unsigned short int>(milieu - 1);
        }
        else 
        {
            bInf = static_cast<unsigned short int>(milieu + 1);
        }
    }
}

void afficherTexteJeuMultiligne(const string texteAAfficher[], unsigned short int nbLigne)
{
    for (unsigned short int i = 0; i < nbLigne; i++)
    {
        cout << texteAAfficher[i] << endl;
    } 
}

void afficherTexteJeu(string texteAAfficher)
{
    cout << texteAAfficher << endl;
}

void saisirChoixJeu(string& choixSaisi)
{
    cout << "Saisir votre choix : ";
    cin >> choixSaisi;
}
