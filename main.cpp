<<<<<<< HEAD
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



=======
#include<bits/stdc++.h>
#include<fstream>
using namespace std;


class environment{
	//whole class will be public only
	public:
		
		//the max length of input
		int max_length;
		
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
		
		//the best length
		int best_length;
		
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
			max_length = 0;
		}
		
		
		
		//this function computes the cost from given start
		//lets say you take action 
		std::vector<int> choose_action(){
			//the comparative cost
			int comp = 0;
			
			//the current best action
			std::vector<int> best;
			
			//the loop on each dash
			for (int j = 0; j < pos.size(); j++){
				
				//moving dash to right
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
				//checking dash movement to left
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
		
		//shows current state of environment
		void render(){
			for (int i = 0; i < current.size() ; i ++){
				for (int j = 0; j < current[0].size(); j++){
					cout << current[i][j] << " ";
				}
				cout << endl;
			}
		}
	
	//taking random restart	
	void random(int l){
		current = input;
		std::vector<vector <int> >pos1; 
		for (int i = 0; i < k ; i++){
			for (int j = 0; j < l - input[i].size() ; j++){
				int z = rand() %(current[i].size()) + 1;
				std::vector<int> temp;
				temp.push_back(i);
				temp.push_back(z);
				current[i].insert(current[i].begin() + z, v);
				pos1.push_back(temp);
			}
		}
		pos = pos1;
	}
	
	//function to compute cost
	int cost_state(){
		int repeat[v+1][max_length];
		for (int i = 0 ; i < v+1 ; i++){
			for(int j = 0; j < max_length; j++){
				repeat[i][j] = 0;
			}
		}
		for (int i = 0; i < max_length ; i++){
			for (int j = 0; j < k; j++){
				repeat[current[j][i]][i] = repeat[current[j][i]][i] + 1;
			}
		}
		int ans = 0;
		for(int j = 0; j < max_length; j++){
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

//the main function
int main(int argc, char **argv){	
	
	//define time variable
	time_t t;
	t = time(NULL);
	//input output file
	string inp = argv[1];
	string out = argv[2];
	
	//reading file
    int tm, V, K, CC, h;
	string chars, Kelem, chars2;
    ifstream inFile;
    
    
    inFile.open(inp);
    
    inFile >> tm;
	inFile >> V;
	tm = tm*60;
    
	std::vector<char> Vs;
	int i=0, count=0;
	while(i<V) //read number, ignore comma, repeat
	{
		inFile>>chars;
		Vs.push_back(chars[0]);
	
		i++;
	}
	inFile >> K;
    environment e(K,V);
	i=0;
	while(i<V){
		e.poschar.push_back(Vs[i]);
		i++;
	}
	int val, j=0;
	e.input.assign(K, std::vector<int>());
	while(j<K){
		inFile >> Kelem;
		i=0;
		
		while(i<Kelem.length()){
			h=0;
			while(h<V){
				if(Kelem[i]==e.poschar[h]){
					break;	
				}
				h++;
			}
			e.input[j].push_back(h);
			i++;	
		}
		j++;
	}

	inFile >> CC;	
	
	
	e.cost.assign(V+1, std::vector<int>());
	for(int j=0; j<V+1; j++){
		i=0;
		while(i<V+1) //read number, ignore comma, repeat
		{
    		inFile>>Kelem;
			stringstream conv(Kelem);
			conv>>h;
			e.cost[j].push_back(h);
			
			i++;
		}
	}

	inFile.close();
	
	//calculating max length
	for (int i = 0 ; i < e.input.size(); i ++){
		if (e.max_length < e.input[i].size()){
			e.max_length = e.input[i].size();
		}
	}
	
	//assigning constant cost
	e.cc = CC;
	
	//working on the l
	//taking on average over all l
	for (int i = 0 ; i <= 3 ; i ++){
		
		//intialize the state
		e.random(e.max_length + i);
		
		//now work on iterations
		
		for (int j = 0; j < 10000; j++){
			//choosing action
			std::vector<int> temp = e.choose_action();
			
			if (temp.begin() == temp.end()){
				
				int x = e.cost_state();
				
				if (e.best_cost > x){
					
					e.best_state = e.current;
					e.best_cost = x;
					e.best_length = i + e.max_length;
				}
				
				e.random(e.max_length + i);
			
			}
		
			else{
				
				e.take_action(temp);
			}
		}
	}
	e.random(e.best_length);
	tm = tm - 3;
	while(time(NULL) - t < tm){
		//choosing action
		std::vector<int> temp = e.choose_action();
			
		if (temp.begin() == temp.end()){
							
			int x = e.cost_state();
				
			if (e.best_cost > x){
					
				e.best_state = e.current;
				e.best_cost = x;
			}
				
			e.random(e.best_length);
			
		}
		
		else{
				
			e.take_action(temp);
		}
	}
	e.current = e.best_state;

	ofstream outdata; // outdata is like cin
	e.poschar.push_back('-');
	outdata.open(out); // opens the file
	for (int i = 0; i < e.current.size() ; i ++){
				for (int j = 0; j < e.current[0].size(); j++){
					outdata << e.poschar[e.current[i][j]];
				}
				outdata << endl;
		}
	outdata.close();
}

>>>>>>> ccf200a286fbd790e7e13cb13c3e6afd52882340
