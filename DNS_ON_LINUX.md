This file contains the record of the investigation into the way linux handles resolving dns queries, and ideas about how to intercept that flow.

## systemd-resolved


https://wiki.archlinux.org/index.php/Systemd-resolved


"systemd-resolved is a systemd service that provides network name resolution to local applications via a D-Bus interface, the resolve NSS service (nss-resolve(8)), and a local DNS stub listener on 127.0.0.53. See systemd-resolved(8) for the usage."

The simplest (and probably the least hacky) way to do it would be to setup a server (that answers dns queries our way) somewhere on the 127.0.0.0/8 range and have it added to systemd-resolved list of DNS-Servers. This might get tricky if systemd-resolved has some sort of logic behind choosing the DNS server it uses.

Another approach would be to attempt to replace systemd-resolved in some way, but this seems more troublesome.