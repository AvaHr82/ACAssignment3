#include<stdio.h>
#include<string.h>
#include "md5.h" 
	char dictionary[5526][5];
	char reducedHash[5526][5];
	int hashChain=200;
	
	//if the char is A-Z or a-z or 0-9 keep as it is. or push the value to the upper range
char returnChar(unsigned int hash)
{
	int n=hash%122;
		if(hash%11 == 0 || hash%27 == 0)
			hash--;

	if(n<48)
	{
		while(n<48)	
			n=n+hash%11;
	}
		
	else if(n > 57 && n < 65)
	{
		while(n<65)
			n = n+hash%27;

	}
	else if(n > 90 && n<97)
	{
		while(n<97)
			n = n+hash%27;
	}
		
	
	return n;
}

// split the hash to 4 single bytes and convert each to valid chars

  char *hashReduction(unsigned int hash)
{
	unsigned int fourth8 = 0x00FF & hash;
	unsigned int third8 =  0x00FF & hash>>8;
	unsigned int second8 =  0x00FF & hash>>16;
	unsigned int first8 =  0x00FF & hash>>24;

	
	char results[5];
	results[0]=returnChar(first8);
	results[1]=returnChar(second8);
	results[2]=returnChar(third8);
	results[3]=returnChar(fourth8);
	results[4]="\0";
	
	return results;	
}

//MD5 hashing

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

//Check in rainbow table for the entry

int checkInRainbowTable(char* value)
{
	int i=0;
	for(i=0;i<5526;i++)
	{	
		if(strcmp(reducedHash[i],value) == 0)
			{
							return i;

			}
	}
	return -1;
}

//Given a hash and the index of the matched rainbow table find the plain text 

void findPlainText(int index,unsigned int inputHash)
{
	char word[5];
	char* ans;
	int i;
	unsigned int hash;
	hash=hashFunction(dictionary[index]);
    	word[0] = dictionary[index][0];	
		word[1] = dictionary[index][1];		
		word[2] = dictionary[index][2];		
		word[3] = dictionary[index][3];		
		word[4] = dictionary[index][4];	
	for(i=0;i<=hashChain;i++)
	{
		if(hash == inputHash)
		{
			printf("\nFound Match: %s",word);		
		}
		else
		{
		    ans= hashReduction(hash);
		    word[0] = *ans++;
			word[1] = *ans++;
			word[2] = *ans++;
			word[3] = *ans++;
			word[4] = "\0";	
			hash = hashFunction(word);
		}
			
	}
}

int main()
{
	FILE *ifp, *ofp;
	char *mode = "r";
	char *read;
	char readWord[5],word[5],name[5];
	int chk=0,nos;
	char *ans;
	int i=0,j=0,index;
	unsigned int inputHash = 0X7e1d96fd;
	unsigned int hash;
	ifp = fopen("C:\\Users\\swetha\\Desktop\\dictionary.txt", mode);
	if (ifp == NULL) {
 		 exit(1);
	}
	i=0;
	
	
	while (1) {
			// Read from the dictionary
		nos = fscanf(ifp, "%s", readWord);	
		dictionary[i][0] = readWord[0];	
		dictionary[i][1] = readWord[1];	
		dictionary[i][2] = readWord[2];	
		dictionary[i][3] = readWord[3];	
		dictionary[i][4] = readWord[4];	
	    
		word[0] = readWord[0];	
		word[1] = readWord[1];	
		word[2] = readWord[2];	
		word[3] = readWord[3];	
		word[4] = readWord[4];	
		
		//calculate the hashchain and update the rainbow table

			for(j=0;j<hashChain;j++)
			{
			
			hash=hashFunction(word);
			ans= hashReduction(hash);
		    word[0] = *ans++;
			word[1] = *ans++;
			word[2] = *ans++;
			word[3] = *ans++;
			word[4] = "\0";	
		
			}

    	reducedHash[i][0] = word[0];	
		reducedHash[i][1] = word[1];	
		reducedHash[i][2] = word[2];	
		reducedHash[i][3] = word[3];	
		reducedHash[i][4] = word[4];	
	    

 		 i++;		 
 		 if(nos == EOF)
 		 	break;
}


			printf("\nInput hash: %x",inputHash);

	ans = hashReduction(inputHash);
	
	// get the hash value and find from the rainbow table
	
	for(i=0;i<=hashChain;i++)
	{
	        word[0] = *ans++;
			word[1] = *ans++;
			word[2] = *ans++;
			word[3] = *ans++;
			word[4] = "\0";	
					index= checkInRainbowTable(word);

			
				if(index> 0)
				{
					printf("\n%s\t%s",dictionary[index],reducedHash[index]);
					findPlainText(index,inputHash);
				
				}
			
					hash=hashFunction(word);
					ans = hashReduction(hash);						
	}

fclose(ifp);
}


