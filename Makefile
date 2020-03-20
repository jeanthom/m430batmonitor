CC := msp430-elf-gcc
MSPDEBUG := mspdebug
MCU := msp430g2452

CFLAGS := -Wall -Werror -mmcu=$(MCU) -Os
LDFLAGS :=  -mmcu=$(MCU)

OBJS := src/main.o
TARGET := m430batmonitor.elf

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

flash: $(TARGET)
	$(MSPDEBUG) rf2500 "prog $(TARGET)" "run"
.PHONY: flash

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
.PHONY: clean
