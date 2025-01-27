# esp32pico_watch 项目
# 基于ESP32微控制器的端侧语音处理系统设计与产品实现
[中文文档](README.md) | [English Documentation](README_en.md)


## 项目概览
[![Watch Video](https://img.shields.io/badge/Watch%20Video-Click%20Here-blue)](https://b23.tv/0AbVd6G)

![9.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/9.png)
![10.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/10.png)

本项目成功设计并实现了一款基于ESP32微控制器的端侧语音处理系统，旨在结合人工智能技术与物联网嵌入式系统，提供低成本、高效率的AI模型部署。项目成果是一款集硬件设备和软件系统于一体的智能手表，具备手势控制和语音识别功能。更正文档：待机时间72h以上。
**硬件开源:https://oshwhub.com/dht3218/esp32picowatch**
## 特性
- **硬件设计**：采用ESP32-PICO-V3-02为核心，集成Wi-Fi和蓝牙功能，并通过SiP封装技术实现小型化。
- **软件设计**：基于MFCC和CNN的音频识别模型在MCU上成功部署，准确率达到95%，响应时间在300ms以内。
- **系统集成**：环境光传感器、全向麦克风、扬声器功放、陀螺仪和TFT显示屏等外设，支持时钟、日历、设置、手电筒和AI问答等功能。
- **用户交互**：通过手势传感器和实体按钮实现用户交互，并具备云端语音识别助手功能。

## 更新内容
### 2025.1.22新增：1.抬腕亮屏实装 demo/wakeupdetectbyhand；2.RTC更新-4G网络更新模式
### 2025.1.27新增：--闹钟实装
#### 新增闹钟程序，可同时设置三个闹钟，使用switch切换开启/关闭；
![11.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/11.png)
#### 闹钟在休眠模式下和正常工作模式下均有效
#### demo/alarmmusic.ino为闹钟铃声demo，提供了一种使用特殊编码格式实现
该手表所搭载的扬声器，目前支持3个八度的音色（使用mp3等格式文件空间占用太大，不适合，特此使用该方法）
### 音符表示方法

音符的表示方式如下：
- `a-g` 表示低音（do-si）
- `1234567` 表示中音（do-si）
- `A-G` 表示高音（do-si）
- `0` 表示休止符

### 时值修饰符

默认速度为 1 倍速，支持以下修饰符：
- `s` 表示 0.75 倍速
- `S` 表示 0.5 倍速
- `l` 表示 1.5 倍速
- `L` 表示 2 倍速

例如：
- `5l` 表示将音符 5 的时长延长到 1.5 倍
- `3s` 表示将音符 3 的时长缩短到 0.75 倍

目前不支持连续的延长符号，如 `5LL`。

<img src="https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/13.png" style="width:50%;">
#### 请看示例代码（长亭外）5l3s5AL0s6As65L0s5l1s23l2s12L005l3s5Al70s6lAl5L05l2s34lg1L006lAlAL07l6s7AL06s7As66s53s10s2L0s53s5Al70s6lAl5l0s5l2s34lg0s1L005L2s34Lg0s1L0000
例如第一段5l表示5音阶加长到1.5倍；3s表示3缩短到0.75
但暂时不支持5LL这样连续的加长
#### 闹钟设定图示
![12.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/12.png)

## 效果展示
### 3.1.0操作逻辑介绍

![0.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/0.png)

本系统采用手势传感器检测（上下左右、按下）五个维度的操作，为主要的UI控制手段；同时右上角的实体按钮作为功能键使用。
#### （1）手势控制：
在所有UI界面上，可以通过上下滑动来切换选中的对象，朝手势传感器按下则表示确认操作；
在没有明确提供返回按钮的界面上，支持统一的右滑返回桌面菜单；
在具有多个按钮、滑块的界面，左右滑动被定义为关闭、开启该选项，并提供了明确的返回按钮。
（具体操作界面见后）
#### （2）功能键
功能键有短按和长按两个功能。
短按功能键将进入息屏休眠，长按功能键进入AI语音助手界面，据使用者的语音指令执行对应操作

### 3.1.1时钟(clock)
 

![1.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/1.png)

从桌面按下确认后进入时钟程序，由板载RTC芯片提供计时功能并由后台任务RTC_task实时刷新时间数据，结合设置(setting)界面的手动、自动校时功能，可以保证时间的准确性。


### 3.1.2设置(setting)


![2.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/2.png)

从桌面按下确认后进入设置主界面，目前功能有：屏幕连续亮度调节、WIFI开启/关闭、时钟校准、网页端设置功能。
其中按下时间校准按钮后会跳转至子界面可选手动设置时间和联网校准时间。
网页端设置主要用于手表端不便于操作的部分，如WIFI信息录入等。

### 3.1.3日历(calendar)
![3.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/3.png)

在日历主界面中，上下滑动可以切换显示的月份，右滑退出程序返回主界面

### 3.1.4 手电筒(light)
![4.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/4.png)

在电筒主界面中，可以通过上下滑动增加/降低亮度，右滑退出程序返回主界面

### 3.1.5 AI问答
![5.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/5.png)

进入程序后，首先进行鉴权请求，如果网络未连接，或请求失败，将会提示“未连接网络”。
在主界面按下手势传感器后，将会进入问答过程： 

![6.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/6.png)

在问答期间可以随时再次按下手势传感器取消对话或右滑退出该程序。

### 3.2 AI语音助手
AI语音助手没有独立的桌面图标入口，而是使用长按功能键在任意界面唤出的方式。

#### 3.2.1 本地识别模型
![8.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/8.png)

采用MFCC进行特征提取后，使用（主体）4层卷积神经网络进行分类，得到结果后，返回指定的标签值（如setting），在检测到label发生变化后，将自动跳转到对应的界面，实现简单的语音助手功能。

#### 3.2.2 云端识别模型
![7.png](https://raw.githubusercontent.com/dht3218/esp32pico_watch/main/pictures/7.png)

通过类似于AI问答的流程，将采集到的语音信息转文字后让云端LLM模型自主判断，返回什么参数，本地解析返回之后执行对应指令，具有一定的任务自主规划能力。
prompt如下：
```
你需要根据我提供的信息进行推理并返回指定的数据：你现在可以控制一块智能手表，返回值只允许必须从以下范围取出：（setting，light，calendar，clock），请务必按要求根据下面的任务要求返回指定的字符串，不允许返回上述字符串以外的任何值，如calendar，日期相关请返回calendar，时刻相关返回clock以下是任务：
```
通过以上设定可以使系统按预期工作。
使用prompt直接接入LLM的好处是，不需要针对具体长期收集大量训练数据集进行微调，只需要逐步优化prompt提示词即可，降低使用者的调节门槛，同时减少对特定模型的依赖性，实现去耦的效果。

## 特性

- **硬件设计**：采用ESP32-PICO-V3-02为核心，集成Wi-Fi和蓝牙功能，并通过SiP封装技术实现小型化。
- **软件设计**：基于MFCC和CNN的音频识别模型在MCU上成功部署，准确率达到95%，响应时间在300ms以内。
- **系统集成**：环境光传感器、全向麦克风、扬声器功放、陀螺仪和TFT显示屏等外设，支持时钟、日历、设置、手电筒和AI问答等功能。
- **用户交互**：通过手势传感器和实体按钮实现用户交互，并具备云端语音识别助手功能。

## 目录结构
- demos/                       # 功能测试程序
- libraries/                   # 主要用到的库
- ui/                          # UI和外设代码
  - ui.ino                    # 主程序
  - port_indev.ino            # 输入设备注册
  - cw2015                    # 电池电量相关
  - clock                     # 时钟程序
  - user_led                  # 屏幕亮度调节
  - WIFItask                  # 网络配置
  - AiassistantLocal           # 本地语音识别模型
  - AiassistantWeb             # 云端语音程序
- demos/Ailocal/                 # 本地模型训练数据采集
  - datagetdemo/              # 烧录到板子上进行数据采集
  - datareceive/              # 用于数据采集的pc端py程序
- LVGL相关学习文档.docx         # 学习笔记和UI逻辑原理
- UItest1/                      # UI设计的squareline studio源文件
- picofinal.stl                 # 外壳文件


## 硬件系统设计与实现

### 器件选型

- **核心微控制器**：ESP32-PICO-V3-02，集成2.4GHz Wi-Fi 和蓝牙双模。
- **外设**：
  - 手势传感器：APDS9960（I2C）
  - 电量计：cw2015 (I2C)
  - 全向麦克风：MSM261；扬声器功放：MAX98357A（I2S）
  - 陀螺仪：MPU6050（I2C）
  - 显示：1.69寸 TFT屏，ST7789V驱动（SPI）

## 软件设计

### 基于梅尔倒谱系数的音频识别模型

- **数据提取**：从全向麦克风MSM261中以I2S协议传出，每次获取512byte数据。
- **MFCC特征提取**：基于MFCC和CNN的音频识别模型，准确率达到95%。
- **卷积神经网络分类器**：使用TensorFlow-lite框架，实现在MCU上的部署。

### 云端模型的流式调用

- **数据采集**：通过I2S协议从麦克风中读出音频数据，并使用Base64格式编码上传。
- **云端STT处理**：使用百度智能云提供的STT服务器进行语音转文字处理。
- **接入云端大语言模型**：通过流式传输接入云端大语言模型，实现智能化控制。

--------
## 本地模型
### 训练数据采集
esp32pico_watch\demos\Ailocal\datagetdemo文件夹中的程序为本地模型训练数据采集（不需要SD卡），
请配合esp32pico169\demos\Ailocal\datareceive文件夹中的py文件进行串口收集，
1. 确保串口正确配置并运行py程序。
2. 按下板子的复位键，在py终端提醒start后开始说话，直到出现found。
3. 出现found后，通过串口传输音频数据，期间不要关闭py也不要复位板子，直到提示文件保存完成。
4. 文件保存完成后，请迅速按下板子复位键，进行新一轮数据采集。数据采集到的音频文件名称可以在py文件中自行修改，实测导入Edge impulse中可用。

### 替换文件
训练完成后，
请将 esp32pico_watch\demos\Ailocal 的 depthwise_conv.c 和conv.c 
文件替换到 esp32pico_watch\libraries\pico_detect_inferencing\src\edge-impulse-sdk\tensorflow\lite\micro\kernels 中，
以避免由于ESPidf版本太小而导致的错误。

## 云端模型接入
接入云端模型部分参考了 [厚国兄的实现](https://gitee.com/chging/esp32s3-ai-chat/)。具体实现可以star他后从前述地址中参考学习。
将原本的文心一言替换为了讯飞星火Spark pro具有联网搜索功能和实时天气查询的能力。（需要自己申请API）

## 注意事项
- 请确保在使用前已自行申请讯飞星火Spark pro的API。
- 本项目使用LVGL进行UI设计，相关学习文档包含设计原理和app编写规范。

## 贡献与支持
欢迎对本项目进行贡献，如有任何问题，欢迎提出Issue或Pull Request。

## 参考文献

[1] 郭佳淇,张继通.基于MFCC和HMM的语音识别优化方法研究[J].电声技术,2024,48(10):83-85.DOI:10.16311/j.audioe.2024.10.024.

[2] 杨阳;陈永明;.声纹识别技术及其应用[J].电声技术,2007(02):46-47+51.

[3] 王刚.基于脉冲神经网络的音频信号分类算法研究[D].东南大学,2021.DOI:10.27014/d.cnki.gdnau.2021.004522.

[4] 卢潇. 基于FPGA的声纹识别系统研究与实现[D].电子科技大学,2024.DOI:10.27005/d.cnki.gdzku.2024.001946.

[5] [接入云端模型，厚国兄的实现](https://gitee.com/chging/esp32s3-ai-chat/)

