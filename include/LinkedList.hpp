

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
        SingleNode(T* nextPtr);
        SingleNode(const T& value, T* nextPtr);      
        
        T getValue() const;
        void setValue(const T& value);
        
        T* getNextPtr() const;
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
    SingleNode<T>::SingleNode(T* nextPtr)
    {
        m_nextPtr = nextPtr;
    }
    
    template <class T>
    SingleNode<T>::SingleNode(const T& value, T* nextPtr)
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
    T* SingleNode<T>::getNextPtr() const
    {
        return m_nextPtr;
    }
    
    template <class T>
    void SingleNode<T>::setNextPtr(SingleNode* nextPtr) 
    {
        m_nextPtr = nextPtr;
    }
}
