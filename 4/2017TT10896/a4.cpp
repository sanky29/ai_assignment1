#include <bits/stdc++.h>



// Format checker just assumes you have Alarm.bif and Solved_Alarm.bif (your file) in current directory
using namespace std;

// Our graph consists of a list of nodes where each node is represented as follows:
//now given node can have multiple parents and children
//each node will have vector to its parent and children as follows
class node{

	//make everything public
	public:
	
		//the name of the node is follows
		string name;
		
		//the pointer vector to children
		vector<node*> children;
		
		//the vector of parents as follows
		vector<node*> parents;
		
		//the number of categories as follows
		int nvalues;
		
		//the vector of possible catagories values
		vector<string> values;
		
		//the conditional table of probabilities
		vector<double> cpt;
		
		//the helper vector is
		vector<int> cpt_help;
		
		//we will also need the id of the node as
		int id;
	
		// Constructor- a node is initialised with its name and its categories
	    node(string name1,int n,vector<string> vals)
		{   
			name=name1;
			nvalues=n;
			values=vals;
		}
	
		//the constructor to just declare variable
		node(){
		}
		
		//the functions from here
	    // add another node in a graph as a child of this node
	    int add_child(node* new_child){
	    	
			//check if child already exist or not
	        for(int i=0; i<children.size(); i++){
	        	
	        	//if children already exist then
	            if(children[i]->name == new_child->name){
	                return 0;}
	        }
	        
	        //if this code is executed it means there is no child so just add at end
	        children.push_back(new_child);
	        return 1;
	    }
	    
	    // add another node in a graph as a child of this node
	    int add_par(node* new_par){
	    	
			//check if child already exist or not
	        for(int i=0; i<parents.size(); i++){
	        	
	        	//if children already exist then
	            if(parents[i]->name == new_par->name){
	                return 0;}
	        }    
	        //if this code is executed it means there is no child so just add at end
	        parents.push_back(new_par);
	        return 1;
	    }
};


// The whole network represted as a list of nodes
//it will execute simple functuon as adding node
//the inteferance and all that things 
class network{

	//everything is public
	public:
		
		//the vector of all nodes as
		vector <node*> graph_node;
		
    	// get the index of node with a given name
    	node* get_node(string val_name){
    		
    		//just run for loop as
        	for(int i = 0; i <= graph_node.size(); i++){	
        		
        		//check the name
        	    if(graph_node[i]->name.compare(val_name) == 0){
        	    	//just return the value
        	        return graph_node[i];
        		}
        	}
        	//else just return int
        	cout << "the node not found"<<endl;
        	return NULL;
    	}
    
    	//define function to add node
    	// get the index of node with a given name
    	int add_node(node* new_node){
    		
    		//the intial ans
    		int ans = -1;
    		
    		//define temp string as
    		string temp = new_node->name;
    		
    		//run the loop and check if already exist or not
        	for(int i = 0; i < graph_node.size(); i++){	
        	
        		//check the name
        	    if(graph_node[i]->name.compare(temp) == 0){
        	    	
					//ans update
					ans = i;
					
					//break here
					break;
        		}
        	}
    		//check ans as
    		if(ans == -1){
    			
    			//the id of new node will be
    			new_node->id = graph_node.size();
    			
    			//just push back the thing
    			graph_node.push_back(new_node);
			}
        	//return the ans
        	return ans;
    	}
    	//write function to infer
    	int infer(vector<int> e, int x){
    		
    		//we have to find probability x gven e
    		//now we will assume x to be one thing and one by one compute all thing
    		double t = 0.0;
    		
    		//now work on each one
    		vector<double> ans;
    	
    		//the temporary varaible
    		node temp = *(graph_node[x]);    		
    		//run for loop
    		for(int i = 1; i < temp.nvalues; i++){
    			
    			//the probability
    			double po = 1.0;
    			
				//set the node as
    			e[x] = i;
    			
    			//now go for the position as
    			int pos = e[x]*temp.cpt_help[0];
				 	
    			//now the parent loop
    			for(int j = 0 ; j < temp.parents.size(); j++){
    				
    				//run on cpt help as
    				pos = pos + e[temp.parents[j]->id]*temp.cpt_help[j+1];
				}
				
				//the po will be
				po = po*temp.cpt[pos];
				
				//now for child as
				for(int l = 0; l < temp.children.size(); l++){
					
					//just go for its parent as
					node temp2 = *(temp.children[l]);
					
					//now go for the position as
	    			int pos = e[l]*temp2.cpt_help[0];
					 	
	    			//now the parent loop
	    			for(int j = 0 ; j < temp2.parents.size(); j++){
	    				
	    				//run on cpt help as
	    				pos = pos + e[temp2.parents[j]->id]*temp2.cpt_help[j+1];
					}
					
					//the po will be
					po = po*temp2.cpt[pos];
				}
				ans.push_back(po);
				t = t + po;
			}
			double z = 0.0;
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			//just divide each thing by po as
			double max_prob = -1.0;
			int g = 0;
			for(int i = 0 ; i < ans.size(); i++){
				if(max_prob < ans[i]){
					max_prob = ans[i];
					g = i;
					
				}
			}
			return (g);
		}
		//write function to infer
    	int infer2(vector<int> e, int x){
    		
    		//we have to find probability x gven e
    		//now we will assume x to be one thing and one by one compute all thing
    		double t = 0.0;
    		
    		//now work on each one
    		vector<double> ans;
    	
    		//the temporary varaible
    		node temp = *(graph_node[x]);
    		
    		//run for loop
    		for(int i = 0; i < temp.nvalues; i++){
    			
				//another temporary variable
    			double po = 1.0;
    			
				//change e[x]
				e[x] = i;
				
				//defien the pos as
				int pos = e[x]*temp.cpt_help[0];
				
				//now run for loop as
				for(int j = 0 ; j < temp.parents.size(); j++){
					
					//now change pos as
					pos = pos + e[temp.parents[j]->id]*temp.cpt_help[j+1];
					
				}
				//now change po as
				po = po*temp.cpt[pos];
				
				//just go to children an calaculate the thing
				for(int k = 0 ; k < temp.children.size(); k++){
						
						//define new temp as and temporary variables
						node temp2 = *(temp.children[k]);
						int y = temp2.id;
						
						//now just run the for loop for all its parent
						//defien the pos as
						int pos = e[y]*temp2.cpt_help[0];
						
						//now run for loop as
						for(int j = 0 ; j < temp2.parents.size(); j++){
							
							//now change pos as
							pos = pos + e[temp2.parents[j]->id]*temp2.cpt_help[j+1];
							
						}
						//now change po as
						po = po*temp2.cpt[pos];
						
					}
					//now just push to ans as
					ans.push_back(po);
					t = t + po;
			}
			double z = 0.0;
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			//just divide each thing by po
			for(int i = 0 ; i < ans.size(); i++){
				z = z + (ans[i]/t);
				if(r > z){
					
					return(i);
				}
			}
			return(ans.size()-1);
		}
};

//write function to read network as
network read_network(string y){
	
	//first declare the network as
	network Alarm;
	
	//the temporary line to read
	string line;
	
	//first open the file as
  	ifstream myfile(y); 
	ofstream outfile("solved_alarm.bif");
	
  	
	//this are temporary variables as follows
	//temp : the first word of node
	//name : the varaible name
  	string temp;
  	string name;
  	vector<string> values;
  	bool x = true;
  	//start reading the file as
    if (myfile.is_open()){
    	
    	//while the file is open and have content
    	while (! myfile.eof() ){
    		
    		//defuine the string stream as follows
    		stringstream ss;
    		
    		//copy content to line
      		getline (myfile,line);
      		ss.str(line);
      		
      		//the first word as follows
     		ss>>temp;
    		
    		//if first word is variable then it is new node
     		if(temp.compare("variable")==0){  
			 	x = true;                  
  				outfile << line<<'\n';
  				//the next word is name of node
				ss>>name;
				
				//now read the next line as
 				getline (myfile,line);
 				outfile << line<<'\n';
 				//now our line contain element under variable line
 				//define new string stream as
 				//this is to read the parantheses and keywords
   				stringstream ss2;
   				
   				//ss2 will split the words
				ss2.str(line);
				
				//the first three words are useless like type, discrete, }
				//so just read them and store them in temp
				for(int i=0; i<4; i++){
		    		ss2>>temp;		
				}
				
				//now cclear the old values
    			values.clear();
    			
				//the possible values will till "};" appeares
     			while(temp.compare("};")!=0){
     				
     				//just push temp to value and read new pne
     				values.push_back(temp);	
					ss2>>temp;
   				}
   				
   				//neew to add the node to graph
   				//define memory block to it and update it
   				node *new_node = new node();
				*new_node = node(name,values.size(),values);
				
				//the position of new_node
 				int pos=Alarm.add_node(new_node);
    		}
    		
    		//now if the first word is probability then
     		else if(temp.compare("probability")==0){
     			x = false;
     			//this one is '('
     			ss>>temp;
     			
     			//this one is varaible name
     			ss>>temp;
     			
				//will need two iterator that will point to current and parent	
            	node* curr;
	            node* par;
	            
	            //the curr will be just finding in graph_node
     			curr = Alarm.get_node(temp);
     			
     			//the first parent
                ss>>temp;
                
                //define the parent vector as
        		vector<node*> parv;
        
                //run while loop as
    			while(temp.compare(")")!=0){
    				
    				//get parent node as and curr as child to it
                	par = Alarm.get_node(temp);
                	par->add_child(curr);
                	
					//now for current just add the parent to list
					parv.push_back(par);
					
					//read next parent as
    				ss>>temp;
   				}
   				
   				//set the parent of current as
                curr->parents = parv;
                
                //the temperory variables for cpt_help
                
				vector<int> e;
				if(parv.size() > 0){
					e = vector<int>(parv.size() + 1, 0);
					int tempi = 1;
					
					//now need to update cpt_help as
					for(int i = parv.size() - 1 ; i >= 0; i--){
						
						//just add tempi to cpt_help one
						e[i+1] = tempi;
						tempi = tempi*(parv[i]->nvalues);
					}
					e[0]= tempi;
	    			//now update cpt_help a
	    		}
	    		else{
	    			e = {1};
				}
    			curr->cpt_help = e;
    			
				//read the probability line	
				getline (myfile,line);
				
				//define local string steam as and split at space
    			stringstream ss2;    
     			ss2.str(line);
     			
     			//the first word is table and next start with probability
     			ss2>> temp;    
     			ss2>> temp;
                    
                //define current probability vector as and string to read float value
     			vector<double> curr_CPT;
                string::size_type sz;

                //now just read the values
     			while(temp.compare(";")!=0){
                    
					//add to curr_cpt    
     				curr_CPT.push_back(atof(temp.c_str()));
     				
					//read the next cpt value	
     				ss2>>temp;
    			} 
				//just change cpt of curr   
                curr->cpt = curr_CPT;
     		}
     		//else it is just propert one which we dont need
            else{
            	if(x){
 				outfile << line<<'\n';}}
    	}
    	myfile.close();
    	outfile.close();
  	}

  	return Alarm;
}

//now we need to learn data for that we have to learn it first
//i will save data as int 2d vector
tuple<vector<vector<int> >,vector<int> > read_data(network net, string da){
	
	//also need to keep track of pos of ?
	vector<int> unk;
	
	//define ans vector as
	vector<vector<int> > ans;
	
	//just opent the stream for data as
	fstream infile;
	
	//now open the file
	infile.open(da);

	//just define line as
	string line;
	
	//now run while loop till file is not end as
	while(! infile.eof()){
		
		//the anst vector as
		vector<int> anst;
		
		//now define temp string as
		string temp;
		
		//now define string stream as
		stringstream s;
		
		//now write get line function as
		getline(infile,line);
		
		//split at space
		s.str(line);
		
		//the counter as
		int c = 0;
		
		//for the c we have to do
		int iou = unk.size();
		
		//run while loop as
		while(s>>temp){
			
			//just define the graph node as
			vector<string> g = net.graph_node[c]->values;
			
			//the intial lenght of vector
			int intial = anst.size();
			
			//just compare the thing
			for(int l = 0 ; l < g.size(); l++){
				
				//now check the codition as
				if (temp.compare(g[l]) == 0){
					anst.push_back(l);
					break;
				}
			}
			
			//check if it is not "?" or not
			if(intial == anst.size()){
				anst.push_back(-1);
				unk.push_back(c);
			}
			//increase int by one
			c = c + 1;
		}
		//check if not any "?"
		if(iou == unk.size()){
			unk.push_back(-1);
		}
		
		//now just push back to the ans
		ans.push_back(anst);
	}
	tuple<vector<vector<int> >, vector<int> > y = make_tuple(ans,unk);
	return(y);
}

//now need to write function to learn
vector< vector<double> > learn(network net, 	vector< vector<int> > d){
		vector< vector<int> > data = d; 
	
	//now just need to create the counter variable 
	//this will be vector of all the probability distributions as
	vector< vector<double> >counter;
	
	//now initate it with 0
	for(int i = 0 ; i < net.graph_node.size(); i++){
		
		//just push back
		counter.push_back(vector<double>(net.graph_node[i]->cpt.size(), 0.1));
	}
		
	//the temporary variable as
	int n = data.size();
	int m = net.graph_node.size();
	
	//now just start the counting as
	for(int i = 0; i < n; i++){
	
		//now for each node
		for(int j = 0; j < m ; j++){
			
			//the helper variable function for pos as
			int pos = data[i][j]*(net.graph_node[j]->cpt_help[0]);
			int poo = 0;
			//now add all parents as
			for(int k = 0; k < net.graph_node[j]->parents.size(); k++){
				//just add to pos as
				poo = pos;
				pos = pos + (net.graph_node[j]->cpt_help[k+1])*(data[i][net.graph_node[j]->parents[k]->id]);
				
//				if(pos >= counter[j].size()){
//				cout << "j: "<<j<<" "<<endl;
//				cout<<"pos: "<<pos<<" "<<endl;
//				cout<<"poo: "<<poo<<" "<<endl;
//				cout<<"counter size thet is cpt size: "<< counter[j].size()<<" "<<endl;
//				cout<<"cpt help size that is paternt + 1: "<<net.graph_node[j]->cpt_help.size()<< " "<<endl;
//				cout<<"k+1: "<<k+1<<" "<<endl;
//				cout<<"cpt value at k+1: "<<net.graph_node[j]->cpt_help[k+1]<< " "<<endl;
//				cout<<"parent size: "<<net.graph_node[j]->parents.size()<<endl;
//				cout << "the id of parent: "<<net.graph_node[j]->parents[k]->id<<endl;
//				cout << "the name of parent: "<<net.graph_node[j]->parents[k]->name<<endl;
//				cout << data[i][net.graph_node[j]->parents[k]->id]<<endl;
//			}

			}
//			if(pos >= counter[j].size()){
//				cout<< "no"<<endl;
//				cout << j << " "<< pos<< " "<< counter[j].size();
//			}
			//now just add to counter[m][pos] 1
			counter[j][pos] = counter[j][pos] + 1;
		}
	}
	//now go for the probability one
	vector<vector<double> > ans;
	
	//go for each parent
	for(int i = 0; i < m; i++){
			
		//push ans as
		ans.push_back(vector<double>(counter[i].size(), 0.0));
		
		int v = net.graph_node[i]->cpt_help[0];
		//now count total samples and vctor
		vector<double> temp5 = vector<double>(net.graph_node[i]->nvalues, 0.0);
		vector<double> temp6 = vector<double>(v, 0.0);
		//now run for loop as
		if(v == 1){
			int c = 0;
			for(int j = 0 ; j < temp5.size(); j++){
				c = c + counter[i][j];
			}
			temp5[0] = c;
			for(int j = 0 ; j < temp5.size(); j++){
				ans[i][j] = counter[i][j]/temp5[0];
			}
		}
		else{
			for(int k = 0 ; k < v; k++){
				double c = 0.0;
				for(int j = 0; j < temp5.size() ; j++){
					c = c + counter[i][j*v+k];
				}
				temp6[k] = c;
				for(int j = 0; j < temp5.size() ; j++){
					ans[i][j*v+k] = counter[i][j*v+k]/temp6[k];
				}
			}
		}
		net.graph_node[i]->cpt = ans[i];
	}
	return(ans);
}
//now need to guess to overall data as

//write function to show graph as follows
void show(network x){
	
	//will work on how to show the graph
	//the title will be here now work as follows
	cout<<"-----------------------------------------------------------------------"<<endl;
	cout<<"|                       THE GRAPH INFORMATION IS HERE                 |"<<endl;
	cout<<"-----------------------------------------------------------------------"<<endl;
	cout<<"| number of nodes: "<<x.graph_node.size()<<"                                                 |"<<endl;
	cout<<"-----------------------------------------------------------------------"<<endl<<endl;
	
	//work on each node
	for (int i = 0; i <x.graph_node.size(); i++){
		
		//define the temporary node as
		node tn = *(x.graph_node[i]);
		
		//first print the name of node
		cout<< i <<". "<<"Name: "<<tn.name<<endl;
		
		//the possiible values are as
		cout<<"Values: ";
		for (int j = 0 ; j < tn.values.size(); j++){
			cout << tn.values[j]<<" ";
		}
		cout<<endl;
		
		//now the parents as
		cout<<"Parents: ";
		for (int j = 0 ; j < tn.parents.size(); j++){
			cout << tn.parents[j]->name<<" ";
		}
		cout<<endl;
		cout<<"-----------------------------------------------------------------------"<<endl;
	}                                     
}

//show the data as
void show_data(vector< vector<int> > x, int n){
	
	//will work on how to show the graph
	//the title will be here now work as follows
	cout<<"-------------------------------------------------------------------------"<<endl;
	cout<<"|                               THE DATA IS HERE                         |"<<endl;
	cout<<"-------------------------------------------------------------------------"<<endl;
	
	//just run for loop
	for(int i = 0; i < n; i++){
		cout << i <<". ";
		for(int j = 0 ; j < x[i].size(); j++){
			cout << x[i][j]<<" ";
		}
		cout <<endl;
		cout<<"-------------------------------------------------------------------------"<<endl;
	}
	
}
//write function to guess
vector<vector <int> > guess(network net, vector<vector<int> > d, vector<int> c){
	vector<vector<int> > data = d;
	srand (static_cast <unsigned> (time(0)));
	//just go and infer for the c[i] givent data[i]
	for(int i =0 ; i < data.size(); i++){
		
		//just change the thing
		if(c[i] > 0){
			data[i][c[i]] = net.infer(data[i],c[i]);
		}
	}
	return(data);
}
int error(network n, vector< vector<int> > x, vector<int> c){
	int p = 0;
	for(int i = 0; i < x.size(); i++){
		if(c[i] > 0){
			if(x[i][c[i]] == n.infer(x[i],c[i])){
				p = p +1;
			}
		}
	}
	return(p);
}
void showp(network x){
	
	//will work on how to show the graph
	//the title will be here now work as follows
	cout<<"-----------------------------------------------------------------------"<<endl;
	cout<<"|                       THE PROBA INFORMATION IS HERE                 |"<<endl;
	cout<<"-----------------------------------------------------------------------"<<endl;
	cout<<"| number of nodes: "<<x.graph_node.size()<<"                                                 |"<<endl;
	cout<<"-----------------------------------------------------------------------"<<endl<<endl;
	
	//work on each node
	for (int i = 0; i <x.graph_node.size(); i++){
		cout << i <<". ";
		vector<double> t = x.graph_node[i]->cpt;
		for(int j = 0 ; j < t.size(); j++){
			cout << t[j]<<" ";
		} 
		cout<<endl;                            
	}
}
int main(int argc, char** argv)
{
	network alarm;
	alarm = read_network("alarm.bif");
	tuple<vector<vector<int> >, vector<int>> y = read_data(alarm,"records.dat");
	vector<vector<int> > x = get<0>(y);
	vector<int> c = get<1>(y);
	//now create random input as
	for(int i = 0 ; i < c.size(); i++){
		if(c[i] >= 0){
			x[i][c[i]] = int (rand() % (alarm.graph_node[c[i]]->nvalues));
		}
	}
	vector< vector<double> > old = learn(alarm,x);
	vector< vector<double> > n = old;
	float e = 100.0;
	int z = 1;
	int zmax = 0;
	while(e > 0){
		vector<vector<int>> data = guess(alarm,x,c);
		old = n;
		cout <<"i am here"<<endl;
		n = learn(alarm,data);
		z = error(alarm,data,c);
		if(z > zmax){
			zmax = z;
		}
		e=e-1;
	}
	cout << zmax<<endl;
	int zold = 0;
	network ao = alarm;
	while(false){
		vector<vector<int>> data = guess(alarm,x,c);
		n = learn(alarm,data);
		zold = z;
		ao = alarm;
		z = error(alarm,data,c);
		cout << z<<" "<<zold<<" "<<zmax<<endl;
	}
	alarm = ao;
	ofstream outfile;
	outfile.open("solved_alarm.bif", std::ios_base::app);
	for(int i = 0 ; i < alarm.graph_node.size(); i++){
		outfile << "probability (  ";
		node temp = *(alarm.graph_node[i]);
		outfile << temp.name<<" ";
		for(int j = 0 ; j < temp.parents.size(); j++){
			outfile << temp.parents[j]->name<<" ";
		}
		outfile <<") { //"<<(1+temp.parents.size())<<" variable(s) and "<<temp.cpt.size()<<" values"<<'\n'<<"\ttable ";
		for(int j = 0 ; j < temp.cpt.size(); j++){
			double v = round( temp.cpt[j] * 10000.0 ) / 10000.0;
			outfile << v<<" ";
		}
		outfile<<";\n}\n";
		
	}
	outfile.close();
}
