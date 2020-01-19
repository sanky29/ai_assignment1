#include<iostream>;
using namespace std;
int main(int argv, char* argc[]){
int x = 280;
char* p = (char*) &x;
printf("%d\n", *p);
}
