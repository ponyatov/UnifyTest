#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { glob_init(); return yyparse(); }

Sym::Sym(string T,string V) { tag=T; val=V; }
Sym::Sym(string V):Sym("sym",V) {}
void Sym::push(Sym*o) { nest.push_back(o); }

string Sym::ptr() { ostringstream os; os << " @" << this; return os.str(); }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::head() { return "<"+tag+":"+val+">"+ptr(); }
string Sym::dump(int depth) { string S = "\n"+pad(depth)+head();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }

Sym* Sym::uni(Sym*o) {
	push(o);
	return this;
}

Term::Term(string V):Sym("term",V){}
Var::Var(string V):Sym("var",V){}
Op::Op(string V):Sym("op",V){}

extern map<string,Sym*> glob;
extern void glob_init(){}
