/*
    Programme : JEU DU MEMORY
    But : Mémory est un jeu à un joueur nécessitant un jeu de cartes et une grille (ou plateau) contenant un nombre pair de cases 
    (exemple : 4 lignes et 4 colonnes, 6 lignes et 6 colonnes, 4 lignes et 6 colonnes,...).
    Le jeu de cartes est composé de paires de cartes ‘identiques’.
    En début de jeu, sur chaque case est déposée une carte, le côté de la figure étant caché. 
    Le jeu est composé de plusieurs ‘tours’.
    Lors d’un tour, le joueur retourne 2 cartes, leur côté ‘figure’ est donc visible.
    Si elles sont identiques, le joueur prélève les 2 cartes identiques du plateau et les dépose devant lui (c’est son ‘butin’).
    Si elles sont différentes, le joueur retourne à nouveau les 2 cartes, leur côté ‘figure’ est à nouveau caché. Fin du tour 
    courant. Le joueur est prêt à recommencer un nouveau tour. 
    Le but du Mémory est, pour le joueur, de prélever les paires de cartes du plateau en un nombre le plus petit possible de 
    tours.
    La partie se termine quand le joueur : 
        - A ‘vidé’ le plateau, 
        - Quand il abandonne, 
        - Quand le nombre de tours atteint un nombre limité maximal.
    Date de dernière modification : 09/01/2023     
    Auteurs : El Mahdi Dirchaoui / Laborde Romain
    Nous certifions être les auteurs de ce code source et attestons ne pas avoir utilisé d'extraits de code
    provenant d'internet. Ce code source s'appuie uniquement sur les notions de programmation vues dans le
    cadre du module R1.01 - Initiation au développement.
*/ 


#include "case.h"
#include "procedure.h"
#include "game-tools.h"

enum EtatPartie {abandon, perdu, gagne}; // Les différents états de la partie

struct Partie {
    string difficulte; // Le nom du niveau de difficulte
    unsigned short int nbCartes; // Le nombre de cartes utilisées pour la partie
    unsigned short int nbPaires; // Le nombre de paires à trouver
    unsigned short int nbManches; // Le nombre de manche disponible pour la partie
    unsigned short int nbBonus; // Le nombre de bonus disponible pour la partie
    unsigned short int mancheEnCours; // Le numero de la manche en cours
    unsigned short int nbPairesTrouvees; // Le nombre de paires trouvées par l'utilisateur
    bool mancheAvecBonus; // Indique si l'utilisateur dispose de l'option bonus pour la manche.
    EtatPartie etat; // indique l'état de la partie soit abandon soit perdu ou gagné
    
};

struct Choix {
    string init; // La valeur du choix de l'utilisateur pour l'initialisation
    string manche; // La valeur du choix de l'utilisateur pendant la manche
    string rejouer; // La valeur du choix de l'utilisateur pour rejouer une partie
    unsigned short int carte1; // La coordonnee de la première carte à retourner saisi par l'utilisateur
    unsigned short int carte2; // La coordonnee de la deuxième carte à retourner saisi par l'utilisateur
};

struct MessageJeu {
    string init; // Le message affiché apres l'initialisation de la partie
    string erreur; // Le massage affiché en cas d'erreur de saisi d'un choix
    string erreurCoord; // Le message affiché en cas d'erreur de saisi d'une coordonnee de case
    string arret; // Le message affiché avant l'arret du jeu
    string gagne; // Le message affiché lorsque la partie est gagné
    string perdu; // Le message affiché lorsque la partie est perdu par depassement du nombre de manche
    string abandon; // Le message affiché lorsque la partie est perdu par abandon
};

/******************************************
        Déclaration des fonctions                     
******************************************/
Partie paramtrerPartie(string difficulte);
/* But : retourne une partie paramétrée en fonction de la valeur de difficulte, 
         les valeurs possibles sont : "f" ou "F", "n" ou "N", "e" ou "E" */


int main(void)
{   
    /******************************************
                    VARIABLES                     
    ******************************************/
    const unsigned short int NB_LIGNE_INFO_PRINCIPE = 13; // Le nombre de ligne du tableau de texteInfoPrincipe
    string texteInfoPrincipe[NB_LIGNE_INFO_PRINCIPE] = {
        "_________ JEU DU MEMORY___________", ">> Principe du jeu :",
        "Une partie se deroule en plusieurs manches.", "En fonction du niveau de difficulte choisi vous disposez d un",
        "nombre maximal de manches et un nombre de paires a trouver.", "Pour jouer vous saisissez les coordonnees de la premiere carte a retourner,",
        "puis les coordonnees de la deuxieme si les deux cartes correspondent", "elles sont ajoutees a votre butin.",
        " > Si vous depassez le nombre de manche maximal, vous perdez.", " > Si vous trouvez toutes les paires, vous gagnez.",
        " > Vous avez droit a plusieurs bonus pendant la partie, un bonus", "retourne un court instant les cartes associees aux cartes choisies a la manche precedente.",
        "A tout moment vous avez la possibilite d abandonner la partie."
    }; // Le tableau contenant les lignes de texte sur le principe du jeu

    const unsigned short int NB_LIGNE_INFO_IMPORTANT = 5; // Le nombre de ligne du tableau de texteInfoImportant
    string texteInfoImportant[NB_LIGNE_INFO_IMPORTANT] = {
        ">> Important :", "Pour chaque saisie qui vous sera demandee,",
        "veuillez saisir le caractere present entre [ ]", "ou les coordonnees ligne colonne de votre carte.",
        " > Exemple : [ a ] - abandonner la partie."
    }; // Le tableau contenant les lignes de texte sur les informations importantes

    const unsigned short int NB_LIGNE_INFO_INIT = 13; // Le nombre de ligne du tableau de texteInfoInit
    string texteInfoInit[NB_LIGNE_INFO_INIT] = {
        ">> Initialisation de la partie :", "Niveau facile:",
        " > 4 paires a trouver", " > 8 manches",
        " > 2 bonus", "Niveau normal:",
        " > 6 paires a trouver", " > 11 manches",
        " > 3 bonus", "Niveau expert:",
        " > 8 paires a trouver", " > 13 manches",
        " > 4 bonus"
    }; // Le tableau contenant les lignes de texte sur les différents mode de difficulté disponible pour initialiser la partie

    const unsigned short int NB_LIGNE_CHOIX_INIT = 4; // Le nombre de ligne du tableau texteChoixInit
    string texteChoixInit[NB_LIGNE_CHOIX_INIT] = {
        "Vos choix : ", "  [ f ] - niveau facile", "  [ n ] - niveau normal", "  [ e ] - niveau expert"
    }; // Le tableau contenant les lignes de texte sur les différents choix proposés à l'utilisateur pour l'initialisation de la partie

    const unsigned short int NB_LIGNE_CHOIX_MANCHE = 4; // Le nombre de ligne du tableau texteChoixManche
    const unsigned short int NB_LIGNE_CHOIX_MANCHE_SANS_BONUS = 3; // Le nombre de ligne du tableau texteChoixManche sans le bonus
    string texteChoixManche[NB_LIGNE_CHOIX_MANCHE] = {
        "Vos choix : ", "  [ a ] - abandonner la partie", 
        "  [ s ] - saisir les coordonnees des cartes a retourner", "  [ u ] - utiliser un bonus"
    }; // Le tableau contenant les lignes du texte sur les différents choix proposés à l'utilisateur pendant une manche

    const unsigned short int NB_LIGNE_CHOIX_REJOUER = 3; // Le nombre de ligne du tableau texteChoixRejouer
    string texteChoixRejouer[NB_LIGNE_CHOIX_REJOUER] = {
        "Vos choix : ", "  [ o ] - oui, car je suis joueur", "  [ n ] - non, j'ai piscine"
    }; // Le tableau contenant les lignes du texte sur les différents choix proposés à l'utilisateur en fin de partie
    
    const unsigned short int NB_CHOIX_INIT_PARTIE = 6; // Le nombre de choix possible pour l'initialisation de la partie
    string choixInitPartie[NB_CHOIX_INIT_PARTIE] = {"f", "F", "n", "N", "e", "E"}; // Les différentes valeurs attendues pour l'initialisation de la partie

    const unsigned short int NB_CHOIX_MANCHE = 6; // Le nombre de choix possible pendant la manche
    const unsigned short int NB_CHOIX_MANCHE_SANS_BONUS = 4; // Le nombre de choix possible sans le bonus pendant la manche
    string choixManche[NB_CHOIX_MANCHE] = {"a", "A", "s", "S", "u", "U"}; // Les différentes valeurs attendues pendant la manche

    const unsigned short int NB_CHOIX_REJOUER = 4; // Le nombre de choix possible pour rejouer la partie
    string choixRejouer[NB_CHOIX_REJOUER] = {"o", "O", "n", "N"}; // Les différentes valeurs attendues pour rejouer la partie

    MessageJeu messageJeu = {
        "Lancement de la partie niveau ",
        "Saisie incorrecte ! Veuillez saisir le caractere entre [ ]",
        "Saisie incorrecte ! Veuillez saisir des coordonnees ligne colonne qui correspondent a une carte",
        "Le jeu va s'arreter, Merci a bientot !",
        "Bien joue ! Vous avez gagne en trouvant toutes les paires.\nEst-ce que vous etes si bon que ca..! Rejouer une partie ? ",
        "Dommage ! Vous avez perdu.. Vous avez atteint le nombre maximal de manche. \nMoi je dis ca vaut le coup de retenter votre chance. \nAlors partant pour une autre partie ?",
        "Vous abandonnez deja ..! Une derniere partie ?"
    }; // Les différents messages du jeu

    const unsigned short int NB_CARTE = 16; // Le nombre de carte du jeu
    Carte jeuDeCarte[NB_CARTE] = {
        {"|A|", "|X|"}, {"|A|", "|X|"}, {"|B|", "|X|"}, {"|B|", "|X|"},
        {"|C|", "|X|"}, {"|C|", "|X|"}, {"|D|", "|X|"}, {"|D|", "|X|"},
        {"|E|", "|X|"}, {"|E|", "|X|"}, {"|F|", "|X|"}, {"|F|", "|X|"},
        {"|G|", "|X|"}, {"|G|", "|X|"}, {"|H|", "|X|"}, {"|H|", "|X|"}
    }; // Les différentes valeurs du jeu de cartes

    Carte butin[NB_CARTE]; // Le butin de l'utilisateur

    Case tableJeu[NB_CARTE] = {
        {libre, 11, {"   ", "   "}}, {libre, 12, {"   ", "   "}}, {libre, 13, {"   ", "   "}}, {libre, 14, {"   ", "   "}},
        {libre, 21, {"   ", "   "}}, {libre, 22, {"   ", "   "}}, {libre, 23, {"   ", "   "}}, {libre, 24, {"   ", "   "}},
        {libre, 31, {"   ", "   "}}, {libre, 32, {"   ", "   "}}, {libre, 33, {"   ", "   "}}, {libre, 34, {"   ", "   "}},
        {libre, 41, {"   ", "   "}}, {libre, 42, {"   ", "   "}}, {libre, 43, {"   ", "   "}}, {libre, 44, {"   ", "   "}}
    }; // La table de jeu avec ces différentes case, leur etat, leur coordonnee, valeur de carte vide

    Choix choixSaisi; // Regroupe les différents choix de l'utilisateur
    Partie partieJoueur; // Regroupe les différents paramètres de configuration de la partie de l'utilisateur
    unsigned short int indexAleatoire; // Une valeur aléatoire utilisée pour mélanger les cartes de jeu
    unsigned short int posCarte1; // La valeur de la position de la première carte choisie par l'utilisateur
    unsigned short int posCarte2; // La valeur de la position de la deuxième carte choisie par l'utilisateur

    bool trouve; // indicateur de reussite / échec des différentes recherches présentes dans le jeu.

    /******************************************
                    TRAITEMENTS                     
    ******************************************/
    
    /********** INITIALISER LA PARTIE ********/

    /* texteInfoPrincipe, NB_LIGNE_INFO_PRINCIPE, texteInfoImportant, NB_LIGNE_INFO_IMPORTANT
       texteInfoInit, NB_LIGNE_INFO_INIT >> Afficher principe, infos importantes et mode d'initialisation >> (ecran) */
    afficherTexteJeuMultiligne(texteInfoPrincipe, NB_LIGNE_INFO_PRINCIPE);
    pause(6);
    effacer();
    afficherTexteJeuMultiligne(texteInfoImportant, NB_LIGNE_INFO_IMPORTANT);
    pause(4);
    effacer();
    afficherTexteJeuMultiligne(texteInfoInit, NB_LIGNE_INFO_INIT);

    /* texteChoixInit, NB_LIGNE_CHOIX_INIT, choixInitPartie, NB_CHOIX_INIT_PARTIE,
       messageJeu.erreur >> Saisir et vérifier choix initialisation partie >> choixSaisi.init */
    while (true)
    {
        // texteChoixInit, NB_LIGNE_CHOIX_INIT >> afficherTexteJeuMultiligne >> (ecran)
        afficherTexteJeuMultiligne(texteChoixInit, NB_LIGNE_CHOIX_INIT);

        // (clavier) >> saisirChoixJeu >> choixSaisi.init
        saisirChoixJeu(choixSaisi.init);

        // choixInitPartie, NB_CHOIX_INIT_PARTIE, choixSaisi.init >> verifChaineCarac >> trouve
        verifChaineCarac(choixInitPartie, NB_CHOIX_INIT_PARTIE, choixSaisi.init, trouve);
        
        if (trouve)
        {
            break;
        }

        // messageJeu.erreur >> afficherTexteJeu >> (ecran)
        afficherTexteJeu(messageJeu.erreur);
    }

    // choixSaisi.init >> Initialiser paramétres partie >> partieJoueur
    partieJoueur = paramtrerPartie(choixSaisi.init);

    effacer();

    // messageJeu.init + partieJoueur.difficulte >> afficherTexteJeu >> (ecran)
    afficherTexteJeu(messageJeu.init + partieJoueur.difficulte);
       
    pause(2);
    effacer();
    
    /********** JOUER LA PARTIE *************/
    
    while (true)
    {   
        // Initialiser table jeu et butin
        // partieJoueur.nbCartes, jeuDeCarte >> Mélanger jeu de cartes >> jeuDeCarte
        for (unsigned short int i = 0; i < partieJoueur.nbCartes; i++)
        {
            indexAleatoire = static_cast<unsigned short int>(rand() % partieJoueur.nbCartes + 0);
            echanger2Cartes(jeuDeCarte[i], jeuDeCarte[indexAleatoire]);
        }
        
        // partieJoueur.nbCartes, tableJeu, jeuDeCarte >> Attibuer cartes sur table de jeu >> tableJeu
        for (unsigned short int i = 0; i < partieJoueur.nbCartes; i++)
        {
            setEtat(tableJeu[i], occupe);
            setCarte(tableJeu[i], jeuDeCarte[i]);
        }

        // partieJoueur.nbCartes, butin >> Initialiser le butin >> butin
        for (unsigned short int i = 0; i < partieJoueur.nbCartes; i++)
        {
            init(butin[i], vide);
        }

        // Jouer les manches
        while (true)
        {
            // Afficher infos manches, table de jeu, butin.
            // partieJoueur >> Afficher infos manches >> (ecran)
            cout << "- Manche " << partieJoueur.mancheEnCours;
            cout << " - Bonus " << partieJoueur.nbBonus;
            cout <<" - Paires a trouver " << (partieJoueur.nbPaires - partieJoueur.nbPairesTrouvees);
            cout << " - Manches restantes " << (partieJoueur.nbManches - partieJoueur.mancheEnCours) << endl;
            
            // tableJeu, partieJoueur.nbCartes >> Afficher table de jeu >> (ecran)
            cout << "   1  2  3  4 ";
            for (unsigned short int i = 0; i < partieJoueur.nbCartes; i++)
            {
                if (i%4 == 0) 
                {
                    cout << endl << ((i/4)+1) << " ";
                }

                afficherDosCarte(getCarte(tableJeu[i]));
            }
            cout << endl << endl;
            
            // butin, partieJoueur.nbPairesTrouvees >> Afficher butin >> (ecran)
            cout << "butin : ";
            for (unsigned short int i = 0; i < (partieJoueur.nbPairesTrouvees * 2); i++)
            {
                if (i%4 == 0)
                {
                    cout << endl;
                }
                afficherFaceCarte(butin[i]);
            }
            cout << endl;

            // Traiter etat de la manche, Saisir et vérifier choix manche
            if (partieJoueur.mancheAvecBonus && partieJoueur.nbBonus != 0)
            {
                /* texteChoixManche, NB_LIGNE_CHOIX_MANCHE, choixManche, NB_CHOIX_MANCHE,
                   messageJeu.erreur >> Saisir et vérifier choix manche >> choixSaisi.manche */
                while (true)
                {
                    // texteChoixManche, NB_LIGNE_CHOIX_MANCHE >> afficherTexteJeuMultiligne >> (ecran)
                    afficherTexteJeuMultiligne(texteChoixManche, NB_LIGNE_CHOIX_MANCHE);

                    // (clavier) >> saisirChoixJeu >> choixSaisi.manche
                    saisirChoixJeu(choixSaisi.manche);

                    // choixManche, NB_CHOIX_MANCHE, choixSaisi.manche >> verifChaineCarac >> trouve
                    verifChaineCarac(choixManche, NB_CHOIX_MANCHE, choixSaisi.manche, trouve);
                    
                    if (trouve)
                    {
                        break;
                    }

                    // messageJeu.erreur >> afficherTexteJeu >> (ecran)
                    afficherTexteJeu(messageJeu.erreur);
                }
            }
            else 
            {
                /* texteChoixManche, NB_LIGNE_CHOIX_MANCHE_SANS_BONUS, choixManche, NB_CHOIX_MANCHE_SANS_BONUS,
                   messageJeu.erreur >> Saisir et vérifier choix manche sans bonus >> choixSaisi.manche */
                while (true)
                {
                    // texteChoixManche, NB_LIGNE_CHOIX_MANCHE >> afficherTexteJeuMultiligne >> (ecran)
                    afficherTexteJeuMultiligne(texteChoixManche, NB_LIGNE_CHOIX_MANCHE_SANS_BONUS);

                    // (clavier) >> saisirChoixJeu >> choixSaisi.manche
                    saisirChoixJeu(choixSaisi.manche);

                    // choixManche, NB_CHOIX_MANCHE_SANS_BONUS, choixSaisi.manche >> verifChaineCarac >> trouve
                    verifChaineCarac(choixManche, NB_CHOIX_MANCHE_SANS_BONUS, choixSaisi.manche, trouve);
                    
                    if (trouve)
                    {
                        break;
                    }

                    // messageJeu.erreur >> afficherTexteJeu >> (ecran)
                    afficherTexteJeu(messageJeu.erreur);
                }
            }
            
            // Traiter choix de la manche
            if (choixSaisi.manche == "a" || choixSaisi.manche == "A")
            {
                partieJoueur.etat = abandon;
                break;
            }
            else if (choixSaisi.manche == "s" || choixSaisi.manche == "S")
            {
                /* tableJeu, partieJoueur.nbCartes, messageJeu.erreurCoord 
                   >> Saisir et vérifier coordonnée carte1 >> choixSaisi.carte1, posCarte1 */
                while (true)
                {
                    // (clavier) >> Saisir coordonnée carte 1 >> choixSaisi.carte1
                    cout << "Saisir les coordonnees ligne colonne carte 1 : ";
                    cin >> choixSaisi.carte1;

                    // tableJeu, partieJoueur.nbCartes, choixSaisi.carte1 >> rechercherCoordDansTableauCase >> trouve, [posCarte1] 
                    rechercherCoordDansTableauCase(tableJeu, partieJoueur.nbCartes, choixSaisi.carte1, posCarte1, trouve);

                    if (trouve)
                    {
                        break;
                    }

                    // messageJeu.erreur >> afficherTexteJeu >> (ecran)
                    afficherTexteJeu(messageJeu.erreurCoord);
                }

                /* tableJeu, partieJoueur.nbCartes, messageJeu.erreurCoord, choixSaisi.carte1 
                   >> Saisir et vérifier coordonnée carte2 >> choixSaisi.carte2, posCarte2 */
                while (true)
                {
                    // (clavier) >> Saisir coordonnée carte 2 >> choixSaisi.carte2
                    cout << "Saisir les coordonnees ligne colonne carte 2 : ";
                    cin >> choixSaisi.carte2;

                    // tableJeu, partieJoueur.nbCartes, choixSaisi.carte2 >> rechercherCoordDansTableauCase >> trouve, [posCarte2] 
                    rechercherCoordDansTableauCase(tableJeu, partieJoueur.nbCartes, choixSaisi.carte2, posCarte2, trouve);
                    
                    if (trouve && choixSaisi.carte2 != choixSaisi.carte1)
                    {
                        break;
                    }

                    // messageJeu.erreur >> afficherTexteJeu >> (ecran)
                    afficherTexteJeu(messageJeu.erreurCoord);
                }
            }
            else if (choixSaisi.manche == "u" || choixSaisi.manche == "U")
            {   
                // Rechercher les cartes associées et mettre à jour nombre bonus
                
                /* tableJeu, partieJoueur.nbCartes, choixSaisi.carte1, posCarte1 
                   >> Rechercher la case ayant la même carte que la première carte choisie >> 
                   [ posCarte1 ], trouve */

                // Initialiser la recherche
                unsigned short int posCourante = 0;
                bool trouve = false;

                // Effectuer la recherche
                while (posCourante < partieJoueur.nbCartes && !trouve)
                {
                    if (contientLaMemeCarte(tableJeu[posCourante], tableJeu[posCarte1]) && getCoordonnee(tableJeu[posCourante]) != choixSaisi.carte1)
                    {
                        trouve = true;
                        posCarte1 = posCourante;
                    }
                        
                    posCourante ++;
                }
                
                /* posCarte1, tableJeu, poartieJoueur.nbCartes, choixSaisi.carte2, posCarte2 
                   >> Rechercher la case ayant la même carte que la deuxième carte choisie >>
                   trouve, [ posCarte2 ] */
                   
                // Initialiser la recherche
                posCourante = 0;
                trouve = false;

                // Effectuer la recherche
                while (posCourante < partieJoueur.nbCartes && !trouve)
                {
                    if (contientLaMemeCarte(tableJeu[posCourante], tableJeu[posCarte2]) && getCoordonnee(tableJeu[posCourante]) != choixSaisi.carte2)
                    {
                        trouve = true;
                        posCarte2 = posCourante;
                    }
                            
                    posCourante ++;
                }
                
                partieJoueur.nbBonus --;
            }
            
            // posCarte1, posCarte2, partieJoueur.nbCartes, tableJeu >> Afficher table de jeu avec cartes retournées >> (ecran)
            cout << "   1  2  3  4 ";
            for (unsigned short int i = 0; i < partieJoueur.nbCartes; i++)
            {
                if (i%4 == 0) 
                {
                    cout << endl << ((i/4)+1) << " "; // Affiche le numéro de la ligne de la table de jeu
                }

                posCarte1 == i || posCarte2 == i ? afficherFaceCarte(getCarte(tableJeu[i])) : afficherDosCarte(getCarte(tableJeu[i]));
            }
            cout << endl;

            pause(1);
            effacer();

            /* tableJeu, butin, partieJoueur.mancheAvecBonus, partieJoueur.mancheEnCours,
               partieJoueur.nbPairesTrouvees, posCarte1, posCarte2, choixSaisi.manche
               >> Vérifier cartes et mettre à jour manche, table jeu et butin >> 
               partieJoueur.mancheAvecBonus, partieJoueur.mancheEncours, [partieJoueur.nbPairesTrouvees], [tableJeu], [butin], */
            partieJoueur.mancheEnCours ++;

            if (contientLaMemeCarte(tableJeu[posCarte1], tableJeu[posCarte2]))
            {
                echanger2Cartes(tableJeu[posCarte1].carte, butin[partieJoueur.nbPairesTrouvees * 2]);
                echanger2Cartes(tableJeu[posCarte2].carte, butin[(partieJoueur.nbPairesTrouvees * 2) + 1]);
                setEtat(tableJeu[posCarte1], libre);
                setEtat(tableJeu[posCarte2], libre);
                partieJoueur.nbPairesTrouvees ++ ;
                partieJoueur.mancheAvecBonus = false;
            }
            else 
            {
                if ((choixSaisi.manche == "s" || choixSaisi.manche == "S"))
                {
                    partieJoueur.mancheAvecBonus = true;
                }
                else 
                {
                    partieJoueur.mancheAvecBonus = false;
                } 
            }
            
            if (partieJoueur.nbPairesTrouvees == partieJoueur.nbPaires)
            {
                partieJoueur.etat = gagne;
                break;
            }

            if (partieJoueur.mancheEnCours > partieJoueur.nbManches)
            {
                partieJoueur.etat = perdu;
                break;
            } 
        }

        effacer();

        // partieJoueur.etat >> Afficher informations fin partie >> (ecran)
        afficherTexteJeu("__________ FIN DE PARTIE _________");
        if (partieJoueur.etat == gagne)
        {
            afficherTexteJeu(messageJeu.gagne);
        }
        else if (partieJoueur.etat == perdu)
        {
            afficherTexteJeu(messageJeu.perdu);
        }
        else if (partieJoueur.etat == abandon)
        {
            afficherTexteJeu(messageJeu.abandon);
        }
        

        /* choixRejouer, NB_CHOIX_REJOUER, texteChoixRejouer, NB_LIGNE_CHOIX_REJOUER, messageJeu.erreur 
           >> Saisir et vérifier choix rejouer partie >> choixSaisi.rejouer */
        while (true)
        {
            // texteChoixRejouer, NB_LIGNE_CHOIX_REJOUER >> afficherTexteJeuMultiligne >> (ecran)
            afficherTexteJeuMultiligne(texteChoixRejouer, NB_LIGNE_CHOIX_REJOUER);

            // (clavier) >> saisirChoixJeu >> choixInitSaisi
            saisirChoixJeu(choixSaisi.rejouer);
            
            // choixRejouer, NB_CHOIX_REJOUER, choixSaisi.rejouer >> verifChaineCarac >> trouve
            verifChaineCarac(choixRejouer, NB_CHOIX_REJOUER, choixSaisi.rejouer, trouve);
            
            if (trouve)
            {
                break;
            }

            // messageJeu.erreur >> afficherTexteJeu >> (ecran)
            afficherTexteJeu(messageJeu.erreur);
        }

        effacer(); 

        if (choixSaisi.rejouer == "n" || choixSaisi.rejouer == "N")
        {
            break;
        }

        // partieJoueur, choixSaisi.init >> Reinitialiser paramètres partie >> partieJoueur
        partieJoueur = paramtrerPartie(choixSaisi.init);
    }
    
    effacer();
    
    /********** ANNONCER FIN DU JEU ***************/
    afficherTexteJeu(messageJeu.arret);
    
    return 0;
}

/******************************************
        Définition des fonctions                    
******************************************/
Partie paramtrerPartie(string difficulte)
{
    Partie paramPartie;
    Partie partieFacile = {"facile", 8, 4, 8, 2, 1, 0, false, perdu}; // Les paramètres de configuration d'une partie en mode facile
    Partie partieNormal = {"normal", 12, 6, 11, 3, 1, 0, false, perdu}; // Les paramètres de configuration d'une partie en mode normal
    Partie partieExpert = {"expert", 16, 8, 13, 4, 1, 0, false, perdu}; // Les paramètres de configuration d'une partie en mode expert

    if (difficulte == "f" || difficulte == "F")
    {
        paramPartie = partieFacile;
    }
    else if (difficulte == "n" || difficulte == "N")
    {
        paramPartie = partieNormal;
    }
    else if (difficulte == "e" || difficulte == "E")
    {
        paramPartie = partieExpert;
    }

    return paramPartie;
}
