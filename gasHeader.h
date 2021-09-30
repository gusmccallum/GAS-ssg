#ifndef SDDS_GASHEADER_H
#define SDDS_GASHEADER_H

#include <string>


static void processText(std::string fileName, int fileType);
static void newFolder();
std::string makeHeader1(std::string line);
std::string hzRule(std::string line);


#endif