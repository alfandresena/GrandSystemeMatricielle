Voici le code avec des commentaires ajoutés pour expliquer chaque partie :

```cpp
#ifndef _GSM_FINAL // Vérifie si la macro _GSM_FINAL n'est pas définie
#define _GSM_FINAL // Définit la macro _GSM_FINAL si elle n'est pas définie

#include <fstream> // Inclut le fichier d'en-tête pour les opérations de flux de fichiers
#include <cmath> // Inclut le fichier d'en-tête pour les fonctions mathématiques
#include <cstring> // Inclut le fichier d'en-tête pour les fonctions de manipulation de chaînes
#include <iomanip> // Inclut le fichier d'en-tête pour la mise en forme de sortie

using namespace std;

class Factorisation {
public:
    // Constructeur prenant le nom du fichier de données en entrée
    Factorisation(string filename);

    // Méthodes pour afficher différents éléments de la matrice et les résultats
    void affichage_de_la_Matrice();
    void afficheResultat();
    void afficheResultatP();
    void afficheMat_L();
    void affiche_diag();
    void afficheAP();
    void affiche_LP();
    void affiche_Pdiag();

    // Méthodes pour la factorisation et la résolution sans optimisation de mémoire
    void methode_factorisation_1();
    void methode_resolution_1();

    // Méthodes pour accéder aux éléments de la matrice
    float mat(int i, int j);
    float lp(int i, int j);
    void set_lp(int i, int j, float val);

    // Méthodes pour la transformation en profil et la factorisation et résolution avec optimisation de mémoire
    void rangement_en_profil();
    void methode_factorisation_profil_2();
    void methode_resolution_profil_2();

    // Méthode pour inverser le résultat
    void inversion_resultat(float* &x);

    // Destructeur de la classe
    ~Factorisation();

private:
    float **L, **Mat; // Matrices L et Mat
    float *x, *diag, *b, *x_p; // Tableaux de flottants pour diverses valeurs
    float *AP, *LP, *Pdiag; // Tableaux de flottants pour diverses valeurs
    int dim, dimAP; // Dimensions de la matrice et d'autres valeurs liées à l'optimisation de mémoire
    int *nDiag, *pi, *ki, *sommet; // Tableaux d'entiers pour diverses valeurs
};

#endif // Fin de la directive conditionnelle #ifndef