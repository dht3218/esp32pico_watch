# esp32pico_watch 项目

## 概述
基于esp32 pico v3 02的手表设计，结合云端模型和本地语音识别模型，提供智能化控制能力。

## 特性
- 支持Air700E 低功耗4G模块和MPU6050。
- 集成了基于edge impulse的本地语音识别模型。
- 接入云端大模型的语音程序，替换为讯飞星火Spark pro，具备联网搜索功能和实时天气查询能力。

## 目录结构
esp32pico_watch/
├── demos/                       # 功能测试程序
├── libraries/                   # 主要用到的库
├── ui/                          # UI和外设代码
│   ├── ui.ino                    # 主程序
│   ├── port_indev.ino            # 输入设备注册
│   ├── cw2015                    # 电池电量相关
│   ├── clock                     # 时钟程序
│   ├── user_led                  # 屏幕亮度调节
│   ├── WIFItask                  # 网络配置
│   ├── AiassistantLocal           # 本地语音识别模型
│   └── AiassistantWeb             # 云端语音程序
├── esp32pico_watch\demos\Ailocal\ # 本地模型训练数据采集
│   ├── datagetdemo/               #烧录到板子上进行数据采集
│   └── datareceive/                #用于数据采集的pc端py程序
├── LVGL相关学习文档.docx         # 学习笔记和ui逻辑原理
└── UItest1/                      # UI设计的squareline studio源文件
└── picofinal.stl                 # 外壳文件


## 硬件支持
- **Air700E 4G模块**：低功耗4G模块，已测试可用。
- **MPU6050**：已测试可用，尚未在软件上实装。

## 软件配置
- **Arduino IDE**：所有文件需放在同一个文件夹内。
- **Libraries**：`Arduino_APDS9960` 库需使用修改后的版本以支持国产ID为0xa8的传感器。

## 本地模型训练数据采集
1. 确保串口正确配置并运行py程序。
2. 按下板子的复位键，在py终端提醒start后开始说话，直到出现found。
3. 出现found后，通过串口传输音频数据，期间不要关闭py也不要复位板子，直到提示文件保存完成。
4. 文件保存完成后，请迅速按下板子复位键，进行新一轮数据采集。数据采集到的音频文件名称可以在py文件中自行修改，实测导入Edge impulse中可用。

## 替换文件
训练完成后，请将 `esp32pico_watch\demos\Ailocal` 的 `depthwise_conv.c` 和 `conv.c` 文件替换到 `esp32pico_watch\libraries\pico_detect_inferencing\src\edge-impulse-sdk\tensorflow\lite\micro\kernels` 中，以避免由于ESPidf版本太小而导致的错误。

## 云端模型接入
接入云端模型部分参考了 [厚国兄的实现](https://gitee.com/chging/esp32s3-ai-chat/)。具体实现可以star他后从前述地址中参考学习。由于网络原因，如果链接无法访问，请检查链接的合法性并适当重试。

## 注意事项
- 请确保在使用前已自行申请讯飞星火Spark pro的API。
- 本项目使用LVGL进行UI设计，相关学习文档包含设计原理和app编写规范。

## 贡献与支持
欢迎对本项目进行贡献，如有任何问题，欢迎提出Issue或Pull Request。
