This project aims to provide a functional development environment for the M2 Portfolio OS, focusing on serial communication via the NS16550 UART - RS232 port.
The standard ROM-based shell is unusable for development because the kernel's native printf OS-calls are hardwired to the CDE2 ASIC UART. This project bypasses those limitations by reimplementing core system commands to use the NS16550 UART for serial communication (e.g., via PuTTY).
Specifically developed and tested on the Panasonic FZ-35S. Compatibility with other M2 variants is unknown due to potential differences in serial port availability.
<img width="998" height="961" alt="example shell" src="https://github.com/user-attachments/assets/773b73ea-7b36-462f-b596-75c51a37da4c" />
