
#include "../include/gasHeader.hpp"

int main(int argc, char **argv) {

  if (argc < 1) {
    // Empty argument list
    return -1;
  }

  std::string cliString = argv[1];

  // validate input
  if (cliString.length() < 2 && cliString != "-v" && cliString != "--version" &&
      cliString != "-h" && cliString != "--help" && cliString != "-i" &&
      cliString != "--input" && cliString != "-c" && cliString != "--config") {
    std::cout << "Invalid entry." << std::endl;
    return -1;
  }
  if (cliString == "-c" || cliString == "--config") {
    std::string input = argv[2];
    if (isJson(input)) {
      processJsonFormat(input);
    } else {
      std::cout << "Invalid entry." << std::endl;
      return -1;
    }
  } else {
    // version argument
    if (cliString == "-v" || cliString == "--version") {
      std::cout << "*********************************\n"
                << "*********************************\n"
                << "****                         ****\n"
                << "**** Gus' Awesome Ssg V1.0.0 ****\n"
                << "****                         ****\n"
                << "*********************************\n"
                   "*********************************"
                << std::endl;
    }

    // help argument
    if (cliString == "-h" || cliString == "--help") {
      std::cout << "Run this program with -v or --version for version "
                   "information \nRun this program "
                << "with - i or --input to specify input file / folder name"
                << std::endl;
    }

    // input argument
    if (cliString == "-i" || cliString == "--input") {
      std::string fileNameString = "";
      if (argc > 3) {
        // concatenate argument words for file input & output
        for (int i = 2; i < argc - 1; i++) {
          fileNameString += argv[i];
          fileNameString += " ";
        }
        fileNameString += (argv[argc - 1]);
      }

      else {
        fileNameString = argv[2];
      }

      // text file input
      if (isText(fileNameString)) {
        std::ifstream inFile(fileNameString);
        if (!inFile) {
          inFile.close();
          return -1;
        } else {
          newFolder();
          processText(fileNameString, 1);
        }

      }
      // md file input
      else if (isMarkDown(fileNameString)) {
        std::ifstream inFile(fileNameString);
        if (!inFile) {
          inFile.close();
          return -1;
        } else {
          newFolder();
          processText(fileNameString, 2);
        }
      } else if (isFolder(fileNameString)) {
        // folder input
        newFolder();
        for (const auto &dirItem :
             std::filesystem::recursive_directory_iterator(fileNameString)) {
          std::string path = dirItem.path().string();
          if (isText(path)) {
            processText(path, 1);
          } else if (isMarkDown(path)) {
            processText(path, 2);
          }
        }
      }
    }
  }
  return 0;
}
