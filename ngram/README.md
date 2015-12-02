ngram.exe counts the frequency of every n-gram.

```bash
   g++-4.8 -O3 -o ngram.exe -std=c++11 ngram.cc
   cat sample
a b c d
a b b c
```

## simple n-gram

```bash
   ./ngram.exe -n 2 sample # ./ngram.exe -v -n 2 <sample # also ok
2 2 __BOS__ a
2 2 a b
2 1 b b
2 2 b c
2 1 c __EOS__
2 1 c d
2 1 d __EOS__
```

output each line is:
`<n> <freq> <n-gram>`

```
   ./ngram.exe -n 2,3 sample # bi- and tri-gram
2 2 __BOS__ a
3 2 __BOS__ a b
2 2 a b
3 1 a b b
3 1 a b c
2 1 b b
3 1 b b c
2 2 b c
3 1 b c __EOS__
3 1 b c d
2 1 c __EOS__
2 1 c d
3 1 c d __EOS__
2 1 d __EOS__
```

## tf-idf

docs separeted line `---` (see `--delimiter`)

```bash
   ./ngram.exe --tfidf -n 2 --limit 1.0 sample.multi
2 1.38629 __BOS__ a
2 1.38629 a b
2 1.38629 b c
---
2 1.38629 a __EOS__
2 1.38629 b a
2 1.38629 c b
```

