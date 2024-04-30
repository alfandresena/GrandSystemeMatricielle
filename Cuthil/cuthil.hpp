#ifndef _CUTHIL
#define _CUTHIL
#include <string>
#include <vector>
#include<iostream>

using namespace std ; 

class Excentricite {
    public:
        Excentricite(string filename);  // constructeur : lecture du fichier
        void display_dim();             // fonction d'affichage de dim
        void display_A();               // fonction d'affichage de A
        int cal_excentricite( int num , vector <vector<int> >& v ) ; //Calcul excentricite et voisin
        void cal_premier_sommet();      //Calclul du premier sommet
        void cuthil() ;         //L'ordre du sommet
        void cuthil_inverse() ;     //Inverstion de l'ordre du sommet
        void permutation() ;        //Re-arrangement de la matricie en utilisant l'ordre du sommet non inverse
        void permutation_avec_inversion() ; //Re-arrangement de la matricie en utilisant l'ordre du sommet avec inversion
        void enregistrement(string nomFichier) ; //Sauvgarde le fichier
        void set_resp() ;
        bool get_resp() ;
        ~Excentricite() ;         //

    private:
        int dim; // dimension
        int *sommet_1; // sommet sans inversion
        int *sommet_2; // sommet avec inversion
        float **A ; // matrice A
        float *b ; // le vecteurs b
        bool response ; //pour la choix avec inverse ou non
        vector <vector<int> > v_n ; // les voisins de n
        vector <vector<int> > v_s ; // les voisins de s
};

#endif