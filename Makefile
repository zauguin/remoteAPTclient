all: remoteAPTclient
%.o: %.cxx
	g++ -std=c++11 -c $<
%: %.o
	g++ -std=c++11 -o $@ $+
