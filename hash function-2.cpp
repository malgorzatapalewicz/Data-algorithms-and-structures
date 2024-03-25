#include <iostream>
using namespace std;

//lista
struct node {
    int val;
    node* next;
};

// wstawianie elementu na poczatek listy
void addToTheBeginning(node* &head, int x){
    node* nodeToAdd = new node;
    nodeToAdd->val = x;
    nodeToAdd->next = head;
    head = nodeToAdd;
}

// zmieniam litery na liczby
int textToASCII(const string& text){
    int total = 0; //suma wartosci ASCII liter z tekstu
    for(char letter : text){ //iterujemy przez text
        total += static_cast<int>(letter);
    }
    //cout << total << endl;
    return total;
}

// liczenie modulo
int modulo(int x){
    int afterModulo = x % 13;
    return afterModulo;
}

// dodawanie do glownej tablicy
void addToMainHead(node* mainHEAD[], int size){
    string name, surname;
    cout << "podaj imie i nazwisko: " << endl;
    cin >> name >> surname;
    int person = textToASCII(name) + textToASCII(surname);
    int index = modulo(person); //przypisanie unikalnego numeru dla wartosci
    addToTheBeginning(mainHEAD[index], person);
}

// zwolnianie pamieci
void deleteMainHead(node* mainHEAD[], int size){
    for(int i = 0; i < size; i++){
        node* current = mainHEAD[i];
        while (current != nullptr) {
            node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] mainHEAD;
}

// wyswietlanie
void show(node* head){
    cout << "head -> ";
    node* tmp = head;
    while(tmp != nullptr){
        cout << tmp->val << " -> ";
        tmp = tmp->next;
    }
    cout << "NULL" << endl;
}

// wyswietlanie wszystkich elementow
void showAllElements(node* mainHEAD[], int size){
    for(int i = 0; i < size; i++){
        cout << "lista " << i + 1 << ": ";
        show(mainHEAD[i]);
    }
}


int main(){
    const int size = 13;
    node** mainHEAD = new node* [size]; //utowrzenie tablicy z innymi listami

    //ustawienie wszystkich elementkow na NULL
    for(int i = 0; i < size; i++){
        mainHEAD[i] = nullptr;
    }

    addToMainHead(mainHEAD, size);
    showAllElements(mainHEAD, size);
    deleteMainHead(mainHEAD, size); //zwolnienie pamieci

    return 0;
}