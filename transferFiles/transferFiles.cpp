#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <boost/filesystem.hpp>


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

#include <boost/archive/basic_xml_archive.hpp>

#include <boost/property_tree/xml_parser.hpp>

#include <boost/algorithm/string/trim.hpp>

#include <iostream>

#include <string>



void main(void)

{

	//essa variavel pt guarda toda a árvore de nós do xml lida do arquivo.

	boost::property_tree::ptree pt;


	//Path para o arquivo, no meu caso encontra-se na mesma pasta do execultavel

	std::string fileName = "../config.xml";


	try

	{       //realize o parser propriamente ditto do arquivo

		boost::property_tree::xml_parser::read_xml(

			fileName.c_str(),

			pt,

			boost::property_tree::xml_parser::trim_whitespace);


		//pega o nó raiz

		auto c1 = pt.get_child("xml");


		//navegue através de todos os nós filhos da raiz

		for (auto i = c1.begin(); i != c1.end(); i++)

		{

			//pega os filhos deste nós que se esta visitando    

			auto c2 = i->second;



			//navegue através dos filhos caso este nó tenha  

			for (auto j = c2.begin(); j != c2.end(); j++)

			{

				//pega os valores dos atributos e imprimi na tela

				std::cout << "attr:" << j->second.get<std::string>("<xmlattr>.attr") << " | ";

				std::cout << "value:" << j->second.get<std::string>("<xmlattr>.value") << std::endl;

			}

		}

	}

	catch (...)

	{

		//caso tenha ocorra algum erro

		std::cout << "Error: parser fail!" << std::endl;

		return;

	}

}