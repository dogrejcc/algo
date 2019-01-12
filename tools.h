#pragma once
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <cmath>
#include <sstream>
#include <vector>
#include <algorithm>
enum loglevel{
    trace,
    info,
    warn,
    fatal
};
enum dfs_option{
    preorder,
    postorder
};
//logging system
//TODO: incorporate file-logging system by using more general system calls?
//TODO: perform a multi arg easy logging system using a combination of string stream and variadic template?
/*
class log
{
public:
	log(const loglevel);
	log(const loglevel& level,std::string msg);
private:
	std::string msg;
};*/	
void log(const loglevel& level,std::string msg);

template <typename T>
class matrix{
public:
	template <typename T_arg> matrix(int m,int n,T_arg arg);
	matrix(int m,int n);
	const std::vector<T>& operator[] (int index) const;
	std::vector<T>& operator[] (int index);
    friend std::ostream& operator<<(std::ostream& os,const matrix<T>& m);
private:
	std::vector<std::vector<T> > data;
	std::pair<int,int> m_shape;
};
template <typename T>
	template<typename T_arg>
matrix<T>::matrix(int m,int n,T_arg arg){
	//sanity check
	if (m<=1 || n<=1){
		std::cout<<"0 or negative indices unsupported!"<<std::endl;
		exit(1);
	}
	m_shape.first=m;
	m_shape.second=n;
	data=std::vector<std::vector<T> >(m,std::vector<T>(n,arg));
}

template <typename T> 
matrix<T>::matrix(int m,int n):data(std::vector<std::vector<T> >(m,std::vector<T>(n))){};

template <typename T>
const std::vector<T>& matrix<T>::operator[] (int index) const{
	if (index<0 || index>m_shape.first-1){
		std::cout<<"invalid access"<<std::endl;
		exit(1);
	}
	return data[index];
}
template <typename T>
std::vector<T>& matrix<T>::operator[] (int index) {
	if (index<0 || index>m_shape.first-1){
		std::cout<<"invalid access"<<std::endl;
		exit(1);
	}
	return data[index];
}
template <typename T>
std::ostream& operator<<(std::ostream& os,const matrix<T>& m){
    for (int i=0;i<m.m_shape.first;++i){
        for (int j=0;i<m.m_shape.second;++i){
            os<<m[i][j]<<',';
        }
        os<<'\n';
    }
}
