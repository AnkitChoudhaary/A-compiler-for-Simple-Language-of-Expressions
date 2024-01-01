/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

// Write your code below this line

SymNode::SymNode()
{
    key = "";
    height = -1;
    right = NULL;
    left = NULL;
    par = NULL;
}

SymNode::SymNode(string k)
{
    key = k;
    right = NULL;
    left = NULL;
    par = NULL;
    height = 0;
}

SymNode *SymNode::LeftLeftRotation()
{
    SymNode *temp = this->right;
    this->right = this->right->left;
    temp->left = this;
    this->par = temp;
    if (this->right)
    {
        this->right->par = this;
    }
    if (this->left && this->right)
    {
        this->height = max(this->left->height, this->right->height) + 1;
    }
    else if (this->right)
    {
        this->height = this->right->height + 1;
    }
    else if (this->left)
    {
        this->height = this->left->height + 1;
    }
    else
    {
        this->height = 0;
    }
    if (temp->right)
    {
        temp->height = max(temp->left->height, temp->right->height) + 1;
    }
    else
    {
        temp->height = temp->left->height + 1;
    }
    return temp;
}

SymNode *SymNode::RightRightRotation()
{
    SymNode *temp = this->left;
    this->left = this->left->right;
    temp->right = this;
    this->par = temp;
    if (this->left)
        this->left->par = this;
    if (this->left && this->right)
    {
        this->height = max(this->left->height, this->right->height) + 1;
    }
    else if (this->right)
    {
        this->height = this->right->height + 1;
    }
    else if (this->left)
    {
        this->height = this->left->height + 1;
    }
    else
    {
        this->height = 0;
    }
    if (temp->left)
    {
        temp->height = max(temp->left->height, temp->right->height) + 1;
    }
    else
    {
        temp->height = temp->right->height + 1;
    }
    return temp;
}

SymNode *SymNode::LeftRightRotation()
{
    this->right = this->right->RightRightRotation();
    this->right->par = this;
    return this->LeftLeftRotation();
}

SymNode *SymNode::RightLeftRotation()
{
    this->left = this->left->LeftLeftRotation();
    this->left->par = this;
    return this->RightRightRotation();
}

SymNode::~SymNode()
{
    if (this)
    {
        key = "";
        height = -1;
        address = -1;
        left = NULL;
        right = NULL;
        par = NULL;
    }
}