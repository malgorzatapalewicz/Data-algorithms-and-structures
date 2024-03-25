#include <iostream>
using namespace std;

//drzewo binarne
struct nodeBST {
    int key; // val
    nodeBST* parent;
    nodeBST* left;
    nodeBST* right;
};

// korzen -> lewe poddrzewo -> prawe poddrzewo
void preorder(nodeBST* root){
    if(!root){ return; }
    cout << root->key << " ";
    if(root->left){ preorder(root->left);}
    if(root->right){ preorder(root->right);}
}

// lewe poddrzewo -> korzen -> prawe poddrzewo
void inorder(nodeBST* root){
    if(!root){ return;}
    if(root->left){ inorder(root->left);}
    cout << root->key << " ";
    if(root->right){ inorder(root->right);}
}

// lewe poddrzewo -> prawe poddrzewo -> korzen
void postorder(nodeBST* root){
    if(!root){ return; }
    if(root->left){ postorder(root->left);}
    if(root->right){ postorder(root->right);}
    cout << root->key << " ";
}

// wyszukiwanie minimum
nodeBST* minimum(nodeBST* root){
    while(root->left){
        root = root->left;
    }
    //cout << "minimum to: " << root->key << endl;
    nodeBST* min = root;
    return min;
}

// wyszukiwanie maksimum
nodeBST* maximum(nodeBST* root){
    while(root->right){
        root = root->right;
    }
    //cout << "maximum to: " << root->key << endl;
    nodeBST* max = root;
    return max;
}

// szukanie nastepnika
nodeBST* findNext(nodeBST* nodeToFind){

    if(!nodeToFind){ return nullptr;} // nie istnieje taki element
    if(nodeToFind->right){
        return minimum(nodeToFind->right);

    } else { // brak prawego poddrzewa
        nodeBST *tmpParent = nodeToFind->parent;
        while (tmpParent && (nodeToFind == tmpParent->right)) {
            nodeToFind = tmpParent;
            tmpParent = tmpParent->parent;
        }
        return tmpParent;
    }
}

// wyswietlanie rezultatu funkcji findNext
void findNext_show(nodeBST* nodeToFind){
    if (nodeToFind) {
        nodeBST* next = findNext(nodeToFind);

        if (next) {
            cout << "nastepnik liczby " << nodeToFind->key << " to " << next->key << endl;
        } else {
            cout << "brak nastepnika liczby " << nodeToFind->key << endl;
        }
    } else {
        cout << "nie istnieje taki element" << endl;
    }
}

//wyszukiwanie poprzednika
nodeBST* findBefore(nodeBST* nodeToFind){
    if(!nodeToFind){ return nullptr;}
    if(nodeToFind->left){   // istnieje lewe poddrzewo
        return maximum(nodeToFind);

    } else {    // brak lewego poddrzewa
        nodeBST* tmpParent = nodeToFind->parent;
        while(tmpParent && nodeToFind == tmpParent->left){ // cofamy sie do gory
            nodeToFind = tmpParent;
            tmpParent = tmpParent->parent;
        }
        return tmpParent;
    }
}

// wyswietlanie rezultatu funkcji findNext
void findBefore_show(nodeBST* nodeToFind){
    if (nodeToFind) {
        nodeBST* before = findBefore(nodeToFind);

        if (before) {
            cout << "poprzednik liczby " << nodeToFind->key << " to " << before->key << endl;
        } else {
            cout << "brak poprzednika liczby " << nodeToFind->key << endl;
        }
    } else {
        cout << "nie istnieje taki element" << endl;
    }
}

// dodawanie
void insert(nodeBST* &root, int x){
    nodeBST* nodeToAdd = new nodeBST {x, nullptr, nullptr, nullptr};

    if(root == nullptr){
        root = nodeToAdd;
    } else {
        nodeBST* tmp = root; //wskaznik na biezacy wezel
        nodeBST* tmpParent = nullptr; // wskaznik na biezacego rodzica
        while(tmp) {
            tmpParent = tmp;
            if (x <= tmp->key) { tmp = tmp->left;}
            else { tmp = tmp->right;}
        }
        nodeToAdd->parent = tmpParent;

        if(tmpParent->key >= x){
            tmpParent->left = nodeToAdd;
        } else {
            tmpParent->right = nodeToAdd;
        }
    }
}

// usuwanie wezla
void remove(nodeBST* &root, nodeBST* nodeToRemove){
    nodeBST* tmpNode; // wskazik ktory wskazuje na usuwany wezel
    if(root == nullptr){
        cout << "drzewo jest puste" << endl;
        return;
    }
    if(nodeToRemove->left && nodeToRemove->right){ // ma oba poddrzewa
        tmpNode = findNext(nodeToRemove); // tmpNode = nastepnik nodeToRemove
    } else { tmpNode = nodeToRemove;}

    nodeBST* tmpChild = nullptr; // wezel ktory wstawiamy za usuwany wezel
    if(tmpNode->left){
        tmpChild = tmpNode->left;
    } else { tmpChild = tmpNode->right;}

    if(tmpChild){ tmpChild->parent = tmpNode->parent;}

    if(tmpNode->parent){
        if(tmpNode == tmpNode->parent->left){
            tmpNode->parent->left = tmpChild;
        } else { tmpNode->parent->right = tmpChild;}

    } else {
        root = tmpChild; // jesli nodeToRemove = tmpNode
    }
    if(tmpNode != nodeToRemove){
        nodeToRemove->key = tmpNode->key;
        delete tmpNode;
    }

    // nodeToRemove= 10, tmpNode = 12, tmpChild = 0
}

// wyszukiwanie elementu w drzewie
nodeBST* find(nodeBST* root, int x) {
    if (root == nullptr || root->key == x) {
        return root;
    }

    if (x < root->key) {
        return find(root->left, x);
    } else {
        return find(root->right, x);
    }
}

// wyswietlanie drzewa
void show(nodeBST* root, int indent = 0){
     // wciecie w akapicie - indent
    if(root){ show(root->right, indent + 4);

        for(int i = 0; i < indent; i++){ cout << " ";}
        cout << " " << root->key << endl;

       show(root->left, indent + 4);}
}

//sprawdza czy mozna dodac
bool checkReservation(nodeBST* nodeToAdd, int userTime){
    if (nodeToAdd == nullptr){
        insert(nodeToAdd,userTime);
        cout << "pomyslna rezerwacja!" << endl;
        return true;
    }
    int rootTime = nodeToAdd->key;
    if(abs(userTime - rootTime) <= 5){ // modul z roznicy
        cout << "sprobuj wybrac inna godzine, roznica czasu jest za mala (<5min)" << endl;
        return false;
    }
    if (userTime < rootTime) {
        return checkReservation(nodeToAdd->left, userTime);
    } else {
        return checkReservation(nodeToAdd->right, userTime);
    }
}

// system rezerwacji toru kartingowego
bool reservation(nodeBST* &root, int hour, int minutes){
    // sprawdzenie poprawnosci danych
    const int minutesINhour = 60;
    while(minutes >= minutesINhour){
        hour++;
        minutes -= minutesINhour;
    }
    if(hour >= 25){
        cout << "blednie wpisales godzine" << endl;
        return false;
    }
    if(minutes < 10) {
        cout << "wybrana przez ciebie godzina to: " << hour << ":0" << minutes << "\t";
    } else {
        cout << "wybrana przez ciebie godzina to: " << hour << ":" << minutes << "\t";
    }
    //rezerwacja
    int userTime = hour * 60 + minutes;

    if (checkReservation(root, userTime)) {
        insert(root, userTime);
        return true;
    } else {
        return false;
    }
}



int main(){
    nodeBST* root = nullptr;
    nodeBST* rootReservation = nullptr;
    insert(root,10);
    insert(root, 5);
    insert(root,15);
    insert(root,3);
    insert(root, 8);
    insert(root,12);
    insert(root,18);
//    postorder(root);
//    preorder(root);
//    inorder(root);
//    minimum(root);
//    maximum(root);
//    findNext_show(find(root,5));
//    findBefore_show(find(root,4));
//
//    nodeBST* min = minimum(root);
//    cout << "minimum to: " << min->key << endl;
//    nodeBST* max = maximum(root);
//    cout << "maximum to: " << max->key << endl;
//    remove(root, find(root,10));
//    cout << endl;
//    show(root);
    reservation(rootReservation,14,53);
    reservation(rootReservation,15,50);
    reservation(rootReservation,15,54);
    show(rootReservation);
    return 0;
}
