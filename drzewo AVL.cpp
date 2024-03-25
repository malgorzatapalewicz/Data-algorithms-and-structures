#include <iostream>
using namespace std;

//drzewo AVL
struct nodeAVL {
    int key; // val
    nodeAVL* parent;
    nodeAVL* left;
    nodeAVL* right;
    int balance;
};

//aktualizacja balansu
int updateBalance(nodeAVL* &node){
    int leftHeight = (node->left != nullptr) ? node->left->balance + 1 : 0;
    int rightHeight = (node->right != nullptr) ? node->right->balance + 1 : 0;
    int balance = leftHeight - rightHeight;
    node->balance = balance;
    return balance;
}

// rotacja pojedyncza prawa
void rotateRight(nodeAVL* &root, nodeAVL* nodeToRotate){
    nodeAVL* newRoot = nodeToRotate->left;
    newRoot->balance = nodeToRotate->balance = 0;
    nodeToRotate->left = newRoot->right;

    if(nodeToRotate->left != nullptr) {
        nodeToRotate->left->parent = nodeToRotate;
    }
    newRoot->parent = nodeToRotate->parent;

    if(nodeToRotate->parent == nullptr){
        root = newRoot;
    } else if(nodeToRotate->parent->left == nodeToRotate){
        nodeToRotate->parent->left = newRoot;
    } else {
        nodeToRotate->parent->right = newRoot;
    }
    newRoot->right = nodeToRotate;
    nodeToRotate->parent = newRoot;

    updateBalance(nodeToRotate);
    updateBalance(newRoot);
}

// rotacja pojedyncza lewa
void rotateLeft(nodeAVL* &root, nodeAVL* nodeToRotate){
    nodeAVL* newRoot = nodeToRotate->right;
    nodeToRotate->right = newRoot->left;

    if(nodeToRotate->right != nullptr){
        nodeToRotate->right->parent = nodeToRotate; //aktualizacja rodzica lewego dziecka
    }
    newRoot->parent = nodeToRotate->parent; // do porownania

    if(nodeToRotate->parent == nullptr){ // nodeToRotate jest korzeniem
        root = newRoot;
    } else if(nodeToRotate->parent->right == nodeToRotate){ // jesli jest prawym dzieckiem
        nodeToRotate->parent->right = newRoot;
    } else {
        nodeToRotate->parent->left = newRoot;
    }
    newRoot->left = nodeToRotate;
    nodeToRotate->parent = newRoot;

    //aktualizacja balansu
    updateBalance(nodeToRotate);
    updateBalance(newRoot);
}

// rotacja podwojna prawa
void rotateRightLeft(nodeAVL* &root, nodeAVL* nodeToRotate){
    nodeAVL* middle = nodeToRotate->left;
    nodeAVL* newRoot = middle->right;

    //przypisanie lewej galezi newRoot
    middle->right = newRoot->left;
    if(middle->right != nullptr){ //jesli istnieje taka galaz
        middle->right->parent = middle;
    }

    //przypisanie rodzica nodeToRotate do nowego korzenia
    newRoot->parent = nodeToRotate->parent; //newRoot ma byc nowym korzeniem
    if(nodeToRotate->parent == nullptr){
        root = newRoot;
    } else if(nodeToRotate->parent->left == nodeToRotate){ //nodeToRotate jest lewym dzieckiem
        newRoot->parent->left = newRoot;
    } else { // nodeToRotate jest prawym dzieckiem
        newRoot->parent->right = nodeToRotate;
    }

    //ustawienie prawego poddrzewa newRoot jako lewe nodeToRotate
    nodeToRotate->left = newRoot->right;
    if(nodeToRotate->left != nullptr){
        nodeToRotate->left->parent = nodeToRotate;
    }

    //w koncu dodajemy do korzenia dzieci
    newRoot->right = nodeToRotate;
    newRoot->left = middle;
    middle->parent = nodeToRotate->parent = newRoot;

    //aktualizacja wspolczynnikow balansu
    if(newRoot->balance == 1){ //przed rotacja bylo niezrownowazone w prawo
        middle->balance = -1; // znajduje sie na nizszym poziomie niz wczesniej
        nodeToRotate->balance = 0;
    } else {
        middle->balance = 0;
        nodeToRotate->balance = 1;
    }
    newRoot->balance = 0;
}

// rotacja podwojna lewa
void rotateLeftRight(nodeAVL* &root, nodeAVL* nodeToRotate){
    nodeAVL* middle = nodeToRotate->right;
    nodeAVL* newRoot = middle->left;

    //przypisanie prawej galezi newRoot do middle
    middle->left = newRoot->right;
    if(middle->left != nullptr){
        middle->left->parent = middle;
    }

    //przypisanie rodzina nowemu korzeniowi
    newRoot->parent = nodeToRotate->parent;
    if(nodeToRotate->parent == nullptr){
        root = newRoot;
    } else if(nodeToRotate->parent->left == newRoot){
        newRoot->parent->left = newRoot;
    } else {
        newRoot->parent->right = newRoot;
    }

    //przepisanie lewego dziecka newRoot jako prawe nodeToRotate
    nodeToRotate->right = newRoot->left;
    if(newRoot->left != nullptr) {
        nodeToRotate->right->parent = nodeToRotate;
    }

    //dodajemy dzieci nowemu korzeniowi
    newRoot->right = middle;
    newRoot->left = nodeToRotate;
    middle->parent = nodeToRotate->parent = newRoot;

    //aktualizacja wspolczynnika balansu
    if(newRoot->balance == -1){ //przed rotacja bylo niezrownowazone w prawo
        middle->balance = 1; // znajduje sie na nizszym poziomie niz wczesniej
        nodeToRotate->balance = 0;
    } else {
        middle->balance = 0;
        nodeToRotate->balance = 1;
    }
    newRoot->balance = 0;
}

// wyszukiwanie elementu w drzewie
nodeAVL* find(nodeAVL* root, int x) {
    if (root == nullptr || root->key == x) {
        return root;
    }
    if (x < root->key) {
        return find(root->left, x);
    } else if (x >= root->key){
        return find(root->right, x);
    } else {
        cout << "brak elementu" << endl;
        return nullptr; //nic nie zwraca
    }
}

// wyszukiwanie minimum
nodeAVL* minimum(nodeAVL* root){
    while(root->left){
        root = root->left;
    }
    //cout << "minimum to: " << root->key << endl;
    nodeAVL* min = root;
    return min;
}

// szukanie nastepnika
nodeAVL* findNext(nodeAVL* nodeToFind){

    if(!nodeToFind){ return nullptr;} // nie istnieje taki element
    if(nodeToFind->right){
        return minimum(nodeToFind->right);

    } else { // brak prawego poddrzewa
        nodeAVL *tmpParent = nodeToFind->parent;
        while (tmpParent && (nodeToFind == tmpParent->right)) {
            nodeToFind = tmpParent;
            tmpParent = tmpParent->parent;
        }
        return tmpParent;
    }
}

// wstawianie wezlow
void insert(nodeAVL* &root, nodeAVL* parent, int x){
    if(!root){
        root = new nodeAVL {x, parent, nullptr, nullptr,0};
        updateBalance(root);
        return;
    } else if(x < root->key){ //do lewego poddrzewa
        insert(root->left, root, x);

        switch(root->balance) {
            case 0: if(root->left->balance == -1) rotateRight(root, root->left);
                    else if(root->left->balance == 1) rotateRightLeft(root, root->left);
                    root->balance = 1;
                    break;
            case 1: root->balance = 0; break;
            default: root->balance = 1; break;
        }

        if(root->parent){
            updateBalance(root->parent);
        }

    } else {
        insert(root->right,root,x);
        switch(root->balance){
            case -1: if(root->right->balance == 1) rotateLeftRight(root,root->right);
                     else if(root->right->balance == -1) rotateLeft(root,root->right);
                     root->balance = 0;
                     break;
            default: root->balance = 0; break;
        }

        if(root->parent){
            updateBalance(root->parent);
        }
    }
}

//usuwanie wezlow
void remove(nodeAVL* &root, int x){
    if(!root){
        cout << "brak elementow w drzewie, nie ma czego usunac" << endl;
        return;
    }

    nodeAVL* nodeToRemove = find(root,x);
    if(!nodeToRemove){
        cout << "element " << x << " nie istnieje w drzewie" << endl;
        return;
    }

//przypadek 1 - brak dzieci
    if(nodeToRemove->left == nullptr && nodeToRemove->right == nullptr) {
        if (nodeToRemove->parent != nullptr) {
            if (nodeToRemove->parent->left == nodeToRemove) { //jest lewym dzieckiem
                nodeToRemove->parent->left = nullptr;
            } else {
                nodeToRemove->parent->right = nullptr;
            }
            delete nodeToRemove;
        } else { //usuwamy korzen
            delete nodeToRemove;
            root = nullptr;
        }

// przypadek 2 - dwoja dzieci
    } else if(nodeToRemove->left != nullptr && nodeToRemove->right != nullptr) {
        nodeAVL* next = findNext(nodeToRemove);
        if(next){
            nodeToRemove->key = next->key;
            remove(nodeToRemove->right, next->key);
        }
// przypadek 3 - jedno dziecko
    } else {
        nodeAVL* child = (nodeToRemove->left != nullptr) ? nodeToRemove->left : nodeToRemove->right;
        if(nodeToRemove->parent != nullptr){
            if (nodeToRemove->parent->left == nodeToRemove) {
                nodeToRemove->parent->left = child;
            } else {
                nodeToRemove->parent->right = child;
            }
            if (child) {
                child->parent = nodeToRemove->parent;
            }
            delete nodeToRemove;
        } else {
            delete nodeToRemove;
            root = child;
            if(child) child->parent = nullptr;
        }
    }

    if(root){
        updateBalance(root);
        int balance = root->balance;
        if (balance == -2) {
            if (root->right->balance == 1) {
                rotateRightLeft(root, root->right);
            } else {
                rotateLeft(root, root->right);
            }
        } else if (balance == 2) {
            if (root->left->balance == -1) {
                rotateLeftRight(root, root->left);
            } else {
                rotateRight(root, root->left);
            }
        }
    }
}

// wyswietlanie drzewa
void show(nodeAVL* root, int indent = 0){
    // wciecie w akapicie - indent
    if(root){ show(root->right, indent + 4);

        for(int i = 0; i < indent; i++){ cout << " ";}
        cout << " " << root->key << endl;

        show(root->left, indent + 4);}
}

// korzen -> lewe poddrzewo -> prawe poddrzewo
void preorder(nodeAVL* root){
    if(!root){ return; }
    cout << root->key << " ";
    if(root->left){ preorder(root->left);}
    if(root->right){ preorder(root->right);}
}

int main(){
    nodeAVL* root = nullptr;
    insert(root, nullptr, 30);
    insert(root, nullptr,31);
    insert(root, nullptr,32);
    preorder(root);
    cout << endl;
   rotateLeft(root,root);
   // rotateRightLeft(root,find(root,28));
//    insert(root,10);
//    insert(root, 5);
//    insert(root,15);
//    insert(root,12);
//    insert(root, 18);
//    insert(root,17);
//    insert(root,30);
//    rotateRight(root,);
    preorder(root);
    cout << endl;
    cout << root->balance;
    cout << find(root, 32)->balance;
    cout << find(root,30)->balance;
    remove(root, 30);
    cout << endl;
    show(root);
//    show(root);

//    cout << node->left->right->parent->key; //??
// funkcja wstawiajaca insert ktora bedzie od razu balansowac i wyswirtlanie wraz z balansem
//avl.tree
    return 0;
}