from dnslib import DNSRecord, QTYPE, RCODE, RR, A
from dnslib.server import DNSServer
import socket
from subprocess import Popen, PIPE, TimeoutExpired
from threading import Lock
import fnmatch


def get_nameserv():
    DEFAULT_IP="8.8.8.4"
    RESOLV_CONF="/etc/resolv.conf"
    nameserver_indicator="nameserver "
    with open(RESOLV_CONF,"r") as resolv_conf:
        for line in resolv_conf:
            if line.startswith(nameserver_indicator):
                nameserver_ip=line[len(nameserver_indicator):-1]
                if not nameserver_ip.startswith("127"): #can't use local ones unfortunately
                    return nameserver_ip
    return DEFAULT_IP

class CustomResolver(object):
    lock = Lock()

    def __init__(self, address, port, domain, timeout=0):
        self.match = "*." + domain + "."
        self.address = address
        self.port = port
        self.timeout = timeout

    def get_ip_from_dns(self, qname):
        # Synchronize so the getter is called only once at the time
        with self.lock:
            # TODO: change it. Start the c++ ip getter
            process = Popen(["./get_ip.x", str(qname)], stdout=PIPE, stderr=PIPE)
            try:
                exit_code = process.wait(self.timeout)
                (output, err) = process.communicate()
                print(exit_code)
                print(err.decode("utf-8"))
                if exit_code:
                    return ""
                else:
                    return output.decode("utf-8")
            except TimeoutExpired:
                return ""

    def resolve(self, request, handler):
        qname = request.q.qname
        qtype = QTYPE[request.q.qtype]

        # Custom answer only for A (ipv4) or ANY requests
        if fnmatch.fnmatch(str(qname), self.match) and qtype in ('A', 'ANY'):
            reply = request.reply()
            ip = self.get_ip_from_dns(str(qname))
            if len(ip) == 0:
                reply.header.rcode = getattr(RCODE, 'NXDOMAIN')
            else:
                reply.add_answer(RR(qname, QTYPE.A, rdata=A(ip), ttl=60))
            return reply
        try:
            if handler.protocol == 'udp':
                proxy_r = request.send(self.address, self.port,
                                       timeout=self.timeout)
            else:
                proxy_r = request.send(self.address, self.port,
                                       tcp=True, timeout=self.timeout)
            reply = DNSRecord.parse(proxy_r)
        except socket.timeout:
            reply = request.reply()
            reply.header.rcode = getattr(RCODE, 'NXDOMAIN')
        return reply


if __name__ == '__main__':
    import argparse, time

    p = argparse.ArgumentParser(description="local-dns-dump")
    p.add_argument("--port", "-p", type=int, default=53,
                   metavar="<port>",
                   help="Local proxy port (default:53)")
    p.add_argument("--address", "-a", default="",
                   metavar="<address>",
                   help="Local proxy listen address (default:all)")
    p.add_argument("--upstream", "-u", default=None,
                   metavar="<dns server:port>",
                   help="Upstream DNS server:port (default:8.8.8.8:53)")
    p.add_argument("--tcp", action='store_true', default=False,
                   help="TCP proxy (default: UDP only)")
    p.add_argument("--timeout", "-o", type=float, default=5,
                   metavar="<timeout>",
                   help="Upstream timeout (default: 5s)")
    p.add_argument("--domain", "-d", default="localdns",
                    metavar="<domain>",
                   help="local-dns domain name (default:localdns)")

    args = p.parse_args()

    if args.upstream==None:
        args.upstream=get_nameserv()+":53"

    print(args.upstream)

    args.dns, _, args.dns_port = args.upstream.partition(':')
    args.dns_port = int(args.dns_port or 53)

    print("Starting local-dns-dump (%s:%d -> %s:%d) [%s]" % (
        args.address or "*", args.port,
        args.dns, args.dns_port,
        "UDP/TCP" if args.tcp else "UDP") + "for domain name: " + args.domain)

    resolver = CustomResolver(args.dns, args.dns_port, args.domain, args.timeout)
    udp_server = DNSServer(resolver,
                           port=args.port,
                           address=args.address)
    udp_server.start_thread()

    if args.tcp:
        tcp_server = DNSServer(resolver,
                               port=args.port,
                               address=args.address,
                               tcp=True)
        tcp_server.start_thread()

    while udp_server.isAlive():
        time.sleep(10)
