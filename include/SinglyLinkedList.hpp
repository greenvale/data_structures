

namespace datastructlib
{
    // SINGLE LINKED NODE HEADER
    
    template <class T> 
    class SingleNode
    {
    private:
        T m_value;
        SingleNode* m_nextPtr;
    public:
        SingleNode();
        SingleNode(const T& value);
        SingleNode(SingleNode* nextPtr);
        SingleNode(const T& value, SingleNode* nextPtr);      
        
        T getValue() const;
        void setValue(const T& value);
        
        SingleNode* getNextPtr() const;
        void setNextPtr(SingleNode* nextPtr);
    };
    
    // SINGLE LINKED LIST HEADER
    
    template <class T>
    class SinglyLinkedList
    {
    private:
        SingleNode<T>* m_headPtr;
        SingleNode<T>* m_tailPtr;
        unsigned int m_length;
    public:
        SinglyLinkedList();
        SinglyLinkedList(SingleNode<T>* headPtr, SingleNode<T>* tailPtr);
        
        SingleNode<T>* getHeadPtr() const;
        SingleNode<T>* getTailPtr() const;
        SingleNode<T>* getPtr(const unsigned int& index);
        unsigned int getLength();
        
        void insertHead(SingleNode<T>* nodePtr);
        void insertTail(SingleNode<T>* nodePtr);
        void insert(const unsigned int& index, SingleNode<T>* nodePtr);
        
        void removeHead();
        void removeTail();
        void remove(const unsigned int& index);
        void clear();
    };
    
    // =============================================================================
    // =============================================================================
    // =============================================================================
    // SINGLE LINKED NODE FUNCTIONS
    
    template <class T>
    SingleNode<T>::SingleNode()
    {
    }
    
    template <class T>
    SingleNode<T>::SingleNode(const T& value)
    {
        m_value = value;
    }
    
    template <class T>
    SingleNode<T>::SingleNode(SingleNode* nextPtr)
    {
        m_nextPtr = nextPtr;
    }
    
    template <class T>
    SingleNode<T>::SingleNode(const T& value, SingleNode* nextPtr)
    {
        m_value = value;
        m_nextPtr = nextPtr;
    }
    
    template <class T>
    T SingleNode<T>::getValue() const { return m_value; }
    
    template <class T>
    void SingleNode<T>::setValue(const T& value) { m_value = value; } 
        
    template <class T>
    SingleNode<T>* SingleNode<T>::getNextPtr() const { return m_nextPtr; }
    
    template <class T>
    void SingleNode<T>::setNextPtr(SingleNode* nextPtr) { m_nextPtr = nextPtr; }
    
    // =============================================================================
    // =============================================================================
    // =============================================================================
    // SINGLE LINKED LIST FUNCTIONS
    
    template <class T>
    SinglyLinkedList<T>::SinglyLinkedList()
    {
        m_headPtr = nullptr;
        m_tailPtr = nullptr;
        m_length = 0;
    }
    
    template <class T>
    SinglyLinkedList<T>::SinglyLinkedList(SingleNode<T>* headPtr, SingleNode<T>* tailPtr)
    {
        m_headPtr = headPtr;
        m_tailPtr = tailPtr;
        m_headPtr->setNextPtr(m_tailPtr);
        m_tailPtr->setNextPtr(nullptr);
        m_length = 2;
    }
    
    // =============================================================================
    
    template <class T>
    SingleNode<T>* SinglyLinkedList<T>::getHeadPtr() const
    {
        return m_headPtr;
    }
    
    template <class T>
    SingleNode<T>* SinglyLinkedList<T>::getTailPtr() const
    {
        return m_tailPtr;
    }
    
    template <class T>
    SingleNode<T>* SinglyLinkedList<T>::getPtr(const unsigned int& index)
    {
        assert((index >= 0) && (index < m_length)); // do not use with head or tail
        
        SingleNode<T>* travPtr = m_headPtr; // initialise traverse pointer
        SingleNode<T>* travNextPtr;
        
        unsigned int dist = 0;
        while (dist < index)
        {
            travNextPtr = travPtr->getNextPtr();
            assert(travNextPtr != nullptr); // should not encounter null ptr
            
            travPtr = travNextPtr; // traverse to next ptr
            dist++;
        }
        
        return travPtr;
    }
    
    template <class T>
    unsigned int SinglyLinkedList<T>::getLength() 
    { 
        return m_length; 
    }
    
    // =============================================================================
    
    template <class T>
    void SinglyLinkedList<T>::insertHead(SingleNode<T>* nodePtr)
    {
        if (m_length == 0)
        {
            // for empty list also set to tail ptr
            m_tailPtr = nodePtr;
            nodePtr->setNextPtr(nullptr);
        }
        else
        {
            nodePtr->setNextPtr(m_headPtr);
        }
        m_headPtr = nodePtr;
        m_length++;
    }
    
    template <class T>
    void SinglyLinkedList<T>::insertTail(SingleNode<T>* nodePtr)
    {
        if (m_length == 0)
        {
            // for empty list also set to head ptr
            m_headPtr = nodePtr;
        }
        else
        {
            m_tailPtr->setNextPtr(nodePtr);
        }
        m_tailPtr = nodePtr;
        nodePtr->setNextPtr(nullptr);
        m_length++;
    }
    
    template <class T>
    void SinglyLinkedList<T>::insert(const unsigned int& index, SingleNode<T>* nodePtr)
    {
        assert(m_length > 2);
        assert((index > 0) && (index < m_length));
        
        SingleNode<T>* prevPtr = getPtr(index - 1);
        
        nodePtr->setNextPtr(prevPtr->getNextPtr());
        prevPtr->setNextPtr(nodePtr);
        m_length++;
    }
    
    // =============================================================================
    
    template <class T>
    void SinglyLinkedList<T>::removeHead()
    {
        assert(m_length > 0);
        
        if (m_length == 1)
        {
            m_headPtr = nullptr; // no more elements in list
            m_tailPtr = nullptr;
        }
        else if (m_length == 2)
        {
            m_headPtr = m_tailPtr; // set head to be current tail - forget old head
        }
        else
        {
            m_headPtr = m_headPtr->getNextPtr(); // set head to be next ptr from old head
        }
        m_length--;
    }
    
    template <class T>
    void SinglyLinkedList<T>::removeTail()
    {
        assert(m_length > 0);
        
        if (m_length == 1)
        {
            m_headPtr = nullptr; // no more elements in list
            m_tailPtr = nullptr;
        }
        else if (m_length == 2)
        {
            m_tailPtr = m_headPtr; // set tail to be current head - forget old tail
            m_headPtr->setNextPtr(nullptr);
        }
        else
        {
            SingleNode<T>* prevNode = getPtr(m_length - 2); // get node before tail - make this tail
            prevNode->setNextPtr(nullptr);
            m_tailPtr = prevNode;
        }
        m_length--;
    }
    
    template <class T>
    void SinglyLinkedList<T>::remove(const unsigned int& index)
    {
        assert(m_length > 2);
        assert((index > 0) && (index < m_length));
        
        SingleNode<T>* prevNode = getPtr(index - 1);
        SingleNode<T>* thisNode = prevNode->getNextPtr();
        prevNode->setNextPtr(thisNode->getNextPtr());
        m_length--;
    }
    
    template <class T>
    void SinglyLinkedList<T>::clear()
    {
        unsigned int length = m_length;
        for (int i = 0; i < length; ++i) 
        {
            removeHead();
        }
    }
}
