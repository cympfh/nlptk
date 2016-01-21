
tf のファイルから tf-idf を計算する

### format

```
   cat sample/ngram_a
10 A
5 B A
1 B A C

   cat sample/ngram_b
100 A
20 B A
1 B A C

   cat sample/ngram_c
10 A
```

### simple usage

```
   ./tfidf sample/ngram_a sample/ngram_b
# sample/ngram_a
0.0 A
0.0 B A
0.0 B A C
# sample/ngram_b
0.0 A
0.0 B A
0.0 B A C

   ./tfidf sample/ngram_a sample/ngram_c
# sample/ngram_a
0.0 A
3.4657359027997265 B A
0.6931471805599453 B A C
# sample/ngram_c
0.0 A
```

### filter by limit (`>=`)

```
   ./tfidf --limit 0.1 sample/ngram_a sample/ngram_c
# sample/ngram_a
3.4657359027997265 B A
0.6931471805599453 B A C
# sample/ngram_c
```

### output of specified files (whitelist with `+`)

```
   ./tfidf --limit 0.1 +sample/ngram_a sample/ngram_c
# sample/ngram_a
3.4657359027997265 B A
0.6931471805599453 B A C
```

