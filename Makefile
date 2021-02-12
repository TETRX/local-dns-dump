CONFIG=./config
CACHE_LOC=/var/cache/local_dns
CONFIG_LOC=/etc/local_dns
PROGRAM_LOC=/usr/local/local_dns
UNIT_FILE_LOC=/etc/systemd/system

all: 
	cd networking; make libcrafter; make get_ip;

clean:
	cd networking; make clean;
	

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