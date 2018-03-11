#ifndef _myMatrix_h_
#define _myMatrix_h_

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
//Definition of Complex Numbers
template<typename T = double>
struct complex{
	T a; //real part
	T b; //imaginary part
	complex(T a1 = 0 , T b1 = 0):a(a1), b(b1){};//Constructor
};
//Operator overloading for Complex numbers . ADDITION
template<typename T>
complex<T> operator+(const complex<T>& x, const complex<T>& y){
	complex<T> z;
	z.a = y.a+x.a;
	z.b = y.b+x.b;
	return z;  
}
//Operator overloading for Complex numbers . MULTIPLICATION
template<typename T>
complex<T> operator*(const complex<T>& x, const complex<T>& y)
{
	complex<T> z;
	z.a = (x.a)*(y.a) - (x.b)*(y.b);
	z.b = (x.a)*(y.b) + (x.b)*(y.a);
	return z;    
}
//Output a complex number
template<typename T>
ostream& operator<<(ostream& out, const complex<T>& x){
	out<<"("<<x.a<<") + i("<<x.b<<")";
	return out;
}
//Input a complex number
template<typename T>
istream& operator>>(istream& in, complex<T>& x){
	in>>x.a;	cout<<" + i "; cin>>x.b;
	return in;
}
//Operator Overloading for addition of vectors
template<typename T>
vector<T> operator+ (const vector<T>& a,const vector<T>& b){
    vector<T> c(a.size());
    for(size_t i = 0; i<c.size(); i++)
        c[i] = a[i] + b[i];
    return c;
}
//class matrix which consists of a vector of vectors as a container by default
template<typename T, typename C = vector<vector <T> > >
class myMatrix{
	C matrix; //container
	size_t row_size; // number of rows
	size_t col_size; // number of columns
	public:
		//Constructors
		myMatrix(){		};	//Default constructor.
		myMatrix(size_t n):		row_size(n),	col_size(n){};	//Square matrix when order of matrix is the input. 
		myMatrix(size_t n, size_t m):	row_size(n), 	col_size(m){};	//Rectangle matrix when no.of rows and no. of cols are specified. 
		myMatrix(const C& mat):		matrix(mat){};//,	row_size(mat.size()),	col_size(mat[0].size()){};	//Copy the contents of a matrix in the form vector of vectors to the 'matrix' data member. 
		myMatrix(const myMatrix& mat):	matrix(mat.matrix){};//, 	row_size(mat.size().first), 	col_size(mat.size().second){};//Copy constructor
		myMatrix(size_t n, size_t m, const T init_value); //Given no of rows and cols, creates a matrix with all elements equal to init_value
		//Functions
		void push_back(vector<T> a){ 	matrix.push_back(a);	}; //inserts a new row which has col_size number of elements.
		pair<size_t, size_t> size() const{	return {row_size, col_size};	}	//returns the number of rows and columns.
		C& data(){	return matrix;		}; //returns the container i.e., the 2D matrix made of vector of vectors.
        const C& data() const{ return matrix; };	
		//Operator Overloading
		myMatrix& operator=(const myMatrix&);	//overloaded =. Parameter is an object of myMatrix class.
		vector<T> operator[] (const size_t i)const{return matrix[i];};	//overloaded []. Returns a vector. 
		template<typename T2, typename R2> myMatrix& operator=(const myMatrix<T2, R2>& oth){//overloaded = for other data types say, expressions
            for (size_t i = 0; i < matrix.size(); ++i) matrix[i] = oth[i];
            return *this;
        }
};
//overloaded assignment operator
template<typename T, typename C1>
myMatrix<T,C1>& myMatrix<T,C1>::operator=(const myMatrix& mat)
{	
	row_size = mat.row_size;
	col_size = mat.col_size;
	for(size_t i = 0; i < row_size; i++){
		matrix.push_back(vector<T>(col_size));
		for(size_t j = 0; j < col_size; j++){
			matrix[i][j] = mat.matrix[i][j];
		}
	}
	return *this;
}
//Constructor which takes initial values of elements
template<typename T, typename C>
myMatrix<T,C>::myMatrix(size_t n, size_t m, const T init_value){
	row_size = n; col_size = m;
	for(size_t i = 0; i < row_size; i++){
        matrix.push_back(vector<T>(col_size));
        for(size_t j = 0; j < col_size; j++){
            matrix[i][j] = init_value;
        }
    } 
}
//To output a matrix
template<typename T>
ostream& operator<<(ostream& out, myMatrix<T>& mat)
{
    for(size_t i = 0; i < mat.size().first; i++){   vector<T> temp = mat[i];
        for(size_t j = 0; j <mat.size().second; j++){  
            out<<temp[j]<<" ";
        }out<<endl;
    }return out;
}
//To input a matrix
template<typename T, typename C>
istream& operator>>(istream& in, myMatrix<T, C>& mat)
{
    for(size_t i = 0; i <mat.size().first; i++){
        vector<T> a;
        for(size_t j = 0; j < mat.size().second; j++){
            T temp;
            in>>temp;
            a.push_back(temp);
        }mat.push_back(a);
    }return in; 
}
//Expression Template for Addition
template<typename T, typename T1, typename T2>
class add_exp{
	public:
		const T1& lhs;
		const T2& rhs;
		add_exp(const T1& l,const T2& r):lhs(l), rhs(r){};	
		pair<size_t, size_t> size() const{	return {lhs.size().first, lhs.size().second};	};
	    vector<T> operator[](const long int a) const{return lhs[a]+rhs[a];  };
};
//Operation "+"
template<typename T1, typename T2, typename T>
myMatrix<T, add_exp<T, T1, T2> >
operator+ (const myMatrix<T, T1>& a,const myMatrix<T, T2>& b){
  return myMatrix<T, add_exp<T, T1, T2> >(add_exp<T, T1, T2>(a.data(), b.data()));
}
//Operation "+="
template<typename T1, typename T2, typename T>
myMatrix<T, add_exp<T, T1, T2> >
operator += ( myMatrix<T, T1>& a,const myMatrix<T, T2>& b){
  a = myMatrix<T, add_exp<T, T1, T2> >(add_exp<T, T1, T2>(a.data(), b.data()));
}
//Expression Template for Multiplication
template<typename T, typename T1, typename T2>
class mul_exp
{
	public:
		const T1& lhs;
		const T2& rhs;
		mul_exp(T1& l, T2& r):lhs(l), rhs(r){};	
		pair<size_t, size_t> size(){	return {lhs.size().first, rhs.size().second};	};
		vector<T> operator[](const long int a) const{
		    vector<T> ans(lhs.size(), 0);
    		for(size_t j = 0; j < rhs[0].size(); j++){
    		    for(size_t k = 0; k < rhs.size();k++){
    		        ans[j] = ans[j] + lhs[a][k]*rhs[k][j];
    		    }
    		}
    		return ans;
		};
};
//Operation "*"
template<typename T1, typename T2, typename T>
myMatrix<T, mul_exp<T, T1, T2> >
operator* ( myMatrix<T, T1>& a, myMatrix<T, T2>& b){
    return myMatrix<T, mul_exp<T, T1, T2> >(mul_exp<T, T1, T2>(a.data(), b.data()));
}
//Operation " *= "
template<typename T1, typename T2, typename T>
myMatrix<T, mul_exp<T, T1, T2> >
operator*= ( myMatrix<T, T1>& a, myMatrix<T, T2>& b){
  a = myMatrix<T, mul_exp<T, T1, T2> >(mul_exp<T, T1, T2>(a.data(), b.data()));
}

#endif