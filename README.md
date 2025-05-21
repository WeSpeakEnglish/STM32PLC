# STM32PLC  
A Programmable Logic Controller Based on the STM32F746

This repository showcases a PLC built around ST's powerful STM32F7 microcontroller. It includes a range of hardware and software features designed for robust industrial or embedded applications.

## Features

1. **Native LCD Driver**  
   Designed for displays without a built-in controller (tested on 8" and 9" 800x480 panels). Supports precise timing and rendering.

2. **GUI Library with Layered Rendering**  
   Implements a multi-layer (Z-indexed) GUI system, allowing overlapping objects to be rendered in the correct visual order.

3. **Image Rendering with Transparency Support**  
   Enables user-defined "invisible" colors, perfect for elements like buttons with rounded corners.

4. **Dual CAN Bus Support**  
   Two CAN interfaces for industrial communication and device networking.

5. **RS-485 and RS-232 Interfaces**  
   Standard serial communication options for a wide range of peripherals.

6. **Temperature Sensing with LM75 over I2C**  
   Easy-to-use temperature readings in floating-point format. Additional I2C devices supported.

7. **TW8819 Video Decoder Support**  
   Ready to drive the TW8819 chip, enabling support for up to 4 PAL/NTSC cameras.

8. **Analog I/O**  
   Includes two analog inputs and two high-current outputs capable of driving external loads.

9. **Real-Time Clock (PCF8563)**  
   On-board RTC for long-term timekeeping.

10. **Capacitive Touchscreen Support (STMPE811)**  
    Built-in controller for touch interface applications.

11. **Class-D Audio Amplifier**  
    On-board amplifier enables sound output for voice or audio signals.

12. **Optional GPS Module**  
    GPS module support via UART for location-based applications.

## PCB project in Altium Designer
see [here](https://github.com/WeSpeakEnglish/PLC_PCB)

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

