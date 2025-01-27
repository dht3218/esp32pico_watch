# esp32pico_watch Project
# Design and Implementation of an End-Side Speech Processing System Based on ESP32 Microcontroller

[Chinese Documentation](README.md) | [English Documentation](README_en.md)

## Video Demonstration
[![14.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/14.png)](https://player.bilibili.com/player.html?isOutside=true&aid=113685318076176&bvid=BV1Jmk2Y1ESa&cid=27441235894&p=1)

## Project Overview

![9.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/9.png)
![10.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/10.png)

This project successfully designs and implements an end-side speech processing system based on the ESP32 microcontroller, aiming to combine AI technology with IoT embedded systems to provide a low-cost, high-efficiency AI model deployment. The outcome is an integrated hardware and software system in the form of a smartwatch that supports gesture control and voice recognition. The device has a standby time of over 72 hours.

**Hardware Open Source:** [https://oshwhub.com/dht3218/esp32picowatch](https://oshwhub.com/dht3218/esp32picowatch)

## Features

- **Hardware Design**: Uses ESP32-PICO-V3-02 as the core, integrating Wi-Fi and Bluetooth functionalities, and achieving miniaturization through SiP packaging technology.
- **Software Design**: Successfully deploys an audio recognition model based on MFCC and CNN on the MCU, achieving 95% accuracy with a response time within 300ms.
- **System Integration**: Integrates ambient light sensors, omnidirectional microphones, speaker amplifiers, gyroscopes, and TFT displays, supporting features like clock, calendar, settings, flashlight, and AI Q&A.
- **User Interaction**: Achieves user interaction through gesture sensors and physical buttons, and includes cloud-based voice recognition assistant functionality.

## Update Logs

### 2025.1.22 Added:
1. Wrist-lift screen wake-up demo: `demo/wakeupdetectbyhand`
2. RTC update - 4G network update mode

### 2025.1.27 Added:
- Alarm function implementation
  - Supports setting up to three alarms, using a switch to toggle on/off.
  - ![11.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/11.png)
  - The alarm works both in sleep mode and normal operation mode.
  - `demo/alarmmusic.ino` provides a demo for alarm sound using a special encoding format.
    - The watch's speaker supports three octaves of notes (using MP3 files would occupy too much space, so this method is used).
    - Notes are represented as follows: 
      - `a-g` for low notes (do-si)
      - `1234567` for mid-range notes (do-si)
      - `A-G` for high notes (do-si)
      - `0` for rest
    - Duration modifiers: 
      - Default speed = 1x
      - `s` = 0.75x
      - `S` = 0.5x
      - `l` = 1.5x
      - `L` = 2x
    - Example code (`Long Ting Wai`):
      ```
      5l3s5AL0s6As65L0s5l1s23l2s12L005l3s5Al70s6lAl5L05l2s34lg1L006lAlAL07l6s7AL06s7As66s53s10s2L0s53s5Al70s6lAl5L05l2s34lg0s1L005L2s34Lg0s1L0000
      ```
    - For example:
      - `5l` indicates that the duration of note 5 is extended to 1.5 times
      - `3s` indicates that the duration of note 3 is shortened to 0.75 times
    - Currently does not support consecutive extensions like `5LL`.

#### Alarm Setting Diagram
![12.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/12.png)

## Demonstration

### 3.1.0 Operation Logic Introduction

![0.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/0.png)

The system uses gesture sensors to detect five-dimensional operations (up, down, left, right, press), primarily for UI control, while the physical button at the top-right corner serves as a function key.

#### (1) Gesture Control:
- In all UI interfaces, swipe up or down to switch selected objects; press the gesture sensor to confirm.
- Right-swipe returns to the main menu if no explicit back button is provided.
- Left or right swipes in multi-button/slider interfaces toggle options on/off, with clear return buttons.

#### (2) Function Key:
- Short press enters screen-off sleep mode.
- Long press enters the AI voice assistant interface, executing commands based on user voice input.

### 3.1.1 Clock (clock)

![1.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/1.png)

From the home screen, pressing the confirmation button enters the clock program, which uses the onboard RTC chip for timing and updates time data via the background task `RTC_task`. Time synchronization can be manually or automatically adjusted via the settings interface.

### 3.1.2 Settings (setting)

![2.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/2.png)

From the home screen, pressing the confirmation button enters the main settings interface, which currently includes:
- Screen brightness adjustment
- Wi-Fi on/off
- Time calibration
- Web-based settings (for tasks inconvenient on the watch, such as entering Wi-Fi information)

### 3.1.3 Calendar (calendar)

![3.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/3.png)

In the calendar main interface, swipe up or down to switch months, and right-swipe to exit and return to the main menu.

### 3.1.4 Flashlight (light)

![4.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/4.png)

In the flashlight main interface, swipe up or down to increase/decrease brightness, and right-swipe to exit and return to the main menu.

### 3.1.5 AI Q&A

![5.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/5.png)

After entering the program, it first performs an authentication request. If the network is disconnected or the request fails, it will display "Not Connected to Network."
Pressing the gesture sensor starts the Q&A process:

![6.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/6.png)

During the Q&A session, you can cancel the conversation by pressing the gesture sensor again or right-swiping to exit the program.

### 3.2 AI Voice Assistant

The AI voice assistant does not have a dedicated icon on the home screen but can be invoked by long-pressing the function key from any interface.

#### 3.2.1 Local Recognition Model

![8.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/8.png)

Uses MFCC for feature extraction followed by classification using a 4-layer CNN, returning specific labels (e.g., `setting`). When a label change is detected, it automatically jumps to the corresponding interface, implementing basic voice assistant functionality.

#### 3.2.2 Cloud-Based Recognition Model

![7.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/7.png)

Similar to AI Q&A, collected voice data is converted to text and processed by a cloud-based LLM, returning parameters that the local system parses and executes accordingly. This setup allows for autonomous task planning.

Prompt example:
```
You need to infer and return specified data based on the information I provide: You can now control a smartwatch. Return values must only be from the following range: (setting, light, calendar, clock). Please ensure you return one of these strings strictly according to the task requirements.***
```

Using prompts directly connects to LLMs without requiring extensive training datasets, reducing user tuning effort and minimizing dependency on specific models.

## Features

- **Hardware Design**: Uses ESP32-PICO-V3-02 as the core, integrating Wi-Fi and Bluetooth functionalities, and achieving miniaturization through SiP packaging technology.
- **Software Design**: Successfully deploys an audio recognition model based on MFCC and CNN on the MCU, achieving 95% accuracy with a response time within 300ms.
- **System Integration**: Integrates ambient light sensors, omnidirectional microphones, speaker amplifiers, gyroscopes, and TFT displays, supporting features like clock, calendar, settings, flashlight, and AI Q&A.
- **User Interaction**: Achieves user interaction through gesture sensors and physical buttons, and includes cloud-based voice recognition assistant functionality.

## Directory Structure

- `demos/`                       # Functional test programs
- `libraries/`                   # Main libraries used
- `ui/`                          # UI and peripheral code
  - `ui.ino`                    # Main program
  - `port_indev.ino`            # Input device registration
  - `cw2015`                    # Battery management
  - `clock`                     # Clock program
  - `user_led`                  # Screen brightness adjustment
  - `WIFItask`                  # Network configuration
  - `AiassistantLocal`          # Local voice recognition model
  - `AiassistantWeb`            # Cloud-based voice program
- `demos/Ailocal/`               # Local model training data collection
  - `datagetdemo/`              # Data collection program burned onto the board
  - `datareceive/`              # PC-side Python program for data collection
- `LVGL相关学习文档.docx`         # Learning notes and UI logic principles
- `UItest1/`                      # UI design source files in Squareline Studio
- `picofinal.stl`                 # Enclosure file

## Hardware System Design and Implementation

### Component Selection

- **Core Microcontroller**: ESP32-PICO-V3-02, integrating 2.4GHz Wi-Fi and Bluetooth dual-mode.
- **Peripherals**:
  - Gesture Sensor: APDS9960 (I2C)
  - Battery Management: cw2015 (I2C)
  - Omnidirectional Microphone: MSM261; Speaker Amplifier: MAX98357A (I2S)
  - Gyroscope: MPU6050 (I2C)
  - Display: 1.69-inch TFT screen, driven by ST7789V (SPI)

## Software Design

### Audio Recognition Model Based on Mel-Frequency Cepstral Coefficients (MFCC)

- **Data Extraction**: Acquires 512-byte data from the omnidirectional microphone MSM261 via I2S protocol.
- **MFCC Feature Extraction**: An audio recognition model based on MFCC and CNN achieves 95% accuracy.
- **Convolutional Neural Network Classifier**: Implemented using TensorFlow Lite framework for deployment on the MCU.

### Streaming Call of Cloud-Based Models

- **Data Collection**: Reads audio data from the microphone via I2S protocol and uploads it using Base64 encoding.
- **Cloud-Based STT Processing**: Uses Baidu Intelligent Cloud's STT server for speech-to-text conversion.
- **Accessing Cloud-Based LLM**: Implements intelligent control through streaming access to cloud-based LLMs.

---

## Local Model

### Training Data Collection

The program in `esp32pico_watch\demos\Ailocal\datagetdemo` folder collects training data for the local model (no SD card required).

1. Ensure correct serial port configuration and run the Python script.
2. Press the reset button on the board; start speaking when the Python terminal prompts "start" until "found" appears.
3. After "found", audio data is transmitted via serial port. Do not close the Python script or reset the board until "file saved" is prompted.
4. Quickly press the reset button for the next round of data collection. Modify audio file names in the Python script as needed. Verified compatibility with Edge Impulse.

### File Replacement

After training, replace the following files:
- Replace `depthwise_conv.c` and `conv.c` in `esp32pico_watch\demos\Ailocal` with those in `esp32pico_watch\libraries\pico_detect_inferencing\src\edge-impulse-sdk\tensorflow\lite\micro\kernels` to avoid errors due to small ESP-IDF versions.

## Cloud-Based Model Access

Referenced [Hou Guo's implementation](https://gitee.com/chging/esp32s3-ai-chat/) for cloud-based model integration. Specifically, replaced Wenxin Yiyang with Xunfei Spark Pro, which supports internet search and real-time weather queries (API key required).

## Precautions

- Ensure you have applied for an API key for Xunfei Spark Pro before use.
- This project uses LVGL for UI design; related learning documents include design principles and app writing guidelines.

## Contributions and Support

Contributions to this project are welcome. If you have any questions, feel free to open an Issue or Pull Request.

## References

[1] Guo Jiaqi, Zhang Jitong. Research on Optimization Methods of Speech Recognition Based on MFCC and HMM [J]. Audio Technology, 2024, 48(10):83-85. DOI:10.16311/j.audioe.2024.10.024.

[2] Yang Yang, Chen Yongming. Voiceprint Recognition Technology and Its Applications [J]. Audio Technology, 2007(02):46-47+51.

[3] Wang Gang. Research on Audio Signal Classification Algorithm Based on Spiking Neural Networks [D]. Southeast University, 2021. DOI:10.27014/d.cnki.gdnau.2021.004522.

[4] Lu Xiao. Research and Implementation of Voiceprint Recognition System Based on FPGA [D]. University of Electronic Science and Technology of China, 2024. DOI:10.27005/d.cnki.gdzku.2024.001946.

[5] [Cloud-Based Model Integration, Hou Guo's Implementation](https://gitee.com/chging/esp32s3-ai-chat/)
