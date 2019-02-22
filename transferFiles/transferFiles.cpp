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

void main(void){

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

	}
	catch(...) {
		cout << "Erro";
	}
}