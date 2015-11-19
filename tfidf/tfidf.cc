#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i=0;i<(n);++i)
#define trace(var) cerr<<">>> "<<#var<<" = "<<var<<endl;

void usage() {
  cerr << "usage: tfidf.exe [options] [file]" << endl;
  cerr << "options:" << endl;
  cerr << "  -d, --delimiter <word>    specify delimiter word separating documents (default='---')" << endl;
  cerr << "  -N <int>                  output top N featurefull words for each doc. specify -1 to output all words (default=-1)" << endl;
  cerr << "  -?, --help" << endl;
  cerr << "file:" << endl;
  cerr << "  read this path. When not specified, read stdin." << endl;
  exit(0);
}

void read(istream&cin, string delimiter, int N) {
  string word;
  vector<map<string, int>> docs = { {} };
  vector<int> doc_size = { 0 };
  int i = 0;
  while (cin >> word) {
    if (word == delimiter) {
      docs.push_back({});
      doc_size.push_back(0);
      ++i;
    } else {
      docs[i][word] += 1;
      doc_size[i] += 1;
    }
  }
  int D = docs.size();
  map<string, int> df;
  for (int i = 0; i < D; ++i) {
    vector<pair<double, string>> ls;
    for (auto&kv: docs[i]) {
      string word = kv.first;
      int tf = kv.second;
      if (df.count(word) == 0) {
        for (int i = 0; i < D; ++i) if (docs[i].count(word)) df[word]++;
      }
      double tfidf =
        static_cast<double>(tf) / doc_size[i]
        * log(static_cast<double>(D) / df[word]);
      ls.push_back(make_pair(tfidf, word));
    }
    sort(begin(ls), end(ls), greater<pair<double, string>>());
    for (int j = 0; j < (N==-1 ? ls.size() : N); ++j) {
      cout << ls[j].first << ' ' << ls[j].second << endl;
    }
    if (i < D - 1) cout << delimiter << endl;
  }
}

int main(int argc, char*argv[])
{
  string delimiter = "---";
  string doc_path = "";
  int N = -1;
  for (int i = 1; i < argc; ++i) {
    string arg = argv[i];
    if (arg == "-?" or arg == "--help" or arg == "-h") {
      usage();
    }
    else if (arg == "-d" or arg == "--delimiter") {
      delimiter = argv[i+1];
      ++i;
    }
    else if (arg == "-N") {
      N = atoi(argv[i+1]);
      ++i;
    }
    else {
      doc_path = argv[i];
    }
  }

  if (doc_path == "") {
    read(cin, delimiter, N);
  } else {
    ifstream sin(doc_path);
    read(sin, delimiter, N);
  }

  return 0;
}
