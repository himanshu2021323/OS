cf: p1uf.c p2uf.c
	gcc p1uf.c -o f1
	gcc p2uf.c -o f2

cm: p1um.c p2um.c
	gcc p1um.c -o m1
	gcc p2um.c -o m2

cs: p1us.c p2us.c
	gcc p1us.c -o s1
	gcc p2us.c -o s2

clean: f1 f2 s1 s2 m1 m2
	rm f1 f2 m1 m2 s1 s2

rff: sendThroughFifo ackThroughFifo
	rm sendThroughFifo ackThroughFifo

rfs: unix_sock.server unix_sock.client
	rm unix_sock.server unix_sock.client