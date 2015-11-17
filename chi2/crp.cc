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

double str_to_double(string s) {
  stringstream a(s);
  double r; a >> r;
  return r;
}

int str_to_int(string s) {
  stringstream a(s);
  int r; a >> r;
  return r;
}

using vi = vector<int>;
using vvi = vector<vi>;

enum PUnitType {
  VAR, POS, WORD
};

struct PUnit
{
  PUnitType t;
  string pos;
  string word;

  PUnit() : t(VAR) {}
  PUnit(string pos_) : t(POS), pos(pos_) {}
  PUnit(string pos_, string w) : t(WORD), pos(pos_), word(w) {}

  bool operator!=(PUnit&rh) {
    if (this-> t != rh.t) return true;
    switch (this->t) {
      case VAR:
        return false;
      case POS:
        return this->pos != rh.pos;
      case WORD:
        return this->word != rh.word;
    }
  }

  bool operator==(PUnit& rh) {
    return not (*this == rh);
  }

};

  bool operator<(const PUnit& rl, const PUnit& rh) {
    switch (rl.t) {
      case VAR:
        return (rh.t != VAR);
      case POS:
        if (rh.t == WORD) return true;
        if (rh.t == POS) return (rl.pos < rh.pos);
        return false;
      case WORD:
        if (rh.t == WORD) return (rl.word < rh.word);
        return false;
    }
  }

ostream& operator<<(ostream& os, PUnit r) {
  switch (r.t) {
    case VAR:
      return os << "<>";
    case POS:
      return os << '<' << r.pos << '>';
    case WORD:
      return os << r.word << '/' << r.pos;
  }
}


struct Alphabet {
  string word;
  string pos;
  Alphabet(string p, string w) : pos(p), word(w) {}

  bool operator==(Alphabet& rh) {
    return this->word == rh.word and this->pos == rh.pos;
  }

  bool operator<(Alphabet& rh) {
    return this->pos < rh.pos or this->word < rh.word;
  }
};

  bool operator<(const Alphabet& lh, const Alphabet& rh) {
    return lh.pos < rh.pos or lh.word < rh.word;
  }

ostream& operator<<(ostream& os, const Alphabet& a) {
  return os << a.word << '/' << a.pos;
}

using Pattern = vector<PUnit>;
using Text = vector<Alphabet>;

// istream Text
//
pair<string, string> split_word_pos(string&s)
{
  string w, p;
  const int n = s.size();
  int i;
  for (i = n - 2; i >= 0; --i) {
    if (s[i] == '_') break;
  }
  if (i <= 0) {
    for (i = n - 2; i >= 0; --i) {
      if (s[i] == '/') break;
    }
  }
  if (i <= 0) {
    return make_pair(s, s);
  }
  w = s.substr(0, i);
  p = s.substr(i+1, 2);
  return make_pair(w, p);
}

Text to_sentence(string s)
{
  stringstream sin(s);
  Text t;
  for (;;) {
    string s; sin >> s;
    if (!sin) break;
    auto pr = split_word_pos(s);
    t.push_back( Alphabet(pr.second, pr.first) );
  }
  return t;
}

// istream Pattern
//
Pattern to_pattern(string s) {
  stringstream sin(s);
  Pattern p;
  for (;;) {
    string s; sin >> s;
    if (!sin) break;
    if (s == "<>") p.push_back(PUnit());
    else if (s[0] == '<') p.push_back(PUnit(s.substr(1, s.size()-2)));
    else {
      auto pr = split_word_pos(s);
      p.push_back(PUnit(pr.second, pr.first));
    }
  }
  return p;
}

/*
 * non-erasing generalization system <=
 */

bool preceq(const Alphabet& a, const PUnit& u) {
  if (u.t == VAR) return true;
  if (u.t == POS) return a.pos == u.pos;
  return a.pos == u.pos and a.word == u.word;
}

bool preceq(const Text& s, const Pattern& p, bool DEBUG) {
  int n = s.size();
  int m = p.size();
  if (n < m) return false;

  // tail matching
  while (m > 0 and p[m-1].t != VAR) {
    if (preceq(s[n-1], p[m-1])) {
      --n; --m;
    } else {
      return false;
    }
  }
  if (n == 0 and m == 0) return true;
  if (m == 0) return false;

  // p should be "<>[.<>]*<>" or "[.<>]*<>"

  int __pos = 0; // of text
  int __begin = 0; // of pattern

  // head matching
  while (p[__begin].t != VAR) {
    if (preceq(s[__pos], p[__begin])) {
      ++__pos; ++__begin;
    } else {
      return false;
    }
    if (__pos >= n) return false;
  }

  // p should be "<>[.<>]*<>"
  
  int __end;
  for (int i = p.size();i > 0; --i) {
    while (__begin < m and p[__begin].t == VAR) {
      ++__pos; ++__begin;
    }
    if (__begin >= m and __pos <= n) return true;
    if (__pos >= n) return false;

    for (__end = __begin + 1; __end < m; ++__end)
      if (p[__end].t == VAR) break;

    if (DEBUG) {
      cerr << "pos, begin, end = "
        << __pos << ' '
        << __begin << ' '
        << __end << endl;
    }

    for (; __pos < n - (__end - __begin); ++__pos) {
      bool res = true;
      for (int i = 0; i < __end - __begin; ++i) {
        if (not preceq(s[__pos + i], p[__begin + i])) {
          res = false;
          break;
        }
      }
      if (res) {
        __pos += (__end - __begin);
        __begin = __end;
        break;
      }
    }
    if (__pos >= n - (__end - __begin)) return false;
  }
  return false;
}

int main(int argc, char*argv[])
{

  vector<Pattern> patterns;
  vector<vector<Text>> tests;

  for (int i = 1; i < argc; ++i)
  {
    string arg = string(argv[i]);

    if (arg == "--list" or arg == "-p") {
      ifstream sin(argv[i+1]);
      string s;
      while (getline(sin, s)) {
        Pattern p = to_pattern(s);
        patterns.push_back(p);
      }
      cerr << "Patterns loaded: " << patterns.size() << endl;
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

  if (patterns.size() == 0 or tests.size() == 0) {
    cerr << "Usage: " << argv[0] << " --list <patterns-file> <test-topic1> <test-topic2> ..." << endl;
    cerr << "sort <classed-regular-pattern-file> by the chi2 decreasing" << endl;
    return 0;
  }

  int m = patterns.size();
  int n = tests.size();

  trace(make_pair(m, n));
  rep (i, n) trace(tests[i].size());

  vector<pair<double, Pattern>> ans;
  int lack=0;

  cerr << endl;
  rep (i, m) {
    Pattern& p = patterns[i];
    cerr << "\rpattern: " << i;

    vi mt(n, 0);
    vi nt(n, 0);
    int N1 = 0;
    int N0 = 0;

    rep (j, n) {
      for (Text& t: tests[j]) {
        if (preceq(t, p, false)) {
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

    int sum = 0; rep (j, n) sum += mt[j];
    if (sum < 3) continue;
    if (std::isnan(chi2)) { ++lack; continue; }
    ans.push_back({ abs(chi2), p });
  }
  cerr << endl;

  sort(begin(ans), end(ans));
  reverse(begin(ans), end(ans));

  rep (i, ans.size()) {
    cout << ans[i].second << endl;
  }

  if (lack>0) {
    cerr << "Warning: " << lack << " patterns lacked because of nan" << endl;
  }

  return 0;
}
