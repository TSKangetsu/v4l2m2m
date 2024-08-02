rm -rf v4l2m2mpass.ko
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

python3 .vscode/generate_compdb.py -O ../openwrt-SingleFlight/build_dir/target-arm_cortex-a7+neon-vfpv4_musl_eabi/linux-sunxi_cortexa7/linux-5.10.176 /home/user/build/v4l2M2MPasser

# rmmod v4l2m2mpass.ko
# make -C /usr/src/linux-headers-6.9.3-76060903-generic M=${PWD}
# insmod v4l2m2mpass.ko
# python3 .vscode/generate_compdb.py -O /usr/src/linux-headers-6.9.3-76060903-generic ${PWD}