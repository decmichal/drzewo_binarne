#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

struct node {
	int key;
	struct node *left;
	struct node *right;
	struct node *parent;
};

//Wskaznik na korzen
struct node *root = NULL;

/*
Funkcja dodawania wezla - funkcja ta przechodzi przez drzewo
w poszukiwaniu wolnego miejsca na wezel. Jesli wartosc nowego wezla
jest mniejsza od aktualnego, przechodzi w lewo, w przeciwnym przypadku
przechodzimy w prawo. Gdy natkniemy sie na wartosc null wstawiamy tam
nowy wezel pamietajac o przypisaniu wskaznikow.
*/
void add_node(int val) {
	//tworzymy wskazniki wskazujace na aktualnie rozpatrywany wezel i nowy wezel
	struct node *now = root;
	struct node *addedNode = new node;

	//Przypisujemy wartosci do wezla
	addedNode->key = val;
	addedNode->left = NULL;
	addedNode->right = NULL;

	//Jesli korzen ma wartosc null, nowy wezel staje sie korzeniem
	if (root == NULL) {
		addedNode->parent = NULL;
		root = addedNode;
		return;
	}
	else {

		while (now!= NULL) {
			//wartosc nowego wezla jest wieksza badz rowna od wskazywanego
			if (now->key <= addedNode->key) {
				//jesli po prawej jest wolne miejsce dodajemy w nie wezel
				if (now->right == NULL) {
					addedNode->parent = now;
					now->right = addedNode;
					return;
				}
				//w innym przypadku przechodzimy w glab drzewa
				else {
					now = now->right;
				}
			}
			//wartosc nowego wezla jest mniejsza od wskazywanego
			if (now->key > addedNode->key) {
				//jesli po lewej jest wolne miejsce dodajemy w nie wezel
				if (now->left == NULL) {
					addedNode->parent = now;
					now->left = addedNode;
					return;
				}
				//w innym przypadku przechodzimy w glab drzewa
				else {
					now = now->left;
				}
			}
		}
	}
}

/*
Funkcja usuwania wezla - funkcja przechodzi po drzewie w poszukiwaniu
wezla o zadanej wartosci. Jesli szukana wartosc jest mniejsza od wartosci
aktualnie wskazywanego wezla, przechodzi w lewo, w przeciwnym przypadku
przechodzimy w prawo. Jesli znajdziemy wezel o zadanej wartosci, usuwamy go.
W przypadku gdy posiadal jakiekolwiek dzieci, wstawiamy je w wolne miejsce.
Jesli zadana wartosc nie znajduje sie w drzewie, zwracamy NULL.
*/
struct node* del_node_key(struct node* node, int find) {

	if (node == NULL)
		return node;

	if (find < node->key) {
		return node->left = del_node_key(node->left, find);		//Rekurencyjne przejscie do szukanej wartosci
	}

	else if (find > node->key) {
		return node->right = del_node_key(node->right, find);
	}

	if (find == node->key) {
		//Jezeli drzewo sklada sie z samego korzenia
		if (root->left == NULL && root->right == NULL) {
			delete(root);
			root = NULL;
			return NULL;
		}
		//Wsuniecie prawego syna na miejsce aktualnie wskazywanego
		if (node->left == NULL) {
			struct node *tmp = node->right;
			delete(node);
			return tmp;
		}
		//Wsuniecie lewego syna na miejsce aktualnie wskazywanego
		else if (node->right == NULL) {
			struct node *tmp = node->left;
			delete(node);
			return tmp;
		}

		//Przypadek gdy wskazywany wezel ma dwóch synow
		struct node* tmp = node->right;

		node->key = tmp->key;
		while (tmp->left != NULL) {
			tmp = tmp->left;
		}

		//Znalezienie nastepcy
		node->right = del_node_key(node->right, tmp->key);
	}
	return node;
}

//Zlicz wezly w sposob rekurencyjny
int count_node(struct node *now)
{
    int count = 1;
    if (now->left != NULL) {
       count += count_node(now->left);
    }
    if (now->right != NULL) {
        count += count_node(now->right);
    }
    return count;
}

//Zlicz wszystkie wezly
int count_all_nodes()
{
    int count = 0;
    if (root != NULL) {
        count = count_node(root);
    }
    return count;
}

//Wyszukaj zadana wartosc w drzewie
bool if_node_exsists(struct node *now, int find)
{
    if (now == NULL)
        return false;

    if (now->key == find)
        return true;

    // przejdz do lewego wezla
    bool res1 = if_node_exsists(now->left, find);
    // odnaleziono wezel z poszukiwana wartoscia
    if(res1) return true;

    //jesli nie odnaleziono wartosci po lewej stronie, to sprawdz prawy wezel
    bool res2 = if_node_exsists(now->right, find);

    return res2;
}

//wyswietl elementy drzewa
void display(struct node *now){

	if(now != NULL){

		//przejdz do wezla na lewo
		display(now->left);

		//wyswietl wartosc wezla
		cout<<"Wartosc wezla wynosi: "<< now->key<<endl;

		//przejdz do wezla na prawo
		display(now->right);
	}
}

int main()
{
	bool isRunning = true;
	int answ, inpu;
	while (isRunning) {
		system("cls");
		cout << endl;

		cout << "###########MENU###########" << endl;
		cout << "[1] Dodaj wezel" << endl;
		cout << "[2] Usun wezel" << endl;
		cout << "[3] Policz ilosc wezlow" << endl;
		cout << "[4] Znajdz zadana wartosc" << endl;
		cout << "[5] Wyswietl wartosci wezlow"<<endl;
		cout << "[6] Wyjdz" << endl;
		cout << "##########################" << endl;

		cin >> answ;
		cout << endl;

		switch (answ) {
		case 1: {
			cout << "Wporwadz wartosc wezla: ";
			cin >> inpu;
			add_node(inpu);
			system("PAUSE");
			break;
		}
		case 2: {
			cout << "Wprowadz wartosc do usuniecia: ";
			cin >> inpu;
			if (root == NULL) {
				cout << "Brak korzenia - drzewo jest puste" << endl;
			}
			else{
                del_node_key(root, inpu);
			}
			system("PAUSE");
			break;
		}
		case 3: {
			cout << "Ilosc wezlow = " << count_all_nodes() << endl;
			system("PAUSE");
			break;
		}
		case 4: {
		    cout<<"Wprowadz wartosc do wyszukania: "<<endl;
		    cin>>inpu;

		    if(if_node_exsists(root, inpu))
            {
                cout<<"Odnaleziono poszukiwana wartosc"<<endl;
            }
            else
            {
                cout<<"Nie odnaleziono poszukiwanej wartosci"<<endl;
            }
			system("PAUSE");
			break;
		}
		case 5: {
            display(root);
            system("PAUSE");
            break;
		}
		case 6: {
			isRunning = false;
			break;
		}
		default: {
			cout << "Zly wybor!" << endl;
			system("PAUSE");
			break;
		}
		}
	}

	return 0;
}
