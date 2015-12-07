test: ngram.exe
	./ngram.exe -n 2 sample
	./ngram.exe -n 2 --tfidf --limit 0.01 sample.multi

ngram.exe: ngram.cc
	g++ -O3 -std=c++11 -o $@ $^

