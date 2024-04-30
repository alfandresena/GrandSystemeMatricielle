#include"gsm_final.hpp"
#include<iostream>
#include<math.h>
#include<vector>

Factorisation :: Factorisation(string filename){
    int i(0), j(0);

    // ouvrir le fichier
    ifstream f(filename.c_str());
    
    if(!f.good()) {
        cout<<"Erreur du lecture du fichier"<<endl ;
    }
    else {
        //Prendre la dimension du matrice
        f >>dim ;

        //Allocaton du memoire pour la matrice
        Mat = new float*[dim] ;
        L = new float*[dim] ;
        diag = new float[dim] ;
        sommet = new int[dim] ;

        for(i=0 ; i<dim ; i++){
            Mat[i] = new float [dim] ;
            L[i] = new float[dim] ;
        }

        //Entrer du donner de la matrice
        for(i=0 ; i<dim ;i++ ){
            for(j=0 ; j<dim ; j++) {
                f >> Mat[i][j] ;
                L[i][j] = 0 ;
            }
            diag[i] = 0 ;
        }
 
        //Allocation et entrer des donner du vecteur
        b = new float [dim] ;
        x = new float [dim] ;
        x_p = new float [dim] ;
        pi = new int [dim] ;
        nDiag = new int[dim] ;
        Pdiag = new float[dim] ;
        ki = new int[dim] ;
        for(i = 0 ; i<dim ; i++){
            f >> b[i] ;
            x[i] = 0 ;
            x_p[i] = 0 ;
            Pdiag[i] = 0 ;
            nDiag[i] = 0 ;
            pi[i] = 0 ;
            ki[i] = 0 ;
        }
        for(i=0 ; i<dim ; i++){
            f >> sommet[i] ;
        }
    }
    f.close();

    cout<<"Donner entrer avec succes !"<<endl;
    cout<<"\n\n" ;

}


Factorisation::~Factorisation() {
    delete[] Mat;
    delete[] x;
    delete[] b;
    delete[] L;
    delete[] diag;
    delete[] AP;
    delete[] LP;
    delete[] Pdiag;
    delete[] nDiag;
    delete[] pi;
    delete[] ki;
    
    cout<<"Memoire liberer ! Merci d'avoir utiliser se programme ;-) \n"<<endl ;
}


void Factorisation::affichage_de_la_Matrice(){
    cout<<"La dimension du matrice est : "<< dim <<endl;
    cout<<"La matrice actuel :"<<endl;
    for(int i(0) ; i<dim ; i++ ){
        for(int j(0) ; j<dim ; j++){
            cout<< Mat[i][j] <<"\t" ;
        }
        cout<<"\n" ;
    }
    cout<<"\n\n" ;
}

void Factorisation::inversion_resultat(float* &x) {
    float *c ;
    c = new float[dim] ;
    for(int i(0) ; i<dim ; i++){
        c[sommet[i]]=x[i] ;
    }
    for(int i(0) ; i<dim ; i++){
        x[i]=c[i] ;
    }
}

void Factorisation::afficheResultat(){
    inversion_resultat(x) ;
    for (int i(0) ; i<dim ; i++){
        cout<<"x"<<i+1<<"\t=\t"<<x[i]<<endl ;
    }
}

void Factorisation::afficheResultatP(){
        inversion_resultat(x_p) ;
    for (int i(0) ; i<dim ; i++){
        cout<<"x_p"<<i+1<<"\t=\t"<<x_p[i]<<endl ;
    }
}

void Factorisation::afficheMat_L(){
    cout<<"La matrice L :"<<endl;
    for(int i(0) ; i<dim ; i++ ){
        for(int j(0) ; j<dim ; j++){
            cout << fixed << setprecision(2) << L[i][j] <<"\t\t" ;
        }
        cout<<"\n" ;
    }
    cout<<"\n" ;
}

void Factorisation::affiche_diag(){
    for (int i(0) ; i<dim ; i++){
        cout<<"diag ["<< i+1 <<"]: "<<" = "<<diag[i]<<endl ;
    }
    cout<<endl ;
}

void Factorisation::afficheAP() {
    cout<<"Matrice de profil : \n" ; 
    for(int i=0 ; i<dim ; i++){
        for(int j(0) ; j<=i ; j++){
            cout<<mat(i,j)<<"\t" ;
        }
        cout<<"\n" ;
    }
    cout<<endl ;
}


void Factorisation::affiche_LP(){
    cout<<"Matrice L :\n" ;
    for(int i=0 ; i<dim ; i++){
        for(int j(0) ; j<=i ; j++){
            cout<<lp(i,j)<<"\t" ;
        }
        cout<<"\n" ;
    }
    cout<<endl ;
    cout<<endl ;
}

void Factorisation::affiche_Pdiag(){
    for (int i(0) ; i<dim ; i++){
        cout<<"Diagonal du profil : "<<i+1<<"\t=\t"<<Pdiag[i]<<endl ;
    }
    cout<<endl ;
    cout<<"\n" ;
}

void Factorisation :: methode_factorisation_1(){
    for (int i = 0; i < dim; i++) {
        float sum = 0.0;
        for (int k = 0; k < i; k++) {
            sum += L[i][k] * L[i][k] * diag[k];
        }
        diag[i] = Mat[i][i] - sum;
        L[i][i] = 1 ;

        for (int j = i + 1 ; j < dim; j++) {
            float sum2 = 0.0;
            for (int k = 0; k < i; k++) {
                sum2 += L[j][k] * L[i][k] * diag[k];
            }
            L[j][i] = (Mat[j][i] - sum2) / diag[i];
        }
    }
    cout<<"\n\n" ;
}

void Factorisation :: methode_resolution_1(){
    for (int i = 0; i < dim; ++i) {
        x[i] = b[i];
        for (int j = 0; j < i; ++j) {
            x[i] -= L[i][j] * x[j];
        }
    }

    for (int i = 0; i < dim; ++i) {
        x[i] /= diag[i];
    }

    for (int i = dim - 1; i >= 0; --i) {
        for (int j = i + 1; j < dim; ++j) {
            x[i] -= L[j][i] * x[j];
        }
    }
}


void Factorisation::rangement_en_profil(){
    dimAP = 0 ;
    for( int i(0) ; i<(dim) ; i++ ){
        bool reste = false ;
        for( int j(0) ; j <= i ; j++){
            if( Mat[i][j] != 0 && reste == false){
                dimAP++;
                reste = true ;
                continue ;
            }
            if(reste) {
                dimAP++ ;
            }
        }
    }
    cout<<"\n                          Dim AP = "<<dimAP<<endl ; 
    
    AP = new float [dimAP] ;
    LP = new float [dimAP] ; 
    dimAP = 0 ;
    for( int i(0) ; i<(dim) ; i++ ){
        bool reste = false ;
        for( int j(0) ; j <= i ; j++){
            if(i==j){
                nDiag[i] = dimAP ; 
            }
            if(reste == true) {
                AP[dimAP] = Mat[i][j] ;
                LP[dimAP] = 0 ;
                dimAP++ ;
            }
            if( Mat[i][j] != 0 && reste == false){
                AP[dimAP] = Mat[i][j] ;
                LP[dimAP] = 0 ;
                pi[i] = dimAP ;
                ki[i] = j ;
                dimAP++;
                reste = true ;
            }
        }
    }
}

float Factorisation::mat(int i, int j) {
    if( i < j ) return mat( j , i ) ;
    if( j < ki[i] ) return 0 ;
    if ( i== j) return AP[ nDiag[i] ] ;
    return AP[ pi[i] + j - ki[i] ] ; 
}

float Factorisation::lp(int i, int j) {
    if( i < j ) return lp( j , i ) ;
    if( j < ki[i] ) return 0 ;
    if ( i == j ) return LP[nDiag[i]] ;
    else return LP[ pi[i] + j - ki[i] ] ;
}

void Factorisation::set_lp(int i, int j, float val) {
    if( i < j ) return set_lp( j , i, val ) ;
    if( j < ki[i] ) return ;
    if ( i == j ) LP[nDiag[i]] = val ;
    else (LP[ pi[i] + j - ki[i] ] = val) ; 
}


void Factorisation::methode_factorisation_profil_2() {
    for (int i = 0; i < dim; i++) {
        float sum = 0.0;
        for (int k = 0; k < i; k++) {
            sum += lp(i,k) * lp(i,k) * Pdiag[k];
        }
        Pdiag[i] = mat(i,i) - sum;
        set_lp(i,i,1) ;

        for (int j = i + 1 ; j < dim; j++) {
            float sum2 = 0.0;
            for (int k = 0; k < i; k++) {
                sum2 += lp(j,k) * lp(i,k) * Pdiag[k];
            }
            set_lp(j , i , ((mat(j,i) - sum2) / Pdiag[i]) );
        }
    }
}


void Factorisation::methode_resolution_profil_2() {
    for (int i = 0; i < dim; ++i) {
        x_p[i] = b[i];
        for (int j = 0; j < i; ++j) {
            x_p[i] -= lp(i,j) * x_p[j];
        }
    }

    for (int i = 0; i < dim; ++i) {
        x_p[i] /= Pdiag[i];
    }

    for (int i = dim - 1; i >= 0; --i) {
        for (int j = i + 1; j < dim; ++j) {
            x_p[i] -= lp(j,i) * x_p[j];
        }
    }
}