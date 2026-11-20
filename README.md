# ESP-IDF UART UTF-8 Interactive Console

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-ESP32%20%7C%20ESP32--S3%20%7C%20ESP32--P4%20%7C%20ESP32--C6-red.svg)](https://www.espressif.com/)
[![Framework](https://img.shields.io/badge/framework-ESP--IDF%20v5.0+-green.svg)](https://docs.espressif.com/projects/esp-idf/)

A lightweight, non-blocking interactive UART console component for ESP-IDF that properly handles multi-byte UTF-8 character encoding (German umlauts `ä, ö, ü, Ä, Ö, Ü, ß`, French accents, international Unicode), VT100/ANSI terminal navigation, line editing, and command history.

See [CHANGELOG.md](CHANGELOG.md) for the release history.

---

## Features

- **True Multi-Byte UTF-8 Editing:** Cursor navigation and character deletion operate on whole Unicode code points rather than raw split bytes. No corrupt multi-byte UTF-8 characters on backspace or arrow keys.
- **VT100 / ANSI Terminal Control:** Supports Left/Right arrow cursor movement, Up/Down arrow history browsing, Home (`Ctrl+A`), End (`Ctrl+E`), Clear Line (`Ctrl+U`), and Cancel (`Ctrl+C`).
- **Ringbuffer Command History:** Configurable history buffer retaining past commands for fast recall.
- **Non-Blocking FreeRTOS Architecture:** Dedicated console worker task listening on raw UART VFS without locking the main application task.
- **Custom ANSI Prompts:** Flexible prompt styling (e.g. `"\x1b[36mESP32>\x1b[0m "`).

---

## Installation & Integration

### Option 1: ESP-IDF Component Registry / Git Submodule

Add to your project's `main/idf_component.yml`:

```yaml
dependencies:
  esp-idf-uart-utf8-console:
    git: https://github.com/Strg-Alt-Entf-0x00/esp-idf-uart-utf8-console.git
```

Or reference locally in multi-repo workspaces:

```yaml
dependencies:
  esp-idf-uart-utf8-console:
    path: ../../esp-idf-uart-utf8-console
```

### Option 2: Clone directly into `components/`

```bash
git clone https://github.com/Strg-Alt-Entf-0x00/esp-idf-uart-utf8-console.git components/esp-idf-uart-utf8-console
```

---

## Quick Start Example

```c
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "uart_utf8_console.h"

static const char *TAG = "main";

static void my_command_handler(const char *line)
{
    ESP_LOGI(TAG, "Command received: %s", line);

    if (strcmp(line, "help") == 0) {
        printf("Available commands:\r\n  help     - Show this help\r\n  status   - Print system status\r\n");
    } else if (strcmp(line, "status") == 0) {
        printf("Status: System operational. Free heap: %u bytes\r\n", (unsigned)esp_get_free_heap_size());
    } else {
        printf("Unknown command: '%s'. Type 'help' for commands.\r\n", line);
    }
}

void app_main(void)
{
    // Start console with cyan prompt and custom callback handler
    esp_err_t err = uart_utf8_console_start("\x1b[36mESP32>\x1b[0m ", my_command_handler);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize UTF-8 console: %s", esp_err_to_name(err));
        return;
    }

    ESP_LOGI(TAG, "Interactive UTF-8 console started successfully.");
}
```

---

## License

This component is open-source software licensed under the [MIT License](LICENSE).
