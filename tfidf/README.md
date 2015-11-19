# options

```bash
   ./tfidf.exe --help
usage: tfidf.exe [options] [file]
options:
  -d, --delimiter <word>    specify delimiter word separating documents (default='---')
  -N <int>                  output up-to N words for each doc (in default, outpu all words)
  --limit <double>          output only words whose tf-idf > limit
  -?, --help
file:
  read this path. When not specified, read stdin.
```

# easy example

When no options passed, this program outputs all words for each document,
sorted by tf-idf.

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

# top 2 words (for each)

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

# filtering by tf-idf

Following outputs only words whose tf-idf > limit (greater then and not equal).

```bash
   ./tfidf.exe --limit 0.0 sample.input
0.27031 a
---
0.27031 c
---
0.135155 c
0.135155 a
```

## both

filtering, then top N.

```bash
   ./tfidf.exe -N 1 --limit 0.1 sample.input
0.27031 a
---
0.27031 c
---
0.135155 c
```

