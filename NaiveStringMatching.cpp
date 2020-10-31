#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;
void NaiveAlgo(vector<char> gi,char *pattern);

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
			ss>>numbers;	
			for(int j=0;j<50;j++){
				if(numbers.size()!='\0'){
					gi.push_back(numbers[j]);
				}
			}k++;
		}
	}
	NaiveAlgo(gi,pattern);
	return 0;
}

void NaiveAlgo(vector<char> gi,char *pattern){
    ofstream newfile;
	newfile.open("results.txt",std::ios_base::app);
	
	newfile<<"..........This is Naive String Matching Algorithm..........\n"<<endl;
	newfile<<"\nBirthday pattern is : 970520\n"<<endl;
	int count=0;
	int text=gi.size();
	int match=strlen(pattern);
	
	for(int k=0;k<=text-match;k++){
		int l;
		for(l=0;l<match;l++){
			if(gi[k+l]!=pattern[l])
			    break;
			}
		if(l==match){
			count++;
			newfile<<"Pattern found at index :"<<k<<endl;
		}	
	}
	newfile<<"\nNumber of matchings are : "<<count<<endl;
	newfile.close();
}
