# Roguelike
### Descrição do projeto
Este projeto foi feito para a matéria de Estruturas de Dados, buscando aplicar os conceitos de implementação de uma lista encadeada, ou ainda árvores binárias. Para isso, implementamos um jogo de temática Roguelike.

### Aplicação da lista encadeada
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
Esse código, reseta o ponteiro da lista para o início, e então, vai iterando até chegar no índice desejado.

## Mecânicas do jogo
### Inimigos
Os inimigos utilizam o algoritmo A* para determinar o melhor caminho até o herói. Esse algoritmo utiliza o grid criado pelo mapa, e tenta traçar o melhor caminho a partir da posição atual do inimigo.

Para um maior aprofundamento, utilize os links a seguir:
* http://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html
* http://www.redblobgames.com/pathfinding/a-star/introduction.html
* http://mat.uab.cat/~alseda/MasterOpt/AStar-Algorithm.pdf
