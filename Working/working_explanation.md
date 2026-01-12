# Working Explanation

The OLED Eye Animation project displays two animated eyes on an SSD1306 OLED display.

## How it Works
- The OLED screen is initialized using the Adafruit SSD1306 library.
- Eyes are drawn using rounded rectangles to resemble eye shapes.
- Animations are created by dynamically changing:
  - Eye height (blinking & sleeping)
  - Eye width (emotions)
  - Eye position (movement)
- The `draw_eyes()` function refreshes the display after each change.
- A demo loop continuously shows different expressions and movements.

## Animation Flow
1. Eyes appear at the center
2. Blink animation
3. Eye movements (left, right, up, down)
4. Emotional expressions
5. Sleep and wake-up cycle

This modular approach allows easy expansion with sensors, AI, or IoT inputs.
