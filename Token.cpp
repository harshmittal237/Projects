#include<bits/stdc++.h>
using namespace std;
int row=0,col=0;
//string s;
bool isKey(string s)
{
	string key[6]={"if","for","while","int","cout","cin"};
	for(int i=0;i<6;i++)
		if(s==key[i])
		{
			cout<<key[i]<<"\t\tKeyword\t\t"<<row<<"\t"<<col-key[i].size()<<endl;
			s="";
			return true;
		}
	return false;
}
bool op(char c)
{
    string op="+-*<>=";
    for(int i=0;i<6;i++)
		if(c==op[i])
			return true;
	return false;
}
bool brace(char c)
{
    string brace="[]{}()";
    for(int i=0;i<6;i++)
        if(c==brace[i])
        	return true;
    return false;
}
int main()
{
	ifstream fi;
	fi.open("code.cpp");
	int i,flag;
	string s="",s1="";
	cout<<"Name\t\tType\t\tRow\tColumn"<<endl;
	while(!fi.eof())
	{
		char ch;
		fi.get(ch);
		if(op(ch)||brace(ch)||ch==' '||ch==';'||ch=='\n')
        {
            if(s.size()&&!isKey(s))
            {
                string w=(s.size()>7)? "\t":"\t\t";
                cout<<s<<w<<"Identifier\t"<<row<<"\t"<<col-s.size()<<endl;
            }
            s="";
        }
		else
            s+=ch;
        if(op(ch))
            cout<<ch<<"\t\tOperator\t"<<row<<"\t"<<col<<endl;
        else if(brace(ch))
            cout<<ch<<"\t\tBrace\t\t"<<row<<"\t"<<col<<endl;
        col++;
        if(ch=='\n')
		{
			row++;
			col=0;
		}
	}
	fi.close();
}

