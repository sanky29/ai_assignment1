/*
in this file we are going to read the graph and convert it into sat input
the first thing i will do is to make node sorted with degree and all that
the adjacency list will be made and the matrix of edges also
*/
#include<bits/stdc++.h>
using namespace std;
string convertToString(char* a) 
{ 
    int size = strlen(a); 
    string s = ""; 
    for (int i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 
int main(int argc , char **argv){
	
	//declare the filestream
	fstream infile;
	
	//the two int i will read
	//the input c1 c2 shows there is edge between c1 -> c2 
	int c1,c2;
	c1 = -1;
	
	string h = convertToString(argv[1]);
	
	h.append(".graphs");
	
	//create stream from arguments
	infile.open(h.c_str());

	//the vector of nodes
	vector<int> phoned;
	
	//the vector of nodes
	vector<vector<int> > phonee;
	
	//the vector of nodes
	vector<int> emaild;
	
	//the vector of nodes
	vector<vector<int> > emaile;

	//now read the second int and first
	infile >> c1;
	infile >> c2;
	//while there is int do read the file
	while(c1 != 0){	
		//the int y
		int y = max(c1,c2);
		
		//lets check wether this nodes are in current range or not
		int z = y - phonee.size();
			
		//check the z
		if(z > 0){
			//just run for loop
			//this loop reshape edge matix
			//first row wise thencolomunwise
			for(int i = 0 ; i < phonee.size(); i++){
				vector<int> temp = vector<int>(z,0);
				phonee[i].insert(phonee[i].end(), temp.begin(), temp.end());
			}
			//this one do columnwise
			//also extend the row
			for(int j = 0 ; j < z; j++){
				phonee.push_back(vector<int>(y,0));
				phoned.push_back(0);
			}
		}
		//now add info
		phonee[c1-1][c2-1] = 1;
		phoned[c1-1] = phoned[c1-1] + 1;
		
		//now read the second int and first
		infile >> c1;
		infile >> c2;
	}
	//while there is int do read the file
	
	while(infile >> c1){
		
		//now read the second int
		infile >> c2;
		
		//the int y
		int y = max(c1,c2);
		
		//lets check wether this nodes are in current range or not
		int z = y - emaile.size();
			
		//check the z
		if(z > 0){
			//just run for loop
			//this loop reshape edge matix
			//first row wise thencolomunwise
			for(int i = 0 ; i < emaile.size(); i++){
				vector<int> temp = vector<int>(z,0);
				emaile[i].insert(emaile[i].end(), temp.begin(), temp.end());
			}
			//this one do columnwise
			//also extend the row
			for(int j = 0 ; j < z; j++){
				emaile.push_back(vector<int>(y,0));
				emaild.push_back(0);
			}
		}
		emaile[c1-1][c2-1] = 1;
		emaild[c1-1] = emaild[c1-1] + 1;
}

	infile.close();
	//now we have read the graph and now just work on it
	//first we have 
	//first find the total number of clauses
	int n = phonee.size();
	int m = emaile.size();
	cout << n << " "<<m<<endl;
	int t = m + (int)(n*(n-1)*m/2);
	int c = 0;
	for(int i = 0 ; i < n; i++){
		if (phoned[i] == 0){
			c = c + 1;
		}
	}
		cout << c<<endl;
		c = 0;
	for(int i = 0 ; i < m; i++){
		if (emaild[i] == 0){
			c = c + 1;
		}
	}
	cout << c<<endl;
	//open stream to out file
	ofstream outfile;
	
	string h2 = convertToString(argv[1]);
	h2.append(".satinput");
	outfile.open(h2.c_str());
	ofstream tempfile;
	tempfile.open("temp.txt");
	tempfile << n << " "<<m;
	outfile << "p cnf "<< (n*m) << " "<< t <<'\n';
	tempfile.close();
	//now write the clauses as follows
	int mapping = n*m;
	
	for(int i = 0; i < m; i++){
		for(int j = 1; j <= n ; j++){
			if(phoned[j-1] < emaild[i]){
				outfile <<"-" <<(i*n+j)<<" 0\n";
			}
		}
	}
	cout <<"one part done"<<endl;
	//just write the clauses of atleast one true
	for(int i = 0 ; i < m ; i++){
		for(int j = 1; j <= n ; j++){
			if(phoned[j-1] >= emaild[i]){
			outfile <<(i*n + j)<< " ";}
		}
		outfile <<"0\n";
	}
	cout <<"two part done"<<endl;
	//no two assignment should true
	//just write the clauses of atleast one true
	for(int i = 0 ; i < m ; i++){
		for(int j = 1; j < n ; j++){
			for(int k = j+1; k <= n ; k++){
					if(phoned[j-1] >= emaild[i] && phoned[k-1] >= emaild[i]){
						outfile <<"-"<<(i*n + j)<<" -"<<(i*n + k)<<" 0\n";
				}
			}
		}	
	}
	cout <<"three part done"<<endl;
	//the two phone will not have same mail
	for(int i = 1 ; i <= n ; i++){
		for(int j = 0; j < m -1 ; j++){
			for(int k = j+1; k < m ; k++){
				if(phoned[i-1] >= emaild[j] && phoned[i-1] >= emaild[k]){
						outfile <<"-"<<(j*n + i)<<" -"<<(k*n + i)<<" 0\n";
				}
			}	
		}
	}
	c = 0;
	for(int i = 1 ; i < mapping; i++){
	
		int eo = (int)(i/n) + 1;
		int po = (int)(i%n);
		if(po == 0){
				po = n;
				eo = eo - 1;
			}
		if(emaild[eo] > phoned[po]){
			c = c + 1;
		}
}
cout << c <<endl;
	cout <<"four part done"<<endl;
	//now also need to work on the degree
	//no equal degree dont work on it
	int eo, e1,po,p1;
	//now the degree one are here
	for(int i = 1 ; i < mapping; i++){
		eo = (int)(i/n) + 1;
		po = (int)(i%n);
		if(po == 0){
				po = n;
				eo = eo - 1;
			}
		if(emaild[eo] <= phoned[po]){
			for(int j = i+1 ; j <= mapping; j++){
				
				e1 = (int)(j/n) + 1;
				p1 = (int)(j%n);
				if(p1 == 0){
					p1 = n;
					e1 = e1 - 1;
				}
				if(emaild[e1] <= phoned[p1]){
					if(phonee[po-1][p1 - 1] != emaile[eo - 1][e1 - 1] || phonee[p1-1][po - 1] != emaile[e1 - 1][eo - 1]){
						if (po != p1 && eo != e1){
							outfile << "-" << i <<" -"<< j<<" 0\n";	
						}
					}
				}
			}
		}
	}
	outfile.close();
}
