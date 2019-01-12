#include "tools.h"
#include "algos.h"
using namespace std;
class node;
typedef std::shared_ptr<node> np_t; // np is short for node pointer
class node
{
public:
	node();
	node(const std::string& input_name);
	node(const std::string& input_name,const vector<np_t>& input_adj,int input_val);
	vector<np_t> adj;//current representation is adjacency list based
	int val;
	string name;
};
node::node():val(NAN),name(""){};
node::node(const std::string& input_name):val(NAN),name(input_name){};
node::node(const std::string& input_name,const vector<np_t>& input_adj,int input_val):adj(input_adj),val(input_val),name(input_name){};
class graphBase
{
public:
	graphBase();
	graphBase(np_t input_root):root(input_root){log(info,"Created a new tree");};
	~graphBase();
	void bfs();
	void dfs(dfs_option mode,np_t n);//mode can be preorder or postorder
	void dfs(dfs_option mode);
	void visit_node(std::shared_ptr<const node> n); //note the type change here implements const T*
	void change_node(np_t n);
private:
	np_t root;
};
graphBase::graphBase()
{
	root=std::make_shared<node>();
	log(info,"Creating new tree with one root");
}
graphBase::~graphBase()
{
	log(info,"destructing tree");	
}
void graphBase::bfs(){
	log(info,"Starting BFS");
	queue<np_t> q;
	if (!root){
		log(warn,"empty tree with null root");
	}
	q.push(root);
	node* n_current; // queue head node, current node to process
	while (!q.empty()){
		np_t n_qhead=q.front();
		for (auto n_next:n_qhead->adj){
			visit_node(n_next);
			q.push(n_next);
		}
		q.pop();
	}
	log(info,"Finishing BFS");
}
void graphBase::dfs(dfs_option mode,np_t n){
	if (!((mode==preorder)||(mode==postorder))){
		log(fatal,"invalid specification of dfs mode!");
		abort();
	}
	if (mode==preorder){
		visit_node(n);
	}
	for (auto n_next:n->adj){
		dfs(mode,n_next);
	}

	if (mode==postorder){
		visit_node(n);
	}
}
void graphBase::dfs(dfs_option mode){
	log(info,"Starting DFS");
	dfs(mode,root);
	log(info,"Finishing DFS");
}
void graphBase::visit_node(std::shared_ptr<const node> n)
{
	std::stringstream ss;
	ss<<"Visiting node "<<n->name<<", val "<<n->val;
	log(info,ss.str());
}	
	
int main()
{
	//initializing a graph
	/*
	a->b->d
	|
	c
	*/
	np_t a=std::make_shared<node>("a");
	np_t b=std::make_shared<node>("b");
	np_t c=std::make_shared<node>("c");
	np_t d=std::make_shared<node>("d");
	
	a->adj=vector<np_t>({b,c});
	b->adj=vector<np_t>({d});
	
	vector<double> price={1,5,8,9,10,17,17,20,24,30};
	rod_cutting algo(price);
	
	longest_subsequence algo1("ABCBDAB","BDCABA");
	algo1.solve();
	
	const vector<int> dim={30,35,15,5,10,20,25}; //6 matrices
	//matrix_mult_parenthesis algo2(dim);
	//algo2.solve();
	matrix<int> m(3,4,0);
	cout<<m<<endl;
	return 0;
}
