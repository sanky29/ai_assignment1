#include<bits/stdc++.h>
using namespace std;
class environment{
	//whole class will be public only
	public:
  		 
		//int number of characters visited
		int visited;
		
		//the no of characters
		int v;
		
		//the number of strings
		int k;
		
		//possible characters
		std::vector<char> poschar;
		
		//current position od dashes
		std::vector<std::vector<int> > pos;
		
		//the given strings which are converted to 2D char array
		std::vector<std::vector<int> > input;
		
		//the current string
		std::vector<std::vector<int> > current;
		
		//the value state as
		int value;
		
		//the cost matrix
		std::vector<std::vector<int> > cost;
		
		//define constructor
		environment(int k1,int v1){
			k = k1;
			v = v1;
		}
		
		
		
		//this function computes the cost from given start
		//lets say you take action 
		std::vector<int> choose_action(){
			int comp = 0;
			std::vector<int> best;
			for (int j = 0; j < pos.size(); j++){
				if (pos[j][1] + 1 < current.size()){
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
						intial = intial + cost[current[row][column]][current[i][column]] + cost[current[row][column_new]][current[i][column_new]]; 
						final = final + cost[current[row][column_new]][current[i][column]] + cost[current[row][column]][current[i][column_new]]; 
					}
					if (comp > final - intial){
						comp = final - intial;
						best = action;
					}
				}
				if (pos[j][1] - 1 >= 0){
					std::vector<int> action;
					action.push_back(pos[j][0]);
					action.push_back(pos[j][1]);
					action.push_back(-1);
					int intial = 0;
					int final = 0;
					int row = action[0];
					int column = action[1];
					int column_new = column + action[2]; 
					for (int i = 0; i < k ; i++){
						intial = intial + cost[current[row][column]][current[i][column]] + cost[current[row][column_new]][current[i][column_new]]; 
						final = final + cost[current[row][column_new]][current[i][column]] + cost[current[row][column]][current[i][column_new]]; 
					}
					if (comp > final - intial){
						comp = final - intial;
						best = action;
					}
				}
			}
			if (comp == 0){
				std::vector<int> x;
				x.push_back(-1);
				return(x);
			}
			else{
				return(best);
			}
		}
		
		//int take the action action 
		int take_action(std::vector<int> action){
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
};


int main(int argc, char **argv){
	string inp = argv[1];
	string out = argv[2];
    int time, V, K, CC, h;
	string chars, Kelem, chars2;
    ifstream inFile;
    
    inFile.open(inp);
    
    inFile >> time;
	inFile >> V;

    
	std::vector<char> Vs;
	int i=0, count=0;
	while(i<V) //read number, ignore comma, repeat
	{
		inFile>>chars;
		Vs.push_back(chars[0]);
		cout<<"chars are "<<chars[0]<<endl;
		i++;
	}
	inFile >> K;
    environment e(V,K);
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

	inFile.close();//---------------------------------------------------------------------------------------------------------------		
	e.current.assign(2, std::vector<int>());
	int z[] = {0,1,2};
	e.current[0].assign(z,z+3);
	z[0] = 1;
	z[1] = 2;
	z[2] = 3;
	e.current[1].assign(z,z+3);
	e.pos.assign(1,std::vector<int>());
	e.pos[0].push_back(1);
	e.pos[0].push_back(2);
	e.cost.assign(4, std::vector < int >());
	int x[] = {0,2,2,1};
	e.cost[0].assign(x,x+4);
	x[0] = 2;
	x[1] = 0;
	x[2] = 2;
	x[3] = 1;
	e.cost[1].assign(x,x+4);
	x[0] = 2;
	x[1] = 2;
	x[2] = 0;
	x[3] = 1;
	e.cost[2].assign(x,x+4);
	x[0] = 1;
	x[1] = 1;
	x[2] = 1;
	x[3] = 1;
	e.cost[3].assign(x,x+4);
	e.render();
	cout << " the solution is"<<endl;
	e.take_action(e.choose_action());
	e.take_action(e.choose_action());
	e.render();
}

