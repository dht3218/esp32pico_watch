import serial
import struct
import time

# 配置串口
ser = serial.Serial('COM23', 115200, timeout=1)  # 替换 'COM21' 为您的串口号

# WAV文件参数
SAMPLE_RATE = 16000  # 采样率
SAMPLE_BITS = 16    # 样本位数（16位深度）
CHANNELS = 1        # 声道数（1为单声道）
WAV_HEADER_SIZE = 44  # WAV文件头的大小

# 标志位
SIGNATURE = b'%'
SIGNATURESTART = b'#'
signature_found = False
raw_audio_data = b''  # 用于存储原始音频数据

# 生成WAV文件头
def generate_wav_header(wav_size, sample_rate, sample_bits, channels):
    file_size = wav_size + WAV_HEADER_SIZE - 8
    byte_rate = sample_rate * channels * sample_bits // 8
    block_align = channels * sample_bits // 8
    header = (
        b'RIFF'                    # ChunkID
        + struct.pack('<I', file_size)  # ChunkSize
        + b'WAVE'                    # Format
        + b'fmt '                    # Subchunk1ID
        + struct.pack('<I', 16)        # Subchunk1Size
        + struct.pack('<HH', 1, channels)  # AudioFormat, NumChannels
        + struct.pack('<I', sample_rate)  # SampleRate
        + struct.pack('<I', byte_rate)    # ByteRate
        + struct.pack('<HH', block_align, sample_bits)  # BlockAlign, BitsPerSample
        + b'data'                    # Subchunk2ID
        + struct.pack('<I', wav_size)     # Subchunk2Size
    )
    return header
file_count=0
# 接收数据并检查标志位
while(1):
    while (1):
        data = ser.read(1)  # 读取1字节
        if data == SIGNATURESTART:
            print("Start")
        if data == SIGNATURE:
            print("found")
            signature_found = True
            raw_audio_data = b''  # 重置原始音频数据缓冲区

            start_time = time.time()
            while True:
                data = ser.read(1024)  # 读取1024字节
                if not data:
                    # 检查是否已经过了1秒或者更多
                    if time.time() - start_time > 1:
                        print("received")
                        file_count = file_count+1
                        # 生成WAV文件头并保存文件
                        wav_header = generate_wav_header(len(raw_audio_data), SAMPLE_RATE, SAMPLE_BITS, CHANNELS)
                        filename = f'light.{file_count:03d}.wav'  # 生成文件名
                        with open(filename, 'wb') as wf:
                            wf.write(wav_header + raw_audio_data)
                            print("WAV file saved!")
                            signature_found=0
                        break
                    continue
                raw_audio_data += data





# 关闭串口
ser.close()


# import numpy as np
# from scipy.optimize import fsolve
#
# ni=1e-5
# eg=3.26
# k=8.66667E-05
# xita=4.9
# u=2830
# Hmax=6.05218e28
#
# def equation(x):
#     return (((ni)*((x/300)**(1.5))*(2.718**(eg/2/k*(1/300-1/x)))+1e16)**2/(np.sqrt(xita)*u)-Hmax)
#
# x=fsolve(equation,1000000)
# print(" x =",x[0])
#
#
#
#
#
# ni=1e-5
# eg=3.26
# k=8.66667E-05
# nimax=3.35486e12
# def equation1(x):
#     return ((ni)*((x/300)**(1.5))*(2.718**(eg/2/k*(1/300-1/x)))-nimax)
#
# x=fsolve(equation1,2000)
# print(" x =",x[0])