#include<bits/stdc++.h>
#include<cstring>
using namespace std;
struct Tree
{
	char data;
	struct Tree* left;
	struct Tree* right;
	vector<int> fpos,lpos;
	bool n;
};
stack<char> oper;
stack<Tree*> st;
map<int,vector<int> > follow;
map<pair<vector<int>,char>,vector<int>> dfa;
vector<char> val;
set<char> terminal;
string s;
int pos=1;
int prec(char c)
{
	if(c=='*')
		return 3;
	if(c=='.')
		return 2;
	if(c=='|')
		return 1;
	return -1;
}
bool ter(char c)
{
	if(c=='('||c=='*'||c=='|'||c=='.'||c==')')
		return false;
	return true;
}
void modify()
{
	string s1;
	int i,n=s.length();
	for(i=0;i<n-1;i++)
	{
		s1+=s[i];
		if((ter(s[i])||s[i]==')'||s[i]=='*')&&(ter(s[i+1])||s[i+1]=='('))
			s1+='.';
	}
	s1+=s[i];
	s=s1;
}

vector<int> merge(vector<int> v1,vector<int> v2)
{
	v1.insert(v1.end(),v2.begin(),v2.end());
	set<int> s1(v1.begin(),v1.end());
	v1.assign(s1.begin(),s1.end());
	return v1;
}
void orr()
{
	Tree* b=st.top();
	st.pop();
	Tree* a=st.top();
	st.pop();
	Tree* temp=new Tree{'|',a,b,merge(a->fpos,b->fpos),merge(a->lpos,b->lpos),a->n|b->n};
	st.push(temp);
}
void concat()
{
	Tree* b=st.top();
	st.pop();
	Tree* a=st.top();
	st.pop();
	Tree* temp=new Tree{'.',a,b,(a->n)? merge(a->fpos,b->fpos):a->fpos,(b->n)? merge(a->lpos,b->lpos):b->lpos,false};
	st.push(temp);
}
void closure()
{
	Tree* a=st.top();
	st.pop();
	Tree* temp=new Tree{'*',a,NULL,a->fpos,a->lpos,true};
	st.push(temp);
}
void operation()
{
	if(oper.top()=='*')
		closure();
	else if(oper.top()=='.')
		concat();
	else
		orr();
	oper.pop();
}
void inorder(Tree* root)
{
	if(root==NULL)
		return;
	inorder(root->left);
	if(root->data=='*')
	{
		vector<int> f=root->fpos;
		for(int i=0;i<f.size();i++)
			for(int j=0;j<f.size();j++)
				follow[f[i]].push_back(f[j]);
	}
	else if(root->data=='.')
	{
		vector<int> l=root->left->lpos;
		vector<int> f=root->right->fpos;
		for(int i=0;i<l.size();i++)
			for(int j=0;j<f.size();j++)
				follow[l[i]].push_back(f[j]);
	}
	//cout<<root->data<<endl;
	inorder(root->right);
}
void dfatable()
{
    queue<vector<int> > q;
    q.push(st.top()->fpos);
    while(!q.empty())
    {
        for(auto c:terminal)
        {
            vector<int> v;
            for(auto i:q.front())
            {
                if(val[i-1]==c)
                {
                    //for(auto j:follow[i])
                    //    cout<<j<<" ";
                    v=merge(v,follow[i]);
                }
            }
            //for(auto i:v)
            //    cout<<i;
            dfa[{q.front(),c}]=v;
            if(dfa.find({v,c})==dfa.end())
                q.push(v);
        }
        q.pop();
    }
}
int main()
{
	cin>>s;
	//cout<<s<<endl;
	int i,n,j;
	modify();
	s='('+s+").#";
	n=s.size();
	cout<<"The string is: "<<s<<endl;
	for(i=0;i<n;i++)
	{
		if(ter(s[i]))
		{
			vector<int> f,l;
			if(s[i]!='#')
                val.push_back(s[i]);
			f.push_back(pos);
			l.push_back(pos++);
			Tree* temp=new Tree{s[i],NULL,NULL,f,l,false};
			st.push(temp);
		}
		else if(s[i]==')')
		{
			while(oper.top()!='(')
				operation();
			oper.pop();
		}
		else if(s[i]=='*')
            closure();
		else if(s[i]=='('||oper.empty()||prec(s[i])>prec(oper.top()))
			oper.push(s[i]);
		else
		{
			while(!oper.empty()&&prec(s[i])<=prec(oper.top()))
				operation();
			oper.push(s[i]);
		}
	}
	while(!oper.empty()&&!st.empty())
        operation();
    set<char> so(val.begin(),val.end());
    terminal=so;
    for(auto k:val)
        cout<<k<<endl;
    for(auto k:terminal)
        cout<<k<<endl;
	inorder(st.top());
	cout<<"\nThe Follow Pos Table:"<<endl;
	cout<<"\nState\tFollowpos"<<endl;
	for(auto it=follow.begin();it!=follow.end();it++)
	{
		cout<<it->first<<"\t";
		vector<int> v=it->second;
		for(i=0;i<v.size();i++)
			cout<<v[i]<<" ";
		cout<<endl;
	}
	dfatable();
	cout<<"\nStart State\tInput\tEnd state\n\n";
	for(auto it:dfa)
    {
        for(auto i:it.first.first)
            cout<<i<<" ";
        string p=(it.first.first.size()<4)? "\t\t":"\t";
        cout<<p<<it.first.second<<"\t";
        for(auto i:it.second)
            cout<<i<<" ";
        cout<<endl;

    }
}


