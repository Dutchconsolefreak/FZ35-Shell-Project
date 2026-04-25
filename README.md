# FZ-35S Shell Project

## Overview

This project aims to provide a functional development environment for the **M2 Portfolio OS**, focusing on serial communication via the **NS16550 UART - RS232 port**.

The standard ROM-based shell is unusable for development because the kernel's native printf OS-calls are hardwired to the CDE2 ASIC UART. This project bypasses those limitations by reimplementing core system commands to use the NS16550 UART for serial communication (e.g., via PuTTY).

Specifically developed and tested on the **Panasonic FZ-35S**. Compatibility with other M2 variants is unknown due to potential differences in serial port availability.

<img width="998" height="961" alt="example shell" src="https://github.com/user-attachments/assets/773b73ea-7b36-462f-b596-75c51a37da4c" />

## Technical Setup & Line Endings
This project is developed using the original **M2 SDK** inside the **SheepShaver** (Mac OS 9) emulator. 

### Line Ending Conversion (CR vs. LF)
Because Classic Mac OS uses `CR` (\r) line endings while GitHub and modern tools prefer `LF` (\n), this repository uses a custom Git filter to ensure compatibility:

- **In Git/GitHub:** Files are stored using `LF` for proper web display and diffs.
- **In Workspace (SheepShaver):** Files are automatically converted to `CR` upon checkout to remain compatible with the M2 SDK compiler and tools.

### Required Git Configuration
To work with this repository without breaking the Mac OS 9 source files, you must configure the custom `mac-classic` filter on your local machine:

```bash
git config filter.mac-classic.clean "tr '\r' '\n'"
git config filter.mac-classic.smudge "tr '\n' '\r'"
git config core.autocrlf false
```
<!--### VS Code Settings
To keep the editor UI clean and prevent encoding issues, the following is configured in .vscode/settings.json:

**Files Exclude:** SheepShaver metadata folders (.finf, .rsrc) are hidden from the explorer.
**EOL:** Default line endings are set to LF to match the Git filter expectations.-->

## PuTTY Serial Console Settings

To ensure correct communication with the M2 Shell, configure PuTTY with the following settings:

### Connection → Serial
| Setting | Value |
| :--- | :--- |
| **Speed (Baud)** | 57600 |
| **Data bits** | 8 |
| **Stop bits** | 1 |
| **Parity** | None |
| **Flow Control** | None |

### Terminal
* **Implicit CR in every LF:** ON (This prevents lines from overwriting each other)

### Terminal → Keyboard
* **Backspace key:** Control-H (Ensures correct character deletion in the shell)

> **Note:** Tested with PuTTY 0.81 on Windows 10. These settings match the NS16550 UART configuration used in the project's source code.
