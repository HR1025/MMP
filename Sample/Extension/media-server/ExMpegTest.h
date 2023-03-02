#pragma once

#include <string>

namespace Mmp
{

/**
 * @brief      TS 分流测试
 * @param[in]  tsPath   : ts 文件路径
 * @param[out] h264Path : 264 文件
 * @note       1 - 使用 ffmpeg 生成 ts 文件 : 
 *                 ffmpeg -i xxx.mp4 -codec copy -vbsf h264_mp4toannexb -absf aac_adtstoasc xxx.ts
 *                 MP4 视频压缩格式 H264, 音频 AAC
 *             2 - 暂未实现输出 h264 文件
 *             3 - 音频流忽略,只保留视频流
 */
void MpegTsDemuxTest(const std::string& tsPath, const std::string& h264Path);

// void MpegPsTest();

} // namespace Mmp
