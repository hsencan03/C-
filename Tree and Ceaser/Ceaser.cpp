#include <iostream>
#include <string>
#include "Ceaser.h"
string Ceaser::Encrypt(string text,int count){
	for(int i=0;i<count;i++){
		for(int j=0;j<text.length();j++){
			if(isalpha(tolower(text[j]))){
				if(text[j]=='z')
					text[j]='a';
				else
					text[j]++;
			}
		}
	}
	text+=to_string(count);
	return text;
}
string Ceaser::Decrypt(string text){
	int key;
	int size;
	try{
		key=stoi(text.substr(text.length()-2,2));
		text=(text.substr(0,text.length()-2));
	}
	catch(...){
		key=stoi(text.substr(text.length()-1,1));
		text=(text.substr(0,text.length()-1));
	}
	for(int i=0;i<text.length();i++){
		if(isalpha(text[i])){
			if(text[i]-key<97)
				text[i]=122-key+(text[i]-96);
			else
				text[i]-=key;
		}
	}
	return text;
}
