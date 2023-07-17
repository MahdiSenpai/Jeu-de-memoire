/**
 * Fichier : procedure.h
 * But : contient les déclarations des procédures
 * Date de dernière modification : 09/01/2023     
 * Auteurs : El Mahdi Dirchaoui / Laborde Romain
    Nous certifions être les auteurs de ce code source et attestons ne pas avoir utilisé d'extraits de code
    provenant d'internet. Ce code source s'appuie uniquement sur les notions de programmation vues dans le
    cadre du module R1.01 - Initiation au développement.
 */

#ifndef PROCEDURE_H
#define PROCEDURE_H

#include<iostream>
#include "case.h"
using namespace std;

void verifChaineCarac(const string tableauChaineCarac[], unsigned short int nbChaineCarac, string ChaineAComparer, bool& valTrouvee);
/* But : verifie si chaineAComparer correspond à une occurence de tableauChaineCarac, d'une taille de nbChaineCarac.
         et affecte le résultat la recherche à valTrouvee */

void rechercherCoordDansTableauCase(const Case tableauCase[], unsigned short int nbCases, unsigned short int val, unsigned short int& pos, bool& valTrouvee);
/* But : recherche si val correspond à une coordonée de case de tableauCase et affecte sa position à pos si trouvée.
         et le résultat de la recherche à valTrouvee */

void afficherTexteJeuMultiligne(const string texteAAfficher[], unsigned short int nbLigne);
/* But : afficher les chaines de caractère avec retour à la ligne de textesAAfficher, d'une taille nbLigne. */ 

void afficherTexteJeu(string texteAAfficher);
/* But : afficher la chaine de caractère texteAAfficher avec retour à la ligne. */

void saisirChoixJeu(string& choixSaisi);
/* But : afficher une message invitant l’utilisateur à saisir son choix et affecte le choix à choixSaisi */

#endif

