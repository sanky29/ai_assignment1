#include <bits/stdc++.h>
using namespace std;

/*
lets define struct which has following fields
	NAME: name of card holder
	IS_LUHNA: is it luhna 10 number 
	BALACNE: the available balane in it
	LIMIT: the maximum limit
*/

struct CARD{
	
	string NAME;
	bool IS_LUHNA;
	int BALANCE;
	int LIMIT;
};

/*
the function to identify the given number is luhan or not
*/
bool LUHNA(string N){
	
	int C = N.length();
	int TOTAL = 0;
	int TEMP;
	for(int i = 0; i < C; i++){
		
		TEMP = (int)(N[C - i - 1]) - (int)('0');
		if(i%2 == 0){
			TOTAL = TEMP + TOTAL;
		}
		else{
			TEMP = 2*TEMP;
			TOTAL = TOTAL + int(TEMP/10) + TEMP%10;
		}
	}
	return((TOTAL % 10 == 0)); 
}

/*
we will define the class database which will store the data and work on queries
the following function we need
	ADD_CARD(string NAME, string CARD_NO, int LIMIT): add card to database
	CREDIT_CARD(string NAME, int CREDIT_AMOUNT): substract amount from balance by checking IS_LUHNA 
	CHARGE_CARD(string NAME, int CHARGE_AMOUNT ): add amount to balane by checking IS_LUHNA and LIMIT
*/

class DATABASE{
	
	public:
		
		map<string, CARD> DATA;
		
		void ADD_CARD(string NAME, string CARD_NO, int LIMIT){
			CARD NEW_CARD = {NAME,LUHNA(CARD_NO),0,LIMIT};
			DATA.insert(pair<string,CARD>(NAME,NEW_CARD));
		}
		
		void CHARGE_CARD(string NAME, int CHARGE_AMOUNT){
			CARD TEMP = DATA[NAME];
			if(TEMP.IS_LUHNA  && TEMP.BALANCE + CHARGE_AMOUNT > TEMP.LIMIT){
				DATA[NAME].BALANCE =  DATA[NAME].BALANCE + CHARGE_AMOUNT;
			}
		}
		
		void CREDIT_CARD(string NAME, int CREDIT_AMOUNT){
			CARD TEMP = DATA[NAME];
			if(TEMP.IS_LUHNA){
				DATA[NAME].BALANCE =  DATA[NAME].BALANCE - CREDIT_AMOUNT;
			}
		}
		DATABASE(){
		}
};
int main(int argc, char** argv){
	DATABASE DB;
	ifstream INFILE;
	INFILE.open(argv[1]);
	string LINE;
	string T;
	stringstream SS;
	while(!INFILE.eof()){
		getline(INFILE,LINE);
		SS.str(LINE);
		SS >> T;
		if(T.compare("Add") == 0){
			SS>>T;
			string NAME = T;
			SS>>T;
			string NO = T;
			SS>>T;
			T.erase(0,1);
			int L = stoi(T);
			DB.ADD_CARD(NAME,NO,L);
		}
		else if(T.compare("Charge") == 0){
			SS>>T;
			string NAME = T;
			SS>>T;
			T.erase(0,1);
			int L = stoi(T);
			DB.CHARGE_CARD(NAME,L);
		}
		else{
			SS>>T;
			string NAME = T;
			SS>>T;
			T.erase(0,1);
			int L = stoi(T);
			DB.CREDIT_CARD(NAME,L);
		}
	}
	
	for (std::map<string,CARD>::iterator it=DB.DATA.begin(); it!=DB.DATA.end(); ++it){
		
		if(it->second.IS_LUHNA){
    		cout << it->first << ": $" << it->second.BALANCE << endl;
    	}
    	else{
    		cout << it->first << ": error"<<endl;
		}
	}
}
