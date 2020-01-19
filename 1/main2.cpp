#include<bits/stdc++.h>
using namespace std;


class environment{
	//whole class will be public only
	public:
		
		//the max lenght of input
		int max_lenght;
		
		//the no of characters
		int v;
		
		//the best cost till now
		int best_cost;
		
		//the best state
		std::vector< std::vector<int> > best_state;
		
		//the number of strings
		int k;
		
		//the cost of dashes
		int cc;
		
		//possible characters
		std::vector<char> poschar;
		
		//current position od dashes
		std::vector<std::vector<int> > pos;
		
		//the given strings which are converted to 2D char array
		std::vector<std::vector<int> > input;
		
		//the current string
		std::vector<std::vector<int> > current;
		
		//this stores the privious state
		std::vector<std::vector<int> > previous;
		
		//the cost matrix
		std::vector<std::vector<int> > cost;
		
		//define constructor
		environment(int k1,int v1){
			k = k1;
			v = v1;
			best_cost = INT_MAX;
		}
		
		
		
		//this function computes the cost from given start
		//lets say you take action 
		std::vector<int> choose_action(){
			int comp = 0;
			std::vector<int> best;
			for (int j = 0; j < pos.size(); j++){
				if (pos[j][1] + 1 < current.size() && current[pos[j][0]][pos[j][1] + 1] != v){
					std::vector<int> action;
					action.push_back(pos[j][0]);
					action.push_back(pos[j][1]);
					action.push_back(1);
					action.push_back(j);
					int intial = 0;
					int final = 0;
					int row = action[0];
					int column = action[1];
					int column_new = column + action[2]; 
					for (int i = 0; i < k ; i++){
						if (row != i){
	
						intial = intial + cost[current[row][column]][current[i][column]] + cost[current[row][column_new]][current[i][column_new]]; 	
						final = final + cost[current[row][column_new]][current[i][column]] + cost[current[row][column]][current[i][column_new]]; 
						}
					}
					if (comp >= final - intial){
						int temp = current[action[0]][action[1]];
						std::vector<vector<int> > temp2;
						temp2 = current;
						temp2[action[0]][action[1]] = current[action[0]][action[1]+action[2]];
						temp2[action[0]][action[1]+ action[2]] = temp;
						if (temp2 != previous){
							comp = final - intial;
							best = action;
						}
					}
					
				}
				else if (pos[j][1] - 1 >= 0 && current[pos[j][0]][pos[j][1] - 1] != v){
					
					std::vector<int> action;
					action.push_back(pos[j][0]);
					action.push_back(pos[j][1]);
					action.push_back(-1);
					action.push_back(j);
					int intial = 0;
					int final = 0;
					int row = action[0];
					int column = action[1];
					int column_new = column + action[2];
					for (int i = 0; i < k ; i++){	
						
						if (row != i){
							
							intial = intial + cost[current[row][column]][current[i][column]] + cost[current[row][column_new]][current[i][column_new]]; 
							final = final + cost[current[row][column_new]][current[i][column]] + cost[current[row][column]][current[i][column_new]];
						}
					}
					
					if (comp >= final - intial){
						
						int temp = current[action[0]][action[1]];
						std::vector<vector<int> > temp2;
						temp2 = current;
						temp2[action[0]][action[1]] = temp2[action[0]][action[1]+action[2]];
						temp2[action[0]][action[1]+ action[2]] = temp;
						if (temp2 != previous){
							comp = final - intial;
							best = action;
						}
					}
			}
		}
		return(best);
	}
		//int take the action action 
		void take_action(std::vector<int> action){
			previous = current;
			int temp = current[action[0]][action[1]];
			current[action[0]][action[1]] = current[action[0]][action[1]+action[2]];
			current[action[0]][action[1]+ action[2]] = temp;
			pos[action[3]][1] = pos[action[3]][1] + action[2];
		}
		void render(){
			for (int i = 0; i < current.size() ; i ++){
				for (int j = 0; j < current[0].size(); j++){
					cout << current[i][j] << " ";
				}
				cout << endl;
			}
		}
		
	void random(int l){
		current = input;
		std::vector<vector <int> >pos1; 
		for (int i = 0; i < k ; i++){
			for (int j = 0; j < l - input[i].size() ; j++){
				int z = rand() %(current[i].size());
				std::vector<int> temp;
				temp.push_back(i);
				temp.push_back(z);
				current[i].insert(current[i].begin() + z, v);
				pos1.push_back(temp);
			}
		}
		pos = pos1;
	}
	int cost_state(){
		int repeat[v+1][max_lenght];
		for (int i = 0 ; i < v+1 ; i++){
			for(int j = 0; j < max_lenght; j++){
				repeat[i][j] = 0;
			}
		}
		for (int i = 0; i < max_lenght ; i++){
			for (int j = 0; j < k; j++){
				repeat[current[j][i]][i] = repeat[current[j][i]][i] + 1;
			}
		}
		int ans = 0;
		for(int j = 0; j < max_lenght; j++){
			for(int i = 0; i <= v ; i ++){
				for (int o = j + 1; o <= v ; o++){
					ans = ans + cost[i][o]*repeat[i][j]*repeat[o][j];
				}
			}
		}
		ans  = ans + pos.size()*cc;
		return(ans);
	}		
};

int main(){
	environment e(3,4);
	e.input.assign(3, std::vector<int>());
	int z[] = {0,1,3,2,3,2,0};
	e.input[0].assign(z,z+7);
	z[0] = 3;
	z[1] = 0;
	z[2] = 1;
	z[3] = 3;
	z[4] = 2;
	z[5] = 1;
	e.input[1].assign(z,z+6);
	z[0] = 0;
	z[1] = 1;
	z[2] = 3;
	z[3] = 2;
	z[4] = 0;
	e.input[2].assign(z,z+5);
	e.random(7);
	cout << "the starting condition is " << endl;
	e.render();
	cout << "----------------------------------------------------------------"<<endl << endl;
	e.cost.assign(5, std::vector < int >());
	int x[] = {0,2,2,2,1};
	e.cost[0].assign(x,x+5);
	x[0] = 2;
	x[1] = 0;
	x[2] = 2;
	x[3] = 2;
	x[4] = 1;
	e.cost[1].assign(x,x+5);
	x[0] = 2;
	x[1] = 2;
	x[2] = 0;
	x[3] = 2;
	x[4] = 1;
	e.cost[2].assign(x,x+5);
	x[0] = 2;
	x[1] = 2;
	x[2] = 2;
	x[3] = 0;
	x[4] = 1;
	e.cost[3].assign(x,x+5);
	x[0] = 1;
	x[1] = 1;
	x[2] = 1;
	x[3] = 1;
	x[4] = 1;
	e.cost[4].assign(x,x+5);
	e.max_lenght = 8;
	e.cc = 3;
	for (int i = 0 ; i < 1000 ; i ++){
		std::vector<int> temp = e.choose_action();
		if (temp.begin() == temp.end()){
			int x = e.cost_state();
			cout<< "we have reached the local mimimum and the cost is " << x<<endl;
			e.render();
			cout <<  "----------------------------------------------------------------"<<endl << endl;
			if (e.best_cost > x){
				e.best_state = e.current;
				e.best_cost = x;
			}
			e.random(8);
			cout << "the new state is with cost "<< e.cost_state()<<endl;
			e.render();
			cout <<  "----------------------------------------------------------------"<<endl << endl;
		}
		else{
			e.take_action(temp);
		}
	}
	e.current = e.best_state;
	cout << "the best state is with cost " << e.cost_state()<<endl;
	e.render();
	
	
}


