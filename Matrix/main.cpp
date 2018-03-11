#include<iostream>
#include<ctime>
#include<chrono>
#include "myMatrix.h"

using namespace std;

int main()
{
    cout<<"--DOUBLE MATRIX OPERATIONS--"<<endl;
    myMatrix<double> A(3,3);
    cout<<"Enter the matrix A(3x3)"<<endl;
    cin>>A;
    myMatrix<double> B(3,2);
    cout<<"Enter the matrix B(3x2)"<<endl;
    cin>>B;
    myMatrix<double> C(2,3);
    cout<<"Enter the matrix C(2x3)"<<endl;
    cin>>C;
    myMatrix<double> D(3,3,0);
    std::chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
    D = A+B*C;
    std::chrono::_V2::system_clock::time_point  end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "TIME TAKEN TO COMPUTE A+B*C: "<<chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count()<<" nanoseconds"<<endl;
    cout<<D;
    start = chrono::high_resolution_clock::now();
    D+=A;
    end = chrono::high_resolution_clock::now();
    elapsed = end - start;
    cout << "TIME TAKEN TO COMPUTE D+=A: "<<chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count()<<" nanoseconds"<<endl;
    cout<<D;
    start = chrono::high_resolution_clock::now();
    D*=A;
    end = chrono::high_resolution_clock::now();
    elapsed = end - start;
    cout << "TIME TAKEN TO COMPUTE D*=A: "<<chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count()<<" nanoseconds"<<endl;
    cout<<D;
    cout<<"\n--COMPLEX MATRIX OPERATIONS--"<<endl;
    myMatrix<complex<> > w(2,2);
    cout<<"Enter the matrix A(2x2)"<<endl;
    cin>>w;
    myMatrix<complex<> > x(2,3);
    cout<<"Enter the matrix B(3x2)"<<endl;
    cin>>x;
    myMatrix<complex<> > y(3,2);
    cout<<"Enter the matrix C(2x3)"<<endl;
    cin>>y;
    myMatrix<complex<> > z(2,2,0);
    std::chrono::_V2::system_clock::time_point start1 = chrono::high_resolution_clock::now();
    z = w*x+y;
    std::chrono::_V2::system_clock::time_point  end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed1 = end1 - start1;
    cout << "TIME TAKEN TO COMPUTE A*B+C: "<<chrono::duration_cast<std::chrono::nanoseconds>(elapsed1).count()<<" nanoseconds"<<endl;
    cout<<z;
    return 0;
}