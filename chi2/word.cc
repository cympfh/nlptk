#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i=0;i<(n);++i)
#define loop for(;;)
#define trace(var) cerr<<">>> "<<#var<<" = "<<var<<endl;

template<class T>
inline
ostream& operator<<(ostream& os, vector<T> v) {
  if (v.size() == 0) { return os << "(empty vector)"; }
  os << v[0];
  for (int i = 1, len = v.size(); i < len; ++i) {
    os << " " << v[i];
  }
  return os;
}

template<class T>
inline
ostream& operator<<(ostream& os, set<T> v) {
  for (T t: v) os << t << ' ';
  return os;
}

template<class S, class T>
inline
ostream& operator<<(ostream& os, pair<S,T> p) {
  return os << '(' << p.first << ", " << p.second << ')';
}

template<class T> inline
istream& operator>>(istream&is, vector<T>&v) {
  rep (i, v.size()) is >> v[i];
  return is;
}

template<class S, class T, class U>
inline
ostream& operator<<(ostream& os, tuple<S,T,U> t) {
  return os << '('
    << get<0>(t) << ", "
    << get<1>(t) << ", "
    << get<2>(t) << ", " << ')';
}

template<class S, class T>
inline
ostream& operator<<(ostream& os, map<S,T>& m) {
  for (const pair<S,T>& pr: m) {
    os << pr << ' ';
  }
  return os;
}

using vi = vector<int>;

using Text = vector<string>;
Text to_sentence(const string& line) {
  stringstream ss(line);
  Text t;
  string w;
  while (ss >> w) t.push_back(w);
  sort(begin(t), end(t));
  return t;
}

/*
using Text = set<string>;
Text to_sentence(const string& line) {
  stringstream ss(line);
  Text t;
  string w;
  while (ss >> w) t.insert(w);
  return t;
}
*/

inline
bool contains(const Text& t, const string& w) {
  auto addr = lower_bound(begin(t), end(t), w);
  if (addr == end(t)) return false;
  return (*addr == w);
  // rep (i, t.size()) if (t[i] == w) return true;
  // return false;
}

int main(int argc, char*argv[])
{

  vector<vector<Text>> tests;
  vector<string> words;

  for (int i = 1; i < argc; ++i)
  {
    string arg = string(argv[i]);

    if (arg == "--list") {
      ifstream sin(argv[i+1]);
      string w;
      while (getline(sin, w)) {
        words.push_back(w);
      }
      cerr << "words loaded: " << words.size() << endl;
      ++i;
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

  if (words.size() == 0 or tests.size() == 0) {
    cerr << "Usage: " << argv[0] << " --list <words-list-file> <test-topic1> <test-topic2> ..." << endl;
    cerr << "sort <bag-of-words> by the chi2 decreasing" << endl;
    return 0;
  }

  int m = words.size();
  int n = tests.size();

  vector<pair<double, string>> ans;

  cerr << endl;
  rep (i, m) {
    string& w = words[i];
    cerr << "\rword: " << i;

    vi mt(n, 0);
    vi nt(n, 0);
    int N1 = 0;
    int N0 = 0;

    rep (j, n) {
      for (const Text&t: tests[j]) {
        if (contains(t, w)) {
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

    if (std::isnan(chi2)) continue;
    ans.push_back({ abs(chi2), w });
  }
  cerr << endl;

  sort(begin(ans), end(ans));
  reverse(begin(ans), end(ans));

  rep (i, ans.size()) {
    cout << ans[i].second << endl;
  }

  return 0;
}
