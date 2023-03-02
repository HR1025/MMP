#include "ExMpegTest.h"

#include <cstdint>
#include <cassert>
#include <fstream>

#ifdef USE_MEDIA_SERVER_MPEG
#include "Common/LogMessage.h"
#include "Sample/Common/Utility.h"
#include "mpeg-ts.h"
#endif /* USE_MEDIA_SERVER_MPEG */

namespace Mmp
{
#ifdef USE_MEDIA_SERVER_MPEG

#define TS_PACKET_SIZE		188

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

static int on_ts_packet(void* ts, int program, int stream, int avtype, int flags, int64_t pts, int64_t dts, const void* data, size_t bytes)
{
    MMP_LOG_INFO << "[" << ts_type(avtype) << "] pts is: " << pts << ", dts is: " << dts << ", size is: " << bytes;
    return 0;
}

void MpegTsDemuxTest(const std::string& tsPath, const std::string& h264Path /* unused */)
{
    InitLogger();

    std::ifstream ifs;
    struct ts_demuxer_t *ts;
    uint8_t tsPacket[TS_PACKET_SIZE] = {0};

    ifs.open(tsPath);
    if (!ifs.is_open())
    {
        MMP_LOG_ERROR << "Open ts file fail, file path is: " << tsPath;
        return;
    }
    
    ts = ts_demuxer_create(on_ts_packet, nullptr);

    while (!ifs.eof())
    {
        ifs.read(reinterpret_cast<char*>(tsPacket), TS_PACKET_SIZE);
        if (ifs.gcount() != TS_PACKET_SIZE) break;
        ts_demuxer_input(ts, tsPacket, sizeof(tsPacket));
    }

    ts_demuxer_flush(ts);
    ts_demuxer_destroy(ts);
    ifs.close();
}

#else
void MpegTsDemuxTest(const std::string& tsPath, const std::string& h264Path)
{

}
#endif /* USE_MEDIA_SERVER_MPEG */
}