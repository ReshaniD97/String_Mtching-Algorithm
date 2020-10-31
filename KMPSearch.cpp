#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

void KMPsearch(vector<char> gi,char *pattern);
void calculateLPSArray(char* pattern, int match, int* lps);

int main(){
	vector<char> gi;
	string line,numbers;
	string year,month,day,birthday;
	
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
	KMPsearch(gi,pattern);
	return 0;
}

void KMPsearch(vector<char> gi,char *pattern){
	ofstream newfile;
	newfile.open("results.txt",std::ios_base::app);
	
	newfile<<"\n..........This is KMP Algorithm..........\n"<<endl;
	newfile<<"\nBirthday pattern is : 970520\n"<<endl;
	int match=strlen(pattern);
	int text=gi.size();
	
	int lps[match];   //That will hold the longest prefix suffix, values for pattern
	calculateLPSArray(pattern,match,lps);
	int count=0;
	int i=0; //index for gi
	int j=0; //index for pattern
	
	while(i<text){     //matching using KMPsearch algorithm
		if(pattern[j]==gi[i]){
			j++;
			i++;
		}
		if(j==match){
			newfile<<"Pattern found at index :"<<i-j<<endl;
			j=lps[j-1];
			count++;
		}
		else if(pattern[j]!=gi[i]){       
			if(j!=0)
			   j=lps[j-1];
			else
			   i=i+1;
		}
	}
	newfile<<"\nNumber of matchings are:"<<count<<endl;
    newfile.close();	
}

void calculateLPSArray(char* pattern, int match, int* lps){
	int length=0;
	lps[0]=0;
	int i=1;
	while(i<match){
		if(pattern[i]==pattern[length]){
			length++;
			lps[i]=length;
			i++;
		}
		else{
			if(length!=0){
				length=lps[length-1];
			}
			else{           //length=0
				lps[i]=0;
				i++;
			}
		}
	}
	
}
