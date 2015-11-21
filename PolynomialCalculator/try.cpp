#include <iostream>
#include <cstdlib>

using namespace std;

class Polynomial{
public:
	Polynomial(){coef = new double[1];degree=0;coef[degree]=0;};
	Polynomial(const Polynomial& pol);
	~Polynomial(){delete [] coef;}
	int getDegree(){return degree;};
	void input();
	void output();
	void add(const Polynomial& pol);
	void subtract(const Polynomial& pol);
	void mult(const Polynomial& pol);
	void div(const Polynomial& divisor, Polynomial& quotient, Polynomial& remainder);
	Polynomial& operator=(const Polynomial& pol); 
	
	friend Polynomial operator+(const Polynomial&, const Polynomial&);
	friend Polynomial operator-(const Polynomial&, const Polynomial&); 
	friend Polynomial operator*(const Polynomial&, const Polynomial&); 
	friend Polynomial operator/(const Polynomial&, const Polynomial&); 
	friend Polynomial operator%(const Polynomial&, const Polynomial&); 
	friend istream& operator>>(istream&, Polynomial&); 
	friend ostream& operator<<(ostream&, const Polynomial &); 
private:
	double* coef;
	int degree;
	Polynomial(const Polynomial& base, double scalar,int mdegree);
	void reset(); // sets degree to zero, array one elem, and the coefficient to 0.0	
	void checkandreduce(); // check if the degree has decreased after addition and reduce the polynomial
};

ostream& operator <<(ostream& output, const Polynomial& pol){
	int cdegree;
    int first = 0;
    cdegree = pol.degree+1;
    while (cdegree>0){
        cdegree--;
        if(pol.coef[cdegree]==0)continue;
        if(pol.coef[cdegree]>0){
            if((cdegree==0) && (first==0)){
                output<< pol.coef[cdegree];
                first=1;
                continue;
            }
            if((cdegree==0) && (first==1)){
                output<< "+" << pol.coef[cdegree];
                continue;
            }
            if((cdegree==1) && (first==0) && (pol.coef[cdegree]!=1)){
                output<< pol.coef[cdegree]<<"*x";
                first=1;
                continue;
            }
            if((cdegree==1) && (first==1)&&(pol.coef[cdegree]!=1)){
                output<< "+" << pol.coef[cdegree]<<"*x";
                continue;
            }
            if((cdegree==1) && (first==0) && (pol.coef[cdegree]==1)){
                output<< "x";
                first=1;
                continue;
            }
            if((cdegree==1) && (first==1)&&(pol.coef[cdegree]==1)){
                output<< "+" << "x";
                continue;
            }
            if((first==0)&&(pol.coef[cdegree]==1)){
                output << "x^" << cdegree;
                first=1;
                continue;
            }
            if((first==1)&&(pol.coef[cdegree]==1)){
                output << "+x^" << cdegree;
                continue;
            }
            if(first==0){
                output << pol.coef[cdegree] << "*x^" << cdegree;
                first=1;
                continue;
            }
            if(first==1){
                output << "+" << pol.coef[cdegree] << "*x^" << cdegree;
                continue;
            }
        }
        if(pol.coef[cdegree]<0){
            if(cdegree==0){
                output<< pol.coef[cdegree];
                first=1;
                continue;
            }
            if((cdegree==1)&&(pol.coef[cdegree]==-1)){
                output<< "-x";
                first=1;
                continue;
            }
            if(pol.coef[cdegree]==-1){
                output << "-x^" << cdegree;
                first=1;
                continue;
            }
            else{
                output << pol.coef[cdegree] << "*x^" << cdegree;
                first=1;
                continue;
			}
		}
		
	}	
	return output;
}



Polynomial& Polynomial::operator=(const Polynomial& pol){
	Polynomial finpol;
	finpol.degree = pol.degree;
	delete [] finpol.coef;
	finpol.coef = new double [finpol.degree+1];
	for(int finaldeg = finpol.degree+1; finaldeg >= 0; finaldeg--){
        finpol.coef[finaldeg] = pol.coef[finaldeg];
    }
}

Polynomial operator +(const Polynomial& pol1, const Polynomial& pol2){
	Polynomial finpol;
	if(pol1.degree<=pol2.degree)finpol.degree=pol2.degree;
	if(pol1.degree>pol2.degree)finpol.degree=pol1.degree;
	delete [] finpol.coef;
	finpol.coef = new double[finpol.degree+1];
	finpol.add(pol1);
	finpol.add(pol2);
	return finpol;
}
Polynomial operator -(const Polynomial& pol1, const Polynomial& pol2){
	Polynomial finpol;
	if(pol1.degree<=pol2.degree)finpol.degree=pol2.degree;
	if(pol1.degree>pol2.degree)finpol.degree=pol1.degree;
	delete [] finpol.coef;
	finpol.coef = new double[finpol.degree+1];
	finpol.add(pol1);
	finpol.subtract(pol2);
	return finpol;
	
}
Polynomial operator *(const Polynomial& pol1, const Polynomial& pol2){
	Polynomial finpol;
	finpol.degree = pol1.degree + pol2.degree;
	delete [] finpol.coef;
	finpol.coef = new double[finpol.degree+1];
	finpol.add(pol1);
	finpol.mult(pol2);
	return finpol;
}
Polynomial operator /(const Polynomial& pol1, const Polynomial& pol2){
	Polynomial finpol;
	if(pol1.degree<pol2.degree)finpol.degree=pol2.degree-pol1.degree;
	if(pol1.degree>pol2.degree)finpol.degree=pol1.degree-pol2.degree;
	if(pol1.degree==pol2.degree)finpol.degree=0;
	delete [] finpol.coef;
	finpol.coef = new double[finpol.degree+1];
	finpol.add(pol1);
	return finpol;
	
}
Polynomial operator %(const Polynomial& pol1, const Polynomial& pol2){
	
}

Polynomial::Polynomial(const Polynomial& base, double scalar, int mdegree){
	degree = base.degree+mdegree;
    int i = degree;
	int j = base.degree;
    coef = new double[degree+1];
    do{
		coef[i] = scalar * base.coef[j];
		i--;
		j--;
	}while((i>=0)&&(j>=0));
}

void Polynomial::add(const Polynomial& pol){
    int ndegree = degree;
    int adegree = pol.degree;
    do{
		if(ndegree==adegree){
			while(ndegree>=0){
				coef[ndegree] = coef[ndegree] + pol.coef[ndegree];
				ndegree--;
			}
			break;
		}
		if(ndegree>adegree){
			while(ndegree!=adegree){
				ndegree--;
			}
			while(ndegree>=0){
				coef[ndegree] += pol.coef[ndegree];
				ndegree--;
			}
			break;
		}
		if(ndegree<adegree){
			degree=adegree;
			while(ndegree!=adegree){
				coef[adegree] = pol.coef[adegree];
				adegree--;
			}
			while(ndegree>=0){
				coef[ndegree] += pol.coef[ndegree];
				ndegree--;
			}
			break;
		}
    }while(ndegree>=0);
}

void Polynomial::subtract(const Polynomial& pol){
    int ndegree = degree;
    int sdegree = pol.degree;
    do{
		if(ndegree==sdegree){
			while(ndegree>=0){
				coef[ndegree] = coef[ndegree] - pol.coef[ndegree];
				ndegree--;
			}
			break;
		}
		if(ndegree>sdegree){
			while(ndegree!=sdegree){
				ndegree--;
			}
			while(ndegree>=0){
				coef[ndegree] -= pol.coef[ndegree];
				ndegree--;
			}
			break;
		}
		if(ndegree<sdegree){
			degree=sdegree;
			while(ndegree!=sdegree){
				coef[sdegree] = pol.coef[sdegree]*-1;
				sdegree--;
			}
			while(ndegree>=0){
				coef[ndegree] -= pol.coef[ndegree];
				ndegree--;
			}
			break;
		}
    }while(ndegree>=0);
}

void Polynomial::mult(const Polynomial& pol){
    Polynomial multypol;
	multypol.degree=pol.degree+degree;
    delete [] multypol.coef;
	multypol.coef = new double[multypol.degree+1];
    for(int i = pol.degree; i >= 0; i--){
		Polynomial tmp(*this,pol.coef[i],i);
		multypol.add(tmp);
	}
    delete [] coef;
    coef = new double[multypol.degree+1];
    degree=multypol.degree;
    for(int finaldeg = degree+1; finaldeg >= 0; finaldeg--){
        coef[finaldeg] = multypol.coef[finaldeg];
    }
}

void Polynomial::div(const Polynomial& divisor, Polynomial& quotient, Polynomial& remainder){
	
}

void Polynomial::input(){ //DONE
    int cdegree;
    cin >> degree;
    cdegree = degree;
    delete [] coef;
    coef=new double [cdegree+1];
    while (cdegree>=0){
        cin >> coef[cdegree];
        cdegree--;
    }
}

void Polynomial::output(){ //DONE
    int cdegree;
    int first = 0;
    cdegree = degree+1;
    while (cdegree>0){
        cdegree--;
        if(coef[cdegree]==0)continue;
        if(coef[cdegree]>0){
            if((cdegree==0) && (first==0)){
                cout<< coef[cdegree];
                first=1;
                continue;
            }
            if((cdegree==0) && (first==1)){
                cout<< "+" << coef[cdegree];
                continue;
            }
            if((cdegree==1) && (first==0) && (coef[cdegree]!=1)){
                cout<< coef[cdegree]<<"*x";
                first=1;
                continue;
            }
            if((cdegree==1) && (first==1)&&(coef[cdegree]!=1)){
                cout<< "+" << coef[cdegree]<<"*x";
                continue;
            }
            if((cdegree==1) && (first==0) && (coef[cdegree]==1)){
                cout<< "x";
                first=1;
                continue;
            }
            if((cdegree==1) && (first==1)&&(coef[cdegree]==1)){
                cout<< "+" << "x";
                continue;
            }
            if((first==0)&&(coef[cdegree]==1)){
                cout << "x^" << cdegree;
                first=1;
                continue;
            }
            if((first==1)&&(coef[cdegree]==1)){
                cout << "+x^" << cdegree;
                continue;
            }
            if(first==0){
                cout << coef[cdegree] << "*x^" << cdegree;
                first=1;
                continue;
            }
            if(first==1){
                cout << "+" << coef[cdegree] << "*x^" << cdegree;
                continue;
            }
        }
        if(coef[cdegree]<0){
            if(cdegree==0){
                cout<< coef[cdegree];
                first=1;
                continue;
            }
            if((cdegree==1)&&(coef[cdegree]==-1)){
                cout<< "-x";
                first=1;
                continue;
            }
            if(coef[cdegree]==-1){
                cout << "-x^" << cdegree;
                first=1;
                continue;
            }
            else{
                cout << coef[cdegree] << "*x^" << cdegree;
                first=1;
                continue;
			}
		}
		
	}
}

int main()
{
    Polynomial poly1,poly2;
	char choice;
    int done = 0;
    cout << "CGS 2421: Polynomial calculator" << endl;
    do{
        cout << endl << endl <<"0. Quit"
        << endl <<"1. Enter polynomials"
        << endl <<"2. Add"
        << endl <<"3. Subtract"
        << endl <<"4. Multiply"
        << endl <<"5. Divide"
        << endl <<"6. Remainder" << endl << endl;
		
		
        do{
            cout << "Enter your choice : ";
            cin >> choice;
            if((choice!='6') && (choice!='5') && (choice!='4') && (choice!='3')
			   && (choice!='2') && (choice!='1') && (choice!='0')){
                cout << "'" << choice << "' is an invalid choice"<< endl;
            }
        }while((choice!='6') && (choice!='5') && (choice!='4') && (choice!='3')
			   && (choice!='2') && (choice!='1') && (choice!='0'));
        if(choice=='0')exit(1);
        if(choice=='1'){
			cout << "Enter polynomial 1 (degree then coefficients) : ";
            poly1.input();
            cout << "Enter polynomial 2 (degree then coefficients) : ";
			poly2.input();
			done=1;
        }
        if(choice=='2'){
            if(done==0){
                cout << "Enter the polynomial first" << endl;
                continue;
            }
			cout << "(" << poly1 << ")+(" << poly2 << ")=" << (poly1+poly2);
        }
        if(choice=='3'){
            if(done==0){
                cout << "Enter the polynomial first" << endl;
                continue;
            }
			cout << "(" << poly1 << ")-(" << poly2 << ")=" << (poly1-poly2);
        }
        if(choice=='4'){
            if(done==0){
                cout << "Enter the polynomial first" << endl;
                continue;
            }
			cout << "(" << poly1 << ")*(" << poly2 << ")=" << (poly1*poly2);
        }
        if(choice=='5'){
            if(done==0){
                cout << "Enter the polynomial first" << endl;
                continue;
            }
			cout << "(" << poly1 << ")/(" << poly2 << ")=" << (poly1/poly2);
        }
        if(choice=='6'){
            if(done==0){
                cout << "Enter the polynomial first" << endl;
                continue;
            }
			cout << "(" << poly1 << ")%(" << poly2 << ")=" << (poly1%poly2);
        }
    }while(choice!=0);
	
	
	return 0;
}



