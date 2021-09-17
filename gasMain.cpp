#include <filesystem>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <direct.h>


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
			"********************************" << std::endl;
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
			for (int i = 2; i < argc - 1; i++) {
				argString2 += argv[i];
				argString2 += " ";
			}
			argString2 += (argv[argc - 1]);
		}

		else {
			argString2 = argv[2];
		}

		if (argString2.find(".txt") != std::string::npos) {
			std::ifstream inFile(argString2);
			if (!inFile)
			{
				inFile.close();
			}

			//text file input and output 
			std::filesystem::remove_all("./dist");
			if (_mkdir("./dist") != 0) {
			std::cout << "Error creating ./dist folder." << std::endl;
			}
			std::ofstream outFile("./dist/" + argString2.substr(0, argString2.find(".")) + ".html");
			if (outFile) {
				
				outFile << " <!DOCTYPE html>" << '\n' << "<html>" << '\n' << "<head>";
				
				//get Title
				std::string line1 = "";
				std::string line2 = "";
				std::string line3 = "";

				std::getline(inFile, line1);
				std::getline(inFile, line2);
				std::getline(inFile, line3);

				//Set title if present
				if (line1 != "" && line2 == "" && line3 == "") {
					outFile << " <title> " << line1 << "</title>" << '\n';
				}

				outFile << "<body>" << '\n' << "<h1> " << line1 << "</h1>";
				std::string inLine = "";
				std::string lastLine = "";
				outFile << '\n' << "</head>" << '\n' << "<body>" << '\n';
				while (std::getline(inFile, inLine)) {

					if (inLine != "" && lastLine == "") {
						outFile << "<p> " << '\n' << inLine << '\n';
					}
					else if (inLine == "" && lastLine != "") {
						outFile << " </p>" << '\n';
					}
					else {
						outFile << inLine << "\n";
					}
					lastLine = inLine;
				}
				outFile << " </body>" << '\n' << "</html>";

			}
		}
		else {
			//folder input
			std::filesystem::remove_all("./dist");

			if (_mkdir("./dist") != 0) {
				std::cout << "Error creating ./dist folder." << std::endl;
			}

			argString2 = argv[2];

			for (const auto& dirItem : std::filesystem::recursive_directory_iterator(argString2)) {
				std::string path = dirItem.path().string();
				std::ifstream inFile(path);
				if (!inFile) {
					inFile.close();
				}
				else {
					path = path.erase(0, path.find_last_of("\\") + 1);
					path = path.substr(0, path.find("."));
					std::ofstream outFile("./dist/" + path + ".html");
					if (outFile) {
						outFile << " <!DOCTYPE html> <html> <br> <head>" << '\n';
						//get Title
						std::string line1 = "";
						std::string line2 = "";
						std::string line3 = "";

						std::getline(inFile, line1);
						std::getline(inFile, line2);
						std::getline(inFile, line3);

						//Set title if present
						if (line1 != "" && line2 == "" && line3 == "") {
							outFile << " <title> " << line1 << "</title>" << '\n';
						}

						std::string inLine = "";
						std::string lastLine = "";
						outFile << "</head>" << '\n' << "<body>" << '\n' << "<h1> " << line1 << "</h1>" << '\n';
						while (std::getline(inFile, inLine)) {

							if (inLine != "" && lastLine == "") {
								outFile << "<p> " << '\n' << inLine << '\n';
							}
							else if (inLine == "" && lastLine != "") {
								outFile << " </p>" << '\n';
							}
							else {
								outFile << inLine << "\n";
							}
							lastLine = inLine;
						}

						outFile << " </body>" << '\n' << "</html>";
					}

				}
			}
		}

	}

}