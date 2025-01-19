#pragma once

#define I2C1_SCL_PIN GP3
#define I2C1_SDA_PIN GP2
#define I2C_DRIVER I2CD1
#define OLED_BRIGHTNESS 128
#define OLED_WIDTH 32
#define OLED_HEIGHT 128

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17 // Specify a optional status led by GPIO number which blinks when entering the bootloader

#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 5000
