#include <filesystem>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <direct.h>


#include "gasHeader.h"

int main(int argc, char** argv) {

	std::string cliString = argv[1];

	//validate input
	bool argFlag = false;
	if (cliString.length() < 2 && cliString != "-v" && cliString != "--version" && cliString != "-h" && cliString != "--help" && cliString != "-i" && cliString != "--input") {
		std::cout << "Invalid entry." << std::endl;
		return -1;		
	}

	//version argument
	if (cliString == "-v" || cliString == "--version") {
		std::cout << "********************************\n" <<
			"********************************\n" <<
			"****                        ****\n" <<
			"****  Gus' Awesome Ssg V0.1 ****\n" <<
			"****                        ****\n" <<
			"********************************\n"
			"********************************" << std::endl;
	}

	//help argument
	if (cliString == "-h" || cliString == "--help") {
		std::cout << "Run this program with -v or --version for version information \nRun this program "
			<< "with - i or --input to specify input file / folder name" << std::endl;
	}

	//input argument
	if (cliString == "-i" || cliString == "--input") {
		std::string fileNameString = "";
		if (argc > 3) {
			//concatenate argument words for file input & output
			for (int i = 2; i < argc - 1; i++) {
				fileNameString += argv[i];
				fileNameString += " ";
			}
			fileNameString += (argv[argc - 1]);
		}

		else {
			fileNameString = argv[2];
		}

		//text file input
		if (fileNameString.find(".txt") != std::string::npos) {
			std::ifstream inFile(fileNameString);
			if (!inFile)
			{
				inFile.close();
				return -1;
			}
			else {
				newFolder();
				processText(fileNameString, 1);
			}

		}
		//md file input
		else if (fileNameString.find(".md") != std::string::npos) {
			std::ifstream inFile(fileNameString);
			if (!inFile)
			{
				inFile.close();
				return -1;
			}
			else {
				newFolder();
				processText(fileNameString, 2);
			}
		}
		else {
			//folder input
			newFolder();
			for (const auto& dirItem : std::filesystem::recursive_directory_iterator(fileNameString)) {
				std::string path = dirItem.path().string();
				if (path.find(".txt") != std::string::npos || path.find(".md") != std::string::npos) {
					processText(path, 3);
				}
			}
		}
	}
	return 0;
}

static void processText(std::string fileName, int fileType) {
	std::string outFileName = "";
	std::string title = "";
	//open input file
	std::ifstream inFile(fileName);
	if (!inFile) {
		inFile.close();
	}
	if (fileType == 1 || fileType == 2) { //.txt input or .md input
		outFileName = fileName;
		outFileName = outFileName.substr(0, outFileName.find("."));
	}
	else if (fileType == 3) { //folder input
		outFileName = fileName;
		outFileName = outFileName.erase(0, outFileName.find_last_of("\\") + 1);
		outFileName = outFileName.substr(0, outFileName.find("."));
	}
	title = outFileName;
	//open output file
	outFileName = "./dist/" + outFileName + ".html";
	std::ofstream outFile(outFileName);
	if (outFile) {

		outFile << " <!DOCTYPE html> <html> <br> <head>" << '\n';
		//.txt file title/header
		if (fileType == 1) {
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

			outFile << "</head>" << '\n' << "<body>" << '\n' << "<h1> " << line1 << "</h1>" << '\n';
		}
		//.md file title
		else if (fileType == 2) {
			outFile << " <title> " << title << "</title>" << '\n';
			outFile << "</head>" << '\n' << "<body>" << '\n';
		}

		std::string inLine = "";
		std::string lastLine = "";
		while (std::getline(inFile, inLine)) {
			if (fileType == 2) {
				//Check for Header 1 syntax
				if ((inLine.substr(0,2).find("# ") != std::string::npos)) {
					inLine = makeHeader1(inLine);
				}
				//Check for Horizontal rule syntax
				if (inLine.find("---") != std::string::npos) {
					inLine = hzRule(inLine);
				}
			}

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
		inFile.close();
		outFile << " </body>" << '\n' << "</html>";
		outFile.close();
		
	}
	else {
		std::cout << "Error creating output file." << std::endl;
		
	}

}

std::string makeHeader1(std::string line) {
	std::string newLine = line;
	newLine.erase(0, 2);
	newLine = "<h1>" + newLine + "</h1>";
	return newLine;
}

std::string hzRule(std::string line) {
	line.replace(line.find("---"), 3, "<hr>");
	return line;
}

static void newFolder() {
	//create or recreate folder
	std::filesystem::remove_all("./dist");
	if (_mkdir("./dist") != 0) {
		std::cout << "Error - folder creation unsuccessful." << std::endl;
	}
}
