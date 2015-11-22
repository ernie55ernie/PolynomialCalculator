#include<string>
#include<map>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include <fstream>

using namespace std;

bool isdigit(char c)
{
	if(c>='0' && c<='9')
		return true;
	return false;
}

bool isoperator(char c)
{
	if(c=='+' || c=='-' || c=='*' || c=='/')
		return true;
	return false;
}

class Polynomial{
public:
	int num;
	map <int,int> terms;
	Polynomial(){
	}
	Polynomial(string s){
		bool pos =  true;
		bool tri = false;
		int exp = 0;
		int coef = 0;
		for(int i = 0; i < s.length(); i++){
			if(s[i] == 'x'){
				tri = true;
			}else if(isdigit(s[i])){
				if(!tri)
					coef = coef * 10 + (s[i] - '0');
				else
					exp = exp * 10 + (s[i] - '0');
			}
			if(s[i] == '-' && i == 0){
				pos = false;
			} else if(s[i] == '-' || s[i] == '+' || i == s.length() - 1){
				int c = (coef == 0 && pos) ? 1 : 
					(coef == 0 && !pos ? -1: 
					(pos? coef : -coef));
				int e = tri ? (exp == 0 ? 1: exp) : 0;
				terms[e] = c;
				coef = 0;
				exp = 0;
				tri = false;
				pos = (s[i] == '-')? false : true;
			}
		}
		num = terms.size();
	}
	Polynomial(map <int,int> termsp){
		terms = termsp;
		num = terms.size();
	}
	void construct(string s){
	}
	void Print(){
		if(terms.empty())
			return;
		for (map<int,int>::reverse_iterator it=terms.rbegin(); it!=terms.rend(); ++it){
			string o = " ";
			string c = "";
			if(it!=terms.rbegin()){
				if(it->second >= 0){
					o = " +";
				}else if(it->second == -1){
					o = " -";
				}
			}
			if((it->second == 1 || it->second == -1) && it->first != 0)
				c = "";
			else{
				char str[15];
				sprintf(str, "%d", it->second);
				c = string(str) + "*";
			}
			string e = "";
			if(it->first == 0)
				e = "";
			else if(it->first == 1){
				e = "x";
			}else{
				char str[15];
				sprintf(str, "%d", it->first);
				e = string(str);
				e = "x^" + e;
			}
			cout << o << c << e;
		}
		//cout << endl;
	}
	Polynomial Add(Polynomial b){
		map<int,int> mapb = b.terms;
		for (map<int,int>::iterator it=mapb.begin(); it!=mapb.end(); ++it){
			if(terms[it->first]){
				terms[it->first] = terms[it->first] + it->second;
			}else{
				terms[it->first] = it->second;
			}
		}
		num = terms.size();
		return *this;
	}
	Polynomial Sub(Polynomial b){
		map<int,int> mapb = b.terms;
		for (map<int,int>::iterator it=mapb.begin(); it!=mapb.end(); ++it){
			if(terms[it->first]){
				terms[it->first] = terms[it->first] - it->second;
			}else{
				terms[it->first] = - it->second;
			}
		}
		num = terms.size();
		return *this;
	}
	Polynomial Mul(Polynomial b){
		map<int,int> mapb = b.terms;
		map<int,int> newTerm;
		for (map<int,int>::iterator it=mapb.begin(); it!=mapb.end(); ++it){
			for (map<int,int>::iterator itt=terms.begin(); itt!=terms.end(); ++itt){
				int c = it->second * itt->second;
				int e = it->first + itt->first;
				if(newTerm[e]){
					newTerm[e] = newTerm[e] + c;
				}else{
					newTerm[e] = c;
				}
			}
		}
		terms = newTerm;
		num = newTerm.size();
		return *this;
	}
	Polynomial Div(Polynomial b){
		map<int,int> mapb = b.terms;
		map<int,int> qTerm;
		
		map<int,int>::reverse_iterator it;
		for(it=terms.rbegin(); it!=terms.rend(); ++it){
			if(it->second == 0)continue;
			int c = it->second / mapb.rbegin()->second;
			int e = it->first - mapb.rbegin()->first;
			qTerm[e] = c;
			map<int,int>::reverse_iterator rit;
			for(rit=mapb.rbegin(); rit!=mapb.rend(); ++rit){
				if(terms[rit->first + e]){
					terms[rit->first + e] = terms[rit->first + e] - c * rit->second;
				}else{
					terms[rit->first + e] = - c * rit->second;
				}
			}
		}
		terms = qTerm;
		num = qTerm.size();
		return *this;
	}
};

int main()
{
	string s;
  ifstream myfile( "t2.txt" );
  if (myfile)  // same as: if (myfile.good())
    {
		  Polynomial b[2];
    while (getline( myfile, s ))  // same as: while (getline( myfile, line ).good())
      {
			cout << s << "\n";
			if(isoperator(s[0]) && s.length() == 1){
				switch(s[0]){
					case'+':
						b[0].Add(b[1]);
						b[1] = b[0];
						break;
					case'-':
						b[0].Sub(b[1]);
						b[1] = b[0];
						break;
					case'*':
						b[0].Mul(b[1]);
						b[1] = b[0];
						break;
					case'/':
						b[0].Div(b[1]);
						b[1] = b[0];
						break;
				}
				continue;
			}
			b[0] = b[1];
			Polynomial a(s);
			b[1] = a;
      }
		cout << "=";
		b[0].Print();
    myfile.close();
    }
	

	return 0;
}