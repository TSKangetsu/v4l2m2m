make -C "/home/user/build/openwrt-SingleFlight/build_dir/target-arm_cortex-a7+neon-vfpv4_musl_eabi/linux-sunxi_cortexa7/linux-5.10.176" \
KCFLAGS="-fmacro-prefix-map=/home/user/build/openwrt-SingleFlight/build_dir/target-arm_cortex-a7+neon-vfpv4_musl_eabi=target-arm_cortex-a7+neon-vfpv4_musl_eabi -fno-caller-saves " \
HOSTCFLAGS="-O2 -I/home/user/build/openwrt-SingleFlight/staging_dir/host/include -I/home/user/build/openwrt-SingleFlight/staging_dir/hostpkg/include -I/home/user/build/openwrt-SingleFlight/staging_dir/target-arm_cortex-a7+neon-vfpv4_musl_eabi/host/include -Wall -Wmissing-prototypes -Wstrict-prototypes" \
CROSS_COMPILE="arm-openwrt-linux-muslgnueabi-" \
ARCH="arm" \
HOST_LOADLIBES="-L/home/user/build/openwrt-SingleFlight/staging_dir/host/lib" \
KBUILD_HOSTLDLIBS="-L/home/user/build/openwrt-SingleFlight/staging_dir/host/lib" \
CONFIG_SHELL="bash" \
M=${PWD} \
modules