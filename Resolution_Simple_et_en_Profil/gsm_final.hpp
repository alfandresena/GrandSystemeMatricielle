#ifndef _GSM_FINAL
#define _GSM_FINAL

#include<fstream>
#include<math.h>
#include<string.h>
#include<iomanip>

using namespace std ;

class Factorisation {
    public :
        Factorisation(string filename) ;

        void affichage_de_la_Matrice() ;
        void afficheResultat() ;
        void afficheResultatP() ;
        void afficheMat_L() ;
        void affiche_diag() ;
        void afficheAP() ;
        void affiche_LP() ;
        void affiche_Pdiag() ;

        void methode_factorisation_1() ;
        void methode_resolution_1() ;

        float mat(int i, int j) ;
        float lp(int i, int j);
        void set_lp(int i, int j, float val) ;
        void rangement_en_profil() ;
        void methode_factorisation_profil_2() ;
        void methode_resolution_profil_2() ;

        void inversion_resultat(float* &x) ;

        ~Factorisation() ;

    private :
        float **L, **Mat ;
        float *x, *diag, *b, *x_p ;
        float *AP, *LP, *Pdiag ;
        int dim, dimAP ;
        int *nDiag, *pi, *ki, *sommet ;
} ;

#endif