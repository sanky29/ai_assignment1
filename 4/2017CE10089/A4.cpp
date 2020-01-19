#include <bits/stdc++.h>


// Format checker just assumes you have Alarm.bif and Solved_Alarm.bif (your file) in current directory
using namespace std;

// Our graph consists of a list of nodes where each node is represented as follows:
class Graph_Node{
private:
	string Node_Name;  // Variable name 
	vector<int> Children; // Children of a particular node - these are index of nodes in graph.
	vector<string> Parents; // Parents of a particular node- note these are names of parents
	int nvalues;  // Number of categories a variable represented by this node can take
	vector<string> values; // Categories of possible values
	vector<float> CPT; // conditional probability table as a 1-d array . Look for BIF format to understand its meaning

public:
    vector<pair<int,int>> parent_num;
    int self_num;
	// Constructor- a node is initialised with its name and its categories
    Graph_Node(string name,int n,vector<string> vals)
	{
		Node_Name=name;
	
		nvalues=n;
		values=vals;
		

	}
	string get_name()
	{
		return Node_Name;
	}
	vector<int> get_children()
	{
		return Children;
	}
	vector<string> get_Parents()
	{
		return Parents;
	}
	vector<float> get_CPT()
	{
		return CPT;
	}
	int get_nvalues()
	{
		return nvalues;
	}
	vector<string> get_values()
	{
		return values;
	}
	void set_CPT(vector<float> new_CPT)
	{
		CPT.clear();
		CPT=new_CPT;
	}
    void set_Parents(vector<string> Parent_Nodes)
    {
        Parents.clear();
        Parents=Parent_Nodes;
    }
    void set_parent_num(vector<pair<int,int>> vec){
        parent_num.clear();
        parent_num= vec;
    }
    void set_self(int i){
        self_num= i;
    }
    // add another node in a graph as a child of this node
    int add_child(int new_child_index )
    {
        for(int i=0;i<Children.size();i++)
        {
            if(Children[i]==new_child_index)
                return 0;
        }
        Children.push_back(new_child_index);
        return 1;
    }



};


 // The whole network represted as a list of nodes
class network{


public:
    list <Graph_Node> Pres_Graph;
	int addNode(Graph_Node node)
	{
		Pres_Graph.push_back(node);
		return 0;
	}
    
    
	int netSize()
	{
		return Pres_Graph.size();
	}
    // get the index of node with a given name
    int get_index(string val_name)
    {
        list<Graph_Node>::iterator listIt;
        int count=0;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            if(listIt->get_name().compare(val_name)==0)
                return count;
            count++;
        }
        return -1;
    }
// get the node at nth index
    list<Graph_Node>::iterator get_nth_node(int n)
    {
       list<Graph_Node>::iterator listIt;
        int count=0;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            if(count==n)
                return listIt;
            count++;
        }
        return listIt; 
    }
    //get the iterator of a node with a given name
    list<Graph_Node>::iterator search_node(string val_name)
    {
        list<Graph_Node>::iterator listIt;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            if(listIt->get_name().compare(val_name)==0)
                return listIt;
        }
    
            cout<<"node not found\n";
        return listIt;
    }
	// void initialise(){
 //        list<Graph_Node>::iterator listit;
 //        for(listit=Pres_Graph.begin();listit!=Pres_Graph.end();listit++){
 //            float n=listit->get_nvalues();
 //            vector<float> set;
 //            for(int i=0;i<listit->get_CPT().size();i++){
 //                float temp;
 //                temp= 1/n;
 //                // cout<<temp<<"hi";
 //                set.push_back(temp);
 //            }
 //            listit->set_CPT(set);
 //        }
 //    }
    void update(map<string,int> mp, map<string,Graph_Node*> mp1){
        list<Graph_Node>::iterator it;
        int self_n;
        for(it= Pres_Graph.begin(); it!=Pres_Graph.end();it++){
            self_n= mp.find(it->get_name())->second;
            // cout<<"self_n"<<self_n<<" ";
            it->set_self(self_n);
            vector<pair<int,int>> par;
            vector<string> vec=it->get_Parents();
            for(int i=0;i<vec.size();i++){
                int temp=mp.find(vec[i])->second;
                Graph_Node* nd= (mp1.find(vec[i])->second);
                pair<int,int> pp;
                pp.first= temp;
                pp.second= nd->get_nvalues();
                par.push_back(pp);
            }
            // cout<<"par"<<par.size()<<" ";
            it->set_parent_num(par);
        }
    }
};

network read_network(string dname)
{
	network Alarm;
	string line;
	int find=0;
  	ifstream myfile(dname); 
  	string temp;
  	string name;
  	vector<string> values;
  	
    if (myfile.is_open())
    {
    	while (! myfile.eof() )
    	{
    		stringstream ss;
      		getline (myfile,line);
      		
      		
      		ss.str(line);
     		ss>>temp;
     		
     		
     		if(temp.compare("variable")==0)
     		{
                    
     				ss>>name;
     				getline (myfile,line);
                   
     				stringstream ss2;
     				ss2.str(line);
     				for(int i=0;i<4;i++)
     				{
     					
     					ss2>>temp;
     					
     					
     				}
     				values.clear();
     				while(temp.compare("};")!=0)
     				{
     					values.push_back(temp);
     					
     					ss2>>temp;
    				}
     				Graph_Node new_node(name,values.size(),values);
     				int pos=Alarm.addNode(new_node);

     				
     		}
     		else if(temp.compare("probability")==0)
     		{
                    
     				ss>>temp;
     				ss>>temp;
     				
                    list<Graph_Node>::iterator listIt;
                    list<Graph_Node>::iterator listIt1;
     				listIt=Alarm.search_node(temp);
                    int index=Alarm.get_index(temp);
                    ss>>temp;
                    values.clear();
     				while(temp.compare(")")!=0)
     				{
                        listIt1=Alarm.search_node(temp);
                        listIt1->add_child(index);
     					values.push_back(temp);
     					
     					ss>>temp;

    				}
                    listIt->set_Parents(values);
    				getline (myfile,line);
     				stringstream ss2;
                    
     				ss2.str(line);
     				ss2>> temp;
                    
     				ss2>> temp;
                    
     				vector<float> curr_CPT;
                    string::size_type sz;
     				while(temp.compare(";")!=0)
     				{
                        
     					curr_CPT.push_back(atof(temp.c_str()));
     					
     					ss2>>temp;
                       
                        

    				}
                    
                    listIt->set_CPT(curr_CPT);


     		}
            else
            {
                
            }
     		
     		

    		
    		
    	}
    	
    	if(find==1)
    	myfile.close();
  	}
  	
  	return Alarm;
}
vector<vector<string>> read_dataset(int n,network &Alarm,string recordname){
    ifstream myfile(recordname);
    string line,st;
    vector<vector<string>> dat;
    while (! myfile.eof()){
        vector<string> temp;
        getline(myfile,line);
        stringstream ss;
        ss.str(line);
        int i=0;
        for(list<Graph_Node>::iterator nodeit= Alarm.Pres_Graph.begin();nodeit!=Alarm.Pres_Graph.end();nodeit++){
            ss>>st;
            Graph_Node node= *nodeit;
            for(int z=0;z<node.get_nvalues();z++){
                if(node.get_values()[z].compare(st)==0){
                    st=to_string(z);
                    break;
                }
                else if(st.compare("?")==0){
                    break;
                }
            }
            temp.push_back(st);
        }
        dat.push_back(temp);
        temp.clear();
        i+=1;
    }
    return dat;
}
float compute(network &Alarm,int k,int i,vector<vector<string>> &data, map<string,Graph_Node*> &mp, map<int,string> &mp1, Graph_Node &node1){
    list<Graph_Node>::iterator it;
    float val=1;
    for(it=Alarm.Pres_Graph.begin();it!=Alarm.Pres_Graph.end();it++){
        Graph_Node node= *it;
        vector<float> cpt= node.get_CPT();
        int ind=0;
        int num_par= node.parent_num.size();
        int count=1;
        for(auto ze=node.parent_num.rbegin(); ze!= node.parent_num.rend();ze++){
            int a=ze->first,b=ze->second;
            if(data[i][a].compare("\"?\"")==0){
                ind+= count*k;
            }
            else{
                ind+= count*stoi(data[i][a]);
            }
            count=count*b;
        }
        if(data[i][node.self_num].compare("\"?\"")==0){
            ind+=count*k;
        }
        else{
            ind+=count*stoi(data[i][node.self_num]);
        }
        val*= cpt[ind];
    }
    return val;
}
void ealgo(network &Alarm, vector<vector<string>> &data, int n, map<string,Graph_Node*> &mp, map<int,string> &mp1){
    // vector<vector<string>>::iterator it;
    for(int j=0;j<data.size();j++){
        vector<string> temp= data[j];
        for(int i=0;i<n;i++){
            if(temp[i].compare("\"?\"")==0){
                Graph_Node* node= (mp.find(mp1.find(i)->second)->second);
                vector<float> val;
                for(int k=0;k<node->get_nvalues();k++){
                    val.push_back(compute(Alarm,k,i,data,mp,mp1,*node));
                }
                float exp=0,su=0;
                for(int k=0;k<node->get_nvalues();k++){
                    exp+=k*val[k];su+=val[k];
                }
                exp/=su;
                int max=round(exp);
                data[j][i]= to_string(max);
            }
        }
    }
}
void malgo(network &Alarm, vector<vector<string>> &data){
    // cout<<"helllllll";
    for(auto it=Alarm.Pres_Graph.begin();it!=Alarm.Pres_Graph.end();it++){
        int siz=data.size();
        vector<float> cpt2=it->get_CPT();
        for(int q=0;q<cpt2.size();q++){
            cpt2[q]=0.01;
        }
        int count3=0;
        for(int x=0;x<siz;x++){
            int count= it->parent_num.size(),count2=1;
            int ind=0;
            // cout<<it->parent_num.size();
            for(auto i=it->parent_num.rbegin();i!= it->parent_num.rend();i++){
                // cout<<x<<" "<<i->first;
                ind+= count2*stoi(data[x][i->first]);
                count2*=(i->second);
            }
            ind+= count2*stoi(data[x][it->self_num]);
            cpt2[ind]+=1;
            count3=count2;
        }
        siz+=cpt2.size();
        // count3/= it->get_nvalues();
        for(int in=0;in<count3;in++){
            float sum=0;
            float cnt=0;
            for(int i=in;i<cpt2.size();i+=count3){
                sum+=cpt2[i];
                cnt++;
            }
            for(int i=in;i<cpt2.size();i+=count3){
                cpt2[i]= fmax(0.01,fmin(0.99,cpt2[i]/(sum)));
            }
        }
        // for(int q=0;q<cpt2.size();q++){
        //     cpt2[q]= cpt2[q]/siz;
        // }
        it->set_CPT(cpt2);
    }
}
void initial(network &Alarm, vector<vector<string>> &data){
    // cout<<"helllllll";
    for(auto it=Alarm.Pres_Graph.begin();it!=Alarm.Pres_Graph.end();it++){
        int siz=data.size();
        vector<float> cpt2=it->get_CPT();
        for(int q=0;q<cpt2.size();q++){
            cpt2[q]=0.01;
        }
        int count3=0;
        for(int x=0;x<siz;x++){
            int count= it->parent_num.size(),count2=1;
            int ind=0;
            // cout<<it->parent_num.size();
            for(auto i=it->parent_num.rbegin();i!= it->parent_num.rend();i++){
                // cout<<x<<" "<<i->first;
                if(data[x][i->first].compare("\"?\"")!=0){
                    ind+= count2*stoi(data[x][i->first]);
                }
                else{
                    ind+=count2*(rand()%(i->second));
                }
                count2*=(i->second);
            }
            if(data[x][it->self_num].compare("\"?\"")!=0){
                ind+= count2*stoi(data[x][it->self_num]);
            }
            else{
                ind+=count2*(rand()%it->get_nvalues());
            }
            cpt2[ind]+=1;
            count3=count2;
        }
        siz+=cpt2.size();
        // count3/= it->get_nvalues();
        for(int in=0;in<count3;in++){
            float sum=0;
            float cnt=0;
            for(int i=in;i<cpt2.size();i+=count3){
                sum+=cpt2[i];
                cnt++;
            }
            for(int i=in;i<cpt2.size();i+=count3){
                cpt2[i]= fmax(0.01,fmin(0.99,cpt2[i]/(sum)));
            }
        }
        // for(int q=0;q<cpt2.size();q++){
        //     cpt2[q]= cpt2[q]/siz;
        // }
        it->set_CPT(cpt2);
    }
}
map<string,Graph_Node*> create_map(network &Alarm){
    map<string,Graph_Node*> mp;
    list<Graph_Node>::iterator it;
    for(it=Alarm.Pres_Graph.begin();it!=Alarm.Pres_Graph.end();it++){
        pair<string,Graph_Node*> pp;
        pp.first= it->get_name();
        pp.second= &(*it);
        mp.insert(pp);
    }
    return mp;
}
map<int,string> create_map1(network &Alarm){
    map<int,string> mp;
    list<Graph_Node>::iterator it;
    int v=0;
    for(it=Alarm.Pres_Graph.begin();it!=Alarm.Pres_Graph.end();it++){
        Graph_Node node= *it;
        mp.insert(pair<int,string>(v,node.get_name()));
        v++;
    }
    return mp;
}
map<string,int> create_map2(network &Alarm){
    map<string,int> mp;
    list<Graph_Node>::iterator it;
    int v=0;
    for(it=Alarm.Pres_Graph.begin();it!=Alarm.Pres_Graph.end();it++){
        Graph_Node node= *it;
        mp.insert(pair<string,int>(node.get_name(),v));
        v++;
    }
    return mp;
}
void print(vector<vector<string>> data){
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[0].size();j++){
            cout<<data[i][j]<<" ";
        }
        cout<<endl;
    }
}
void printcpt(network Alarm){
    int co=1;
    for(auto i=Alarm.Pres_Graph.begin();i!=Alarm.Pres_Graph.end();i++){
        vector<float> vec= i->get_CPT();
        cout<<"count- "<<co<<endl;
        co++;
        for(int j=0;j<vec.size();j++){
            cout<<vec[j]<<" ";
        }
        cout<<endl;
    }
}
void writetofile(network &Alarm, string filename){
    ofstream outfile;
    outfile.open("solved_alarm.bif", ios::out | ios::trunc );
    ifstream myfile(filename);
    string line;
    list<Graph_Node>::iterator it= Alarm.Pres_Graph.begin();
    while( !myfile.eof()){
        getline(myfile,line);
        if(!(line[0]=='p' && line[3]=='b')){
            if(line.length()!=0)
                outfile<<line<<endl;
        }
        else{
            outfile<<line<<endl;
            outfile<<"    table ";
            vector<float> temp=it->get_CPT();
            for(int i=0; i<temp.size();i++){
                outfile<<setprecision(4)<< temp[i]<<" ";
            }
            outfile<<";"<<endl;
            getline(myfile,line);
            it++;
        }
    }
    outfile<<endl;
    outfile.close();
    myfile.close();
}
int main(int argc, char **argv)
{
    // cout<<"yes";
	network Alarm;
	Alarm=read_network(argv[1]);
    int var= Alarm.netSize();
    vector<vector<string>> data=read_dataset(var,Alarm,argv[2]);

    map<string,Graph_Node*> mp=create_map(Alarm);
    map<int,string> mp1= create_map1(Alarm);
    map<string,int> mp2= create_map2(Alarm);
    // cout<<"yay";
    Alarm.update(mp2,mp);
    initial(Alarm,data);
    // print(data);
    // printcpt(Alarm);
    clock_t begin = clock();
    clock_t end = clock();
    int t=1;
    while((float(end-begin)/CLOCKS_PER_SEC) <100){
        // cout<<"hi";
        ealgo(Alarm,data,var,mp,mp1);
        // print(data);
        cout<<"Iter- "<<t<<endl;
        t++;
        malgo(Alarm,data);
        // cout<<t;
        end=clock();
    }
// Example: to do something
    // print(data);
    // printcpt(Alarm);
    writetofile(Alarm, argv[1]);
	cout<<"Perfect! Hurrah! \n";
	
}