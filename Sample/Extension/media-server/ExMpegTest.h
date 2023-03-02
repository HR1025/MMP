#pragma once

#include <string>

namespace Mmp
{

/**
 * @brief      TS 分流测试
 * @param[in]  tsPath   : ts 文件路径
 * @note       1 - 使用 ffmpeg 生成 ts 文件 : 
 *                 ffmpeg -i xxx.mp4 -codec copy -vbsf h264_mp4toannexb -absf aac_adtstoasc xxx.ts
 *                 MP4 视频压缩格式 H264, 音频 AAC
 *             2 - demux 的输出文件存放在 tsPath 同级目录下
 */
void MpegTsDemuxTest(const std::string& tsPath);

// void MpegPsTest();

} // namespace Mmp
