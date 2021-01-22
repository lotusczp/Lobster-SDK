/***********************************************************************
**  LTree.h - Steve Cai
**  Copyright (C) 2014 by The Trane Company
**  All Rights Reserved
**
**  LTree class gives a implementation of tree data structure
**
**  This file is part of the Lobster project.
**
************************************************************************/

#ifndef LTREE_H
#define LTREE_H

template <class T>
class LTree
{
private:
    //! node class forward declaration
    class Node;

public:
    //! const iterator forward declaration
    class ConstIterator;
    //! mutable iterator forward declaration
    class Iterator;

    //! constructor
    LTree(const T& a_rRootValue) {m_pRoot = new Node(a_rRootValue);}

    //! destructor
    ~LTree() {Iterator iterator(*this); iterator.moveToRoot(); iterator.remove();}

    //! return the entire tree for const iterator
    //! this is equal to subTree when current pointer is to the root node
    ConstIterator constRoot() {return ConstIterator(m_pRoot);}

    //! return a const iterator of the subtree whose root is current node
    ConstIterator constSubTree(const Iterator& a_rIterator) {return ConstIterator(a_rIterator.m_pMutableCurrentNode);}



    friend class Iterator;

    class Iterator
    {
        friend class LTree;
    public:
        //! create a mutable iterator of the whole tree
        Iterator(LTree& a_rTree) {m_pMutableRootNode = a_rTree.m_pRoot; m_pMutableCurrentNode = a_rTree.m_pRoot;}

        //! create a mutable iterator of s subtree
        Iterator(Iterator& a_rIterator) {m_pMutableRootNode = a_rIterator.m_pMutableCurrentNode; m_pMutableCurrentNode = m_pMutableRootNode;}

        //! set the value to the current node
        void setValue(const T& a_rNodeValue) {m_pMutableCurrentNode->m_NodeValue = a_rNodeValue;}

        //! get the value of current node
        const T& getValue() const {return m_pMutableCurrentNode->m_NodeValue;}

        //! remove the current node
        //! if current node is the root of a subtree, this subtree will be deleted as well
        //! The current node will move to previous sibling
        //! if previous sibling not exist, will move to parent
        void remove()
        {
            if (m_pMutableCurrentNode->pLeftChild) {
                // has child
                removeChildrenOf(m_pMutableCurrentNode);
                remove();
            }
            else {
                // has no child
                Node *pTmpNode = m_pMutableCurrentNode;
                if (m_pMutableCurrentNode->pParent) { // not root node
                    if (m_pMutableCurrentNode == m_pMutableCurrentNode->pParent->pLeftChild) {// current node is the first child
                        m_pMutableCurrentNode->pParent->pLeftChild = m_pMutableCurrentNode->pRightSibling;
                        m_pMutableCurrentNode = m_pMutableCurrentNode->pParent;
                    }
                    else {// current node is not the first child
                        Node *pTmpSibling = m_pMutableCurrentNode->pParent->pLeftChild;
                        while (pTmpSibling->pRightSibling != m_pMutableCurrentNode) {
                            pTmpSibling = pTmpSibling->pRightSibling;
                        }
                        pTmpSibling->pRightSibling = m_pMutableCurrentNode->pRightSibling;
                        m_pMutableCurrentNode = pTmpSibling;
                    }
                }
                delete pTmpNode, pTmpNode = NULL;
            }
        }

        //! remove all the children of current node
        //! if the current node has no children, this function will do nothing
        //! please use it together with hasChild()
        void removeChildren() {if(m_pMutableCurrentNode->pLeftChild) removeChildrenOf(m_pMutableCurrentNode);}

        //! return whether the current node has child
        bool hasChild() const {return m_pMutableCurrentNode->pLeftChild != NULL;}

        //! add a child node to the current pointed node
        //! this will not change the current node pointer
        void appendChild(const T& a_rChildValue)
        {
            if(m_pMutableCurrentNode->pLeftChild) {
                //already has child
                Node* pNode = m_pMutableCurrentNode->pLeftChild;
                while(pNode->pRightSibling) {
                    pNode = pNode->pRightSibling;
                }
                pNode->pRightSibling = new Node(a_rChildValue);
                pNode->pRightSibling->pParent = m_pMutableCurrentNode;
            }
            else {
                // has no child yet
                m_pMutableCurrentNode->pLeftChild = new Node(a_rChildValue);
                m_pMutableCurrentNode->pLeftChild->pParent = m_pMutableCurrentNode;
            }
        }

        //! add a child node to the current pointed node
        //! this will change the current node pointer to the newly added child
        void addChild(const T& a_rChildValue)
        {
            if(m_pMutableCurrentNode->pLeftChild) {
                //already has child
                Node* pNode = m_pMutableCurrentNode->pLeftChild;
                while(pNode->pRightSibling) {
                    pNode = pNode->pRightSibling;
                }
                pNode->pRightSibling = new Node(a_rChildValue);
                pNode->pRightSibling->pParent = m_pMutableCurrentNode;
                m_pMutableCurrentNode = pNode->pRightSibling;
            }
            else {
                // has no child yet
                m_pMutableCurrentNode->pLeftChild = new Node(a_rChildValue);
                m_pMutableCurrentNode->pLeftChild->pParent = m_pMutableCurrentNode;
                m_pMutableCurrentNode = m_pMutableCurrentNode->pLeftChild;
            }
        }

        //! return the value of first child
        //! calling this function will change the current pointor to first child node
        //! if the current node has no child, the value will be of current node itself
        //! So please use it together with hasChild()
        const T& moveToFirstChild() {if(m_pMutableCurrentNode->pLeftChild)m_pMutableCurrentNode = m_pMutableCurrentNode->pLeftChild; return m_pMutableCurrentNode->m_NodeValue;}

        //! return the value of first child
        //! calling this function will not change the current pointor
        //! if the current node has no child, the value will be of current node itself
        //! So please use it together with hasChild()
        const T& peekFirstChild() const {if(m_pMutableCurrentNode->pLeftChild) return m_pMutableCurrentNode->pLeftChild->m_NodeValue; else return m_pMutableCurrentNode->m_NodeValue;}

        //! check whether the current node is parent's first child, which mean it has no previous sibling
        bool isFirstChild() const {return m_pMutableCurrentNode->pParent->pLeftChild == m_pMutableCurrentNode;}

        //! return whether the current node has sibling
        bool hasSibling() const {return m_pMutableCurrentNode->pRightSibling != NULL;}

        //! number of sibling of current node, this number includes current node itself
        unsigned int siblingNumber() const
        {
            unsigned int num = 1;
            if (m_pMutableCurrentNode != m_pMutableRootNode) {
                Node *pNode = m_pMutableCurrentNode->pParent->pLeftChild;
                while(pNode->pRightSibling){
                    pNode = pNode->pRightSibling;
                    num++;
                }
            }
            return num;
        }

        //! Change the current node pointer to the next sibling and return its value
        //! If the current node has no next sibling, this function will return the value of current node
        //! So please use it together with hasSibling()
        const T& moveToNextSibling() {if(m_pMutableCurrentNode->pRightSibling)m_pMutableCurrentNode = m_pMutableCurrentNode->pRightSibling; return m_pMutableCurrentNode->m_NodeValue;}

        //! Return the value of next sibling, this function will not change the current node pointer
        //! if the current node has no next sibling, this function will return the value of current node
        //! so please use it together with hasSibling()
        const T& peekNextSibling() const {if(m_pMutableCurrentNode->pRightSibling)return m_pMutableCurrentNode->pRightSibling->m_NodeValue; else return m_pMutableCurrentNode->m_NodeValue;}

        //! Change the current node pointer to the previous sibling and return its value
        //! If the current node has no previous sibling, which means it's the first child, this function will return the value of current node
        //! So please use it together with isFirstChild()
        //! Because the siblings are stored in a singly-linked list, this function will search the whole sibling list untill find the previous sibling
        //! It may need a lot of time if the sibling number is big and current node is at the tail part of list
        //! So call this function if necessary
        const T& moveToPreviousSibling()
        {
            if (m_pMutableCurrentNode->pParent->pLeftChild != m_pMutableCurrentNode) {
                Node* pTmpNode = m_pMutableCurrentNode->pParent->pLeftChild;
                while(pTmpNode->pRightSibling != m_pMutableCurrentNode)
                    pTmpNode = pTmpNode->pRightSibling;
                m_pMutableCurrentNode = pTmpNode;
            }
            return m_pMutableCurrentNode->m_NodeValue;
        }

        //! return the value of next sibling, this function will not change the current node pointer
        //! if the current node has no previous sibling, which means it's the first child, this function will return the value of current node
        //! so please use it together with isFirstChild()
        //! Because the siblings are stored in a singly-linked list, this function will search the whole sibling list untill find the previous sibling
        //! It may need a lot of time if the sibling number is big and current node is at the tail part of list
        //! So call this function if necessary
        const T& peekPreviousSibling() const
        {
            Node* pTmpNode = m_pMutableCurrentNode->pParent->pLeftChild;
            if (m_pMutableCurrentNode->pParent->pLeftChild != m_pMutableCurrentNode) {
                while(pTmpNode->pRightSibling != m_pMutableCurrentNode)
                    pTmpNode = pTmpNode->pRightSibling;
            }
            return pTmpNode->m_NodeValue;
        }

        //! Insert a sibling node next to the current pointed node
        //! Calling this function will change the current node pointer to the sibling just inserted
        //! If the current node is root node, this function will do nothing
        //! So please use it together with isRoot()
        void insertSibling(const T& a_rSiblingValue)
        {
            if (m_pMutableCurrentNode != m_pMutableRootNode) {
                if(m_pMutableCurrentNode->pRightSibling == NULL) {
                    m_pMutableCurrentNode->pRightSibling = new Node(a_rSiblingValue);
                    m_pMutableCurrentNode->pRightSibling->pParent = m_pMutableCurrentNode->pParent;
                }
                else {
                    Node* pTmpNode = m_pMutableCurrentNode->pRightSibling;
                    m_pMutableCurrentNode->pRightSibling = new Node(a_rSiblingValue);
                    m_pMutableCurrentNode->pRightSibling->pRightSibling = pTmpNode;
                    m_pMutableCurrentNode->pRightSibling->pParent = m_pMutableCurrentNode->pParent;
                }
                m_pMutableCurrentNode = m_pMutableCurrentNode->pRightSibling;
            }
        }

        //! Return whether the current node is root node
        bool isRoot() const {return m_pMutableCurrentNode == m_pMutableRootNode;}

        //! Move the current pointor to root node and return the value of root
        const T& moveToRoot() {m_pMutableCurrentNode = m_pMutableRootNode; return m_pMutableCurrentNode->m_NodeValue;}

        //! Return the value of root node
        const T& peekRoot() const {return m_pMutableRootNode->m_NodeValue;}

        //! Move the current node pointer to the parent and return the value of parent
        //! If the current node has no parent, which implys it's root, the value will be of current node itself
        //! So please use it together with isRoot()
        const T& moveToParent() {if(m_pMutableCurrentNode->pParent)m_pMutableCurrentNode = m_pMutableCurrentNode->pParent; return m_pMutableCurrentNode->m_NodeValue;}

        //! Return the value of parent
        //! Will not move the current node pointer to the parent
        //! If the current node has no parent, which implys it's root, the value will be of current node itself
        //! So please use it together with isRoot()
        const T& peekParent() const {if(m_pMutableCurrentNode->pParent)return m_pMutableCurrentNode->pParent->m_NodeValue; else return m_pMutableCurrentNode->m_NodeValue;}

        //! en empty constructor
        Iterator(){m_pMutableCurrentNode = NULL; m_pMutableRootNode = NULL;}

    private:
        //! remove all the children of the given node
        //! please make sure the given node has at least one child before calling this function
        void removeChildrenOf(Node* a_pNode)
        {
            Node *pNode = a_pNode->pLeftChild;
            Node *pTmpNode = NULL;
            while (pNode) {
                if (pNode->pLeftChild) {
                    removeChildrenOf(pNode);
                }

                pTmpNode = pNode;
                if (pTmpNode->pRightSibling) {
                    pTmpNode->pParent->pLeftChild = pTmpNode->pRightSibling;
                }
                else {
                    pTmpNode->pParent->pLeftChild = NULL;
                }

                pNode = pNode->pRightSibling;
                if(pTmpNode) {
                    delete pTmpNode, pTmpNode = NULL;
                }
            }
            a_pNode->pLeftChild = NULL;
        }

    private:
        Node* m_pMutableCurrentNode;   //!< current node pointer

        Node* m_pMutableRootNode;      //!< root node pointer

    };


    class ConstIterator
    {
    public:
        ConstIterator(Node* a_pRootNode) {m_pRootNode = a_pRootNode; m_pCurrentNode = m_pRootNode;}

        //! \note there is no need of destructor here because the nodes will be deleted by Tree

        //! get the value of current node
        const T& getValue() const {return m_pCurrentNode->m_NodeValue;}

        //! return whether the current node has child
        bool hasChild() const {return m_pCurrentNode->pLeftChild != NULL;}

        //! return the value of first child
        //! calling this function will change the current pointor to first child node
        //! if the current node has no child, the value will be of current node itself
        //! So please use it together with hasChild()
        const T& moveToFirstChild() {if(m_pCurrentNode->pLeftChild)m_pCurrentNode = m_pCurrentNode->pLeftChild; return m_pCurrentNode->m_NodeValue;}

        //! return the value of first child
        //! calling this function will not change the current pointor
        //! if the current node has no child, the value will be of current node itself
        //! So please use it together with hasChild()
        const T& peekFirstChild() const {if(m_pCurrentNode->pLeftChild) return m_pCurrentNode->pLeftChild->m_NodeValue; else return m_pCurrentNode->m_NodeValue;}

        //! return whether the current node has sibling
        bool hasSibling() const {return m_pCurrentNode->pRightSibling != NULL;}

        //! number of sibling of current node, this number includes current node itself
        unsigned int siblingNumber() const
        {
            unsigned int num = 1;
            if (m_pCurrentNode != m_pRootNode) {
                Node *pNode = m_pCurrentNode->pParent->pLeftChild;
                while(pNode->pRightSibling){
                    pNode = pNode->pRightSibling;
                    num++;
                }
            }
            return num;
        }

        //! change the current node pointer to the next sibling
        //! if the current node has no sibling, the value will be of current node itself
        //! So please use it together with hasSibling()
        const T& moveToNextSibling() {if(m_pCurrentNode->pRightSibling)m_pCurrentNode = m_pCurrentNode->pRightSibling; return m_pCurrentNode->m_NodeValue;}

        //! Return the value of next sibling, this function will not change the current node pointer
        //! if the current node has no next sibling, this function will return the value of current node
        //! so please use it together with hasSibling()
        const T& peekNextSibling() const {if(m_pCurrentNode->pRightSibling)return m_pCurrentNode->pRightSibling->m_NodeValue; else return m_pCurrentNode->m_NodeValue;}

        //! Change the current node pointer to the previous sibling and return its value
        //! If the current node has no previous sibling, which means it's the first child, this function will return the value of current node
        //! So please use it together with isFirstChild()
        //! Because the siblings are stored in a singly-linked list, this function will search the whole sibling list untill find the previous sibling
        //! It may need a lot of time if the sibling number is big and current node is at the tail part of list
        //! So call this function if necessary
        const T& moveToPreviousSibling()
        {
            if (m_pCurrentNode->pParent->pLeftChild != m_pCurrentNode) {
                Node* pTmpNode = m_pCurrentNode->pParent->pLeftChild;
                while(pTmpNode->pRightSibling != m_pCurrentNode)
                    pTmpNode = pTmpNode->pRightSibling;
                m_pCurrentNode = pTmpNode;
            }
            return m_pCurrentNode->m_NodeValue;
        }

        //! return the value of next sibling, this function will not change the current node pointer
        //! if the current node has no previous sibling, which means it's the first child, this function will return the value of current node
        //! so please use it together with isFirstChild()
        //! Because the siblings are stored in a singly-linked list, this function will search the whole sibling list untill find the previous sibling
        //! It may need a lot of time if the sibling number is big and current node is at the tail part of list
        //! So call this function if necessary
        const T& peekPreviousSibling() const
        {
            Node* pTmpNode = m_pCurrentNode->pParent->pLeftChild;
            if (m_pCurrentNode->pParent->pLeftChild != m_pCurrentNode) {
                while(pTmpNode->pRightSibling != m_pCurrentNode)
                    pTmpNode = pTmpNode->pRightSibling;
            }
            return pTmpNode->m_NodeValue;
        }

        //! return whether the current node is root node
        bool isRoot() const {return m_pCurrentNode == m_pRootNode;}

        //! Move the current pointor to root node and return the value of root
        const T& moveToRoot() {m_pCurrentNode = m_pRootNode; return m_pCurrentNode->m_NodeValue;}

        //! Return the value of root node
        const T& peekRoot() const {return m_pRootNode->m_NodeValue;}

        //! Move the current node pointer to the parent and return the value of parent
        //! If the current node has no parent, which implys it's root, the value will be of current node itself
        //! So please use it together with isRoot()
        const T& moveToParent() {if(m_pCurrentNode->pParent)m_pCurrentNode = m_pCurrentNode->pParent; return m_pCurrentNode->m_NodeValue;}

        //! Return the value of parent
        //! Will not move the current node pointer to the parent
        //! If the current node has no parent, which implys it's root, the value will be of current node itself
        //! So please use it together with isRoot()
        const T& peekParent() const {if(m_pCurrentNode->pParent)return m_pCurrentNode->pParent->m_NodeValue; else return m_pCurrentNode->m_NodeValue;}

    private:
        ConstIterator() {}

        const Node* m_pCurrentNode;   //!< current node pointer

        const Node* m_pRootNode;      //!< root node pointer
    };


private:
    LTree(){}

private:
    class Node
    {
    public:
        Node(T a_NodeValue){m_NodeValue = a_NodeValue; pParent = NULL; pLeftChild = NULL; pRightSibling = NULL;}

        T m_NodeValue;

        Node* pParent; //!< parent

        Node* pLeftChild; //!< left-child

        Node* pRightSibling; //!< right-sibling

    private:
        Node(){}
    };

private:
    Node* m_pRoot;      //!< root node pointer

};


#endif // LTREE_H
