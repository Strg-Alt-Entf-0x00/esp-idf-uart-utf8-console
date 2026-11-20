# Changelog

## 1.0.0

- Initial release of the ESP-IDF UART UTF-8 interactive console.
- Supports UTF-8-aware line editing, VT100/ANSI navigation, and command history.
- Runs the console input loop in a non-blocking FreeRTOS task.
- Supports configurable ANSI prompts and command callbacks.
- Requires ESP-IDF 5.0 or newer.
