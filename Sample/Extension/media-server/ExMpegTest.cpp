#include "ExMpegTest.h"

#include <cstdint>
#include <cassert>
#include <fstream>

#ifdef USE_MEDIA_SERVER_MPEG
#include <Poco/Path.h>
#include <Poco/File.h>
#include "Common/LogMessage.h"
#include "Sample/Common/Utility.h"
#include "mpeg-ts.h"
#endif /* USE_MEDIA_SERVER_MPEG */

namespace Mmp
{
#ifdef USE_MEDIA_SERVER_MPEG

#define TS_PACKET_SIZE		188

namespace field
{
constexpr char kUnknownRawVideoSuffix[] = "video";
constexpr char kH264Suffix[]            = "264";
constexpr char kH265Suffix[]            = "265";
constexpr char kUnknownRawAudioSuffix[] = "audio";
constexpr char kAacSuffix[]             = "aac";
// constexpr char kMp3Suffix[]             = "mp3";
} // namespace field

const std::string ts_type(int type)
{
	switch (type)
	{
        case PSI_STREAM_MP3:  return "MP3 ";
        case PSI_STREAM_AAC:  return "AAC ";
        case PSI_STREAM_H264: return "H264";
        case PSI_STREAM_H265: return "H265";
        default: return "*";
	}
}

static std::ofstream vofs;
static std::ofstream aofs;
static int           videoType = PSI_STREAM_RESERVED;
static int           audioType = PSI_STREAM_RESERVED;

static int on_ts_packet(void* ts, int program, int stream, int avtype, int flags, int64_t pts, int64_t dts, const void* data, size_t bytes)
{
    // MMP_LOG_INFO << "[" << ts_type(avtype) << "] pts is: " << pts << ", dts is: " << dts << ", size is: " << bytes;
    if (avtype == PSI_STREAM_H264 || avtype == PSI_STREAM_H265)
    {
        videoType = avtype;
        vofs.write(reinterpret_cast<const char*>(data), bytes);
    }
    else if (avtype == PSI_STREAM_AAC)
    {
        audioType = avtype;
        aofs.write(reinterpret_cast<const char*>(data), bytes);
    }

    return 0;
}

void MpegTsDemuxTest(const std::string& tsPath)
{
    InitLogger();

    std::ifstream ifs;
    struct ts_demuxer_t *ts;
    uint8_t tsPacket[TS_PACKET_SIZE] = {0};
    std::string videoPath;
    std::string audioPath;

    ifs.open(tsPath);
    if (!ifs.is_open())
    {
        MMP_LOG_ERROR << "Open ts file fail, file path is: " << tsPath;
        return;
    }
    
    {
        Poco::Path path(tsPath);
        videoPath = path.parent().toString() + path.getBaseName() + "." + field::kUnknownRawVideoSuffix;
        audioPath = path.parent().toString() + path.getBaseName() + "." + field::kUnknownRawAudioSuffix;
        vofs.open(videoPath);
        if (!vofs.is_open())
        {
            MMP_LOG_ERROR << "Open raw video file fail, file path is: " << videoPath;
            return;
        } 
        aofs.open(audioPath);
        if (!aofs.is_open())
        {
            vofs.close();
            MMP_LOG_ERROR << "Open raw audio file fail, file path is: " << audioPath;
            return;
        } 
    }

    ts = ts_demuxer_create(on_ts_packet, nullptr);

    while (!ifs.eof())
    {
        ifs.read(reinterpret_cast<char*>(tsPacket), TS_PACKET_SIZE);
        if (ifs.gcount() != TS_PACKET_SIZE) break;
        ts_demuxer_input(ts, tsPacket, sizeof(tsPacket));
    }

    {
        Poco::Path path(tsPath);
        vofs.flush();
        aofs.flush();
        vofs.close();
        aofs.close();
        Poco::File vf(videoPath);
        Poco::File af(audioPath);
        if (videoType == PSI_STREAM_RESERVED)
        {
            vf.remove();
        }
        else if (videoType == PSI_STREAM_H264)
        {
            vf.renameTo(path.parent().toString() + path.getBaseName() + "." + field::kH264Suffix);
        }
        else if (videoType == PSI_STREAM_H265)
        {
            vf.renameTo(path.parent().toString() + path.getBaseName() + "." + field::kH265Suffix);
        }
        if (audioType == PSI_STREAM_RESERVED)
        {
            af.remove();
        }
        else if (audioType == PSI_STREAM_AAC)
        {
            af.renameTo(path.parent().toString() + path.getBaseName() + "." + field::kAacSuffix);
        }
        videoType = PSI_STREAM_RESERVED;
        audioType = PSI_STREAM_RESERVED;
    }

    ts_demuxer_flush(ts);
    ts_demuxer_destroy(ts);
    ifs.close();
}

#else
void MpegTsDemuxTest(const std::string& tsPath)
{

}
#endif /* USE_MEDIA_SERVER_MPEG */
}