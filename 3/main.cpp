/*
in this file we are going to read the graph and convert it into sat input
the first thing i will do is to make node sorted with degree and all that
the adjacency list will be made and the matrix of edges also
*/
#include<bits/stdc++.h>
#include<iostream>
using namespace std;

int main(int argc , char **argv){
	
	//declare the filestream
	fstream infile;
	
	//the two int i will read
	//the input c1 c2 shows there is edge between c1 -> c2 
	int c1,c2;
	c1 = -1;
	
	string h = argv[1];
	//create stream from arguments
	infile.open( h + ".graph");
	
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
	//now we have read the graph and now just work on it
	//first we have 
	//first find the total number of clauses
	int n = phonee.size();
	int m = emaile.size();
	int t = m + (int)(n*(n-1)*m/2);
	
	//open stream to out file
	ofstream outfile;
	outfile.open(h + ".satinput");
	ofstream tempfile;
	tempfile.open("temp.txt");
	tempfile << n << " "<<m;
	outfile << "p cnf "<< (n*m) << " "<< t <<'\n';
	
	//now write the clauses as follows
	int mapping = n*m;
	
	//just write the clauses of atleast one true
	for(int i = 0 ; i < m ; i++){
		for(int j = 1; j <= n ; j++){
			outfile <<(i*n + j)<< " ";
		}
		outfile <<"0\n";
	}
	//no two assignment should true
	//just write the clauses of atleast one true
	for(int i = 0 ; i < m ; i++){
		for(int j = 1; j < n ; j++){
			for(int k = j+1; k <= n ; k++){
				outfile <<"-"<<(i*n + j)<<" -"<<(i*n + k)<<" 0\n";
			}	
		}
	}
	//the two phone will not have same mail
	for(int i = 1 ; i <= n ; i++){
		for(int j = 0; j < m -1 ; j++){
			for(int k = j+1; k < m ; k++){
				outfile <<"-"<<(j*n + i)<<" -"<<(k*n + i)<<" 0\n";
			}	
		}
	}
	//now also need to work on the degree
	//no equal degree dont work on it
	int eo, e1,po,p1;
	//now the degree one are here
	for(int i = 1 ; i < mapping; i++){
		for(int j = i+1 ; j <= mapping; j++){
			eo = (int)(i/n) + 1;
			e1 = (int)(j/n) + 1;
			po = (int)(i%n);
			p1 = (int)(j%n);
			if(po == 0){
				po = n;
				eo = eo - 1;
			}
			if(p1 == 0){
				p1 = n;
				e1 = e1 - 1;
			}
			
			if(phonee[po-1][p1 - 1] != emaile[eo - 1][e1 - 1] || phonee[p1-1][po - 1] != emaile[e1 - 1][eo - 1]){
				if (po != p1 && eo != e1){
					outfile << "-" << i <<" -"<< j<<" 0\n";	
				}
			}
		}
	}
}
