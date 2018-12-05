
#include <complex>
#include"./Matrix.h"
#include<iostream>
#include<fstream>
#include<vector>
#include <cmath>
using namespace std;
class Qubit {
    public:
       static int ID;
        Qubit(complex<double> c0=0, complex<double> c1=0,string n="!NULL", bool iB=false){
            Matrix<complex<double>> V(2,1,0.);
            V(0)=c0;
            V(1)=c1;
            
            if( n == "!NULL" ){ // Sets name if none given to x<i> where i is incremented each new quibit 
                name = "x"; 
                name += to_string(ID);
                ID++;
            }
            else{
                name=n;
            }
            isBra=iB;
        };
        string getNameStr(){ return name; };
        string disp(){
            cout << "|"<<name<<">=\n" << V <<endl;
            //if(isBra)
             //   return "<".name."| = <0|".dat(0,0)." + <1|".dat(0,1);
            //return "|".name."> = ".dat(0,0)."|0> + ".dat(0,1)."|1>";
            return "";
        };  

        void switchD(){
           // isBra = not(isBra); 
            V = trans(V);
            return;
        };
        

        Matrix<complex<double>> V; // Is public so operations can easily be preformed on it

      //  bool isKet(){return not(isBra); };
       // bool isBra(){return isBra; };
        double prob(bool zero_one){
            return zero_one? real((conj(V(0))*V(0))) : real((conj(V(1))*V(1)));

        };
        

        private:

        string name;
        bool isBra;

};
int Qubit::ID = 0;

int main(){
   Matrix<complex<double>> M1(2,2,1i) ;
   Matrix<complex<double>> M2(4,4,0.0);
   Matrix<complex<double>> H(2,2,1.0/sqrt(2));
   Matrix<complex<double>> M3(3,3,0);
   Matrix<complex<double>> Mc(4,4,(1.+1i));
   Mc(0,1)=0.;
   Mc(0,2)=0.;
   Mc(2,3)=0;
   M3(0,1)=1.0;
   M3(0,2)=1.0;
   M3(2,1)=1.0;
   H(1,1)=H(1,1)*(-1.0);
   Matrix<complex<double>> CNOT(4,4,0);
   CNOT(0,0)=1.;
   CNOT(1,1)=1.;
   CNOT(2,3)=1.;
   CNOT(3,2)=1.;
   

   for(unsigned int i=0; i<M2.nrows(); i++)
      for(unsigned int j=0; j<M2.ncols(); j++)
         if(i==j)
            M2(i,j)=1.0;
   
   cout << "M1 = " <<M1;
   cout << endl << "M2 :\n " << M2 << endl;
   cout << "conjugate of M1 : \n";
   cout << conj(M1);
   cout << endl;
   cout << "M3: \n" << M3 << endl << "M3 transpose: " << endl << trans(M3) << endl;

   
   cout << "Tensor Product M2(x)M1 : ";
   Matrix<complex<double>> M4(tensor(M1,M2));
   cout << endl << M4;

   cout << endl << "Haramad H: "<< endl << H;
   cout << endl << " H (x) H : " << endl << tensor(H,H);
   
   Matrix<complex<double>> s1(2,1,0);
   Matrix<complex<double>> s2(2,1,0);
   s1(1,0)=1;
   s2(0,0)=1;

   Matrix<complex<double>>s1_2(tensor(s1,s2));
   cout << "s1 : \n" << s1 << endl << "s2 : \n" << s2 << endl << "s1 (x) s2 : \n" << s1_2 << endl; 

   cout << " CNOT Gate : " << endl << CNOT << endl << endl ;

   cout << "CNOT|s1(x)s2> : ";
   cout << endl << CNOT*s1_2 << endl ;
   cout << endl << endl << endl << "****************";
   s1_2=trans(s1_2);
   cout << "trans(s1(x)s2 :\n" << trans(s1_2) << endl ;
cout << "Mc = " <<  endl << Mc << endl ;
cout << endl << "dagger(Mc) :\n" << dagger(Mc)<< endl;


for(int i=0;i<10;i++)
   cout <<endl;
cout << "******************" << endl;
for(int i = 0;i < max(s1_2.ncols(),s1_2.nrows()); i++)
   cout << "s1_2[" << i << "] : " << s1_2(i) <<endl;
   return 0;

}
