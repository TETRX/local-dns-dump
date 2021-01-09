PROJECT_DIR = $(abspath ..)
TEST = $(PROJECT_DIR)/test
LOCAL_DNS = $(PROJECT_DIR)/local_dns
LIB_CRAFTER_SRC = $(PROJECT_DIR)/libcrafter/libcrafter

test_with_arping: $(TEST)/test_ip_getter_manual.o ip_getter.o arping_context.o arping_requester.o arping_listener.o replier.o arping
	g++ -DUSE_ARPING=1 -o $(TEST)/test_ip_getter_manual.x $(TEST)/test_ip_getter_manual.o arping_context.o ip_getter.o arping_requester.o arping_listener.o replier.o -pthread -L. -l:arping.a -lcap -lnet -lnsl -lrt -lpcap -lm
	rm $(TEST)/test_ip_getter_manual.o ip_getter.o replier.o arping_requester.o arping_listener.o 

test_with_crafter: $(TEST)/test_ip_getter_manual.o ip_getter.o crafter_requester.o crafter_listener.o replier.o arping
	g++ -DUSE_ARPING=0 -o $(TEST)/test_ip_getter_manual.x $(TEST)/test_ip_getter_manual.o ip_getter.o crafter_requester.o crafter_listener.o replier.o -I../libcrafter/libcrafter -pthread -L. -l:arping.a -lcrafter -lcap -lnet -lnsl -lrt -lpcap -lm -lresolv
	rm $(TEST)/test_ip_getter_manual.o ip_getter.o replier.o crafter_requester.o crafter_listener.o


%.o : %.cpp
	g++ -c $^ -o $@

arping:
	cd $(LOCAL_DNS)/src; ./makelib.sh; cd $(PROJECT_DIR)/networking
	mv $(LOCAL_DNS)/src/arping.a .

libcrafter:
	cd $(LIB_CRAFTER_SRC); ./autogen.sh; make; sudo make install; sudo cp .libs/libcrafter.so /usr/lib; sudo ldconfig; cd $(PROJECT_DIR)/networking

clean:
	rm -f ../test/*.x
	rm -f *.o
	rm -f arping.a
	rm -f $(TEST)/test_ip_getter_manual.x
	cd $(LOCAL_DNS)/src; make clean
	cd $(LIB_CRAFTER_SRC); make clean; cd $(PROJECT_DIR)/networking
