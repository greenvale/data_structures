

namespace DataStructLib
{

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
    T DoubleNode<T>::getValue() const { return m_value; }
    
    template <class T>
    void DoubleNode<T>::setValue(const T& value) { m_value = value; }
    
    template <class T>
    DoubleNode<T>* DoubleNode<T>::getPrevPtr() const { return m_prevPtr; }
    
    template <class T>
    DoubleNode<T>* DoubleNode<T>::getNextPtr() const { return m_nextPtr; }
    
    template <class T>
    void DoubleNode<T>::setPrevPtr(DoubleNode* prevPtr) { m_prevPtr = prevPtr; }
    
    template <class T>
    void DoubleNode<T>::setNextPtr(DoubleNode* nextPtr) { m_nextPtr = nextPtr; }
    

}
