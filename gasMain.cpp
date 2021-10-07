#include <filesystem>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <direct.h>


#include "gasHeader.h"

int main(int argc, char** argv) {

	if (argc < 1) {
		//Empty argument list
		return -1;
	}

	std::string cliString = argv[1];

	//validate input
	if (cliString.length() < 2 && cliString != "-v" && cliString != "--version" && cliString != "-h" && cliString != "--help" && cliString != "-i" && cliString != "--input"&& cliString != "-c" && cliString != "--config") {
		std::cout << "Invalid entry." << std::endl;
		return -1;		
	}
	if (cliString == "-c" || cliString == "--config"){
		std::string input = argv[2];
		if (input.find(".json") < input.size()){
			processJsonFormat(input);
		}else{
			std::cout << "Invalid entry." << std::endl;
			return -1;	
		}
	}else{
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
					if (path.find(".txt") != std::string::npos) {
						processText(path, 1);
					}
					else if (path.find(".md") != std::string::npos) {
						processText(path, 2);
					}
				}
			}
		}
	}
	return 0;
}

static void processText(std::string fileName, int fileType, std::string stylesheet, std::string lang, std::string folderOutput) {
	std::string outFileName = "";
	std::string title = "";
	//open input file
	std::ifstream inFile(fileName);
	if (!inFile) {
		inFile.close();
	}
	//folder input
	if (fileName.find("\\") != std::string::npos) { 
		outFileName = fileName;
		outFileName = outFileName.erase(0, outFileName.find_last_of("\\") + 1);
		outFileName = outFileName.substr(0, outFileName.find("."));
	}
	//txt or md input
	else {
		outFileName = fileName;
		outFileName = outFileName.substr(0, outFileName.find("."));
	}

	title = outFileName;
	//open output file
	outFileName = folderOutput + "/" + outFileName + ".html";
	std::ofstream outFile(outFileName);
	if (outFile) {
		if (lang != ""){
			outFile << " <!DOCTYPE html> <html lang='" << lang << "'> <br> <head>" << '\n';
		}
		outFile << " <!DOCTYPE html> <html> <br> <head>" << '\n';
		if(stylesheet != "")
			outFile << "<link rel='stylesheet' href='" << stylesheet <<"'>";
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

static void newFolder(std::string folder) {
	//create or recreate folder
	std::filesystem::remove_all(folder);
	if (_mkdir(folder.c_str()) != 0) {
		std::cout << "Error - folder creation unsuccessful." << std::endl;
	}
}

std::string getJsonValue(std::string line){
    line = line.erase(0, line.find(":"));
    line = line.erase(0, line.find("\"")+1);
    std::string value = line.substr(0, line.find("\""));
    return value;
}

void processJsonFormat(std::string file){
	std::ifstream jsonFile(file);
	if (jsonFile){
		std::vector<std::string> jsonLines;
		std::string temp;
		while(getline(jsonFile, temp)){
			jsonLines.push_back(temp);
		}
		std::string input ="", output ="", stylesheet="", lang="";
		for (int i=0; i<jsonLines.size(); i++){
			if(jsonLines.at(i).find("input") < jsonLines.at(i).size()){
				input = getJsonValue(jsonLines.at(i));
			}else if(jsonLines.at(i).find("output") < jsonLines.at(i).size()){
				output = getJsonValue(jsonLines.at(i));
			}else if(jsonLines.at(i).find("stylesheet") < jsonLines.at(i).size()){
				stylesheet = getJsonValue(jsonLines.at(i));
			}else if(jsonLines.at(i).find("lang") < jsonLines.at(i).size()){
				lang = getJsonValue(jsonLines.at(i));
			}
		}
		std::string fileNameString = input;

		//text file input
		if (fileNameString.find(".txt") != std::string::npos) {
			std::ifstream inFile(fileNameString);
			if (!inFile)
			{
				inFile.close();
			}
			else {
				newFolder(output);
				processText(fileNameString, 1, stylesheet, lang, output);
			}

		}
		//md file input
		else if (fileNameString.find(".md") != std::string::npos) {
			std::ifstream inFile(fileNameString);
			if (!inFile)
			{
				inFile.close();
			}
			else {
				newFolder(output);
				processText(fileNameString, 2, stylesheet, lang, output);
			}
		}
		else {
			//folder input
			newFolder(output);
			for (const auto& dirItem : std::filesystem::recursive_directory_iterator(fileNameString)) {
				std::string path = dirItem.path().string();
				if (path.find(".txt") != std::string::npos) {
					processText(path, 1, stylesheet, lang, output);
				}
				else if (path.find(".md") != std::string::npos) {
					processText(path, 2, stylesheet, lang, output);
				}
			}
		}
		
	}else{
		std::cout << "Cannot open .json file." << std::endl;
	}
}