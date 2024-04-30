#include "cuthil.hpp" // Inclut le fichier d'en-tête contenant les déclarations de classe
#include <iostream> // Inclut le fichier d'en-tête pour les entrées/sorties
#include <fstream> // Inclut le fichier d'en-tête pour les opérations de flux de fichiers
#include <cmath> // Inclut le fichier d'en-tête pour les fonctions mathématiques
#include <vector> // Inclut le fichier d'en-tête pour les conteneurs de vecteurs
#include <string> // Inclut le fichier d'en-tête pour les chaînes de caractères

using namespace std;

int main() {
    // Message de bienvenue et description du programme
    cout << "\nBIENVENUE\n\nCETTE PROGRAMME EST LA PREMIERE PARTIE  DU PROGRAMME DESTINE A LA RESOLUTION D'UNE MATRICE CREUSE SIMTETRIE DEFINIE PROSITIF\n" << endl;
    cout << "\nAPPLICATION DE L'ALGORITHME DE CUTHILL-MCKEE A LA MATRICE A\n" << endl;

    // Création de l'objet Excentricite en lisant les données à partir de "data.txt"
    Excentricite calcul("data.txt");

    // Affichage de la dimension de la matrice
    calcul.display_dim();

    // Affichage de la matrice A
    calcul.display_A();

    // Calcul du premier sommet
    calcul.cal_premier_sommet();

    // Application de l'algorithme de Cuthill-McKee pour l'ordre des sommets
    calcul.cuthil();

    // Application de l'algorithme de Cuthill-McKee avec inversion de l'ordre des sommets
    calcul.cuthil_inverse();

    // Configuration de la réponse en fonction de l'algorithme utilisé
    calcul.set_resp();

    // Si l'algorithme a été appliqué avec succès
    if (calcul.get_resp()) {
        // Permutation des sommets de la matrice
        calcul.permutation();
        // Affichage de la matrice A après permutation
        calcul.display_A();
    } else {
        // Permutation des sommets de la matrice avec inversion
        calcul.permutation_avec_inversion();
        // Affichage de la matrice A après permutation avec inversion
        calcul.display_A();
    }

    // Enregistrement de la matrice A réarrangée dans "new_data.txt"
    calcul.enregistrement("new_data.txt");

    // Appel du destructeur pour libérer la mémoire allouée
    calcul.~Excentricite();

    return 0;
}
