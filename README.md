# esp32pico_watch
基于esp32 pico v3 02的手表设计，并将云端模型和本地语音识别模型组合使用，提供智能化控制能力
由于Arduino IDE特性，所有文件只能放在同一个文件夹内，因此ui文件夹中实际包含了部分外设代码。
Libraries-Arduino_APDS9960库不能直接从库管理器中下载（否则不认国产ID为0xa8的传感器），经过修改后的库可以避免该问题。
本设备包含了Air700E 低功耗4g模块和MPU6050，经测试是可用的，但还没有在软件上实装。

demos文件夹中包含了几个功能的测试程序
libraries文件夹包含了几个主要用到的库
ui文件夹中：
ui.ino——主程序
port_indev.ino——输入设备注册
cw2015——电池电量相关
clock——时钟程序
user_led——屏幕亮度调节
WIFItask——网络配置
AiassistantLocal——基于edge impulse的本地语音识别模型
AiassistantWeb——接入云端大模型的语音程序


其中接入云端模型部分参考了：https://gitee.com/chging/esp32s3-ai-chat/的作者厚国兄的实现，具体实现可以star他后从前述地址中参考学习
将原本的文心一言替换为了讯飞星火Spark pro具有联网搜索功能和实时天气查询的能力。（需要自己申请API）


esp32pico_watch\demos\Ailocal\datagetdemo文件夹中的程序为本地模型训练数据采集（不需要SD卡），
请配合esp32pico169\demos\Ailocal\datareceive文件夹中的py文件进行串口收集，
步骤：
1.确保串口正确配置并运行py程序
2.按下板子的复位键，在py终端提醒start后开始说话，直到出现found
3.出现found后，通过串口传输音频数据，期间不要关闭py也不要复位板子，直到提示文件保存完成
4.文件保存完成后，请迅速按下板子复位键，进行新一轮数据采集。数据采集到的音频文件名称可以在py文件中自行修改，实测导入Edge impulse中可用

esp32pico_watch\demos\Ailocal的depthwise_conv.c和conv.c文件，
请在自己训练完后替换到esp32pico_watch\libraries\pico_detect_inferencing\src\edge-impulse-sdk\tensorflow\lite\micro\kernels中，可以避免由于ESPidf版本太小而导致的错误

LVGL相关学习文档.docx中包含了部分的学习笔记，同时在最后给出了桌面自适应菜单的设计原理，以及app的编写规范。
UItest1文件夹包含了UI设计的squareline studio源文件

picofinal.stl为外壳文件
