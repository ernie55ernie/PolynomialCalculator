#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void getp ly(int b[5000], int *q);
void add(int a[5000], int b[5000]);
void subtract(int a[5000], int b[5000]);
void multiply(int a[5000], int f[5000]);
void divide(int a[5000], int b[5000]);

int main(void)
{
	int apoly[5000],bpoly[5000],c[5000][2];
	int i=0,j=0,k=0,x,y,z,end=0;
	char operator,enter;
	
	for (i=0; i<5000; i++){
		apoly[i]=0;
		bpoly[i]=0;
	}
	getpoly(apoly,&end);
	for (i=0; i<5000;i++){
		if (apoly[i]!=0)
			printf("%d %d\n",apoly[i],i);
	}
	for(;end!=1;){
		getpoly(bpoly,&end);
		for (i=0; i<5000;i++)
			if (bpoly[i]!=0)
				printf("%d %d\n",bpoly[i],i);
		if (end!=1){
			operator=getchar();
			printf("%c\n",operator);
			enter=getchar();
			enter=getchar();
//			if (enter=='\n'){
//				enter='x';
//				printf("%c\n",enter);
//			}
			if (operator=='+'){
				add(apoly,bpoly);
			}
			else if (operator=='-'){
				subtract(apoly,bpoly);
//				printf("%c%c\n",operator,enter);
			}
			else if (operator=='*'){
				multiply(apoly,bpoly);
			}
			else if (operator=='/'){
				divide(apoly,bpoly);
			}
		}
/*		for (i=0; i<500; i++){
			if (apoly[i]!=0)
				printf("%d %d\n",apoly[i],i);
		}
	
		for (i=0; i<600; i++){
			if (bpoly[i]!=0)
				printf("%d %d\n",bpoly[i],i);
		}*/
		for (i=0; i<5000; i++){
			bpoly[i]=0;
		}
//		printf("%d\n",end);
	}
/*	for (i=0; i<5000; i++){
		if (apoly[i]!=0)
			printf("%d %d\n",apoly[i],i);
	}*/
	for (i=4999; i>=0; i--){
		if (apoly[i]!=0){
			c[k][0]=apoly[i];
			c[k][1]=i;
			k++;
		}
	}
	printf("= ");
	for (i=0; i<k; i++){
		if (i==0){
			if (c[i][1]!=0 && c[i][1]!=1){
				if (c[i][0]==1)
					printf("x^%d ",c[i][1]);
				else if (c[i][0]==-1)
					printf("-x^%d ",c[i][1]);
				else
					printf("%d*x^%d ",c[i][0],c[i][1]);
			}
		}
		else if (i==k-1){
			if(c[i][0]>0){
				if(c[i][1]!=0 && c[i][1]!=1){
					if (c[i][0]==1)
						printf("+x^%d\n",c[i][1]);
					else
						printf("+%d*x^%d\n",c[i][0],c[i][1]);
				}
				else if(c[i][1]==0)
					printf("+%d\n",c[i][0]);
				else{
					if (c[i][0]==1)
						printf("+x\n");
					else
						printf("+%d*x\n",c[i][0]);
				}
			}
			else{
				if(c[i][1]!=0 && c[i][1]!=1){
					if (c[i][0]==-1)
						printf("-x^%d\n",c[i][1]);
					else
						printf("%d*x^%d\n",c[i][0],c[i][1]);
				}
				else if (c[i][1]==0)
					printf("%d\n",c[i][0]);
				else{
					if (c[i][1]==-1)
						printf("-x\n");
					else
						printf("%d*x\n",c[i][0]);
				}
			}		
		}
		else{
			if(c[i][0]>0){
				if(c[i][1]!=1){
					if (c[i][0]==1)
						printf("+x^%d ",c[i][1]);
					else
						printf("+%d*x^%d ",c[i][0],c[i][1]);
				}
				else{
					if (c[i][0]==1)
						printf("+x ");
					else
						printf("+%d*x ",c[i][0]);
				}
			}
			else{
				if (c[i][1]!=1){
					if(c[i][0]==-1)
						printf("-x^%d ",c[i][1]);
					else
						printf("%d*x^%d ",c[i][0],c[i][1]);
				}
				else{
					if (c[i][0]==-1)
						printf("-x ");
					else
						printf("%d*x ",c[i][0]);
				}
			}
		}
	}
	return 0;
	
}

void getpoly(int b[5000], int *q){

	char *convert;
	char *str;
	char ch;
	int i,j,k,x,y,z;

	str=malloc(1000*sizeof(char));

	i=0;
	ch=getchar();
	while(ch!='\n' && ch!='.'){
		str[i]=ch;
		i++;
		ch=getchar();
	}
	if (ch=='\n'){
		str[i]='\0';
	}

	if (ch!='.'){
		printf("%s\n",str);
		for(i=0; str[i]!='\0'; i++){
			j=0;
			while (str[i]!=' ' && str[i]!='\0'){
				i++;
				j++;

			}
			convert=malloc(20*sizeof(char));
			memset(convert,0,20);
			strncpy(convert,str+i-j,j);
//			printf("%s %d %d\n",convert,i,j);
			x=0;
			if (convert[0]=='+'){         			// 處理+號在前面的項數
				while (convert[x]!='x'){
					x++;
					if (x==j-1)
					break;
				}				
				if (convert[x]=='x' && x==j-1 ){
					if (convert[x-1]=='+'){
						b[1]=1;
					}
					else
						b[1]=atoi(convert);
				}
				else if (x==j-1)
					b[0]=atoi(convert);
				else{ 
					y=atoi(convert+x+2);
					if (convert[x-1]=='+')
						b[y]=1;
					else
						b[y]=atoi(convert);
				}												//處理+號在前面的項數
			}
			else if (convert[0]=='-'){				//處理-號在前面的項數
				while (convert[x]!='x'){
					x++;
					if (x==j-1)
						break;
				}
				if (convert[x]=='x' && x==j-1){
					if (convert[x-1]=='-'){
						b[1]=-1;
					}
					else
						b[1]=atoi(convert);		
				}
				else if (x==j-1)
					b[0]=atoi(convert);
				else{				
					y=atoi(convert+x+2);
					if (convert[x-1]=='-')
						b[y]=-1;
					else
						b[y]=atoi(convert);
				}
			}										//處理-號在前面的項數
			else {
				while (convert[x]!='x'){			//處理首項無正負號
					if (j==1)
						break;
					x++;
					if (x==j-1)
						break;
				}	
				if (convert[x]=='x' && x==j-1){
					if (x==0)
						b[1]=1;
					else
						b[1]=atoi(convert);
				}	
				else if (x==j-1){
					b[0]=atoi(convert);
				}
				else {
					y=atoi(convert+x+2);
					if (convert[0]=='x'){
						b[y]=1;
					}
					else
						b[y]=atoi(convert);			//處理首項無正負號  昏睡時打 可能有錯
				}	
			}
			free(convert);	
		}
	}
	else 
		*q=1;
	free(str);
}


void add(int a[5000], int b[5000]){
	int i;
	for (i=0; i<5000; i++){
		a[i]=a[i]+b[i];
	}
}
void subtract(int a[5000], int b[5000]){
	int i;
	for (i=0; i<5000; i++){
		a[i]=a[i]-b[i];
	}
}
void multiply(int a[5000], int f[5000]){
	int i,j,c[5000];
/*	for (i=0; i<5000; i++){
		if (f[i]!=0)
			printf("%d%d\n",f[i],i);
	}*/
	for (i=0; i<5000; i++)
		c[i]=0;
	for (i=0; i<5000; i++){
		if (f[i]!=0){
			for(j=0; j<5000; j++){
				if (f[i]*a[j]!=0)
					c[i+j]=c[i+j]+f[i]*a[j];
			}
		}
	}
	for (i=0; i<5000; i++){
		a[i]=c[i];
	}
}
void divide(int a[5000], int b[5000]){
	int i,j,k=0,x,y,z,q,w,c[5000],d[5000];
	
	for (j=4999; j>=0; j--){
		if (b[j]!=0)
			break;
	}
//	printf("%d%d\n",b[j],j);
	while (k!=1){
		for (i=4999; i>=0; i--){
			if (a[i]!=0)
				break;
		}
//		printf("%d%d\n",a[i],i);
		if (j==i){
			c[j-i]=a[i]/b[j];
			k=1;
			break;
		}
		else if (i>j){
			c[i-j]=a[i]/b[j];
			x=i-j;
		}
//		printf("%d\n",x);
		for (y=0; y<5000; y++){
			if (b[y]!=0){
				d[y+x]=c[i-j]*b[y];	
//				printf("%d%d\n",y+x,y);
			}
//			printf("%d%d\n",d[y+x],x+y);
		}
		subtract(a,d);
/*		for (w=0; w<5000; w++){
			if (a[w]==0)
				w++;
		}*/
		
		q=0;
		if(a[q]==0){
			q++;
			for (;a[q]==0;){
				q++;
				if (q==5000){
					k=1;
					break;
				}
			}
		}
	}
//	printf("%d\n",c[2]);
	for (z=0; z<5000; z++){
		a[z]=c[z];
	}	
}

