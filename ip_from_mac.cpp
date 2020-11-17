/* arping/src/arping_main.c
 *
 *  Copyright (C) 2015 Thomas Habets <thomas@habets.se>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#if HAVE_CONFIG_H
#include "local_dns/config.h"
#endif

extern "C" {
	#include "arping.h"
}

#include <iostream>

void ip_addr2values(uint32_t addr, uint8_t * a, uint8_t * b, uint8_t * c, uint8_t * d) {
	*a = (addr & 0xff);
	*b = (addr & 0xff00) >> 8;
	*c = (addr & 0xff0000) >> 16;
	*d = (addr & 0xff000000) >> 24;
}

/**
 * main() wrapping arping_main() for testing purposes.
 */
int
main(int argc, char **argv)
{
	uint32_t out_ip;
	get_ip("10.0.2.2", "52:54:00:12:35:02", &out_ip);
	std::cout << out_ip << std::endl;
	uint8_t a, b, c, d;
	ip_addr2values(out_ip, &a, &b, &c, &d);
	std::cout << (int)a << "." << (int)b << "." << (int)c << "." << (int)d << std::endl;
        return 0;
}
/* ---- Emacs Variables ----
 * Local Variables:
 * c-basic-offset: 8
 * indent-tabs-mode: nil
 * End:
 */
