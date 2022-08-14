

namespace DataStructLib
{
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
}
