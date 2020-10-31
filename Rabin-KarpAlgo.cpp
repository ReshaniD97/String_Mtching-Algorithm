#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include<vector>
#include<math.h>
using namespace std;

void Rabin_KarpAlgo(vector<char> gi, char* pattern, int primeNum);

int main(){
	vector<char> gi;
	string line,numbers;
	ifstream newfile;
	char pattern[]="970520";
	newfile.open("pi.txt");
	if(!newfile.is_open()){
		cout<<"error"<<endl;
	}
	while(!newfile.eof()){
		getline(newfile,line);
		int k=0;
		if(isdigit(line[k])){
			for(int i=0,len=line.size();i<len;i++){
				if(!isalnum(line[i])){
					if(line[i]==':'){
						line.erase(i--,1);
						len=line.size();
						break;
					}
					line.erase(i--,1);
					len=line.size();
				}
			} 
		    stringstream ss(line);
			ss>> numbers ;	
			for(int j=0;j<50;j++){
				if(numbers.size()!='\0'){
					gi.push_back(numbers[j]);
				}
			}k++;
		}
	}
	int primeNum=11;
	Rabin_KarpAlgo(gi,pattern,primeNum);
	return 0;
}

void Rabin_KarpAlgo(vector<char> gi, char* pattern, int primeNum){
	
	ofstream newfile;
	newfile.open("results.txt",std::ios_base::app);
	
	newfile<<"\n..........This is Rabin karp Algorithm..........\n"<<endl;
	newfile<<"\nBirthday pattern is : 970520\n"<<endl;
	int text=gi.size();
	int match=strlen(pattern);
	int patternHash=0, textHash=0;
	int h,d=10;
	int j,i; 
	int count=0;

	h=pow(d,match-1);
	h=h%primeNum;
	
	for(i=0;i<match;i++){
		patternHash=(d*patternHash+pattern[i])%primeNum; //hash value of pattern
		textHash=(d*textHash+gi[i])%primeNum;    //hash value of first window
	}
	//check the matching
	for(i=0;i<=text-match;i++){
		if(patternHash==textHash){
			for(j=0;j<match;j++){
				if(gi[i+j]!=pattern[j])
				    break;
			}
			if(j==match){
				newfile<<"Pattern found at index :"<<i<<endl;
			    count=count+1;
			}
		}
		if(i<text-match){       //fing hash value of next window
			textHash=(d*(textHash-gi[i]*h)+gi[i+match])%primeNum;
			if(textHash<0)     //negative value of textHash cinverting it positive
			    textHash=(textHash+primeNum);
		}
	}
	newfile<<"\nNumber of patterns are : "<<count<<endl;
	newfile.close();
	
}
