# options

```bash
   ./tfidf.exe --help
usage: tfidf.exe [options] [file]
options:
  -d, --delimiter <word>    specify delimiter word separating documents (default='---')
  -N <int>                  output top N featurefull words for each doc. specify -1 to output all words (default=-1)
  -?, --help
file:
  read this path. When not specified, read stdin.
```

# easy example

```bash
   ./tfidf.exe sample.input
   # or
   ./tfidf.exe < sample.input
0.27031 a
0 b
---
0.27031 c
0 b
---
0.135155 c
0.135155 a
0 b
```

# only top 2 words

```bash
   ./tfidf.exe -N 2 sample.input
0.27031 a
0 b
---
0.27031 c
0 b
---
0.135155 c
0.135155 a
```

