#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Collector     //Se crea la clase collector con variables genericas
{
    public:
        vector<T> collect;      //Se instancia un vector en donde se almacenaran las direcciones de memoria
        void display()          //Se crea una funcion para imprimir el vector de las direcciones de memoria
        {
            for (auto it = collect.begin(); it != collect.end(); it++)
            {
                cout << &it << " ";
            }
            cout << endl;
        }
};

template<class T>
class Node              //Se crea la clase nodo con variables genericas
{
    public:
        T data;             //El campo del data
        Node<T> *next;      //El puntero al siguiente nodo

    void *operator new(size_t size)         //Se sobrecarga la funcion new
    {
        void * p = malloc(size);
        return p;
    }  
    void operator delete(void *p)           //Se sobrecarga la funcion delete
    {

        free(p); 
    }
    void printData(Node n)                  //Se crea la funcion para imprimir el nodo
    {
        cout << n->data << n->next << endl;
        return;
    }
    void modifyData(int data, Node n)       //Se crea la funcion modificar el valor de los nodos
    {
        n->data = data;
        return;
    }
};

template<class T>
class List              //Se crea la clase list con variables genericas
{
    private:
        Node<T>* head;
    public:
        Collector<Node<int>*> c;

        List<T>()
        {
            head = NULL;
        }

        void addNode(T data)        //Se crea la funcion para anadir nodos a la lista enlazada
        {
            if (c.collect.empty() == true)
            {
                Node<T>* newnode = new Node<T>();
                newnode ->data = data;
                newnode ->next = NULL;
                if (head == NULL)
                {
                    head = newnode;  //Si la lista se encuentra vacia el nodo se anade como head
                }
                else
                {
                    Node<T>* temp = newnode;    //Si la lista no se encuentra vacia el nodo se convierte en el nuevo head
                    temp -> data = data;
                    temp ->next = head;
                    head = temp;
                }
                return;
            }
            else
            {
                Node<T>* newnode = c.collect.back();        
                c.collect.pop_back();
                newnode->data = data;
                newnode->next = NULL;
                Node<T>*temp = newnode;
                temp->data = data;
                temp->next = head;
                head = temp;
                return;
            }
        }

        void deleteNode(T data)         //Se crea la funcion para eliminar nodos sabiendo el valor del nodo
        {
            if (head->data == data)
            {
                if (head->next == NULL)     //No se puede eliminar el nodo de la lista si la lista solo contiene un nodo puesto a que da un error
                {
                    cout << "List can't be empty" << endl;
                    return;
                }
                else
                {
                    Node<T> *temp = new Node<T>();      //Se elimina de la lista enlazada cuando es head y se anade al collector
                    temp = head;
                    head = head->next;
                    c.collect.push_back(temp);
                    return;
                }
                
            }

            Node<T> *prev = head;
            while (prev -> next != NULL && prev -> next -> data != data)  //Se busca el nodo a traves de la lista
            {
                prev = prev -> next;
            }
            if (prev -> next == NULL)       //Cuando no se encuentra en la lista
            {
                cout << "The node is not present in the list" << endl;
                return;
            }
            Node<T> *temp = new Node<T>();      //Se elimina el nodo de la lista cuando no es head de la lista
            temp = prev->next;
            prev -> next = prev -> next -> next;
            c.collect.push_back(temp);          
            
        }

        void display()      //Se crea funcion para imprimir la lista de los nodos en orden de head a hail
        {
            if (head == NULL)
            {
                cout << "The list is currently empty" << endl;
            }
            else
            {
                Node<T>* temp = head; 
                while (temp != NULL)
                {
                    cout << temp->data << " ";
                    temp = temp->next;
                }
                cout << endl;
            }
            return;
        }
        void printHead()        //Se imprime el head de la lista de los nodos
        {
            cout << head->data << endl;
            return;
        }
        void modifyHead(int data)       //Se puede modificar el head de la lista enlazada
        {
            head->data = data;
            cout << head->data << endl;
            return;
        }
};

int main(){
    List<int> a;        //Se instancia la clase lista con el nombre "a"
    a.addNode(20);      //Se agregan 3 nodos a la lista "a"
    a.addNode(10);
    a.addNode(30);
    a.display();        //Se imprimen las lista de nodos en orden de head a tail
    a.deleteNode(10);   //Se elimina el nodo con el valor de 10
    a.display();        //Se vuelve a imprimir la lista de nodos en orden de head a tail
    a.c.display();      //Se imprime el collector para verificar que se haya pasado la direccion de memoria
    a.addNode(50);      //Se anade otro nodo usando la direccion de memoria previamente guardada
    a.display();        //Se imprime la lista de nodos en orden de head a tail
    a.c.display();      //Se imprime el collector para verificar que se haya usado la direccion guardada
}