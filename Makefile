CONFIG=./config
CACHE_LOC=/var/cache/local_dns
CONFIG_LOC=/etc/local_dns
PROGRAM_LOC=/usr/local/local_dns
UNIT_FILE_LOC=/etc/systemd/system

PROJECT_DIR = $(abspath .)
TEST = $(PROJECT_DIR)/test
CONFIG = $(PROJECT_DIR)/config
LIB = $(PROJECT_DIR)/lib
LOCAL_DNS = $(PROJECT_DIR)/local_dns
LIB_CRAFTER_SRC = $(PROJECT_DIR)/libcrafter/libcrafter
DNS_SERVER=$(PROJECT_DIR)/dns_server
NETWORKING=$(PROJECT_DIR)/networking


test_with_arping: $(TEST)/test_ip_getter_manual.o $(NETWORKING)/ip_getter.o $(NETWORKING)/arping_context.o $(NETWORKING)/arping_requester.o $(NETWORKING)/arping_listener.o $(NETWORKING)/replier.o $(CONFIG)/DnsMap.o $(CONFIG)/DnsMapCache.o $(CONFIG)/DnsMapUser.o $(LIB)/time_utils.o arping
	g++ -DUSE_ARPING=1 -o $(TEST)/test_ip_getter_manual.x $(TEST)/test_ip_getter_manual.o $(NETWORKING)/arping_context.o $(NETWORKING)/ip_getter.o $(NETWORKING)/arping_requester.o $(NETWORKING)/arping_listener.o $(NETWORKING)/replier.o $(CONFIG)/DnsMap.o $(CONFIG)/DnsMapCache.o $(CONFIG)/DnsMapUser.o $(LIB)/time_utils.o -pthread -L. -l:arping.a -lcap -lnet -lnsl -lrt -lpcap -lm

test_with_crafter: $(TEST)/test_ip_getter_manual.o $(NETWORKING)/ip_getter.o $(NETWORKING)/crafter_requester.o $(NETWORKING)/crafter_listener.o $(NETWORKING)/replier.o $(CONFIG)/DnsMap.o $(CONFIG)/DnsMapCache.o $(CONFIG)/DnsMapUser.o $(LIB)/time_utils.o $(CONFIG)/DnsMapUserSettings.o
	g++ -std=c++20 -DUSE_ARPING=0 -o $(TEST)/test_ip_getter_manual.x $(TEST)/test_ip_getter_manual.o $(NETWORKING)/ip_getter.o $(NETWORKING)/crafter_requester.o $(NETWORKING)/crafter_listener.o $(NETWORKING)/replier.o $(CONFIG)/DnsMap.o $(CONFIG)/DnsMapCache.o $(CONFIG)/DnsMapUser.o $(LIB)/time_utils.o $(CONFIG)/DnsMapUserSettings.o -I../libcrafter/libcrafter -pthread -L. -lcrafter -lcap -lnsl -lrt -lpcap -lm -lresolv

get_ip: $(NETWORKING)/ip_getter.global.o $(NETWORKING)/crafter_requester.global.o $(NETWORKING)/crafter_listener.global.o $(NETWORKING)/replier.global.o $(CONFIG)/DnsMap.global.o $(CONFIG)/DnsMapCache.global.o $(CONFIG)/DnsMapUser.global.o $(CONFIG)/DnsMapUserSettings.global.o $(LIB)/time_utils.o
	g++ -std=c++20 -DGLOBAL=1 -DUSE_ARPING=0 $(DNS_SERVER)/get_ip.cpp -o $(DNS_SERVER)/get_ip.x $(NETWORKING)/ip_getter.global.o $(NETWORKING)/crafter_requester.global.o $(NETWORKING)/crafter_listener.global.o $(NETWORKING)/replier.global.o $(CONFIG)/DnsMap.global.o $(CONFIG)/DnsMapCache.global.o $(CONFIG)/DnsMapUser.global.o $(CONFIG)/DnsMapUserSettings.global.o $(LIB)/time_utils.o -I../libcrafter/libcrafter -pthread -L.  -lcrafter -lcap -lnsl -lrt -lpcap -lm -lresolv

%.global.o : %.cpp 
	g++ -DGLOBAL=1 -std=c++20 -c $^ -o $@

%.o : %.cpp
	g++ -std=c++20 -c $^ -o $@

arping:
	cd $(LOCAL_DNS)/src; ./makelib.sh; cd $(PROJECT_DIR)/networking
	mv $(LOCAL_DNS)/src/arping.a .

libcrafter:
	cd $(LIB_CRAFTER_SRC); ./autogen.sh; make; sudo make install; sudo cp .libs/libcrafter.so /usr/lib; sudo ldconfig; cd $(PROJECT_DIR)/networking

clean:
	rm -f $(TEST)/*.x
	rm -f *.o
	rm -f arping.a
	rm -f $(TEST)/test_ip_getter_manual.x
	rm -f $(TEST)/test_ip_getter_manual.o
	rm -f $(CONFIG)/*.o
	rm -f $(LIB)/*.o
	cd $(LOCAL_DNS)/src; make clean
	cd $(LIB_CRAFTER_SRC); make clean; cd $(PROJECT_DIR)/networking
	rm -f $(DNS_SERVER)/*.x


local_dns: libcrafter get_ip


install: 
	mkdir -p $(DESTDIR)/$(CACHE_LOC)
	mkdir -p $(DESTDIR)/$(CONFIG_LOC)
	cp $(CONFIG)/DnsMapCache.config $(DESTDIR)/$(CACHE_LOC)
	cp $(CONFIG)/DnsMapUserSettings.config $(DESTDIR)/$(CONFIG_LOC)
	cp $(CONFIG)/DnsMapUser.config $(DESTDIR)/$(CONFIG_LOC)
	mkdir -p $(DESTDIR)/$(PROGRAM_LOC)
	cp dns_server/get_ip.x $(DESTDIR)/$(PROGRAM_LOC)
	cp dns_server/custom_dns.py $(DESTDIR)/$(PROGRAM_LOC)
	mkdir -p $(DESTDIR)/$(UNIT_FILE_LOC)
	cp installation/unit_file $(DESTDIR)/$(UNIT_FILE_LOC)/local-dns.service