ngram.exe enumerate n-grams and counts its frequency,
and its tf-idf.

```bash
   ./ngram.exe -h
usage: ngram.exe [options] [file]
options:
   -n <ints>                 n of grams (allow multiple integers separated by comma)
   <ints> ::= <int> | <int>,<ints>
   <int> ::= [1-9][0-9]*
   --tfidf                   not freq but tfidf (docs separeted by delimiter)
   -d, --delimiter <word>    specify delimiter word separating documents (default='---')
   -l, --limit <double>      freq (or tfidf) >= limit
   -v, --verbose             verbose
   -h, --help                print this
file:
   specify a textfile. when no file specified, cin will read.
```

## enumerate all bigrams

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

## bigrams and trigrams

```bash
   ./ngram.exe -n 2,3 sample
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

## limit by frequency

```bash
   ./ngram.exe -n 2,3 --limit 2 sample
2 2 __BOS__ a
3 2 __BOS__ a b
2 2 a b
2 2 b c
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

