#include"cuthil.hpp"
#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<string> 

using namespace std ;

int main() {

    cout<<"\nBIENVENUE\n\nCETTE PROGRAMME EST LA PREMIERE PARTIE  DU PROGRAMME DESTINE A LA RESOLUTION D'UNE MATRICE CREUSE SIMTETRIE DEFINIE PROSITIF "<<endl ;
    cout<<"\nAPPLICATION DE L' ALGORYTHME DE CUTHILL-MCKEE A LA MATRICE A\n"<<endl ;


    Excentricite calcul("data.txt"); //Lecture des fihicer dans data.txt et initialisation

    calcul.display_dim(); // Affichage de la dimention

    calcul.display_A(); //Affichage de A

    calcul.cal_premier_sommet() ; //Caclul le premier sommet

    calcul.cuthil() ; //L'ordre du sommet

    calcul.cuthil_inverse() ; //L'ordre du sommet avec invertion

    calcul.set_resp() ;

    if(calcul.get_resp()){
        calcul.permutation() ;
        calcul.display_A() ;
    } else {
        calcul.permutation_avec_inversion() ;
        calcul.display_A() ;
    }

    calcul.enregistrement("new_data.txt") ;//Sauvgarde la matrice A et b re-arranger

    calcul.~Excentricite() ; //Destructeur

    return 0 ;
}
