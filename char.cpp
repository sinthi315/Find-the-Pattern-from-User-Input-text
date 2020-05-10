#include<stdio.h>
#include<string.h>
#include<ctype.h>

struct st
{
	char lex[100], pat[10] ;
	int val ;
}a[1000];

char s[100][100] ;

int num=0, id=0, op=0, key=0 ;

char ke[17][10]	= {"for","while","if","do","else if","switch","break", "return","continue",
						"int","float","long","double","char","__int64", "goto", "exit"
				};

int check(int i, char s[][100])
{
	int j ;
	for(j=0; j<i; j++)
		if(strcmp(s[i], s[j]) == 0)
			return 0;
	return 1;
}

void pattern(int i)
{
	if(isalpha(a[i].lex[0]))
	{
		strcpy(a[i].pat, "id");
		a[i].val = ++id ;
	}
	else if(isdigit(a[i].lex[0]))
	{
		strcpy(a[i].pat, "num");
		a[i].val = ++num ;
	}
	else
	{
		strcpy(a[i].pat, "Op");
		a[i].val = ++op;
	}
}

int keyword(int i)
{
	int j ;

	for(j=0; j<17; j++)
		if(strcmp(ke[j], a[i].lex) == 0)
		{
			strcpy(a[i].pat,"key");
			a[i].val = ++key ;
			return 1;
		}
	
	return 0;
}

int main()
{
	char c, d[100], s[100][100], x[100];
	int i, j, k ;

	printf("Enter the name of the input file : ");
	scanf("%s",d);

	FILE *fin = fopen(d, "r");
	FILE *fout = fopen("output.txt","w");

	fprintf(fout, "File name %s and input was :	\n", d);
	printf("File contain :\n");

	i = 0;
	while(fscanf(fin,"%c",&c)==1)
	{
		fprintf(fout, "%c", c);
		printf("%c", c);
		if(((c>=48 && c<=57) || (c>=65 && c<=90) || (c>=97 && c<=122) ||
			(c>=37 && c<=47) || c==61) && c != 46)
		{
			x[i++] = c;
		}
	}
	x[i] = '\0';
	fprintf(fout, "\n");

	j = k = i = 0;
	while(i < strlen(x))
	{
		if(isalpha(x[i]))
		{
			while(isalpha(x[i]))
				s[j][k++] = x[i++];
			s[j][k] = '\0';
			j++;
			k = 0;
		}
		else if(isdigit(x[i]))
		{
			while(isdigit(x[i]))
				s[j][k++] = x[i++];
			s[j][k] = '\0';
			j++;
			k = 0;
		}
		else if((x[i]>=37 && x[i]<=47) || x[i] == 61)
		{
			s[j][k++] = x[i++];
			s[j][k] = '\0';
			j++;
			k = 0 ;
		}
	}

	
	fprintf(fout, "\n\nLexemes   \tPattern   \tValue\n");
	fprintf(fout, "----------\t----------\t-----\n");


	k = 0;
	for(i=0; i<j; i++)
	{
		if(check(i, s))
		{
			strcpy(a[k].lex, s[i]);
			if(!keyword(k))
			{
				pattern(k);
			}
			k++;
		}
	}

	for(i=0; i<k; i++)
		fprintf(fout, "%s\t\t%s\t\t%d\n", a[i].lex, a[i].pat, a[i].val);

	fclose(fin);
	fclose(fout);

	printf("\nSee the output in Output.txt file.\nThank you.\n", d);
	return 0;
}