/*
in this file we are going to read the graph and convert it into sat input
the first thing i will do is to make node sorted with degree and all that
the adjacency list will be made and the matrix of edges also
*/
#include<bits/stdc++.h>
#include<iostream>
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
	fstream infile;
	int c,n,m,e,p;
	string s;
	string h = convertToString(argv[1]);
	//create stream from arguments
	infile.open((h + ".satoutput").c_str());
	fstream tempfile;
	tempfile.open("temp.txt");
	tempfile >> n;
	tempfile >> m;
	ofstream outfile;
	outfile.open((h +".mapping").c_str());
	infile >> s;
	if (s == "UNSAT"){
		outfile << 0;
	}
	else{
		infile >> c;
		while(c != 0){
			if (c > 0){
				e = (int)(c/n) + 1;
				p = (int)(c%n);
				if(p == 0){
					p = n;
					e = e - 1;
				}
				outfile << e << " "<< p <<'\n';
			}
			infile >> c;	
		}
	}
	infile.close();
	outfile.close();
	tempfile.close();
}
