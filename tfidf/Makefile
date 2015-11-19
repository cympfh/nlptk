test: tfidf.exe
	./tfidf.exe -N 1 --limit 0.0 sample.input

tfidf.exe: tfidf.cc
	g++ -O3 -std=c++11 -o $@ $^
