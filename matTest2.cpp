
#include"Matrix.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <complex>
#include <cmath>


int main(){
	
   Matrix<complex<double>> M1(3,3,0.);
   M1(0,0)=M1(1,1)=M1(2,2)=1.;
   Matrix<complex<double>> M2(3,3,1.);
   bool m1m2=  (M1==M2);
   bool m1m1 = (M1==M1);
   Matrix<complex<double>> c_sqrtNOT(4,4,0.);
   c_sqrtNOT(0,0)=c_sqrtNOT(1,1)=1.;
   c_sqrtNOT(3,2)=c_sqrtNOT(2,3)=.5-.5i;
   c_sqrtNOT(2,2)=c_sqrtNOT(3,3)=.5+.5i;
   Matrix<complex<double>> cNOT=c_sqrtNOT*c_sqrtNOT;
   
   cout << "M1 is Unitary : " << M1.isUnitary() << endl ;
   cout << "M1 is Unitary : " << M1.isHerm() << endl ;
   cout << "M1 == M2 : " << m1m2<< endl ;
   cout << "M1 == M1 : " << m1m1<< endl ;
   cout << "controlled-sqrtNOT : " << c_sqrtNOT.isUnitary() << endl ;
   cout << "cNOT: "<< endl << cNOT << endl << " is Unitary: " << (cNOT.isUnitary() ? 'y': 'n' );
   



//   cout << endl << H4;

   // cout << endl << "Haramad H: "<< endl << H;
   // cout << endl << " H (x) H : " << endl << tensor(H,H);
   /*
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


	cout << endl << endl << "H(x)H(x)H(x)H(x)H:" << tensor(tensor(H,H),tensor(H,H));
	 */
	return 0;
}
