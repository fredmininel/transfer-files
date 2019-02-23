#include <fstream>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <iostream>
#include <regex>
#include <boost/filesystem.hpp>
#include <boost/archive/basic_xml_archive.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/foreach.hpp>
#include <boost/optional/optional.hpp>

namespace fs = boost::filesystem;
using namespace std;


void copyFindFiles(string origin, string destiny){

	try {
		fs::copy_file(origin, destiny, fs::copy_option::overwrite_if_exists);
		cout << "Arquivo copiado com sucesso !" << endl;
	}
	catch (...) {
		cout << "Erro ao copiar" << endl;
	}

}

void findFiles(string origin, string destiny, string fileName, string regexSearch, string regexValue) {
	bool find = false;
	regex rx = regex(regexValue);
	for (const auto& p : fs::directory_iterator(origin)) {
		string nomeAux = p.path().filename().string();
		string fileFullPathOrigin;
		string fileFullPathDestiny;
		bool fileMatch = false;
		int pos = nomeAux.find(fileName);
		int posExt = fileName.find(".");
		bool findRegex = regex_search(nomeAux, rx);

		if (regexSearch == "false" ) {
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
			copyFindFiles(fileFullPathOrigin, fileFullPathDestiny);
			find = true;
			fileMatch = false;
		}
	}
	if (find == false) { //verificação se encontrou o arquivo especificado
		cout << "Arquivo nao encontrado, por favor, corriga o nome" << endl;
	}
}

int main(void){

	//LENDO ARQUIVO DE CONFIGURAÇÃO "config.xml" E SALVANDO VALORES
	boost::property_tree::ptree pt;

	string fileName = "../config.xml";

	try {
		boost::property_tree::xml_parser::read_xml(fileName.c_str(), 
				pt ,boost::property_tree::xml_parser::trim_whitespace);

		string origin = pt.get<string>("xml.config.origin.<xmlattr>.value");
		cout << "Caminho de origem: " << origin << endl;
		string destiny = pt.get<string>("xml.config.destiny.<xmlattr>.value");
		cout << "Caminho de destinho: " << destiny << endl;
		string fileName = pt.get<string>("xml.config.file_name.<xmlattr>.value");
		cout << "Nome do arquivo: " << fileName << endl;
		int loopTimer = pt.get<int>("xml.config.timer.<xmlattr>.value");
		cout << "Tempo de repeticao: " << loopTimer << endl;
		string mostRecent = pt.get<string>("xml.config.most_recent.<xmlattr>.value");
		cout << "Most Recent Files Mode: " << mostRecent << endl;
		string regexValue = pt.get<string>("xml.config.regex.<xmlattr>.value");
		string regexSearch = pt.get<string>("xml.config.regex.<xmlattr>.search");
		cout << "Search Regex: " << regexSearch << endl;
		
		findFiles(origin, destiny, fileName, regexSearch, regexValue);

	}
	catch(...) {
		cout << "Erro";
	}
}