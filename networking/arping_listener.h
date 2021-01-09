#include "listener.h"
#include "arping_context.h"

class ArpingListener: public Listener
{  
	private:
		ArpingContext * context;	
    
	public:
		ArpingListener(ArpingContext * context1) : Listener(), context(context1) {
		}
        virtual bool listen(std::pair<std::string, std::string>* out);
};
