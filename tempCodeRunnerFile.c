#include <stdlib.h> //Inclui bibliotecas
#include <stdio.h>

typedef struct Song{ //Cria e define meu tipo Song, usado para armazenar dados das musicas
	char title[30];
	char artist[30];
	int duration;
	int ID;
} Song;

struct listElement { //Cria minha estrutura de elemento da lista.
	Song songElement;
	struct listElement *next;
} *Head;

int menu();    						//Função de Menu
void begginingInsert(Song mySong);	//Adiciona no início
void endInsert(Song mySong);		//Adiciona no fim
void midInsert(Song mySong, int pos);//Adiciona no meio
void removeSong(int ID); 			//Remove
void showPlaylist();				//Mostra a playlist
Song readSongData();				//Le uma musica
void printSong(Song songToPrint);	//Imprime musica na tela
void pause();						//Pausa

int main() {
    int option, ID, pos;
	while(1){
		option = menu();
		Song inputtedSong;

		switch(option){
			case 1: //inserir no inicio
			
			inputtedSong = readSongData();
			begginingInsert(inputtedSong);
			printf("\nMúsica inserida no início da playlist com sucesso!\n");
    		printSong(inputtedSong);
			
			break;

			case 2: //inserir no fim
			inputtedSong = readSongData();
			endInsert(inputtedSong);
			printf("\nMúsica inserida no final da playlist com sucesso!\n");
    		printSong(inputtedSong);

			break;

			case 3: //inserir no meio	
				inputtedSong = readSongData();
				printf("Digite a posição que deseja inserir o elemento: ");
				scanf("%d", &pos);
				midInsert(inputtedSong, pos);
				printf("\nMúsica inserida na posição %d!\n", pos);
    			printSong(inputtedSong);
			break;

			case 4: ///remover da lista
				printf("Digite ID da música que deseja remover: ");
				scanf("%d", &ID);
				removeSong(ID);

			break;

			case 5: //mostrar itens da lista
				showPlaylist();
			break;

			case 6: //sair
				return 0;

		}
	}

}

int menu() {
	int op, c;
	system("clear");
	printf("============= MENU =============\n");
	printf("1.Inserir no inicio da playlist.\n");
	printf("2.Inserir no fim da playlist. \n");
	printf("3.Inserir no meio da playlist.\n");
	printf("4.Remover da playlist.\n");
	printf("5.Listar playlist.\n");
	printf("6.Sair.\n");

	printf("Digite sua escolha: ");
	scanf("%d", &op);
	while ((c = getchar()) != '\n' && c != EOF) {} // sempre limpe o buffer do teclado.
	
	system("clear");
	return op;
}

Song readSongData()  //Chama o input para ler dados de uma Musica
{
    Song mySong;
	printf("Digite o título da música: ");
    fgets(mySong.title, 50 - 1, stdin);
    printf("\n");
	printf("Digite o artista ou banda: ");
    fgets(mySong.artist, 50 - 1, stdin);
    printf("\n");
    printf("Digite a duração da faixa em segundos: ");
    scanf("%d", &mySong.duration);
	printf("Digite o ID numerico da faixa: ");
    scanf("%d", &mySong.ID);
    scanf("%*c");
    printf("\n");
    return mySong;
}

void printSong(Song songToPrint){ //Imprime uma musica
    printf("Título:........ %s\n", songToPrint.title);
    printf("Artista:....... %s", songToPrint.artist);
	printf("\nDuration:...... %d\n", songToPrint.duration);
	printf("\nID:............ %d\n", songToPrint.ID);
    printf("____________________________________\n");
}

void begginingInsert(Song mySong){ //Insere no início
	struct listElement *newElement;
	//alocar o elemento na memoria
	newElement = (struct listElement *)malloc(sizeof(struct listElement ));
	//Acessa o novo elemento e adiciona o valor de num dentro de NovoElemento.dado.
	newElement->songElement = mySong;

	if (Head == NULL){
		Head = newElement;
		Head-> next = NULL;

	}
	else{
		newElement->next = Head;
		Head = newElement;
	}
};

void midInsert(Song mySong, int pos){ //Insere no meio
	pos = pos -1;
	struct listElement *newElement;
	//alocar o elemento na memoria
	newElement = (struct listElement *)malloc(sizeof(struct listElement ));
	struct listElement *cursorElement;
	cursorElement = (struct listElement *)malloc(sizeof(struct listElement));
	struct listElement *auxElement;
	auxElement = (struct listElement *)malloc(sizeof(struct listElement));

	newElement->songElement = mySong;

	if (pos == 0){

		Head = newElement;
		Head -> next = NULL;

	}
	else{
		cursorElement = Head;

		for (int i = 0; i < pos - 1; i++){
			cursorElement = cursorElement -> next;
		}
		auxElement = cursorElement -> next;
		cursorElement -> next = newElement;
		newElement -> next = auxElement;
	}

};

void removeSong(int ID){ //Remove elemento cujo ID seja igual ao que foi passado
	struct listElement *cursorElement;
	cursorElement = (struct listElement *)malloc(sizeof(struct listElement));
	struct listElement *previousElement;
	previousElement = (struct listElement *)malloc(sizeof(struct listElement));

	cursorElement = Head;
	
	while (cursorElement != NULL){
		if (cursorElement -> songElement.ID == ID){
			if(cursorElement == Head){
				Head = cursorElement -> next;
				free(cursorElement);
				printf("----- Song removed -----\n");
				showPlaylist();
				getchar();
				return;
			}
			else{
				previousElement -> next = cursorElement -> next;
				free(cursorElement);
				printf("----- Song removed -----\n");
				showPlaylist();
				getchar();
				return;
			}
		}
		else{
			previousElement = cursorElement;
			cursorElement = cursorElement -> next;
		}
	}
}

void endInsert(Song mySong){ //Adiciona musica no fim
	struct listElement *newElement;
	//alocar o elemento na memoria
	newElement = (struct listElement *)malloc(sizeof(struct listElement ));
	//Acessa o novo elemento e adiciona o valor de num dentro de NovoElemento.dado.
	newElement->songElement = mySong;
	newElement->next = NULL;

	struct listElement *cursorElement;
	cursorElement = (struct listElement *)malloc(sizeof(struct listElement));
	cursorElement = Head;

	if (Head == NULL){

		Head = newElement;
		Head->next = NULL;

	}
	else{
		while (cursorElement->next != NULL) {
		cursorElement = cursorElement->next;
	}
		cursorElement->next = newElement;
	}
}

void showPlaylist() //Mostra a playlist toda
{
	printf("===== Minha playlist ====\n");
	struct listElement *cursorElement;
	cursorElement = (struct listElement *)malloc(sizeof(struct listElement));

	cursorElement = Head;
	if (cursorElement == NULL) {
		return;
	}
	while (cursorElement != NULL) {
		printSong(cursorElement->songElement);
		cursorElement = cursorElement->next;
	}
	printf("\n");

	pause();
	return;
}

void pause() //pausa
{
    printf("Pressione ENTER para continuar: \n");
    getchar();
}
