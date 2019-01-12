#pragma once
#include "tools.h"
class algoBase{
public:
	algoBase();
	void intro();
	virtual void solve()=0;
	virtual ~algoBase(){};
private:
	std::string name;
	std::string method; //allows the posibility of multiple methods, usage should be specific to derived classes
	std::string source;
};
class longest_subsequence:public algoBase
{
public:
	longest_subsequence()=delete;
	longest_subsequence(const std::string& s1,const std::string& s2);
	void solve();
	int solve(int p1,int p2,int currlength);
private:
	matrix<int> length; //stores the length of a 
	std::string m_s1,m_s2;
	std::string result;
	std::string name="longest subsequence";
};
class rod_cutting:public algoBase
{
public:
	rod_cutting()=delete;
	rod_cutting(const std::vector<double>& price);//price can be double but length must be int
	void solve();
private:
	std::vector<double> m_price;
	int m_length;
	std::vector<int> location;
	std::vector<double> revenue;
	std::string name="rod_cutting";
	std::string source="CSRP";
};

class matrix_mult_parenthesis:public algoBase
{
public:
	matrix_mult_parenthesis(const std::vector<int>& dim):m_dim(dim){};
	void solve();
private:
	std::vector<int> m_dim;
	int INF=1e6;
};