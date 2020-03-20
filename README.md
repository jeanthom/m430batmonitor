# MSP430 based LP-E6 battery monitor

## Installing MSP430 toolchain on Fedora

It seems like the MSP430 toolchain isn't available anymore from the official Fedora repos. You need to enable a copr repo instead:

```
sudo dnf copr enable nielsenb/msp430-development-tools
sudo dnf install msp430-elf-gcc msp430-elf-binutils msp430-gcc-support-files
```

## Compile/flash

```
make flash
```