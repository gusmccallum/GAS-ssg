#include <filesystem>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>


int main(int argc, char** argv) {

	std::string argString = argv[1];

	//validate input
	bool argFlag = false;
	if (argString.length() < 2 && argString != "-v" && argString != "--version" && argString != "-h" && argString != "--help" && argString != "-i" && argString != "--input") {
		while (argFlag == false) {
			std::cout << "Invalid entry. Please re-enter selection." << std::endl;
			std::cin >> argString;
			if (argString.length() >= 2 && (argString == "-v" || argString == "--version" || argString == "-h" || argString == "--help" || argString == "-i" || argString == "--input")) {
				argFlag = true;
			}
 		}
	}

	//version argument
	if (argString == "-v" || argString == "--version") {
		std::cout << "********************************\n" <<
				     "********************************\n" <<
					 "****                        ****\n" <<
					 "****  Gus' Awesome Ssg V0.1 ****\n" <<
					 "****                        ****\n" <<
					 "********************************\n" 
					 "********************************"<< std::endl;
	}

	//help argument
	if (argString == "-h" || argString == "--help") {
		std::cout << "Run this program with -v or --version for version information \nRun this program"
			<< "with - i or --input to specify input file / folder name" << std::endl;
	}
	
	//input argument
	if (argString == "-i" || argString == "--input") {
		argFlag = false;
		std::string argString2 = "";
		if (argc > 3) {
			//concatenate argument words for file input & output
			for (int i = 2; i < argc-1; i++) {	
				argString2 += argv[i];
				argString2 += " ";			
			}
			argString2 += (argv[argc-1]);
		} 		
		


		if (argString2.find(".txt") != std::string::npos) {
			std::ifstream inFile(argString2);
			if (!inFile)
			{
				//TODO: Validation and reattempt input loop
				/*while (argFlag == false) {
					std::cerr << "ERROR: Invalid file/folder name [" << argString2 << "]. Please re-enter selection\n";
					std::cin >> argString2;
					if (inFile) {
						argFlag = true;
					}
				}	*/
				std::cout << "ya dun goofed" << '\n';
			}

			//text file input and output
			std::ofstream outFile(argString2.substr(0, argString2.find(".")) + ".html");
			if (outFile) {
				std::string inLine;
				std::getline(inFile, inLine);
				outFile << " <!DOCTYPE html><html><head><title>" << inLine << "</title>" << '\n' << "<br>" << '\n' << "<body>" << '\n' << "<h1> " << inLine << "</h1>";
				while (std::getline(inFile, inLine)) {
					outFile << "<p> " << inLine << " </p> <br> " << '\n';
				}
				outFile << " </body>" << '\n' << "</html>";
			}
		}


		else {
			//folder input
			argString2 = argv[2];
			for (const auto& dirItem : std::filesystem::recursive_directory_iterator(argString2)) {
				std::string path = dirItem.path().string();
				std::ifstream inFile(path);
				if (!inFile) {
					std::cout << "Error! Invalid file name." << std::endl;
					inFile.close();
				}
				else {
					std::cout << path.find("\\");
					std::ofstream outFile(path.substr(0, path.find(".")) + ".html");
					if (outFile) {
						std::string inLine;
						std::getline(inFile, inLine);
						outFile << " <!DOCTYPE html><html><head><title>" << inLine << "</title>" << '\n' << "<br>" << '\n' << "<body>" << '\n' << "<h1> " << inLine << "</h1>";
						while (std::getline(inFile, inLine)) {
							outFile << "<p> " << inLine << " </p> <br> " << '\n';
						}
						outFile << " </body>" << '\n' << "</html>";
					}

				}
			}
		}
	}	
}