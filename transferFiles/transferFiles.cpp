#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <regex>
#include <ctime>
#include <boost/filesystem.hpp>
#include <boost/archive/basic_xml_archive.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/thread/thread.hpp>

namespace fs = boost::filesystem;
using namespace std;


void transferFindFiles(string origin, string destiny){

	try {
		fs::copy_file(origin, destiny, fs::copy_option::overwrite_if_exists);
		cout << "File transfer with success !" << endl;
		fs::remove(origin);
	}
	catch (...) {
		cout << "Error transfer file" << endl;
	}

}

int compareDate(vector<string> filePaths, string newestOldestValue){
	time_t now;
	time_t timeEdit;
	now = time(NULL);
	double delta;
	double maior;
	int index = 0;
	int maisNovo = 0;
	int maisVelho = 0;

	for (auto i = filePaths.rbegin(); i != filePaths.rend(); ++i) {
		timeEdit = boost::filesystem::last_write_time(filePaths[index]);

		if (index == 0) {
			maior = difftime(now, timeEdit);
		}
		else {
			delta = difftime(now, timeEdit);
			if (delta < maior) {
				maisNovo = index;
			}
			else {
				maisVelho = index;
			}
		}
		
		++index;
	}
	
	if (newestOldestValue == "newest") {
		return maisNovo;
	}
	else if (newestOldestValue == "oldest") {
		return maisVelho;
	}
}

void findFiles(string origin, string destiny, string fileName, bool regexSearch, string regexValue,
				bool newestOldestSearch, string newestOldestValue) {

	bool find = false;
	regex rx = regex(regexValue);
	vector <string> filePathDestiny;
	vector <string> filePathOrigin;

	for (const auto& p : fs::directory_iterator(origin)) {
		string nomeAux = p.path().filename().string();
		string fileFullPathOrigin;
		string fileFullPathDestiny;
		bool fileMatch = false;
		int pos = nomeAux.find(fileName);
		int posExt = fileName.find(".");
		bool findRegex = regex_search(nomeAux, rx);

		if (regexSearch == false ) {
			//procura na pasta de destino para encontrar algum dos casos: nome completo do arquivo, prefixo ou extensão
			if ((nomeAux.compare(fileName) == 0) || (pos == 0)  || ((posExt == 0) && (p.path().extension() == fileName))){ 
				fileMatch = true;
			}
		}
		else {
			//caso a busca seja setada por regex, verifica se a busca encontrou algum arquivo
			if (findRegex == true) {
				fileMatch = true;
			}
		}

		if (fileMatch == true) {
			fileFullPathOrigin = origin;
			fileFullPathDestiny = destiny;
			fileFullPathOrigin += string("\\") + string(nomeAux);
			fileFullPathDestiny += string("\\") + string(nomeAux);
			find = true;
			fileMatch = false;
			if (newestOldestSearch == false) {
				transferFindFiles(fileFullPathOrigin, fileFullPathDestiny);
			}
			else {
				filePathOrigin.push_back(fileFullPathOrigin);
				filePathDestiny.push_back(fileFullPathDestiny);
			}
		}
	}
	
	if (newestOldestSearch == true && find == true) { //verifica se a busca vai ser feita pelo criterio de arquivo mais novo ou mais velho
		int index = compareDate(filePathOrigin, newestOldestValue);
		transferFindFiles(filePathOrigin[index], filePathDestiny[index]);
	}
	
	if (find == false) { //verificação se encontrou o arquivo especificado
		cout << "File(s) not found !" << endl;
	}
}

int main(void){

	//LENDO ARQUIVO DE CONFIGURAÇÃO "config.xml" E SALVANDO VALORES
	boost::property_tree::ptree pt;

	char tecla;
	string fileName = "../config.xml";

	try {
		boost::property_tree::xml_parser::read_xml(fileName.c_str(), 
				pt ,boost::property_tree::xml_parser::trim_whitespace);

		string origin = pt.get<string>("xml.config.origin.<xmlattr>.value");
		cout << "Origin path: " << origin << endl;
		string destiny = pt.get<string>("xml.config.destiny.<xmlattr>.value");
		cout << "Destiny path: " << destiny << endl;
		string fileName = pt.get<string>("xml.config.file_name.<xmlattr>.value");
		cout << "File Name: " << fileName << endl;
		int loopTimer = pt.get<int>("xml.config.timer.<xmlattr>.value");
		cout << "Loop time: " << loopTimer << " seconds" << endl;
		bool newestOldestSearch = pt.get<bool>("xml.config.newest_oldest_search.<xmlattr>.search");
		string newestOldestValue = pt.get<string>("xml.config.newest_oldest_search.<xmlattr>.value");
		
		if (newestOldestSearch == true) {
			cout << "Newest/Oldest Files Search: true" << " --- Mode: " << newestOldestValue << endl;
		}
		else {
			cout << "Newest/Oldest Files Search: false" << endl;
		}
		
		string regexValue = pt.get<string>("xml.config.regex.<xmlattr>.value");
		bool regexSearch = pt.get<bool>("xml.config.regex.<xmlattr>.search");
		cout << "Search Regex: " << regexSearch << endl << endl;

		cout << "Press 'q' to terminate process" << endl << endl;

		while (true) {
			findFiles(origin, destiny, fileName, regexSearch, regexValue, newestOldestSearch, newestOldestValue);
			cout << "Find File(s), waiting..." << endl;

			for (int i = 1; i <= loopTimer; i++) {
				boost::this_thread::sleep_for(boost::chrono::seconds(1));
				if (kbhit() && (tecla = getch()) && (tecla == 'q')) {
					return 0;
				}
			}
		}

	}
	catch(...) {
		cout << "Error";
	}
}