# transfer-files

# O que é ? #

Um projeto feito em C++ para transferências de arquivos entre diretórios pré-definidos. Ele tem como base um arquivo xml de configuração, onde todos os parâmetros são setados para a execução do programa, sendo que uma vez compilado, uma simples alteração nesse xml e a execução já reflete tais mudanças.
Possui suporte para qualquer extensão de arquivo e pode ter sua busca realizada a partir dessas opções: pelo nome completo do arquivo (nome + extensão), por prefixos ou parte de texto e também por extensão. Além disso, o modo de busca pode ser feito a partir de Regex e possui um funcionalidade para realizar a busca pelo arquivo mais novo ou mais velho, levando em conta a data de modificação do mesmo.

# Biblioteca externas utilizadas #

Além das bibliotecas padrão do C++, para esse projeto foi utilizada a biblioteca Boost.

Mais informações podem ser encontrada nesse link [Boost C++ Library](https://www.boost.org/).

- Guia completo de instalação para o windows, nesse link [Guia Instalação Boost Windows](https://gist.github.com/sim642/29caef3cc8afaa273ce6#file-boost-windows-md).
- Guia completo de instalação para linux, nesse link [Guia instalação Boost Linux](aaaa).

# Utilização #

Para fazer uso desse programa, basta você fazer o download do código ou clonar na sua máquina, compilar o arquivo .cpp dentro da pasta "transfer-files", editar o xml de configuração para definir o caminhos de acordo com seu computador e sua necessidade. Feito isso, basta executar o programa que ele exibirá um prompt com as informações passadas e o atual status de execução.

Fique a vontade para fazer o download ou clona o projeto em sua máquina:
    `https://github.com/fredmininel/transfer-files.git`

# Testes #

Como se trata de um programa para transferência de arquivos apenas localmente, sem suporte para arquivos e diretórios remotos (quem sabe no futuro), os teste foram realizados em ambiente local e funcionou corretamente para todos os casos de uso.

# Detalhes #

Para uma explicação mais completo sobre o projeto e suas as funcionalidades como o uso de cada função, fluxo do execução, parâmetros e variáveis, você pode acessar em [Fluxo de Execução] (link fluxo).

Para mais informações sobre o arquivo de configuração xml, assim como a explicação de cada tag e o formato desejado de preenchimento, acesse [Arquivo de configuração XML] (link XML).

