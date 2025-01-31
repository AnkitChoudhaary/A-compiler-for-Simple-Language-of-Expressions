/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

// Write your code below this line

HeapNode::HeapNode()
{
    this->left = NULL;
    this->right = NULL;
    this->par = NULL;
    this->val = -1;
}

HeapNode::HeapNode(int _val)
{
    this->left = NULL;
    this->right = NULL;
    this->par = NULL;
    this->val = _val;
}

HeapNode::~HeapNode()
{
    if (this)
    {
        this->left = NULL;
        this->right = NULL;
        this->par = NULL;
        this->val = -1;
    }
}