#include <fstream>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/archive/basic_xml_archive.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/foreach.hpp>
#include <boost/optional/optional.hpp>

namespace fs = boost::filesystem;
using namespace std;


//int main()
//{
	//fs::create_directories("sandbox/dir/subdir");

	//try // If you want to avoid exception handling, then use the error code overload of the following functions.
	//{
		//fs::copy_file("C:\\teste.xlsx", "C:\\Users\\fredm\\OneDrive\\Área de Trabalho\\relatorio estagio\\teste.xlsx", fs::copy_option::overwrite_if_exists);
		//std::cout << "Arquivo copiado com sucesso !" << std::endl;
	//}
	//catch (std::exception& e) // Not using fs::filesystem_error since std::bad_alloc can throw too.  
	//{
	//	std::cout << e.what();
	//}
	//Config cfg;
	//cfg.readFile("hello.conf");

	//string name = cfg.lookup("target");
	//cout << "Store name: " << name << endl << endl;

//}

void findFiles(string origin, string fileName) {
	bool find = false;
	for (const auto& p : fs::directory_iterator(origin)) {
		string nomeAux = p.path().filename().string();
		string fileFullPath;
		int pos = nomeAux.find(fileName);
		int posExt = fileName.find(".");

		if (nomeAux.compare(fileName) == 0) { //compara o nome completo do arquivo (nome + extensão)
			fileFullPath = origin;
			fileFullPath += string("\\") + string(nomeAux);
			cout << fileFullPath << endl;
			find = true;
		}
		else if (pos == 0) { // compara prefixo do nome passado pelo arquivo de configuração com arquivo da pasta de origem
			fileFullPath = origin;
			fileFullPath += string("\\") + string(nomeAux);
			cout << fileFullPath << endl;
			find = true;
		}
		else if(posExt == 0){ //compara com a extensão passada pelo arquivo de configuração com as extensões dos arquivos da pasta de origem
			if (p.path().extension() == fileName) {
				fileFullPath = origin;
				fileFullPath += string("\\") + string(nomeAux);
				cout << fileFullPath << endl;
				find = true;
			}
		}
	}
	if (find == false) { //verificação se encntrou o arquivo especificado
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

		findFiles(origin, fileName);

	}
	catch(...) {
		cout << "Erro";
	}
}