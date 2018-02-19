#ifndef VARADIC_H
#define VARADIC_H
#include <iostream>
using namespace std;
class Varadic{
public:
	template<typename T>
	static T Sum(T);
	template<typename T,typename...Args>
	static T Sum(T x,Args...y);
	template<typename T>
	static T Carp(T);
	template<typename T,typename...Args>
	static T Carp(T x,Args...y);
	template<typename T>
	static void print(T);
	template<typename T,typename...args>
	static void print(T,args...values);
};
template<typename T,typename...Args>
T Varadic::Sum(T x,Args...y){
	return Sum(x+y...);
}
template<typename T>
T Varadic::Sum(T x){
	return x;
}
template<typename T,typename...Args>
T Varadic::Carp(T x,Args...y){
	return Topla(x*y...);
}
template<typename T>
T Varadic::Carp(T x){
	return x;
}
template<typename T>
void Varadic::print(T x){
	cout<<x<<" ";
}
template<typename T,typename...args>		
void Varadic::print(T x,args...values){
	cout<<x<<" ";
	return print(values...);
}
#endif

