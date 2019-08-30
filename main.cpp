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
		int cost_action(){
			int c[v+1][max_lenght];
			std::vector< std::vector<int> > c1;
			c1.assign(v+1, vector<int>());
			for (int j = 0; j <= k; j ++){
				for(int i = 0; i < max_lenght; i++){
					c[j][i] = 0;
				}
			}
			for (int i = 0; i < k ; i++){
				int l = 0;
				std::vector<int>::iterator a;
				for (std::vector<int>::iterator it = output[i].begin() ; it != output[i].end(); ++it){
					
					
					c[*it][l] = c[*it][l] + 1;
					l = l + 1;
					
					
				}
			
			}
			//now we have repeatance cost matrix just need to find cost
			int ans = 0; 
			for (int i = 0; i < max_lenght; i++){
				for(int j = 0; j <= v ; j++){
					for (int l = j; l <=v ; l++){
						ans = ans + cost[j][l]*c[l][i]*c[j][i];
					}
				}
			}
			return(ans);
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
	int ans = e.cost_action();
	cout << "this is a "<< ans;
	/*std::vector<int> c1;
	c1.assign(3,1);
	std::vector<int>::iterator i = c1.begin();
	cout << c1[0] << endl;
	i = i + 1;
	cout << c1[1]<<endl;
	i = i + 1;
	i = i + 1;
	cout << c1[2] << endl;
	cout << (i == c1.end());*/
}


