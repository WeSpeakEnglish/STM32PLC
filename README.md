# STM32PLC
The PLC based on STM32F746
Hi, my name is Alex 
This REPO dedicate the PLC implemented on the new ST's STM32F7 MCU.
It consist:
1. the LCD driver as native for display's without a controller time management system on displays (8", 9" 800x480 are tested)
2. The GIU library suppors multilayer paradigma to displaying objects on different orders while they will put to the screen.
3. The displaying of images support "invisible" colour, setted up by user to provide displaying such things as button with rounded corners
4. Two CAN's
5. RS-485 and RS-232
6. LM75 on I2C, we read temperature in easy manner in float point format, also I2C to an external device 
7. PLC ready to drive tw8819, up to 4 cameras PAL/NTSC it has been implemented yet.
8. 2 analog inputs and two powerful outputs, whitch can connect the load.
9. The PCF8563 RTC on board to keep the time for a long time
10. Touch screen STMPE811 on board, its works yet of course
11. Power sound class D amplifier on board to provide "talking" functions

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

