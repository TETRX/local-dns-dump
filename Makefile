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
	mkdir -p $(CACHE_LOC)
	mkdir -p $(CONFIG_LOC)
	cp $(CONFIG)/DnsMapCache.config $(CACHE_LOC)
	cp $(CONFIG)/DnsMapUserSettings.config $(CONFIG_LOC)
	cp $(CONFIG)/DnsMapUser.config $(CONFIG_LOC)
	mkdir -p $(PROGRAM_LOC)
	cp dns_server/get_ip.x $(PROGRAM_LOC)
	cp dns_server/custom_dns.py $(PROGRAM_LOC)
	mkdir -p $(UNIT_FILE_LOC)
	cp installation/unit_file $(UNIT_FILE_LOC)/local-dns.service