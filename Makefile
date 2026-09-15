CXX = g++

CXXFLAGS = -m32 -ffreestanding -fno-exceptions -fno-rtti -fno-pie -I.

all: build/patrix.bin iso


# build directory
build:

	mkdir -p build


# architecture
build/boot.o: kernel/arch/x86/boot.s | build

	$(CXX) -m32 -c kernel/arch/x86/boot.s -o build/boot.o


# kernel
build/kernel.o: kernel/main.cpp | build

	$(CXX) $(CXXFLAGS) -c kernel/main.cpp -o build/kernel.o


# kernel binary
OBJS = \
	build/boot.o \
	build/kernel.o


build/patrix.bin: $(OBJS)

	ld -m elf_i386 -T linker.ld -o build/patrix.bin $(OBJS)


# iso
iso: build/patrix.bin grub.cfg

	mkdir -p build/isodir/boot/grub
	cp build/patrix.bin build/isodir/boot/patrix.bin
	cp grub.cfg build/isodir/boot/grub/grub.cfg
	grub-mkrescue -o build/patrix.iso build/isodir


# cleanup
clean:

	rm -rf build