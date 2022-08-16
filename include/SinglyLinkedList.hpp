

namespace datastructlib
{
    // SINGLE LINKED NODE HEADER
    
    template <class T> 
    class SingNode
    {
    private:
        T m_value;
        SingNode* m_nextPtr;
    public:
        SingNode();
        SingNode(const T& value);
        SingNode(SingNode* nextPtr);
        SingNode(const T& value, SingNode* nextPtr);      
        
        T getValue() const;
        void setValue(const T& value);
        
        SingNode* getNextPtr() const;
        void setNextPtr(SingNode* nextPtr);
    };
    
    // SINGLE LINKED LIST HEADER
    
    template <class T>
    class SingLinkList
    {
    private:
        SingNode<T>* m_headPtr;
        SingNode<T>* m_tailPtr;
        SingNode<T>* m_travPtr;
        unsigned int m_length;
    public:
        SingLinkList();
        SingLinkList(SingNode<T>* headPtr, SingNode<T>* tailPtr);
        
        SingNode<T>* getHeadPtr() const;
        SingNode<T>* getTailPtr() const;
        SingNode<T>* getPtr(const unsigned int& index);
        
        T getHeadValue() const;
        T getTailValue() const;
        T getValue(const unsigned int& index);
        
        void insertHead(SingNode<T>* nodePtr);
        void insertTail(SingNode<T>* nodePtr);
        void insert(const unsigned int& index, SingNode<T>* nodePtr);
        
        void removeHead();
        void removeTail();
        void remove(const unsigned int& index);
    public:
        bool fwdStepTravPtr();
        bool fwdWalkTravPtr(const unsigned int& dist);
    };
    
    // =============================================================================
    // =============================================================================
    // =============================================================================
    // SINGLE LINKED NODE FUNCTIONS
    
    template <class T>
    SingNode<T>::SingNode()
    {
    }
    
    template <class T>
    SingNode<T>::SingNode(const T& value)
    {
        m_value = value;
    }
    
    template <class T>
    SingNode<T>::SingNode(SingNode* nextPtr)
    {
        m_nextPtr = nextPtr;
    }
    
    template <class T>
    SingNode<T>::SingNode(const T& value, SingNode* nextPtr)
    {
        m_value = value;
        m_nextPtr = nextPtr;
    }
    
    template <class T>
    T SingNode<T>::getValue() const { return m_value; }
    
    template <class T>
    void SingNode<T>::setValue(const T& value) { m_value = value; } 
        
    template <class T>
    SingNode<T>* SingNode<T>::getNextPtr() const { return m_nextPtr; }
    
    template <class T>
    void SingNode<T>::setNextPtr(SingNode* nextPtr) { m_nextPtr = nextPtr; }
    
    // =============================================================================
    // =============================================================================
    // =============================================================================
    // LINKED LIST FUNCTIONS
    
    template <class T>
    SingLinkList<T>::SingLinkList()
    {
        m_headPtr = nullptr;
        m_tailPtr = nullptr;
        m_length = 0;
    }
    
    template <class T>
    SingLinkList<T>::SingLinkList(SingNode<T>* headPtr, SingNode<T>* tailPtr)
    {
        m_headPtr = headPtr;
        m_tailPtr = tailPtr;
        m_length = 2;
    }
    
    // =============================================================================
    
    template <class T>
    SingNode<T>* SingLinkList<T>::getHeadPtr() const
    {
        return m_headPtr;
    }
    
    template <class T>
    SingNode<T>* SingLinkList<T>::getTailPtr() const
    {
        return m_tailPtr;
    }
    
    template <class T>
    SingNode<T>* SingLinkList<T>::getPtr(const unsigned int& index)
    {
        assert((index >= 0) && (index < m_length));
        
        m_travPtr = m_headPtr;
        bool err = fwdWalkTravPtr(index);
        
        return m_travPtr;
    }
    
    // =============================================================================
    
    template <class T>
    T SingLinkList<T>::getHeadValue() const
    {
        return m_headPtr->getValue();
    }
    
    template <class T>
    T SingLinkList<T>::getTailValue() const
    {
        return m_tailPtr->getValue();
    }
    
    template <class T>
    T SingLinkList<T>::getValue(const unsigned int& index)
    {
        SingNode<T>* nodePtr = getPtr(index);
        return nodePtr->getValue();
    }
    
    // =============================================================================
    
    template <class T>
    void SingLinkList<T>::insertHead(SingNode<T>* nodePtr)
    {
        if (m_length > 0)
        {
            nodePtr->setNextPtr(m_headPtr);
        }
        else
        {
            m_tailPtr = nodePtr;
            nodePtr->setNextPtr(nullptr);
        }
        m_headPtr = nodePtr;
        m_length++;
    }
    
    template <class T>
    void SingLinkList<T>::insertTail(SingNode<T>* nodePtr)
    {
        if (m_length > 0)
        {
            m_tailPtr->setNextPtr(nodePtr);
        }
        else
        {
            m_headPtr = nodePtr;
        }
        m_tailPtr = nodePtr;
        nodePtr->setNextPtr(nullptr);
        m_length++;
    }
    
    template <class T>
    void SingLinkList<T>::insert(const unsigned int& index, SingNode<T>* nodePtr)
    {
        assert(m_length > 2);
        assert((index > 0) && (index < m_length));
        
        SingNode<T>* prevPtr = getPtr(index - 1);
        
        nodePtr->setNextPtr(prevPtr->getNextPtr());
        prevPtr->setNextPtr(nodePtr);
        m_length++;
    }
    
    // =============================================================================
    
    template <class T>
    void SingLinkList<T>::removeHead()
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
    void SingLinkList<T>::removeTail()
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
            SingNode<T>* prevNode = getPtr(m_length - 2); // get node before tail - make this tail
            prevNode->setNextPtr(nullptr);
            m_tailPtr = prevNode;
        }
        m_length--;
    }
    
    template <class T>
    void SingLinkList<T>::remove(const unsigned int& index)
    {
        assert(m_length > 2);
        assert((index > 0) && (index < m_length));
        
        SingNode<T>* prevNode = getPtr(index - 1);
        SingNode<T>* thisNode = prevNode->getNextPtr();
        prevNode->setNextPtr(thisNode->getNextPtr());
        m_length--;
    }
    
    // =============================================================================
        
    template <class T>
    bool SingLinkList<T>::fwdWalkTravPtr(const unsigned int& dist)
    {
        unsigned int temp = 0;
        bool flag = true;
        while (temp < dist)
        {
            flag = fwdStepTravPtr(); // forward step traver
            temp++;
            
            if (flag == false)
            {
                return false; // traver has fallen off edge - return false (jump too big)
            }
       }
       return true; // temp == jump (traver made it to destination node)
    }
    
    template <class T>
    bool SingLinkList<T>::fwdStepTravPtr()
    {
        if (m_travPtr->getNextPtr() != nullptr)
        {
            m_travPtr = m_travPtr->getNextPtr();
            return true;
        }
        return false; // current traver ptr is pointed to tail - no next ptr - could not move!
    }
}
