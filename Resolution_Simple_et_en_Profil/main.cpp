#include "gsm_final.hpp" // Inclure le fichier d'en-tête contenant les déclarations de classe
#include <iostream> // Pour les entrées/sorties
#include <cstdlib> // Pour la fonction system()

using namespace std;

int main () {
    string rep; // Variable pour stocker la réponse de l'utilisateur
    cout << "\nBIENVENUE\n\nCETTE PROGRAMME EST LA DEUXIEME PARTIE  DU PROGRAMME DESTINE A LA RESOLUTION D'UNE MATRICE CREUSE SIMTETRIE DEFINIE PROSITIF\n" << endl;
    cout << "\nAvez-vous déjà lancé la première programme ? (Oui/Non) : ";
    cin >> rep; // Demander à l'utilisateur s'il a déjà lancé le premier programme

    // Vérifier si l'utilisateur a déjà lancé le premier programme
    if(rep != "Oui"){
        cout << "\nVeuillez le faire s'il vous plaît ! Merci :-)\n" << endl;
        // Instructions pour exécuter le premier programme s'il n'a pas été lancé
        //system("cd ..");
        //system("cd Cuthil");
        //system("g++ -std=c++11 *.cpp -o Programme");
        //system("./Programme.exe");
        return 0; // Sortir du programme
    }

    cout << "\n----------------CHARGEMENT DES DONNÉES----------------\n" << endl;
    Factorisation fact("./../Cuthil/new_data.txt"); // Créer un objet Factorisation avec le fichier de données spécifié
    fact.affichage_de_la_Matrice(); // Afficher la matrice chargée à partir du fichier

    cout << "\n~~~~~~~~PARTIE 1 : Résolution sans optimisation de mémoire~~~~~~~~\n" << endl;

    cout << "\n----------------TRAITEMENT DES DONNÉES----------------" << endl;
    // Exécuter les méthodes pour la factorisation et la résolution sans optimisation de mémoire
    fact.methode_factorisation_1();
    fact.methode_resolution_1();
    cout << "                            ." << endl;
    cout << "                            ." << endl;
    cout << "                            ." << endl;

    cout << "\n--------------------LES RÉSULTATS--------------------\n" << endl;
    // Afficher les résultats de la résolution sans optimisation de mémoire
    fact.afficheMat_L();
    fact.affiche_diag();
    fact.afficheResultat();

    cout << "\n\n#######################################################" << endl;
    cout << "#######################################################" << endl;
    cout << "#######################################################\n\n" << endl;

    cout << "\n\n~~~~~~~~PARTIE 2 : Résolution avec optimisation de mémoire~~~~~~~~\n" << endl;
    cout << "\n----------------TRAITEMENT DES DONNÉES EN PROFIL----------------" << endl;

    // Transformer la matrice en profil et exécuter les méthodes de factorisation et de résolution avec optimisation de mémoire
    fact.rangement_en_profil();
    fact.methode_factorisation_profil_2();
    fact.methode_resolution_profil_2();
    cout << "                               ." << endl;
    cout << "                               ." << endl;
    cout << "                               ." << endl;

    cout << "\n-------------------------LES RÉSULTATS--------------------\n" << endl;
    // Afficher les résultats de la résolution avec optimisation de mémoire
    fact.afficheAP();
    fact.affiche_LP();
    fact.affiche_Pdiag();
    fact.afficheResultatP();
    fact.~Factorisation(); // Appeler le destructeur de l'objet Factorisation

    return 0; // Terminer le programme
}
