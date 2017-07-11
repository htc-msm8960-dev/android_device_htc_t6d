$(call inherit-product, vendor/cm/config/common_full_phone.mk)

$(call inherit-product, device/htc/t6d/full_t6d.mk)

PRODUCT_BUILD_PROP_OVERRIDES += PRODUCT_NAME=htccn_chs_ct BUILD_ID=LRX22G BUILD_FINGERPRINT="htc/htccn_chs_ct/t6dwg:5.0.2/LRX22G/524896.8:user/release-keys" PRIVATE_BUILD_DESC="3.22.1401.8 CL524896 release-keys"

PRODUCT_NAME := lineage_t6d
PRODUCT_DEVICE := t6d
