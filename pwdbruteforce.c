#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include "md5.h"
MD5_CTX mdContext; 

char p[5] = {'0','0','0','0','\0'};

char increment(char pwd);
int main()
{
int i=0,j,k,l;
unsigned int result;
unsigned int hash1=0X19fbc7c1, hash2=0X7e1d96fd, hash3=0X88df723c,hash4=0x3974cffc, hash5=0X8f6bb61b, hash6=0X8e564270, hash7=0X655ca818, hash8=0X58712b2b, hash9=0X97e75d32, hash10=0X14928501;
clock_t start, end;
double cpu_time_used;
start=clock();

//brute force all the password combinations

for(i=0;i<62;i++)
{
p[1]='0';
for(j=0;j<62;j++)
	{	
	p[2]='0';
		for(k=0;k<62;k++)
		{
			p[3]='0';
			for(l=0;l<62;l++)
			{
				p[3] = increment(p[3]);
				result = hashFunction(p);
				if(result == hash1 || result == hash2 || result == hash3 || result == hash4 || result == hash5 || result == hash6 || result == hash7 || result == hash8 || result == hash9 || result == hash10)
				{
				printf("%s \t%x",p,result);
				}
			}
		p[2]=increment(p[2]);
		}
	p[1]=increment(p[1]);
	}
p[0]=increment(p[0]);
}

end=clock();
cpu_time_used = ((double) (end - start));
printf("Running time = %d",cpu_time_used);
}


char increment(char pwd)
{																																																																																																																																																																																																																				
unsigned int a;
a=(int) pwd;
a++;
if(a==58) {a=65;}
else if(a==91) {a=97;}
if(a==123) { a=48;}
pwd = (char) a;
return pwd;
}

//0-9 48-57, A-Z 65-90 a-z 97-122

int hashFunction(char pass[])
{
int *pass_pointer, *temp;
int n, result;
MD5_CTX mdContext;
pass_pointer = (int *) pass; // get an int pointer to the password store
 
   MD5Init(&mdContext);  // compute MD5 of password
   MD5Update(&mdContext, pass_pointer, 4);
   MD5Final(&mdContext);
   temp = (int *) &mdContext.digest[12]; 
   result = *temp; // result is 32 bits of MD5 -- there is a BUG here, oh well.
return result;
}

/*
1a2b 	14928501
A1B2 	97e75d32
LOVE 	19fbc7c1
LoVe 	3974cffc
MOVE 	8f6bb61b
MoVe 	58712b2b
lOvE 	88df723c
love 	7e1d96fd
mOvE 	655ca818
move 	8e564270 */
