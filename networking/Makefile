TEST = ../test
LOCAL_DNS = ../local_dns

test: $(TEST)/test_ip_getter_manual.o ip_getter.o arping_requester.o arping_listener.o replier.o arping
	g++ -o $(TEST)/test_ip_getter_manual.x $(TEST)/test_ip_getter_manual.o ip_getter.o arping_requester.o arping_listener.o replier.o -pthread -L. -l:arping.a -lcap -lnet -lnsl -lrt -lpcap -lm
	rm $(TEST)/test_ip_getter_manual.o ip_getter.o replier.o arping_requester.o arping_listener.o 

%.o : %.cpp
	g++ -c $^ -o $@

arping:
	cd $(LOCAL_DNS)/src; ./makelib.sh; cd ../../networking
	mv $(LOCAL_DNS)/src/arping.a .

clean:
	rm -f ../test/*.x
	rm -f *.o
	rm arping.a
	rm $(TEST)/test_ip_getter_manual.x
