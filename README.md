# DIY Color Sensor Library
![Version](https://img.shields.io/badge/Version-1.0.0-blue) ![Arduino](https://img.shields.io/badge/Arduino-Compatible-brightgreen) ![License](https://img.shields.io/badge/License-MIT-green)

RGB color detection library using phototransistors with manual RGB cube calibration and HSB conversion.

## 📦 Installation
1. **Arduino IDE**: Sketch > Include Library > Manage Libraries > Search "DIY Color Sensor"
2. **Manual**: Download [ZIP](https://github.com/LrFranca/DIYColorSensor/archive/main.zip) and add via Sketch > Include Library > Add .ZIP Library
   
## � Color Codes
`getColor()` returns these integer values:

| Code | Color  | Hex Sample |
|------|--------|------------|
| 0    | No color detected | - |
| 1    | Black  | `#000000` |
| 2    | Blue   | `#0000FF` |
| 3    | Green  | `#00FF00` |
| 4    | Yellow | `#FFFF00` |
| 5    | Red    | `#FF0000` |
| 6    | White  | `#FFFFFF` |
| 7    | Silver | `FFFFFF` |
| 8    | unknown | - |

Silver is simply a more reflexive white.

## 🎨 RGB Cube Method
![RGB Cube](https://github.com/user-attachments/assets/9839c4d8-64c8-4d22-8dbb-dee25eb0abff)

Colors are defined by min/max (R,G,B) thresholds creating 3D regions in the RGB color space:
```cpp
// Example: Setting red detection thresholds
sensor.setRedMin(150, 20, 20);   // Minimum (R,G,B)
sensor.setRedMax(255, 100, 100); // Maximum (R,G,B)
```

## 🔌 Schematic
![Circuit](https://github.com/user-attachments/assets/0a0a3cc1-aa1e-46b9-b459-40e835705d82)

## 📂 Examples
| Example | Description | Key Features |
|---------|-------------|--------------|
| [Arduino.ino](/examples/Arduino/Arduino.ino) | Basic color detection | ADC speed optimization |
| [HSBarduino.ino](/examples/HSBarduino/HSBarduino.ino) | HSB color space conversion | Hue-Saturation-Brightness |
| [anythingButArduino.ino](/examples/anythingButArduino/anythingButArduino.ino) | Generic microcontroller use | No ADC tweaks needed |

## 🌈 How It Works
### Color Detection Principle
1. Sequentially pulses RGB LEDs
2. Measures reflected light with phototransistor
3. Calculates differential (LED on - LED off) to cancel ambient light

### HSB Conversion
```cpp
sensor.getRGB();                   // First read raw values
sensor.rgbToHSB(sensor.R_raw,      // Convert to HSB
                sensor.G_raw,
                sensor.B_raw);
// Access converted values:
// sensor.hue (0-360°)
// sensor.saturation (0-1)
// sensor.brightness (0-1)
```

## 🛠️ Public Functions & Variables
### Key Functions
| Function | Description |
|----------|-------------|
| `getColor()` | Detects color (returns 0-8) |
| `getRGB()` | Reads raw RGB values |
| `rgbToHSB()` | Converts RGB to HSB |
| `printValues()` | Prints RGB to Serial |

### Configurable Variables
```cpp
sensor.riseTime = 350;    // LED on time (µs)
sensor.fallTime = 350;    // LED off time (µs) 
sensor.cutOffValue = 150; // Black detection threshold
```

## 🧩 Hardware Setup
```plaintext
RGB LED Connections:
- Red   → Digital Pin (e.g., D6)
- Green → Digital Pin (e.g., D7)
- Blue  → Digital Pin (e.g., D8)
Phototransistor → Analog Pin (e.g., A0)
```

## 🔧 Troubleshooting
| Issue | Solution |
|-------|----------|
| Inconsistent readings | Adjust riseTime/fallTime |
| Color misdetection | Recalibrate RGB thresholds |
| Slow response | Remove ADC prescaler (non-Arduino) |

## 📜 License
MIT License - See [LICENSE](/LICENSE) for details.

---

Developed with ❤️ by LrFranca | [Contribute](https://github.com/yourusername/DIYColorSensor/issues)
```

This version features:
1. Consistent badge-style headers
2. Visual tables for examples and functions
3. Concise code snippets in context
4. Improved visual hierarchy with emoji headers
5. All technical information preserved but more scannable
6. Better mobile readability
7. Clear section separation
8. Quick-reference tables for functions and troubleshooting

The README maintains all the technical depth while being more visually appealing and easier to navigate.
