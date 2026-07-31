# SolarTrace - ESP32 Pin Configuration

## Complete Pin Mapping for SolarTrace System

---

## 1. Pin Configuration Summary

```
┌────────────────────────────────────────────────────────────────────────┐
│                                                                                             │
│                         SOLARTRACE - ESP32 PIN CONFIGURATION                                │
│                                                                                             │
│  ┌──────────────────────────────────────────────────────────────────┐   │
│  │                                                                                      │   │
│  │  ┌───────────────────────────────────────────────────────────┐   │   │
│  │  │                                                                             │   │   │
│  │  │                               ESP32-WROOM-32                               │   │   │
│  │  │                                                                             │   │   │
│  │  │  ┌─────────────────────────────────────────────────────┐   │   │   │
│  │  │  │                                                                     │   │   │   │
│  │  │  │   ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐   │   │   │   │
│  │  │  │   │      │  │       │  │      │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   │ 3V3  │  │ EN    │  │ VP   │  │ VN  │  │ D34 │  │ D35 │  │ D32 │   │   │   │   │
│  │  │  │   │      │  │       │  │      │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘   │   │   │   │
│  │  │  │   ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐   │   │   │   │
│  │  │  │   │     │  │     │  │     │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   │ D33 │  │ D25 │  │ D26 │  │ D27 │  │ D14 │  │ D12 │  │ D13 │   │   │   │   │
│  │  │  │   │     │  │     │  │     │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘   │   │   │   │
│  │  │  │   ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐   │   │   │   │
│  │  │  │   │     │  │     │  │     │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   │ D9  │  │ D10 │  │ D11 │  │ D5  │  │ D6  │  │ D7  │  │ D8  │   │   │   │   │
│  │  │  │   │     │  │     │  │     │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘   │   │   │   │
│  │  │  │   ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐   │   │   │   │
│  │  │  │   │     │  │     │  │     │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   │ D15 │  │ D16 │  │ D0  │  │ D1  │  │ D2  │  │ D3  │  │ D4  │   │   │   │   │
│  │  │  │   │     │  │     │  │     │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘   │   │   │   │
│  │  │  │   ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐   │   │   │   │
│  │  │  │   │     │  │     │  │     │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   │ D5  │  │ D18 │  │ D19 │  │ D21 │  │ RX0 │  │ TX0 │  │ D22 │   │   │   │   │
│  │  │  │   │     │  │     │  │     │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘   │   │   │   │
│  │  │  │   ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐   │   │   │   │
│  │  │  │   │     │  │     │  │     │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   │ D23 │  │ D24 │  │ D25 │  │ D26 │  │ D27 │  │ D32 │  │ D33 │   │   │   │   │
│  │  │  │   │     │  │     │  │     │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘   │   │   │   │
│  │  │  │   ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐  ┌─────┐   │   │   │   │
│  │  │  │   │     │  │     │  │     │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   │ D34 │  │ D35 │  │ VN  │  │ VP  │  │ EN  │  │ GND │  │ VIN │   │   │   │   │
│  │  │  │   │     │  │     │  │     │  │     │  │     │  │     │  │     │   │   │   │   │
│  │  │  │   └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘  └─────┘   │   │   │   │
│  │  │  │                                                                     │   │   │   │
│  │  │  └─────────────────────────────────────────────────────┘   │   │   │
│  │  │                                                                             │   │   │
│  │  └───────────────────────────────────────────────────────────┘   │   │
│  │                                                                                     │   │
│  └─────────────────────────────────────────────────────────────────┘   │
│                                                                                             │
└───────────────────────────────────────────────────────────────────────┘
```

---

## 2. Detailed Pin Configuration Table

| #  | ESP32 Pin | Label | Function        | Connected To | Component         | Wire Color | Notes             |
|----|-----------|-------|-----------------|--------------|-------------------|------------|-------------------|
| 1  | 3.3V      | 3.3V  | Power Output    | VCC          | DS3231 RTC        | RED        | 3.3V Power        |
| 2  | 3.3V      | 3.3V  | Power Output    | VCC          | MAX6675           | RED        | 3.3V Power        |
| 3  | 3.3V      | 3.3V  | Power Output    | VCC          | MicroSD           | RED        | 3.3V Power        |
| 4  | VIN       | 5V    | Power Input     | VCC          | MG995 Servo       | RED        | 5V Power          |
| 5  | GND       | GND   | Ground          | GND          | DS3231 RTC        | BLACK      | Common Ground     |
| 6  | GND       | GND   | Ground          | GND          | MAX6675           | BLACK      | Common Ground     |
| 7  | GND       | GND   | Ground          | GND          | MG995 Servo       | BLACK      | Common Ground     |
| 8  | GND       | GND   | Ground          | GND          | MicroSD           | BLACK      | Common Ground     |
| 9  | GND       | GND   | Ground          | GND          | Pull-up Resistors | BLACK      | Common Ground     |
| 10 | GPIO21    | 21    | I2C Data (SDA)  | SDA          | DS3231 RTC        | GREEN      | I2C Communication |
| 11 | GPIO22    | 22    | I2C Clock (SCL) | SCL          | DS3231 RTC        | BLUE       | I2C Communication |
| 12 | GPIO13    | 13    | PWM Output      | Signal       | MG995 Servo       | ORANGE     | Servo Control     |
| 13 | GPIO15    | 15    | SPI Chip Select | CS           | MAX6675           | YELLOW     | SPI Communication |
| 14 | GPIO14    | 14    | SPI Clock       | SCK          | MAX6675           | WHITE      | SPI Communication |
| 15 | GPIO12    | 12    | SPI Data Out    | SO           | MAX6675           | PURPLE     | SPI Communication |
| 16 | GPIO5     | 5     | SPI Chip Select | CS           | MicroSD           | YELLOW     | SPI Communication |
| 17 | GPIO18    | 18    | SPI Clock       | SCK          | MicroSD           | WHITE      | SPI Communication |
| 18 | GPIO23    | 23    | SPI Master Out  | MOSI         | MicroSD           | BLUE       | SPI Communication |
| 19 | GPIO19    | 19    | SPI Master In   | MISO         | MicroSD           | PURPLE     | SPI Communication |

---

## 3. Pin Function Grouping

### 3.1 Power Pins

| Pin      | Type   | Voltage | Current   | Usage                      |
|----------|--------|---------|-----------|----------------------------|
| **3.3V** | Output | 3.3V    | 600mA max | RTC, MAX6675, SD Card      |
| **VIN**  | Input  | 5V      | 2A max    | Servo Motor, Battery Input |
| **GND**  | Ground | 0V      | -         | All components             |

### 3.2 I2C Pins

| Pin        | Function    | Component  | Speed  | Notes                  |
|------------|-------------|------------|--------|------------------------|
| **GPIO21** | SDA (Data)  | DS3231 RTC | 100kHz | 4.7kΩ Pull-up Required |
| **GPIO22** | SCL (Clock) | DS3231 RTC | 100kHz | 4.7kΩ Pull-up Required |

### 3.3 SPI Pins

| Pin        | Function | Component 1 | Component 2 | Speed | Notes              |
|------------|----------|-------------|-------------|-------|--------------------|
| **GPIO15** | CS       | MAX6675     | -           | 4MHz  | Chip Select        |
| **GPIO14** | SCK      | MAX6675     | MicroSD     | 4MHz  | Shared Clock       |
| **GPIO12** | SO/MISO  | MAX6675     | MicroSD     | 4MHz  | Data Out / Data In |
| **GPIO5**  | CS       | -           | MicroSD     | 4MHz  | Chip Select        |
| **GPIO23** | MOSI     | -           | MicroSD     | 4MHz  | Master Out         |
| **GPIO19** | MISO     | -           | MicroSD     | 4MHz  | Master In          |

### 3.4 PWM Pin

| Pin        | Function | Component   | Frequency | Duty Cycle | Notes            |
|------------|----------|-------------|-----------|------------|------------------|
| **GPIO13** | PWM      | MG995 Servo | 50Hz      | 5-10%      | 1ms=0°, 2ms=180° |

---

## 4. Pull-up Resistor Configuration

### 4.1 I2C Pull-up Resistors

```
┌────────────────────────────────────────────────────────────────────────┐
│                                                                                             │
│                       I2C PULL-UP RESISTOR CONFIGURATION                                    │
│                                                                                             │
│  ┌─────────────────────────────────────────────────────────────────┐   │
│  │                                                                                     │   │
│  │    ESP32 3.3V ──────┬────────────────────────────────────────────┐   │   │
│  │                       │                                                         │   │   │
│  │                       │                                                         │   │   │
│  │                       ▼                                                         │   │   │
│  │                  ┌─────────┐                                                 │   │   │
│  │                  │ 4.7kΩ   │                                                    │   │   │
│  │                  └─────────┘                                                 │   │   │
│  │                       │                                                         │   │   │
│  │                       ├────────────────────────── GPIO21 (SDA)          │   │   │
│  │                       │                                                         │   │   │
│  │                       │                                                         │   │   │
│  │                       │                                                         │   │   │
│  │    ESP32 3.3V ────────┼───────────────────────────────────────┐   │   │   │
│  │                       │                                                     │   │   │   │
│  │                       ▼                                                     │   │   │   │
│  │                  ┌─────────┐                                             │   │   │   │
│  │                  │ 4.7kΩ   │                                                │   │   │   │
│  │                  └─────────┘                                             │   │   │   │
│  │                       │                                                     │   │   │   │
│  │                       ├────────────────────────── GPIO22 (SCL)      │   │   │   │
│  │                       │                                                     │   │   │   │
│  │                       │                                                     │   │   │   │
│  │                       ▼                                                     │   │   │   │
│  │                    ESP32 GND                                                │   │   │   │
│  │                                                                             │   │   │   │
│  └───────────────────────────────────────────────────────────┘   │
│                                                                                    │
└───────────────────────────────────────────────────────────────────────┘
```

### 4.2 Resistor Specifications

| Resistor | Value | Tolerance | Power | Package      | Purpose     |
|----------|-------|-----------|-------|--------------|-------------|
| R1       | 4.7kΩ | ±5%       | 0.25W | Through-hole | SDA Pull-up |
| R2       | 4.7kΩ | ±5%       | 0.25W | Through-hole | SCL Pull-up |

---

## 5. Voltage Level Compatibility

| Component       | Logic Level | ESP32 Level | Compatible | Notes                          |
|-----------------|-------------|-------------|------------|--------------------------------|
| **DS3231 RTC**  | 3.3V        | 3.3V        | ✅ Yes     | Direct connection              |
| **MAX6675**     | 3.3V        | 3.3V        | ✅ Yes     | Direct connection              |
| **MG995 Servo** | 5V (Signal) | 3.3V        | ⚠️ Partial | Signal may need level shifting |
| **MicroSD**     | 3.3V        | 3.3V        | ✅ Yes     | Direct connection              |

### 5.1 Servo Signal Level Shifting (Recommended)

```
┌────────────────────────────────────────────────────────────────────┐
│                                                                                         │
│                     SERVO SIGNAL LEVEL SHIFTER (OPTIONAL)                               │
│                                                                                         │
│  ┌──────────────────────────────────────────────────────────────┐   │
│  │                                                                                 │   │
│  │                        ┌───────────────────────────────────┐         │   │
│  │                        │           Logic Level Converter              │        │   │
│  │                        │  ┌──────────────────────────────┐  │         │   │
│  │                        │  │  3.3V Side          5V Side           │  │         │   │
│  │                        │  │                                       │  │         │   │
│  │  ESP32 GPIO13 ───────┼─┤  LV1 ──────────────── HV1 ──────┼──┼───────┼─── MG995 Signal
│  │                        │  │  GND                 GND               │  │         │   │
│  │                        │  │  3.3V                HV                │  │         │   │
│  │                        │  │  EN                  EN                │  │         │   │
│  │                        │  └──────────────────────────────┘  │         │   │
│  │                        └───────────────────────────────────┘         │   │
│  │                                                                                  │   │
│  └───────────────────────────────────────────────────────────────┘   │
│                                                                                          │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 6. ESP32 Pin Characteristics

### 6.1 Input/Output Characteristics

| Parameter                 | Value      | Notes                             |
|---------------------------|------------|-----------------------------------|
| **Input Voltage (High)**  | 0.75 × VDD | Minimum 2.4V for 3.3V supply      |
| **Input Voltage (Low)**   | 0.25 × VDD | Maximum 0.8V for 3.3V supply      |
| **Output Voltage (High)** | 0.8 × VDD  | Minimum 2.64V for 3.3V supply     |
| **Output Voltage (Low)**  | 0.1 × VDD  | Maximum 0.33V for 3.3V supply     |
| **Output Current (Max)**  | 40mA       | Per GPIO pin                      |
| **Pull-up Resistor**      | 45kΩ       | Internal, can be enabled/disabled |

### 6.2 Pin Capacities

| Pin Type         | Count | Max Current | Notes                |
|------------------|-------|-------------|----------------------|
| **GPIO**         | 34    | 40mA        | General purpose      |
| **Analog Input** | 18    | -           | ADC1 and ADC2        |
| **PWM**          | 16    | -           | LEDC channels        |
| **I2C**          | 2     | -           | SDA and SCL          |
| **SPI**          | 2     | -           | VSPI and HSPI        |
| **UART**         | 3     | -           | Serial communication |

---

## 7. Pin Usage Summary

### 7.1 Used Pins

```
┌───────────────────────────────────────────────────────────────────────┐
│                                                                                             │
│                              USED PINS SUMMARY                                              │
│                                                                                             │
│  ┌─────────────────────────────────────────────────────────────────┐   │
│  │                                                                                     │   │
│  │  Pin     │ Function      │ Component     │ Status                                  │   │
│  │  ────────────────────────────────────────────────────────────── │   │
│  │  3.3V    │ Power         │ All (3.3V)    │ Used                                   │   │
│  │  VIN     │ Power         │ Servo (5V)    │ Used                                   │   │
│  │  GND     │ Ground        │ All           │ Used                                   │   │
│  │  GPIO21  │ I2C SDA       │ DS3231 RTC    │ Used                                   │   │
│  │  GPIO22  │ I2C SCL       │ DS3231 RTC    │ Used                                   │   │
│  │  GPIO13  │ PWM           │ MG995 Servo   │ Used                                   │   │
│  │  GPIO15  │ SPI CS        │ MAX6675       │ Used                                   │   │
│  │  GPIO14  │ SPI SCK       │ MAX6675       │ Used                                   │   │
│  │  GPIO12  │ SPI SO        │ MAX6675       │ Used                                   │   │
│  │  GPIO5   │ SPI CS        │ MicroSD       │ Used                                   │   │
│  │  GPIO18  │ SPI SCK       │ MicroSD       │ Used                                   │   │
│  │  GPIO23  │ SPI MOSI      │ MicroSD       │ Used                                   │   │
│  │  GPIO19  │ SPI MISO      │ MicroSD       │ Used                                   │   │
│  │                                                                                    │   │
│  └────────────────────────────────────────────────────────────────┘   │
│                                                                                           │
└──────────────────────────────────────────────────────────────────────┘
```

### 7.2 Available Pins

```
┌──────────────────────────────────────────────────────────────────────┐
│                                                                                           │
│                            AVAILABLE PINS                                                 │
│                                                                                           │
│  ┌────────────────────────────────────────────────────────────────┐   │
│  │                                                                                   │   │
│  │  Pin     │ Function           │ Status           │ Notes                         │   │
│  │  ───────────────────────────────────────────────────────────── │   │
│  │  GPIO0   │ General Purpose    │ Available      │ Boot mode (Low = Download)     │   │
│  │  GPIO1   │ UART0 TX           │ Available      │ Serial Monitor                 │   │
│  │  GPIO2   │ General Purpose    │ Available      │ Internal pull-up               │   │
│  │  GPIO3   │ UART0 RX           │ Available      │ Serial Monitor                 │   │
│  │  GPIO4   │ General Purpose    │ Available      │                                │   │
│  │  GPIO9   │ General Purpose    │ Available      │                                │   │
│  │  GPIO10  │ General Purpose    │ Available      │                                │   │
│  │  GPIO11  │ General Purpose    │ Available      │                                │   │
│  │  GPIO16  │ General Purpose    │ Available      │                                │   │
│  │  GPIO17  │ General Purpose    │ Available      │                                │   │
│  │  GPIO25  │ General Purpose    │ Available      │                                │   │
│  │  GPIO26  │ General Purpose    │ Available      │                                │   │
│  │  GPIO27  │ General Purpose    │ Available      │                                │   │
│  │  GPIO32  │ General Purpose    │ Available      │                                │   │
│  │  GPIO33  │ General Purpose    │ Available      │                                │   │
│  │  GPIO34  │ Input Only         │ Available      │ No internal pull-up/pull-down   │   │
│  │  GPIO35  │ Input Only         │ Available      │ No internal pull-up/pull-down   │   │
│  │  GPIO36  │ Input Only         │ Available      │ No internal pull-up/pull-down   │   │
│  │  GPIO39  │ Input Only         │ Available      │ No internal pull-up/pull-down   │   │
│  │                                                                                   │   │
│  └───────────────────────────────────────────────────────────────┘   │
│                                                                                           │
└──────────────────────────────────────────────────────────────────────┘
```
