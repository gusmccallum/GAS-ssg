
#ifndef SDDS_GASHEADER_H
#define SDDS_GASHEADER_H

#include <string>

static void processText(std::string fileName, int fileType, std::string = "",
                        std::string = "", std::string = "./dist");

static void newFolder(std::string = "./dist");

bool isText(std::string inLine);

bool isMarkDown(std::string inLine);

bool isFolder(std::string inLine);

bool isJson(std::string inLine);

std::string makeHeader1(std::string line);

std::string hzRule(std::string line);

std::string getJsonValue(std::string line);

void processJsonFormat(std::string file);

#endif
