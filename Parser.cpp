#include "Parser.hpp"

void Parser::Parse(std::string filename)
{
    std::string line;
    std::fstream inifile(filename.c_str());
    if (!inifile) std::cout<<"Cannot open file "<<filename<<std::endl;
    while (!inifile.eof()) {
	std::getline(inifile, line); 
	std::cout<<string;
	if (!line.length()) continue;
	if (line[0] == '#') continue;
	if (line[0] == ';') continue;
    }
    inifile.close();
}
