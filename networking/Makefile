PROJECT_DIR = $(abspath ..)
TEST = $(PROJECT_DIR)/test
CONFIG = $(PROJECT_DIR)/config
LIB = $(PROJECT_DIR)/lib
LOCAL_DNS = $(PROJECT_DIR)/local_dns
LIB_CRAFTER_SRC = $(PROJECT_DIR)/libcrafter/libcrafter
DNS_SERVER=$(PROJECT_DIR)/dns_server

test_with_arping: $(TEST)/test_ip_getter_manual.o ip_getter.o arping_context.o arping_requester.o arping_listener.o replier.o $(CONFIG)/DnsMap.o $(CONFIG)/DnsMapCache.o $(CONFIG)/DnsMapUser.o $(LIB)/time_utils.o arping
	g++ -DUSE_ARPING=1 -o $(TEST)/test_ip_getter_manual.x $(TEST)/test_ip_getter_manual.o arping_context.o ip_getter.o arping_requester.o arping_listener.o replier.o $(CONFIG)/DnsMap.o $(CONFIG)/DnsMapCache.o $(CONFIG)/DnsMapUser.o $(LIB)/time_utils.o -pthread -L. -l:arping.a -lcap -lnet -lnsl -lrt -lpcap -lm

test_with_crafter: $(TEST)/test_ip_getter_manual.o ip_getter.o crafter_requester.o crafter_listener.o replier.o $(CONFIG)/DnsMap.o $(CONFIG)/DnsMapCache.o $(CONFIG)/DnsMapUser.o $(LIB)/time_utils.o arping
	g++ -std=c++20 -DUSE_ARPING=0 -o $(TEST)/test_ip_getter_manual.x $(TEST)/test_ip_getter_manual.o ip_getter.o crafter_requester.o crafter_listener.o replier.o $(CONFIG)/DnsMap.o $(CONFIG)/DnsMapCache.o $(CONFIG)/DnsMapUser.o $(LIB)/time_utils.o -I../libcrafter/libcrafter -pthread -L. -l:arping.a -lcrafter -lcap -lnet -lnsl -lrt -lpcap -lm -lresolv

get_ip: ip_getter.o crafter_requester.o crafter_listener.o replier.o $(CONFIG)/DnsMap.o $(CONFIG)/DnsMapCache.o $(CONFIG)/DnsMapUser.o $(CONFIG)/DnsMapUserSettings.o $(LIB)/time_utils.o
	g++ -std=c++20 -DUSE_ARPING=0 $(DNS_SERVER)/get_ip.cpp -o $(DNS_SERVER)/get_ip.x ip_getter.o crafter_requester.o crafter_listener.o replier.o $(CONFIG)/DnsMap.o $(CONFIG)/DnsMapCache.o $(CONFIG)/DnsMapUser.o $(CONFIG)/DnsMapUserSettings.o $(LIB)/time_utils.o -I../libcrafter/libcrafter -pthread -L.  -lcrafter -lcap -lnsl -lrt -lpcap -lm -lresolv

%.o : %.cpp
	g++ -std=c++20 -c $^ -o $@

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
	rm -f $(TEST)/test_ip_getter_manual.o
	rm -f $(CONFIG)/*.o
	rm -f $(LIB)/*.o
	cd $(LOCAL_DNS)/src; make clean
	cd $(LIB_CRAFTER_SRC); make clean; cd $(PROJECT_DIR)/networking
	rm -f $(DNS_SERVER)/*.x
