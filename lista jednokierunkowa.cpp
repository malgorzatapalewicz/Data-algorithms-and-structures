#include <iostream>
using namespace std;

struct node{
    int val;
    node* next;
};

// wstawianie elementu na poczatek listy
void addToTheBeginning(node* &head, int x){

    node* nodeToAdd = new node;
    nodeToAdd -> val = x;
    nodeToAdd -> next = head;
    head = nodeToAdd;
}

// wstawianie elementu na koniec listy
void addToTheEnd(node* &head, int x){
    node* nodeToAdd = new node;
    nodeToAdd->val = x;
    nodeToAdd->next = nullptr;

    if (!head){ // head == NULL
        head = nodeToAdd; // wtedy to co dodajemy bedzie head'em

    } else {
        node *tmp = head;
        while (tmp->next) {   // jeśli istnieje nastepnik nodeToAdd
            tmp = tmp->next; // przeszukujemy cala liste
        }
        tmp->next = nodeToAdd;
    }
}

// dodawanie po jakims elemencie
void addAfter(node* &head, int x, int valueToAdd){ // nodeToAdd to co chcemy dodac i x po jakim elemencie
    node* tmp = head;

    //Szukanie elementu po ktorym wartosc ma zostac dodana
    while (tmp && (tmp->val != x)) { // musi istniec tmp i
        tmp = tmp->next;
    }
    //Zamiana wskaznikow
    if (tmp){
        node* nodeToAdd = new node{valueToAdd, tmp->next};
        tmp->next = nodeToAdd;
    }
    else {
        cout << "Nie ma elementu o wartosci: " << x << endl;
    }
}

// usuwanie z poczatku
void removeFromTheBeginning(node* &head){
    if(head != NULL){
        node* tmp = head; // wskazuje na 1 element listy ktory bedzie usuwany
        head = head -> next; // head ma wskazywac na kolejny element listy
        delete tmp;
    }
    else{
        cout << "Pusta lista" << endl;
    }
}

// usuwanie z konca
void removeFromTheEnd(node* &head) {
    if (!head) {
        cout << "Lista jest pusta, nie ma nic do usuniecia" << endl;
    } else {
        if (head->next == NULL) { //przypadek jak mamy tylko jeden element
            delete head;
            head = NULL;
        } else {  //gdy elementow jest powyzej jednego
            node *tmp = head;
            while (tmp->next->next != NULL) { //do przedostatniego elementu
                tmp = tmp->next;
            }
            delete tmp->next;
            tmp->next = NULL;
        }
    }
}

// usuwanie po elemencie o wartosci x
void removeAfter(node* &head, int x) {
    node* pointer = head; // zapamietujemy adres head

    //Szukanie elementu po ktorym wartosc ma zostac usunieta
    while (pointer && (pointer->val != x)) {
        pointer = pointer->next;
    }

    //Zamiana wskaznikow
    if (pointer) {
        if (pointer->next == nullptr) {
            cout << "Element o wartosci: " << x << " jest ostatni." << endl;
        }
        else {
            node* tmp = pointer->next;
            pointer->next = pointer->next->next;
            delete tmp;
        }
    }
    else {
        cout << "Nie ma elementu o wartosci: " << x << endl;
    }
}

// wyswietlanie
void show (node* head){ // moze byc bez referencji bo nie bedziemy edytowac head, dzieki temu zaoszczedzimy liczbe zmiennych
    cout << "head -> ";
    node* tmp = head; // head = wskaznikowi na p
    while(tmp != NULL){
        cout << tmp->val << " -> "; // wypisz p->val
        tmp = tmp->next;// a nastepnie przejdz do nastepnego
    }
    cout << "NULL" << endl;
}

// wyswietlanie dlugosci listy
void printListLength(node* head){ //
    int length = 0;
    while(head != nullptr){
        length += 1;
        head = head->next;
    }

    cout << "Dlugosc listy: " << length << endl;
}

// usun co 2 element na liscie
void remove2Element (node* &head){
    node* tmp = head;
    int i = 0;
    if (!tmp || !tmp->next){
        cout << "Lista jest pusta lub ma tylko jeden element, nie ma czego usuwac";
    } else {
        while(tmp && tmp->next){
            if(i%2==0){
                node* p = tmp->next;
                tmp->next = p->next;
                delete p;
            } else {
                tmp=tmp->next;
            }
            i++;
        }
    }
}

// kopia listy h->1->1->2->2 itp..
void doubleList(node* &head){
    node* tmp = head;
    if (!tmp){
        cout << "Lista jest pusta, nie ma czego kopiowac" << endl;
    } else {
        while(tmp){
            node* nodeToAdd= new node;
            nodeToAdd->next = tmp->next;
            tmp->next = nodeToAdd;
            nodeToAdd->val = tmp->val;
            tmp = nodeToAdd->next; // przechodzimy dalej do oryginalnego wezla
        }
    }
}

// kopiowanie listy h->1->2->1->2 itp..
void copyList(node* &head){
    node* tmp = head;
    if(!tmp){
        cout << "Lista jest pusta, nie ma czego kopiowac" << endl;
    } else {
        node* headA = nullptr; // nowa lista ktora bedziemy dolaczac
        while (tmp->next) {
            addToTheEnd(headA, tmp->val);
            tmp = tmp->next;
        }
        addToTheEnd(headA,tmp->val);
        tmp->next = headA;
        //show(headA);
    }
}

// srednia wszystkich elementow listy
double average(node* &head){
    node* tmp = head;
    int counter {0};
    int suma {0};
    double srednia {0.0};

    if(!tmp){
        cout << "Lista jest pusta. Nie ma jak policzyc sredniej" << endl;
    } else {
        while(tmp){
            counter++;
            suma += tmp->val;
            tmp = tmp->next;
        }
        srednia = static_cast<double>(suma) / counter;
        cout << "Srednia wynosi: "<< srednia << endl;
    }
    return srednia;
}

// zamiana elementu x ze swoim poprzednikiem
void replaceBefore(node* &head, int x){
    node* tmp = head;
    node* beforetmp = nullptr;
    if(!tmp || !tmp->next){
        cout << "Lista jest pusta lub ma tylko jeden element. Nie ma mozliwosci zamiany elementow." << endl;
        return;
    } else {
        if (tmp->val == x) { // czy head == x
            node *p = tmp->next;
            tmp->next = p->next;
            p->next = tmp;
            head = p;
        } else {
            while (tmp->next) {
                if (tmp->next->val == x) {
                    node* p = tmp->next;
                    tmp->next = p->next;
                    p->next = tmp;
                    beforetmp->next = p;
                    p->val = x;
                } else {
                    cout << "W liscie nie istnieje element: " << x << endl;
                }
                beforetmp = tmp;
                tmp = tmp->next;
            }
        }
    }
}

// zamiana elementu x ze swoim nastepnikiem
void replaceNext(node* &head, int x){
    node* tmp = head;
    node* beforetmp = nullptr;
    if(!tmp || !tmp->next){
        cout << "Lista jest pusta lub ma tylko jeden element. Nie ma mozliwosci zamiany elementow." << endl;
        return;
    } else {
        if (tmp->val == x) { // czy head == x
            node *p = tmp->next;
            tmp->next = p->next;
            p->next = tmp;
            head = p;
        } else {
            while (tmp) {
                if (tmp->val == x) {
                    node* p = tmp->next;
                    tmp->next = p->next;
                    p->next = tmp;
                    beforetmp->next = p;
                } else {
                    //  cout << "W liscie nie istnieje element: " << x << endl;
                }
                beforetmp = tmp;
                tmp = tmp->next;
            }
        }
    }
}

// usun elementy parzyste
void deleteEvenNumber(node* &head){
    node* tmp = head;
    if (!tmp){
        cout << "Lista jest pusta, nie ma czego usuwac" << endl;
    } else {
        while(tmp && tmp->val % 2 == 0){ // head jest parzyste
            node* p = tmp;
            tmp = tmp->next;
            delete p;
            head = tmp;
        }
        while(tmp && tmp->next) {
            if (tmp->next->val % 2 == 0) {
                node *p = tmp->next;
                tmp->next = p->next;
                delete p;
            } else {
                tmp = tmp->next;
            }
        }
    }
}

// odwrocenie listy i polaczenie jej z pierwotna h->1->2->3   h->1->2->3->3->2->1
void reverseListAndAdd(node* head){
    node* headA = nullptr;
    node* tmp = head;
    while(tmp->next != nullptr){
        addToTheBeginning(headA,tmp->val);
        tmp = tmp->next;
    }
    addToTheBeginning(headA,tmp->val);
    tmp->next = headA;
}

// laczenie dwoch innych list
void connectLists(node* &headA, node* &headB){ // przyjmujemy dwie listy
    node* tmp = headA;
    while(tmp->next != nullptr){
        tmp = tmp->next;
    }
    tmp->next = headB;
}

// zlaczenie 2 posortowanych list w jedna aby byla nadal posortowana
node* connectSortedLists(node* headA,node* headB, node* &result){

    node* resultHead = new node;
    resultHead->next = nullptr;
    addToTheBeginning(resultHead, 0);
    node* tail = resultHead;

    node* pointerA = headA;
    node* pointerB = headB;

    while(pointerA && pointerB){

        if(pointerA->val > pointerB->val){
            tail->next = pointerB;
            pointerB = pointerB->next;

        } else {
            tail->next = pointerA;
            pointerA = pointerA->next;
        }
        tail = tail->next;
    }

    if(pointerA != nullptr){
        tail->next = pointerA;
    } else if (pointerB != nullptr){
        tail->next = pointerB;

    } else {
        cout << "Obie listy sa puste." << endl;
    }

    result = resultHead->next;
    delete resultHead;


    return result;
}

// rozdzielenie listy na pol
void separation(node* &head){
    node* tmp = head; // co 1 elementy
    node* p = head; // co 2 element
    if (!head || !head->next) {
        cout << "Lista jest pusta, badz ma jeden element. Nie da sie podzielic funkcji" << endl;
    } else {
        while (p->next != nullptr && p->next->next != nullptr) {
            tmp = tmp->next;
            p = tmp->next;
        }
        node* headA = tmp->next;
        tmp->next = nullptr;
        show(head);
        show(headA);
    }
}

// zamien pierwszy element z ostatnim
void changeFirstWithLast(node* &head){
    node* beforeLast = head; // wskaznik ktory przechodzi do poprzednika koncowego elementu
    node* last = head;
    node* first = head; // wskaznik na glowe

    if(!head || head->next == nullptr){
        cout << "Lista jest pusta lub ma jeden element" << endl;

    } else {
        while (last->next != nullptr) {
            beforeLast = last;
            last = last->next;
        }
        beforeLast->next = first;
        last->next = first->next;
        first->next = nullptr;
        head = last;
    }
}

// zamiana co 2 element na calej liscie
void swapWithNext(node*& head) {
    if (!head || !head->next) {
        cout << "Lista jest pusta lub ma tylko jeden element, nie mozna wykonac zamiany." << endl;
        return;
    } else {
        node* resultHeadTemporary = new node;
        addToTheBeginning(resultHeadTemporary,0);
        resultHeadTemporary->next = head;
        head = resultHeadTemporary;

        node* before = head;
        node* tmp = before->next;
        while (tmp != nullptr && tmp->next != nullptr) {
            node* after = tmp->next;
            tmp->next = after->next;
            before->next = after;
            after->next = tmp;

            before = tmp;
            tmp = tmp->next;
        }

        node* newHead = head->next; // usuwanie elementu pomocniczego
        delete head;
        head = newHead;

        if(tmp){ // lista nieparzysta
            before->next = tmp;
        }
    }
}

// funkcja zamienia wskaznikow do bubbleSort
void swap(node* nodeA, node* nodeB){
    int tmp = nodeA->val;
    nodeA->val = nodeB->val;
    nodeB->val = tmp;
}
// sortowanie babelkowe
void bubbleSort(node* head){
    if(!head && !head->next){ return;}
    bool if_swap;

    do {
        if_swap = false;
        node* tmp = head;
        node* nodeLast = nullptr;

        while(tmp->next != nodeLast){
            if(tmp->val > tmp->next->val){
                swap(tmp,tmp->next);
                if_swap = true;
                }
            tmp = tmp->next;
            }
        nodeLast = tmp;
    } while(if_swap);
}

int main(){
    node* head = nullptr; // glowa ma wskazywac na NULL na poczatku
    node* headA = nullptr;
    node* result = nullptr;

    addToTheBeginning(head,1);
    addToTheEnd(head,5);
    addToTheEnd(head,3);
    addToTheBeginning(head,7);
    addToTheEnd(head,2);
    addToTheEnd(head,7);

    show(head);
//    show(headA);
//    remove2Element(head);
//
//    doubleList(head);
//    show(head);
//    copyList(head);
//    average(head);
//    replaceNext(head,3);
//    deleteEvenNumber(head);
//    swapWithNext(head);
//    connectSortedLists(head,headA,result);
//    separation(head);
    bubbleSort(head);
    show(head);


    return 0;
}
// referencja zmienia oryginal, nie tylko w obrebie funkcji
// new node - tworzysz nowa strukture typu node