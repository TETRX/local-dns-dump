test: ../test/test_ip_getter_manual.o ip_getter.o arping_requester.o arping_listener.o replier.o arping
	g++ -o ../test/test_ip_getter_manual.x ../test/test_ip_getter_manual.o ip_getter.o arping_requester.o arping_listener.o replier.o -pthread -L. -l:arping.a -lcap -lnet -lnsl -lrt -lpcap -lm
	rm ../test/test_ip_getter_manual.o ip_getter.o replier.o arping_requester.o arping_listener.o 

%.o : %.cpp
	g++ -c $^ -o $@

arping:
	cd ../local_dns/src; ./makelib.sh; cd ../../networking
	mv ../local_dns/src/arping.a .

clean:
	rm -f *.x
	rm -f *.o
	rm arping.a
