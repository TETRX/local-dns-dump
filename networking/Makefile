TEST = ../test
LOCAL_DNS = ../local_dns

test_with_arping: $(TEST)/test_ip_getter_manual.o ip_getter.o arping_context.o arping_requester.o arping_listener.o replier.o arping
	g++ -DUSE_ARPING=1 -o $(TEST)/test_ip_getter_manual.x $(TEST)/test_ip_getter_manual.o arping_context.o ip_getter.o arping_requester.o arping_listener.o replier.o -pthread -L. -l:arping.a -lcap -lnet -lnsl -lrt -lpcap -lm
	rm $(TEST)/test_ip_getter_manual.o ip_getter.o replier.o arping_requester.o arping_listener.o 

test_with_crafter: $(TEST)/test_ip_getter_manual.o ip_getter.o crafter_requester.o crafter_listener.o replier.o arping
	g++ -DUSE_ARPING=0 -o $(TEST)/test_ip_getter_manual.x $(TEST)/test_ip_getter_manual.o ip_getter.o crafter_requester.o crafter_listener.o replier.o -I../../testing/libcrafter/libcrafter -pthread -L. -l:arping.a -lcrafter -lcap -lnet -lnsl -lrt -lpcap -lm -lresolv
	rm $(TEST)/test_ip_getter_manual.o ip_getter.o replier.o crafter_requester.o crafter_listener.o


%.o : %.cpp
	g++ -c $^ -o $@

arping:
	cd $(LOCAL_DNS)/src; ./makelib.sh; cd ../../networking
	mv $(LOCAL_DNS)/src/arping.a .

clean:
	rm -f ../test/*.x
	rm -f *.o
	rm -f arping.a
	rm -f $(TEST)/test_ip_getter_manual.x
