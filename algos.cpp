#include "algos.h"
using std::cout;
using std::endl;
using std::vector;
algoBase::algoBase(){
    log(info,"Initialized algo: "+name);
}
void algoBase::intro(){
    log(info,"algo from "+source);
}

longest_subsequence::longest_subsequence(const std::string& s1,const std::string& s2) 
:length(matrix<int>(s1.size(),s2.size())),m_s1(s1),m_s2(s2)
{

}
void longest_subsequence::solve(){

	//matrix type is not reliable for use yet...
	//std::vector<std::vector<int> > c(1+m_s1.size(),std::vector<int>(1+m_s2.size(),0));
	matrix<int> c(1+m_s1.size(),1+m_s2.size(),0);
	auto b=c;
	//initialize b and c's boundary properly
    for (int i=0;i<=m_s1.size();++i){
		c[i][0]=0;
		b[i][0]=NAN;
	}	
    for (int j=0;j<=m_s2.size();++j){
		c[0][j]=0;
		b[0][j]=NAN;
    }   
	
	for (int i=1;i<=m_s1.size();++i){
		for (int j=1;j<=m_s2.size();++j){
			if (m_s1[i-1]==m_s2[j-1]){
				c[i][j]=c[i-1][j-1]+1;
				b[i][j]=0;
			}
			else if (c[i-1][j]>=c[i][j-1]){
				c[i][j]=c[i-1][j];
				b[i][j]=1;
			}
			else {
				c[i][j]=c[i][j-1];
				b[i][j]=-1;
			}
		}
	}
	std::string out;	
	//print out the result;
	int i=m_s1.size(),j=m_s2.size();
	while (i>0 && j>0){
		if (b[i][j]==0){
			out.push_back(m_s1[i-1]);
			i--;
			j--;
		}
		else if (b[i][j]==1){
			i--;
		}
		else {
			j--;
		}
	}
	std::reverse(out.begin(),out.end());
	std::cout<<out<<std::endl;
			
//	std::cout<<"length from recursion is: "<< solve(0,0,0)<<std::endl;
}
int longest_subsequence::solve(int p1,int p2,int currlength)
{
	//p1 and p2 represent the current location, this is clearly to prevent passing substrings as arguments which will require stripping the head element from a sequential container and copy the container
	if (p1==m_s1.size()-1 || p2==m_s2.size()-1){
		return currlength;
	}
	else if (m_s1[0]==m_s2[0]){
		std::cout<<m_s1[0]<<std::endl;
		return solve(p1+1,p2+1,currlength+1);
	}
	else{
		std::cout<<p1<<", "<<p2<<", "<<currlength<<std::endl;
		return std::max(solve(p1+1,p2,currlength),solve(p1,p2+1,currlength));
	}
}

	

	

rod_cutting::rod_cutting(const std::vector<double>& price):m_price(price){
	//sanity check
	if (m_price.size()<=0){
		log(fatal,"rod should at least be of length 1");
	}
	for (auto p:m_price){
		if (p<0){
			log(fatal,"some price is smaller than 0!");
			break;
		}
	}
	m_length=m_price.size();
	revenue=std::vector<double>(m_length+1,0);
	location=std::vector<int>(m_length+1,0); //this number ranges from 0 to m_length-1, records the location of cutting, hence if you say you wont cut a rod, that's equivalent to cutting at position 0, not position m.
	location[0]=NAN;//protecting the first value of locaiton, cutting a rod at locaiton 0 makes no sense
}

void rod_cutting::solve(){
	revenue[0]=0;	
	revenue[1]=m_price[0];

	for (int i=1;i<=m_length;++i){//revenue for rod of length i
		std::cout<<"computing for length: "<<i<<std::endl;
		for (int j=1;j<=i;++j){
			std::cout<<"cutting at left length: "<<j<<", left rod price: "<<m_price[j-1]<<", right current best rev: "<<revenue[i-j]<<", current best rev:"<<revenue[i]<<std::endl;
			
			if (revenue[i-j]+m_price[j-1]>revenue[i]){
				revenue[i]=revenue[i-j]+m_price[j-1];
				location[i]=j;
				std::cout<<"updated rev: "<<revenue[i]<<" at cut: "<<location[i]<<std::endl;
			}
		}
	}
	std::vector<int> subrod_lengths;//stores results
	for (int i=m_length;i>1;){
		subrod_lengths.push_back(location[i]);
		i=i-location[i];
	}
	std::stringstream ss;
	for (auto rev:revenue){
		std::cout<<rev<<std::endl;
	}
	ss<<"max revenue "<< revenue[m_length]<<", rod lengths are: ";
	for (auto rod:subrod_lengths){
		ss<<rod<<", ";
	}
	log(info,ss.str());
}

void matrix_mult_parenthesis::solve(){
	
    int n=m_dim.size()-1; //number of matrices
    //a matrix to store the optimal costs, def are how many should be on the left side for the first complete paired parenthesization?
    vector<vector<int> > cost=vector<vector<int> >(n+1,vector<int>(n+1,INF)); //square matrix, we use 1 based indexing
    vector<vector<int> > split=vector<vector<int> >(n+1,vector<int>(n+1,INF)); //square matrix
    for (int i=0; i<=n;++i) {
        cost[i][i]=0;
    }
    for (int length=2; length<=n; ++length) { //first loop should indicate the length of the expression!
        for (int i=1; i+length-1<=n; ++i) { //i should be the starting matrix
            int j=i+length-1; //j is ending matrix
            for (int k=i; k<j; ++k) { //k should be the dividing pos, indicating the ending position of first parenthesis, note k cannot be j, this is meaningless
                if (cost[i][k]+cost[k+1][j]+m_dim[i-1]*m_dim[j]*m_dim[k]<cost[i][j]) {
                    cost[i][j]=cost[i][k]+cost[k+1][j]+m_dim[i-1]*m_dim[j]*m_dim[k];
                    split[i][j]=k;
                }
            }
        }
    }
	//TODO: delegate the formatted output mission to matrix template 
	cout.width(5);
    for (int i=0; i<n+1; ++i) {
        for (int j=0; j<n+1; ++j) {
            if (cost[i][j]==INF) {
                cout<<"I"<<',';
            }
            else{
                cout<<cost[i][j]<<',';
            }
            
        }
        printf("\n");
    }
}