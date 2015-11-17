#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i=0;i<(n);++i)
#define loop for(;;)
#define trace(var) cerr<<">>> "<<#var<<" = "<<var<<endl;

bool DEBUG=false;

template<class S, class T> inline
ostream& operator<<(ostream&os, pair<S,T> p) {
  os << '(' << p.first << ", " << p.second << ')';
  return os;
}

template<class T> inline
ostream& operator<<(ostream&os, vector<T> v) {
  if (v.size() == 0) {
    os << "(empty)";
    return os;
  }
  os << v[0];
  for (int i=1, len=v.size(); i<len; ++i) os << ' ' << v[i];
  return os;
}

template<class T> inline
istream& operator>>(istream&is, vector<T>&v) {
  rep (i, v.size()) is >> v[i];
  return is;
}

template<class S, class T, class U> inline
ostream& operator<<(ostream&os, tuple<S, T, U> t) {
  return os << '(' << get<0>(t) << ", " << get<1>(t)
    << ", " << get<2>(t) << ')';
}

using vi = vector<int>;
using Gram = tuple<int, int, vector<string>>;

using Text = vector<string>;

Text to_sentence(const string& line) {
  stringstream ss(line);
  Text t; string w;
  t.push_back("__BOS__");
  while (ss >> w) t.push_back(w);
  t.push_back("__EOS__");
  return t;
}

/*
using Text = map<vector<string>, int>;
Text to_sentence(const string& line) {
  stringstream ss(line);
  vector<string> ws; string w;
  ws.push_back("__BOS__");
  while (ss >> w) ws.push_back(w);
  ws.push_back("__EOS__");

  Text t;

  for (int i = 0; i < ws.size(); ++i) {
    vector<string> frag;
    rep (k, 5) {
      if (i+k >= ws.size()) break;
      frag.push_back(ws[i + k]);
      t[frag] += 1;
    }
  }
  return t;
}
*/

bool preceq(const Text& t, const Gram& g) {
  const int n = t.size();
  const int m = get<0>(g);
  const auto& ws = get<2>(g);

  for (int i = 0; i <= n - m; ++i) {
    bool ok = true;
    for (int j = 0; j < m; ++j) {
      if (t[i+j] != ws[j]) {
        ok = false;
        break;
      }
    }
    if (ok) return true;
  }
  return false;
}

/*
inline
bool preceq(const Text& t, const Gram& g) {
  return t.count(get<2>(g));
}
*/

int
main(int argc, char*argv[])
{
  vector<vector<Text>> tests;
  vector<Gram> grams;

  for (int i = 1; i < argc; ++i)
  {
    string arg = string(argv[i]);

    if (arg == "--list") {
      ifstream sin(argv[i+1]);
      int n, m;
      while (sin >> n >> m) {
        vector<string> ws(n);
        rep (j, n) sin >> ws[j];
        if (not sin) break;
        grams.push_back(make_tuple(n, m, ws));
      }
      ++i;
    }
    else if (arg == "--debug") {
      DEBUG=true;
    }
    else {
      ifstream sin(argv[i]);
      vector<Text> doc;
      string s;
      while (getline(sin, s)) {
        Text t = to_sentence(s);
        doc.push_back(t);
      }
      tests.push_back(doc);
    }
  }

  if (grams.size() == 0 or tests.size() == 0) {
    cerr << "Usage: " << argv[0] << " [--debug] --list <grams-list-file> <test-topic1> <test-topic2> ..." << endl;
    cerr << "sort <grams> by the chi2 decreasing" << endl;
    return 0;
  }
  cerr << grams.size() << " grams" << endl;

  int m = grams.size();
  int n = tests.size();

  vector<pair<double, Gram>> ans;

  cerr << endl;
  rep (i, m) {
    Gram& g = grams[i];
    cerr << "\rgram: " << i;

    vi mt(n, 0);
    vi nt(n, 0);
    int N1 = 0;
    int N0 = 0;

    rep (j, n) {
      for (const Text&t: tests[j]) {
        if (preceq(t, g)) {
          ++mt[j];
          ++N1;
        } else {
          ++nt[j];
          ++N0;
        }
      }
    }

    double chi2 = 0.0;

    /*
    // j について正規化 (mt[j]+nt[j] = 1.0)
    rep (j, n) {
      double n1 = double(mt[j]) / double(mt[j] + nt[j]);
      double n0 = double(nt[j]) / double(mt[j] + nt[j]);
      double e1 = double(N1) / double(N1 + N0);
      double e0 = double(N0) / double(N1 + N0);
      chi2 += (n1 - e1) * (n1 - e1) / e1;
      chi2 += (n0 - e0) * (n0 - e0) / e0;
    }
    */

    bool isnan = false;

    // original chi2
    rep (j, n) {
      double m = mt[j] + nt[j];
      double n1 = double(mt[j]);
      double n0 = double(nt[j]);
      double e1 = m * double(N1) / double(N1 + N0);
      double e0 = m * double(N0) / double(N1 + N0);
      chi2 += (n1 - e1) * (n1 - e1) / e1;
      chi2 += (n0 - e0) * (n0 - e0) / e0;
    }

    ans.push_back({ abs(chi2), g });
  }
  cerr << endl;

  sort(begin(ans), end(ans));
  reverse(begin(ans), end(ans));

  rep (i, ans.size()) {
    if (DEBUG) {
      cout << ans[i].first << ' ';
    }
    const Gram&g = ans[i].second;
    cout << get<0>(g) << ' ' << get<1>(g) << ' ' << get<2>(g) << endl;
  }

  return 0;
}
