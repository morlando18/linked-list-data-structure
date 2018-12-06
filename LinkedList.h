#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

using namespace std;

template<typename T>
struct Node
{
    T info;
    Node *next, *previews;
    Node() { next = previews = 0; info = T(); }
    Node(const T& data, Node *next, Node *prev): info(data), next(next), previews(prev){ }
};

template <typename T>
class LinkedList{

    friend class Iterator;
private:
    Node<T> *headNode, *tailNode;

public:

                class Iterator
                {
                    friend class LinkedList;

                private:
                    Node<T> *nodePtr;
                    LinkedList<T>*linkedList;
                    Iterator (Node<T> *newPtr, LinkedList<T> *list = 0)
                    {
                        nodePtr = newPtr;
                        linkedList = list;
                    }

                public:
                    //This is the constructor for Iterator
                    Iterator(){}

                    //Return the element at the iterator's current position in the queue.
                    T operator*() const
                        {return nodePtr->info;}

                    /*
                     * Pre-increment overload; advance the operator one position in the list.
                     * Return this iterator. NOTE: if the iterator has reached the end of the list
                     * (past the last element), its data should be equal to LinkedList<T>::end().
                     */
                    Iterator& operator++()
                        { nodePtr = nodePtr-> next;  return *this;  }

                    //Returns true it both iterators point to the same node in the list, and false otherwise
                    bool operator==(Iterator const& rhs)
                        {return nodePtr == rhs.nodePtr;}

                    //Returns false it both iterators point to the same node in the list, and true otherwise.
                    bool operator!=(Iterator const& rhs)
                        {return nodePtr != rhs.nodePtr;}
                };

    //This is the constructor for LinkedList.
    LinkedList<T>(){ headNode = tailNode = 0;}

    //Return an Iterator pointing to the beginning of the list.
    Iterator begin() const
        {return Iterator(headNode, 0);}

    //Return an Iterator pointing past the end of the list (an invalid, unique state, data likely pointing to nullptr.)
    Iterator end() const
        {return Iterator(0,0);}

    //Return true if there are no elements, false otherwise.
    bool isEmpty() const
        {
            if(headNode == 0 )
                {return true; }
            return false;
        }

    //Return the first element in the list.
    T getFront() const
        {return headNode->info;}

    //Return the last element in the list.
    T getBack() const
        {return tailNode->info;}

    //Insert the specified element to the list. Handle the special case when the list is empty.
    void enqueue(T element) {
        if (headNode == 0) {
            tailNode = headNode = new Node<T>(element, 0, 0);
        }
        else
        {
            tailNode->next = new Node<T>(element, 0,tailNode);
            tailNode = tailNode->next;
        }
//            if(tailNode) {
//                Iterator(tailNode = tailNode->next = new Node<T>(element, 0, tailNode), this);
//            }else
//                Iterator(headNode = tailNode = new Node<T>(element, 0, 0), this);
        }

    //Remove the first element from the list. Handle the special case when it is also the last element.
    void dequeue()
        {
            if(!isEmpty()) {
                if (headNode == tailNode) {
                    delete headNode;
                    headNode = tailNode = 0;

                } else {
                    Node<T> *temp = headNode->next;
                    delete headNode;
                    headNode = temp;
                }
            }
        }

    //Remove the last element from the list. Handle the special case when it is also the first element.
    void pop()
        {
            if(!isEmpty()) {
                if (headNode == tailNode) {
                    delete headNode;
                    headNode = tailNode = 0;

                } else {
                    Node<T> *temp = tailNode->previews;
                    delete tailNode;
                    tailNode = temp;
                    tailNode->next = 0;
                }
            }
        }

    //Remove all elements from the list.
    void clear()
        {
            for (Node<T> *tmp; headNode != 0; )
            {
                tmp = headNode;
                headNode = headNode->next;
                delete tmp;
            }
            headNode = tailNode = 0;
        }

    //Return true if you find a node whose data equals the specified element, false otherwise.
    bool contains(T element) const
        {
            Node<T> *tmp;
            for (tmp = headNode; tmp != 0; tmp = tmp->next) {
                if (tmp->info == element)
                    return true;
            }
            return false;
        }

    /*
     * Remove the first node you find whose data equals the specified element.
     * Be sure to update the pointers appropriately. Test your code for the following scenarios:
        l If you remove the first node from the list
        l If you remove a node from the middle of the list
        l If you remove the last node from the list
        l If you remove the only node from the list
     */
    void remove(T element)
        {
            if(contains(element))
            {
                if(headNode == tailNode) headNode = tailNode =0;
                else
                {
                    Node<T> *tmp, *found, *preFound;
                    for (tmp = headNode; tmp != 0; tmp = tmp->next)
                    {
                        if (tmp->info == element)
                        {
                            found = tmp;
                            preFound = tmp->previews;
                        }
                    }
                    if(found == headNode)
                    {
                        dequeue();
                    }
                    else if(found == tailNode)
                    {
                        pop();
                    }
                    else
                    {
                        preFound->next = found->next;
                        found->next->previews = preFound;
                        delete found;
                    }
                }
            }
        }

    ~LinkedList(){clear();}
};


#endif //LINKEDLIST_H
