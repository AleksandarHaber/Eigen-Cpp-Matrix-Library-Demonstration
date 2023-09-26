#include<iostream>
#include<vector>
#include <iterator>

#include<Eigen/Dense>
#include <Eigen/Eigenvalues> 

using namespace std;
using namespace Eigen;

int main()
{
    // create a random matrix
    MatrixXd randomMatrix;
    randomMatrix.setRandom(3,3);
    // this vector/matrix will be used to store the eigenvalues
    
    // The matrix has to be complex
    // This is the typedef for MatrixXcd
    // typedef Matrix< std::complex<double> , Dynamic , Dynamic > MatrixXcd
    // That is, this matrix can store std::complex<double> data type
    MatrixXcd eigenvalueMatrix;
    // this matrix will be used to store the eigenvectors
    // the matrix needs to be complex since the eigenvalues can be complex
    MatrixXcd eigenvectorMatrix;
    // print the random matrix
    cout <<endl<< randomMatrix << endl;

    // compute the matrix
    EigenSolver<MatrixXd> eigenValueSolver(randomMatrix);
    
    eigenvalueMatrix=eigenValueSolver.eigenvalues();
    // the eigenvectors are stored column wise
    eigenvectorMatrix=eigenValueSolver.eigenvectors();
    // print the eigenvalues
    cout <<endl<<"Computed eigenvalues:"<<endl<<eigenvalueMatrix<<endl;
    // print the eigenvectors
    cout <<endl<<"Computed eigenvectors:"<<endl<<eigenvectorMatrix<<endl;

    // extract real and imaginary parts of the eigenvalues
    MatrixXd realPartEigenValues;
    MatrixXd imagPartEigenValues;

    realPartEigenValues=eigenvalueMatrix.real();
    imagPartEigenValues=eigenvalueMatrix.imag();

    // print the real parts of the eigenvalues
    cout<<endl<<realPartEigenValues<<endl;
    // print the complex parts of the eigenvalues
    cout<<endl<<imagPartEigenValues<<endl;

    // let us double check one eigenvalue and eigenvector
    MatrixXcd testLeft;
    MatrixXcd testRight;

    // definition of the eigenvalue and the eigenvector
    // test1Right = A*v 
    // test2Right = lambda*v
    // A*v=lambda*v 
    // if everything is computed correctly
    // testLeft = testRight
    testLeft=randomMatrix*eigenvectorMatrix.col(0);
    testRight=eigenvalueMatrix(0,0)*eigenvectorMatrix.col(0);
    cout<<endl<<"Left side vector:"<<endl<<testLeft<<endl;
    cout<<endl<<"Right side vector:"<<endl<<testRight<<endl;
    cout<<endl<<"Left minus right side vector:"<<endl<<testLeft-testRight<<endl;

    // let us do some manipulations with eigenvalues
    // for example let us define a vector structure of eigenvalues
    // we need std:: complex<double>

    std::vector<std::complex<double>> doubledEigenValueVector;
    // eigenvalues are of the type complex <double>
    complex<double> eigenValue;
   
    for (int i=0; i<eigenvalueMatrix.rows(); i++)
    {
        eigenValue=eigenvalueMatrix(i,0);
        cout<<endl<<" Real part of the eigenvalue "<<i<<" is "<<eigenValue.real()<<endl;
        cout<<" Imaginary part of the eigenvalue "<<i<<" is "<<eigenValue.imag()<<endl;
        // double the eigenvalues
        doubledEigenValueVector.push_back(2.0*eigenValue);
    }
    // print the results
    for (auto it=doubledEigenValueVector.begin(); 
    it !=doubledEigenValueVector.end();
    it++)
    {
        cout<<endl<<"Original eigenvalue: "<<eigenvalueMatrix(distance(doubledEigenValueVector.begin(), it),0)<<endl;
        cout<<"Doubled eigenvalue: "<< *it <<endl;
    }


 


    return 0;
}