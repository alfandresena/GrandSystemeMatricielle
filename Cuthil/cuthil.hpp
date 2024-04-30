#ifndef _CUTHIL // Vérifie si la macro _CUTHIL n'est pas définie
#define _CUTHIL // Définit la macro _CUTHIL si elle n'est pas définie

#include <string> // Inclut le fichier d'en-tête pour les chaînes de caractères
#include <vector> // Inclut le fichier d'en-tête pour les vecteurs
#include <iostream> // Inclut le fichier d'en-tête pour les entrées/sorties

using namespace std;

class Excentricite {
public:
    Excentricite(string filename); // Constructeur : lecture du fichier
    void display_dim(); // Fonction d'affichage de dim
    void display_A(); // Fonction d'affichage de A
    int cal_excentricite(int num, vector<vector<int> >& v); // Calcul de l'excentricité et des voisins
    void cal_premier_sommet(); // Calcul du premier sommet
    void cuthil(); // L'ordre du sommet
    void cuthil_inverse(); // Inversion de l'ordre du sommet
    void permutation(); // Réarrangement de la matrice en utilisant l'ordre du sommet non inversé
    void permutation_avec_inversion(); // Réarrangement de la matrice en utilisant l'ordre du sommet avec inversion
    void enregistrement(string nomFichier); // Sauvegarde le fichier
    void set_resp(); // Définit la réponse
    bool get_resp(); // Obtient la réponse
    ~Excentricite(); // Destructeur de la classe

private:
    int dim; // Dimension
    int *sommet_1; // Sommet sans inversion
    int *sommet_2; // Sommet avec inversion
    float **A; // Matrice A
    float *b; // Le vecteur b
    bool response; // Pour le choix avec inversion ou non
    vector<vector<int> > v_n; // Les voisins de n
    vector<vector<int> > v_s; // Les voisins de s
};

#endif // Fin de la directive conditionnelle #ifndef
