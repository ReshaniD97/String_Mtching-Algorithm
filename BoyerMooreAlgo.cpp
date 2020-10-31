#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include<vector>
#define maxChar 256
using namespace std;
void BoyerMooreAlgo(vector<char> gi,char* pattern);
void badCharHeuristic(char* pattern,int match,int* badChar);

int main(){
	vector<char> gi;
	string line,numbers;
	int line_no=0,len,count=0;
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
	
    BoyerMooreAlgo(gi,pattern);
	return 0;
}

void BoyerMooreAlgo(vector<char> gi,char* pattern){
	
	ofstream newfile;
	newfile.open("results.txt",std::ios_base::app);
	
	newfile<<"\n..........This is Boyer-Moore String Matching Algorithm..........\n"<<endl;
	newfile<<"\nBirthday pattern is : 970520\n"<<endl;
	int text=gi.size();
	int match=strlen(pattern);
	int badChar[maxChar];
	
	badCharHeuristic(pattern,match,badChar);
	
	int s=0,count=0;
	
	while(s<=(text-match)){
		int j=match-1;
		while(j>=0 && pattern[j]==gi[s+j]){    //right to lefet search
			j--;
		}
			
		if(j<0){
			newfile<<"pattern found at index : "<<s<<endl;
			count++;
			s+=(s+match<text)?match-badChar[gi[s+match]]:1;
		}
		else
		   s+=max(1,j-badChar[gi[s+j]]);
	}
	newfile<<"\nNumber of patterns are : "<<count<<endl;
	newfile.close();
}
void badCharHeuristic(char* pattern,int match,int* badChar){
	int i=0,j=0;
	while(i<maxChar){
		badChar[i]=-1;
		i++;
	}
	while(j<match){
		badChar[(int)pattern[j]]=j;
		j++;
	}
}
