#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i=0;i<(n);++i)
#define loop for(;;)
#define trace(var) cerr<<">>> "<<#var<<" = "<<var<<endl;

using Int = long;
using Text = vector<string>;

string delimiter = "---";
bool TFIDF=false;

vector< map<vector<string>, Int> > grams;

Text to_sentence(string s)
{
  stringstream sin(s);
  Text t;
  t.push_back("__BOS__");
  string w;
  while (sin >> w) t.push_back(w);
  t.push_back("__EOS__");
  return t;
}

void read_docs(istream& sin, const vector<int>&ns)
{
  grams.push_back({});
  int idx = 0;

  string ln;
  while (getline(sin, ln), sin) {
    if (ln == delimiter) {
      grams.push_back({});
      ++idx;
      continue;
    }
    Text text = to_sentence(ln);
    int m = text.size();
    for (int n: ns) {
      vector<string> gram(n);
      for (int i = 0; i < m - n + 1; ++i) {
        for (int j = 0; j < n; ++j) {
          gram[j] = text[i+j];
        }
        grams[idx][gram]++;
      }
    }
  }
}

void usage(){
  cerr << "usage: ngram.exe [options] [file]" << endl;
  cerr << "options:" << endl;
  cerr << "  -n <ints>                 n of grams (allow multiple integers separated by comma)" << endl;
  cerr << "    <ints> ::= <int> | <int>,<ints>" << endl;
  cerr << "    <int> ::= [1-9][0-9]*" << endl;
  cerr << "  --tfidf                   not freq but tfidf (docs separeted by delimiter)" << endl;
  cerr << "  -d, --delimiter <word>    specify delimiter word separating documents (default='---')" << endl;
  cerr << "  -l, --limit <double>      freq (or tfidf) >= limit" << endl;
  cerr << "  -v, --verbose             verbose" << endl;
  cerr << "  -h, --help                print this" << endl;
  cerr << "file:" << endl;
  cerr << "  specify a textfile. when no file specified, cin will read." << endl;
  exit(0);
}

int main(int argc, char*argv[])
{
  vector<int> ns;
  bool verbose = false;
  double limit = -1.0;

  vector<string> restargs;
  for (int i = 1; i < argc; ++i) {
    string arg = string(argv[i]);
    string nextarg = i < argc-1 ? string(argv[i+1]) : "";

    if (arg == "-n") {
      int n; char comma;
      stringstream sin(nextarg);
      while (sin >> n) {
        ns.push_back(n);
        sin >> comma;
      }
      ++i;
    }
    else if (arg == "--tfidf") {
      TFIDF=true;
    }
    else if (arg == "-d" or arg == "--delimiter") {
      delimiter = argv[i+1];
      ++i;
    }
    else if (arg == "-l" or arg == "--limit") {
      limit = atol(argv[i+1]);
      ++i;
    }
    else if (arg == "-v" or arg == "--verbose") {
      verbose = true;
    }
    else if (arg == "-?" or arg == "--help" or arg == "-h") {
      usage();
    }
    else {
      restargs.push_back(arg);
    }
  }

  if (ns.size() == 0) {
    cerr << "[Err] option -n needs" << endl;
    usage();
  }

  // read documents
  if (restargs.size() == 0) {
    if (verbose) cerr << "read from stdin" << endl;
    read_docs(cin, ns);
  } else {
    if (verbose) cerr << "read from " << restargs[0] << endl;
    ifstream sin(restargs[0]);
    read_docs(sin, ns);
  }

  // output all
  int N = grams.size();
  rep (i, N) {
    for (auto&kv: grams[i]) {
      auto& gram = kv.first;
      int tf = kv.second;
      if (not TFIDF) {
        if (tf < limit) continue;
        cout << gram.size() << ' ' << tf;
      } else {
        int df = 0;
        rep (j, N) if (grams[j][gram]) ++df;
        double tfidf = tf * log(double(N) / df);
        if (tfidf < limit) continue;
        cout << gram.size() << ' ' << tfidf;
      }
      for (string w: gram) cout << ' ' << w;
      cout << endl;
    }
    if (i < grams.size()-1) cout << delimiter << endl;
  }

  return 0;
}

