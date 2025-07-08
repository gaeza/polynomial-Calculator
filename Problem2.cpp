#include<iostream>
#include <fstream>
#include <string>
using namespace std;


struct polynomial{

    int rhs;
    int coef;
    int exp;

};

//----------------FUNCTION READ POLYNOMIAL----------------
void readPoly(polynomial* poly ,int order , int coef[]/*array to read coefs*/){

    poly[0].rhs= coef[0]; //this is the number after =
    int expOrder=0;

    for(int i=1 ; i<= order+1 ; i++){

        poly[i-1].coef=coef[i] ;
        poly[i-1].exp=expOrder;
        expOrder ++ ;

    }
}

//----------FUNCTION DISPLAY POLYNOMION EXPRESSION----------------
void displayPoly(polynomial* poly, int order) {
    bool firstTerm = true; // Track if the first term has been printed

    for (int i = order; i >= 0; i--) {  
        if (poly[i].coef != 0) { // Only print nonzero terms
            if (!firstTerm) { // If this is NOT the first term
                if (poly[i].coef > 0) 
                    cout << " + ";
                else 
                    cout << " - ";
            } 
            else if (poly[i].coef < 0) { // First term is negative
                cout << "-";
            }

            // Print coefficient (avoid printing '1x' or '-1x')
            if (abs(poly[i].coef) != 1 || poly[i].exp == 0) 
                cout << abs(poly[i].coef);

            // Print exponent part
            if (poly[i].exp > 1) 
                cout << "x^" << poly[i].exp;
            else if (poly[i].exp == 1) 
                cout << "x";

            firstTerm = false; // After printing the first term, set this to false
        }
    }

    cout << " = " << poly[0].rhs << endl;
}

//-------------FUNCTION ADD TWO POLYNOMIALS----------
void addPoly(polynomial* p1 , polynomial* p2,polynomial* p3,int orderp1 ,int orderp2){

    int i=0;int j=0;int k=0;
    p3[0].rhs=p1[0].rhs+p2[0].rhs;

    // Iterate to add corresponding terms with the same exponent
    while(i<= orderp1 && j<= orderp2){
        if(p1[i].exp == p2[j].exp){

            p3[k].coef=p1[i].coef + p2[j].coef;
            p3[k].exp=p1[i].exp;
            i++;
            j++;
            k++;
        }
        // If exponent of p1 is greater copy coef from p1
        else if(p1[i].exp > p2[j].exp){
            p3[k].coef=p1[i].coef ;
            p3[k].exp=p1[i].exp;
            i++;
            k++;
        }

        // If exponent of p2 is greater copy coef from p2
        else{
            p3[k].coef=p2[j].coef ;
            p3[k].exp=p2[j].exp;
            j++;
            k++;
        }
    }

     // If there are remaining terms in p1, copy them to p3
    while(i<= orderp1){
        p3[k].coef=p1[i].coef ;
        p3[k].exp=p1[i].exp;
        i++;
        k++;
    }
     // If there are remaining terms in p2, copy them to p3
    while(j<= orderp2){
        p3[k].coef=p2[j].coef ;
        p3[k].exp=p2[j].exp;
        j++;
        k++;
    }

}

//----------FUNCTION SUBTRACT TWO POLYNOMIALS---------------
void subtPoly(polynomial* p1 , polynomial* p2,polynomial* p3,int orderp1 ,int orderp2){

    int i=0;int j=0;int k=0;
    p3[0].rhs= p2[0].rhs - p1[0].rhs;

    while(i<= orderp1 && j<= orderp2){
        if(p1[i].exp == p2[j].exp){

            p3[k].coef=p2[i].coef - p1[j].coef;
            p3[k].exp=p1[i].exp;
            i++;
            j++;
            k++;
        }

        else if(p1[i].exp > p2[j].exp){
            p3[k].coef=p1[i].coef ;
            p3[k].exp=p1[i].exp;
            i++;
            k++;
        }

        else{
            p3[k].coef=p2[j].coef ;
            p3[k].exp=p2[j].exp;
            j++;
            k++;
        }
    }

    while(i<= orderp1){
        p3[k].coef=p1[i].coef ;
        p3[k].exp=p1[i].exp;
        i++;
        k++;
    }

    while(j<= orderp2){
        p3[k].coef=p2[j].coef ;
        p3[k].exp=p2[j].exp;
        j++;
        k++;
    }

}

//----------------MAIN-----------------
int main(){

    //read from file
    ifstream file("p2TestCases.txt");

    if (!file) {
        cout << "can not open file.\n";
        return 1;
    }

    int testcase=1;

    while(!file.eof()){

        int p1order;
        file>>p1order;

        int* polyarr1=new int[p1order+2];
        for (int i = 0; i < p1order + 2; ++i) {
            file >> polyarr1[i];
        }

        int p2order;
        file>>p2order;

        int* polyarr2=new int[p2order+2];
        for (int i = 0; i < p2order + 2; ++i) {
            file >> polyarr2[i];
        }

        int p3order=max(p1order,p2order);

        polynomial* poly1=new polynomial[p1order+1] ;
        polynomial* poly2=new polynomial[p2order+1] ;
        polynomial* poly3=new polynomial[p3order+1] ;

        cout<<"Test Case number "<<testcase++<<":\n";

        readPoly(poly1 ,p1order ,polyarr1);
        cout<<"First polynomial : ";
        displayPoly(poly1,p1order);

        readPoly(poly2 ,p2order ,polyarr2);
        cout<<"Second polynomial : ";
        displayPoly(poly2,p2order);

        cout<<"Sum of polynomials : ";
        addPoly(poly1 ,poly2 ,poly3,p1order,p2order);
        displayPoly(poly3,p3order);

        cout<<"Difference of polynomials : ";
        subtPoly(poly1 ,poly2 ,poly3,p1order,p2order);
        displayPoly(poly3,p3order);

        delete[] poly1;
        delete[] poly2;
        delete[] poly3;
        delete[] polyarr1;
        delete[] polyarr2;
    }
    
    file.close();
    return 0;
}