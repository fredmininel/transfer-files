# Instalando bibliotecas boost para o GCC (MinGW) no Windows

Para esse projeto, foi utlizada a versão 1.67.0 da biblioteca, dessa forma, os passos abaixo serão exemplificados por ela.
O boost source pode ser baixado direto do próprio site [Boost](https://www.boost.org/).

## Configuração de pastas
1. Extrair a boost source baixada, por ex. `C: \ Arquivos de programas \ boost_1_67_0`.
2. Crie uma pasta para a instalação do Boost.Build, por ex. `C: \ Arquivos de programas \ boost-build`.
2. Crie uma pasta dentro para o building, ou seja, `C: \ Arquivos de Programas \ boost_1_67_0 \ build`.
3. Crie uma pasta para instalação, por ex. `C: \ Arquivos de Programas \ boost`.

## Configuração do GCC
1. Abra o prompt de comando.
2. Execute o `g ++ --version`.
3. Se a saída contiver um número de versão g ++, o GCC deverá ser configurado corretamente para ser executado a partir da linha de comando e você poderá continuar.

## Boost.Build setup
1. Abra o Prompt de Comando e navegue até "C: \ Arquivos de Programas \ boost_1_67_0 \ tools \ build".
2. Execute `bootstrap.bat mingw`.
3. Execute `b2 install --prefix =" C: \ Arquivos de Programas \ boost-build "`.
4. Adicione `C: \ Arquivos de programas \ boost-build \ bin` ao Windows PATH.

## boost building
1. Abra o Prompt de Comando e navegue até "C: \ Program Files \ boost_1_67_0".
2. Executar
`` `
b2 --build-dir = "C: \ Arquivos de Programas \ boost_1_67_0 \ build" --prefix = "C: \ Arquivos de Programas \ boost" toolset = gcc install
`` `

## Configuração do projeto
1. Adicione a pasta include, ou seja, `C: \ Arquivos de Programas \ boost \ include \ boost-1_59`.
2. Adicione a pasta do link, ou seja, `C: \ Arquivos de Programas \ boost \ lib`.
3. Vincular bibliotecas necessárias, por exemplo `libboost_regex-mgw48-mt-1_67.a`.



Esse guia foi feito por @sim642 e se encontra em [Installing boost libraries for GCC (MinGW) on Windows](https://gist.github.com/sim642/29caef3cc8afaa273ce6#file-boost-windows-md), apenas foi traduzido para ser inserido aqui.
