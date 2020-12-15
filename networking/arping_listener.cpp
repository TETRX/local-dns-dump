#include <string>
#include <iostream>

#include "arping_listener.h"

bool ArpingListener::listen(std::pair<std::string, std::string>* out) {
	return context->recv(out->first, out->second);
}
