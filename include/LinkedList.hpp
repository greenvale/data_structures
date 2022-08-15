

namespace DataStructLib
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
    
    // DOUBLE LINKED NODE HEADER
    
    template <class T> 
    class DoubleNode
    {
    private:
        T m_value;
        DoubleNode* m_prevPtr;
        DoubleNode* m_nextPtr;
    public:
        DoubleNode();
        DoubleNode(const T& value);
        DoubleNode(DoubleNode* prevPtr, DoubleNode* nextPtr);
        DoubleNode(const T& value, DoubleNode* prevPtr, DoubleNode* nextPtr);      
        
        T getValue() const;
        void setValue(const T& value);
        
        DoubleNode* getPrevPtr() const;
        DoubleNode* getNextPtr() const;
        void setPrevPtr(DoubleNode* prevPtr);
        void setNextPtr(DoubleNode* nextPtr);
    };
    
    // LINKED LIST
    
    template <class T>
    class SingleLinkList
    {
    private:
        SingleNode<T>* m_headPtr;
        SingleNode<T>* m_tailPtr;
        SingleNode<T>* m_trawlPtr;
        unsigned int m_length;
    public:
        SingleLinkList();
        SingleLinkList(SingleNode<T>* headPtr, SingleNode<T>* tailPtr);
        
        SingleNode<T>* getHeadPtr() const;
        SingleNode<T>* getTailPtr() const;
        SingleNode<T>* getNodePtr(const unsigned int& index);
        
        T getHeadValue() const;
        T getTailValue() const;
        T getNodeValue(const unsigned int& index);
        
        void insertHead(SingleNode<T>* nodePtr);
        bool insertTail(SingleNode<T>* nodePtr);
        bool insertNode(const unsigned int& index, SingleNode<T>* nodePtr);
        
        bool removeHead();
        bool removeTail();
        bool removeNode(const unsigned int& index);
    public:
        bool fwdStepTrawlPtr();
        bool fwdWalkTrawlPtr(const unsigned int& dist);
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
    T SingleNode<T>::getValue() const
    {
        return m_value;
    }
    
    template <class T>
    void SingleNode<T>::setValue(const T& value)
    {
        m_value = value;
    }
    
    template <class T>
    SingleNode<T>* SingleNode<T>::getNextPtr() const
    {
        return m_nextPtr;
    }
    
    template <class T>
    void SingleNode<T>::setNextPtr(SingleNode* nextPtr) 
    {
        m_nextPtr = nextPtr;
    }
    
    // =============================================================================
    // =============================================================================
    // =============================================================================
    // DOUBLE LINKED NODE FUNCTIONS
    
    
    template <class T>
    DoubleNode<T>::DoubleNode()
    {
    }
    
    template <class T>
    DoubleNode<T>::DoubleNode(const T& value)
    {
        m_value = value;
    }
    
    template <class T>
    DoubleNode<T>::DoubleNode(DoubleNode* prevPtr, DoubleNode* nextPtr)
    {
        m_prevPtr = prevPtr;
        m_nextPtr = nextPtr;
    }
    
    template <class T>
    DoubleNode<T>::DoubleNode(const T& value, DoubleNode* prevPtr, DoubleNode* nextPtr)
    {
        m_value = value;
        m_prevPtr = prevPtr;
        m_nextPtr = nextPtr;
    }
    
    template <class T>
    T DoubleNode<T>::getValue() const
    {
        return m_value;
    }
    
    template <class T>
    void DoubleNode<T>::setValue(const T& value)
    {
        m_value = value;
    }
    
    template <class T>
    DoubleNode<T>* DoubleNode<T>::getPrevPtr() const
    {
        return m_prevPtr;
    }
    
    template <class T>
    DoubleNode<T>* DoubleNode<T>::getNextPtr() const
    {
        return m_nextPtr;
    }
    
    template <class T>
    void DoubleNode<T>::setPrevPtr(DoubleNode* prevPtr) 
    {
        m_prevPtr = prevPtr;
    }
    
    template <class T>
    void DoubleNode<T>::setNextPtr(DoubleNode* nextPtr) 
    {
        m_nextPtr = nextPtr;
    }
    
    // =============================================================================
    // =============================================================================
    // =============================================================================
    // LINKED LIST FUNCTIONS
    
    template <class T>
    SingleLinkList<T>::SingleLinkList()
    {
        m_headPtr = nullptr;
        m_tailPtr = nullptr;
        m_length = 0;
    }
    
    template <class T>
    SingleLinkList<T>::SingleLinkList(SingleNode<T>* headPtr, SingleNode<T>* tailPtr)
    {
        m_headPtr = headPtr;
        m_tailPtr = tailPtr;
        m_length = 2;
    }
    
    template <class T>
    SingleNode<T>* SingleLinkList<T>::getHeadPtr() const
    {
        return m_headPtr;
    }
    
    template <class T>
    SingleNode<T>* SingleLinkList<T>::getTailPtr() const
    {
        return m_tailPtr;
    }
    
    template <class T>
    SingleNode<T>* SingleLinkList<T>::getNodePtr(const unsigned int& index)
    {
        m_trawlPtr = m_headPtr;
        bool flag = fwdWalkTrawlPtr(index);
        
        if (flag == true)
        {
            return m_trawlPtr;
        }
        return nullptr;
    }
    
    template <class T>
    void SingleLinkList<T>::insertHead(SingleNode<T>* nodePtr)
    {
        if (m_headPtr != nullptr)
        {
            nodePtr->setNextPtr(m_headPtr); // if head then set next ptr to be old head
        }
        m_headPtr = nodePtr;
        m_length++;
    }
    
    template <class T>
    bool SingleLinkList<T>::insertTail(SingleNode<T>* nodePtr)
    {
        if (m_headPtr != nullptr)
        {
            if (m_tailPtr != nullptr)
            {
                m_tailPtr->setNextPtr(nodePtr); // if tail then set old tail to point to new tail
            }
            nodePtr->setNextPtr(nullptr); // make sure new tail points to nullptr
            m_tailPtr = nodePtr;
            m_length++;
            return true;
        }
        return false;
    }
    
    template <class T>
    bool SingleLinkList<T>::insertNode(const unsigned int& index, SingleNode<T>* nodePtr)
    {
        m_trawlPtr = m_headPtr;
        bool flag = fwdWalkTrawlPtr(index);
        
        if (flag == true)
        {
            // only proceed if not fallen off edge
            if (m_trawlPtr->getNextPtr() != nullptr)
            {
                nodePtr->setNextPtr(m_trawlPtr->getNextPtr()); // if not trawl = tail then connect new node to next node
            }
            m_trawlPtr->setNextPtr(nodePtr);
            m_length++;
        }
        return false;
    }
        
    template <class T>
    bool SingleLinkList<T>::fwdWalkTrawlPtr(const unsigned int& dist)
    {
        unsigned int temp = 0;
        bool flag = true;
        while (temp < dist)
        {
            flag = fwdStepTrawlPtr(); // forward step trawler
            temp++;
            
            if (flag == false) 
            {
                return false; // trawler has fallen off edge - return false (jump too big)
            }
       }
       return true; // temp == jump (trawler made it to destination node)
    }
    
    template <class T>
    bool SingleLinkList<T>::fwdStepTrawlPtr()
    {
        if (m_trawlPtr->getNextPtr() != nullptr)
        {
            m_trawlPtr = m_trawlPtr->getNextPtr();
            return true;
        }
        return false; // current trawler ptr is pointed to tail - no next ptr - could not move!
    }
}
