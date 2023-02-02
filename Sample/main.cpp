#include <memory>
#include <string>

#include <Poco/Message.h>
#include <Poco/LoggingFactory.h>
#include <Poco/FileChannel.h>
#include <Poco/ConsoleChannel.h>

using namespace Poco;

int main()
{
    // auto fileChannel
    auto consoleChannel = LoggingFactory::defaultFactory().createChannel("ConsoleChannel");

    Message msg("source", "Hello World", Message::PRIO_WARNING);
    consoleChannel->log(msg);

    return 0;
}