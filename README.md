# esp32pico_watch 项目
# 基于ESP32微控制器的端侧语音处理系统设计与产品实现

## 项目概览

本项目成功设计并实现了一款基于ESP32微控制器的端侧语音处理系统，旨在结合人工智能技术与物联网嵌入式系统，提供低成本、高效率的AI模型部署。项目成果是一款集硬件设备和软件系统于一体的智能手表，具备手势控制和语音识别功能。

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

