[![Codacy Badge](https://api.codacy.com/project/badge/Grade/8e4fe8eb2f924767a0ee0e6752d35dda)](https://www.codacy.com/app/explodingnuggets/Roguelike?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=explodingnuggets/Roguelike&amp;utm_campaign=Badge_Grade)
# Roguelike

### Descrição do projeto
Este projeto foi feito para a matéria de Estruturas de Dados, buscando aplicar os conceitos de implementação de uma lista encadeada. Para isso, implementamos um jogo de temática Roguelike.

## Instalação
### Linux
1. Baixe os arquivos para [Linux](http://www.github.com/explodingnuggets//Roguelike/releases/latest);
2. Coloque os arquivos na pasta que desejar;
3. Antes de executar, utilize o comando ```export LD_LIBRARY_PATH="../SFML/lib"``` na pasta de instalação, ou então, instale a biblioteca SFML.
4. Execute o arquivo ```randventure.out```.

### Windows
1. Baixe os arquivos para [Windows](http://www.github.com/explodingnuggets//Roguelike/releases/latest);
2. Coloque os arquivos na pasta que desejar;
3. Execute o arquivo ```randventure.exe```.

### Aplicação da lista encadeada
![Arquitetura](https://dl.dropboxusercontent.com/sh/t21x4vitadfju4f/AACSVcQ4iDY9HmL9GFeRIrv7a/Roguelike/rogue_arch.png?dl=0)

Os conceitos de lista encadeada foram aplicadas na seleção da classe personagem, sendo que criaram-se os seguintes métodos de percorrimento para a lista de seleção:
```c++
void ButtonList::toNext(){
  m_actualIndex++;
  if(m_actualIndex >= m_buttonSprites.getSize())
    m_actualIndex = 0;
  m_outlineSprite.setPosition(m_buttonSprites[m_actualIndex]->getPosition());
}

void ButtonList::toPrevious(){
  m_actualIndex--;
  if(m_actualIndex < 0)
    m_actualIndex = m_buttonSprites.getSize()-1;
  m_outlineSprite.setPosition(m_buttonSprites[m_actualIndex]->getPosition());
}
```
Foi implementado o operador de acesso [ ], permitindo o acesso mais simples dos elementos da lista encadeada, para isso, utiliza-se o seguinte método:
```c++
template<class T>
T LinkedList<T>::operator[](int index) {
	this->toFirst();
	while (index > 0 && !this->toNext())
		index--;
	return this->current->value;
}
```
Esse código reseta o ponteiro da lista para o início, e então, vai iterando até chegar no índice desejado.

## Mecânicas do jogo
### Inimigos
Os inimigos utilizam o algoritmo A* para determinar o melhor caminho até o herói. Esse algoritmo utiliza o grid criado pelo mapa, e tenta traçar o melhor caminho a partir da posição atual do inimigo.

Para um maior aprofundamento, utilize os links a seguir:
* http://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html
* http://www.redblobgames.com/pathfinding/a-star/introduction.html
* http://mat.uab.cat/~alseda/MasterOpt/AStar-Algorithm.pdf

### Geração do mapa
Para a geração do mapa aleatório, foi utilizado o algoritmo "Recursive Backtracker", que gera um labirinto delimitado pelos extremos do mapa, e logo em seguida, são criadas salas vazias nesse labirinto.

Alguns materiais do Recursive Backtracker:

* http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking
* https://scratch.mit.edu/projects/17358777/

## Ferramentas utilizadas
* [SFML](http://sfml-dev.org)


## Autores
* Alisson Nunes - [GitHub](https://github.com/Alynva)
* Gabriel Alves - [GitHub](https://github.com/CptSpookz)
* Matheus Bortoleto - [GitHub](https://github.com/explodingnuggets)
* Rafael Sales - [GitHub](https://github.com/rsaless)

## Créditos
* Alisson Nunes - Interface e parte gráfica.
* Gabriel Alves - Implementação da estrutura dos dados e controles.
* Matheus Bortoleto - Parte gráfica e controles.
* Rafael Sales - Documentação.
