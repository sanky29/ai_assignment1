#include<bits/stdc++.h>
using namespace std;


class environment{
	//whole class will be public only
	public:
		
		//the max lenght of input
		int max_lenght;
		
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
		
		//this stores the privious state
		std::vector<std::vector<int> > previous;
		
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

	inFile.close();
	cout << "the new state is   "<<endl;
	e.random(8);
	cout << "the local search begins !!!!"<<endl;
	for (int i = 0 ; i < 100 ; i ++){
		std::vector<int> temp = e.choose_action();
		if (temp.begin() == temp.end()){
			cout<< "we have reached the local mimimum "<<endl;
			e.render();
			cout <<  "----------------------------------------------------------------"<<endl << endl;
			e.random(8);
			cout << "the new state is "<<endl;
			e.render();
			cout <<  "----------------------------------------------------------------"<<endl << endl;
		}
		else{
			e.take_action(temp);
		}
	}
}

