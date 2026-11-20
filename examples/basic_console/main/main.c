#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "esp_chip_info.h"
#include "esp_log.h"
#include "esp_system.h"
#include "uart_utf8_console.h"

static const char *TAG = "basic_console";

static void handle_console_command(const char *line)
{
    if (strcmp(line, "help") == 0) {
        printf("\r\n--- Available Commands ---\r\n");
        printf("  help   - Show command overview\r\n");
        printf("  info   - Display chip and system information\r\n");
        printf("  echo   - Echo input (supports German umlauts: ä ö ü ß)\r\n");
        printf("--------------------------\r\n");
    } else if (strcmp(line, "info") == 0) {
        esp_chip_info_t chip_info;
        esp_chip_info(&chip_info);
        printf("\r\n[Chip Info] Cores: %d, Features: 0x%08" PRIx32 ", Free Heap: %" PRIu32 " bytes\r\n",
               chip_info.cores, chip_info.features, esp_get_free_heap_size());
    } else if (strncmp(line, "echo ", 5) == 0) {
        printf("\r\n[Echo] %s\r\n", line + 5);
    } else {
        printf("\r\nUnknown command: '%s'. Type 'help' for available commands.\r\n", line);
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "Starting UART UTF-8 Console Demo...");

    esp_err_t err = uart_utf8_console_start("\x1b[32mConsole>\x1b[0m ", handle_console_command);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start console: %s", esp_err_to_name(err));
        return;
    }

    ESP_LOGI(TAG, "Console task running. Type in your terminal (UTF-8 enabled)!");
}
