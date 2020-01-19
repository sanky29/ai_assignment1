#include<iostream>
#include<vector>
//making class of environment to impliment the problem as ai serach problem
using namespace std;

class environment {
 
 	//whole class will be public only
	public:
  		 
		//int number of characters visited
		int visited;
		
		//the no of characters
		int v;
		
		//the number of strings
		int k;
		
		//maintain the max int
		int max_lenght;
		
		//possible characters
		std::vector<char> poschar;
		
		//current position
		std::vector<int> pos;
		
		//the given strings which are converted to 2D char array
		std::vector<std::vector<int> > input;
		
		//the current string
		std::vector<std::vector<int> > current;
		
		//the stack of actions
		std::vector<std::vector<int> > output;
		
		//the value state as
		int value;
		
		//the cost matrix
		std::vector<std::vector<int> > cost;
		
		//define constructor
		environment(int k1,int v1){
			k = k1;
			v = v1;
		}
		
		//check action a
		void check_action_a(vector<int> action){
			for (int i = 0 ; i < k ; i++){
				if (action[i] = 0){
					output[i].insert(output[i].begin() + pos[i], v+1);  
				}
			}
				
		}
		
		
		//this function computes the cost from given start
		//lets say you take action 
		int cost_action(vector<int> start){
			
			
		}	
};

int main(){
	environment e(2,2);
	std::vector<int> x;
	e.output.push_back(x);
	std::vector<int> y;
	e.output.push_back(y);
	e.output[0].push_back(0);
	e.output[0].push_back(1);
	e.output[1].push_back(1);
	e.output[1].push_back(0);
	int z[] = {0,2,1};
	e.cost.assign(3, vector < int >());
	e.cost[0].assign(z,z+3);
	z[0] = 2;
	z[1] = 0;
	z[2] = 1;
	e.cost[1].assign(z,z+3);
	z[0] = 1;
	z[1] = 1;
	z[2] = 1;
	e.cost[2].assign(z,z+3);
	e.max_lenght = 2;
	std::vector<int> t;
	t.push_back(0);
	t.push_back(1);
	int ans = e.cost_action(t);
	cout << "this is a "<< ans;
	
}



