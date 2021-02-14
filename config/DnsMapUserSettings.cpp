#include "DnsMapUserSettings.h"
#include "filepaths_config.h"

DnsMapUserSettings::DnsMapUserSettings(): dnsMap(SETTINGS_PATH) {

}

std::string DnsMapUserSettings::get_setting(std::string setting_name){
    return dnsMap.getEntry(setting_name)[0];
}
