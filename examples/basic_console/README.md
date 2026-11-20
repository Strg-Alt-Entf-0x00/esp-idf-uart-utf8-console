# Basic UART UTF-8 Console Example

This example demonstrates how to use `esp-idf-uart-utf8-console` to provide an interactive serial terminal that properly handles multi-byte UTF-8 input (including German umlauts `ä, ö, ü, ß`) and ANSI escape navigation.

## Building and Flashing

On Windows, build from this directory with the included helper:

```bat
esp-build.bat
```

The helper uses `esp-build-config.json` for the ESP-IDF path and serial defaults.
You can still use `idf.py` directly:

```bash
# Configure target (e.g. esp32, esp32s3, esp32p4)
idf.py set-target esp32

# Build the project
idf.py build

# Flash and monitor
idf.py -p COMx flash monitor
```
