#include <memory>
#include <string>

#include "Common/Logger.h"

int main()
{
    Mmp::Logger logger;

    logger.SetFilePath("./smaple.log");
    logger.Enable(Mmp::Logger::Direction::CONSLOE);
    logger.Enable(Mmp::Logger::Direction::FILE);

    logger.Log(__LINE__, __FILE__, Mmp::Logger::Level::WARN, "Common", "Hello World");

    return 0;
}