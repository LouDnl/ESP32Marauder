# One line flash command
```shell
	C:\Users\$USERNAME\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\4.5.1\esptool.exe --trace --chip esp32 --port COM4 --baud 921600  --before default_reset --after hard_reset write_flash  -z --flash_mode dio --flash_freq 80m --flash_size 4MB 0x1000 C:\Users\$USERNAME\AppData\Local\Temp\arduino\sketches\EFD42E8C9F9028002B0F2B653C65875D\esp32_marauder.ino.bootloader.bin 0x8000 C:\Users\$USERNAME\AppData\Local\Temp\arduino\sketches\EFD42E8C9F9028002B0F2B653C65875D\esp32_marauder.ino.partitions.bin 0xe000 C:\Users\$USERNAME\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.11/tools/partitions\boot_app0.bin 0x10000 C:\Users\$USERNAME\AppData\Local\Temp\arduino\sketches\EFD42E8C9F9028002B0F2B653C65875D\esp32_marauder.ino.bin 
```

# Error with ieee80211_raw_frame_sanity_check
```shell
	# Make a copy of "libnet80211.a" -> "libnet80211.a.old"

	# location:
	c:\Users\$USERNAME\AppData\Local\Arduino15\packages\esp32\tools\xtensa-esp32-elf-gcc\esp-2021r2-patch5-8.4.0\bin\

	c:\Users\$USERNAME\AppData\Local\Arduino15\packages\esp32\tools\xtensa-esp32-elf-gcc\esp-2021r2-patch5-8.4.0\bin\xtensa-esp32-elf-objcopy --weaken-symbol=ieee80211_raw_frame_sanity_check c:\Users\$USERNAME\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.11\tools\sdk\esp32\lib\libnet80211.a c:\Users\$USERNAME\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.11\tools\sdk\esp32\lib\libnet80211.a2

	# Copy libnet80211.a2 in place of libnet80211.a
```

# Adds -zmuldefs to all compile runs
`platform.txt` - replaces: `c:\Users\$USERNAME\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.11\platform.txt`

# code changes
lang_var.h is updated for Arduino13+ compatibility with PROGMEM
EvilPortal.h is updated for non global apName and index_html

# Further notes
ESPAsyncWebServer is updated for issues with LinkedList in StringArray.h
