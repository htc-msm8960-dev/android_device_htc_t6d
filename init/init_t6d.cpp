/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void common_properties()
{
    property_set("rild.libargs", "-d /dev/smd0");
    property_set("rild.libpath", "/system/lib/libril-qc-qmi-1.so");
    property_set("rild_dsda.libpath", "/system/lib/libril-qc-qmi-qsc.so");
}

void cdma_properties(char const default_cdma_sub[], char const default_network[])
{
    property_set("ro.telephony.default_network", default_network);
    property_set("persist.radio.snapshot_enabled", "1");
    property_set("persist.radio.snapshot_timer", "22");
}

void vendor_load_properties()
{
    std::string platform;
    std::string bootmid;
    std::string device;

    platform = property_get("ro.board.platform");
    if (platform != ANDROID_TARGET)
        return;

    bootmid = property_get("ro.boot.mid");

    if (bootmid == "0P3P20000") {
        /* t6dwg (t6dwg) */
        common_properties();
        cdma_properties("0", "22, 20");
        property_override("ro.product.model", "HTC 809d");
        property_override("ro.build.fingerprint", "htc/htccn_chs_ct/t6dwg:5.0.2/LRX22G/524896.8:user/release-keys");
        property_override("ro.build.description", "3.22.1401.8 CL524896 release-keys");
        property_override("ro.product.device", "t6dwg");
        property_override("ro.build.product", "t6dwg");
        property_override("ro.baseband.arch", "dsda");
        property_set("ro.telephony.default_cdma_sub", "0");
        property_set("ro.ril.enable.sdr", "0");
        property_set("persist.radio.multisim.config", "dsda");
        property_set("ro.ril.oem.ecclist", "110,112,119,120,911,999");
        property_set("ro.ril.oem.nosim.ecclist", "110,112,119,120,911,999,08,000,118,122");
        property_set("ro.ril.oem.normalcall.ecclist", "110,119,120,999");
        property_set("ro.ril.enable.a52", "0");
        property_set("ro.ril.enable.a53", "1");
        property_set("ro.ril.disable.fd.plmn.prefix", "23402,23410,23411,23420,27202");
        property_set("ro.ril.set.mtusize", "1420");
    } else if (bootmid == "0P3P30000") {
        /* t6dug (t6dug) */
        common_properties();
        cdma_properties("0", "0");
        property_override("ro.product.model", "HTC 8060");
        property_override("ro.build.fingerprint", "htc/htccn_chs_cu/t6dug:5.0.2/LRX22G/524896.9:user/release-keys");
        property_override("ro.build.description", "3.22.1402.9 CL524896 release-keys");
        property_override("ro.product.device", "t6dug");
        property_override("ro.build.product", "t6dug");
        property_override("ro.baseband.arch", "dsda");
        property_set("ro.ril.enable.sdr", "0");
        property_set("ro.ril.hsdpa.category", "14");
        property_set("ro.ril.hsupa.category", "6");
        property_set("ro.ril.hsxpa", "4");
        property_set("ro.ril.enable.r8fd", "1");
        property_set("ro.ril.disable.cpc", "1");
        property_set("persist.radio.multisim.config", "dsda");
        property_set("ro.ril.oem.ecclist", "112,911,120,122");
        property_set("ro.ril.oem.nosim.ecclist", "110,112,911,000,08,999,118,119,120,122");
        property_set("ro.ril.oem.normalcall.ecclist", "120,122");
        property_set("ro.ril.disable.fd.plmn.prefix", "23402,23410,23411,23420,27202");
        property_set("ro.ril.enable.a52", "0");
        property_set("ro.ril.enable.a53", "1");
        property_set("ro.ril.svdo", "true");
    }

    device = property_get("ro.product.device");
    ERROR("Found bootmid %s setting build properties for %s device\n", bootmid.c_str(), device.c_str());
}
