/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

// Write your code below this line

ExprTreeNode::ExprTreeNode()
{
    this->type = "UnDef";
    this->left = NULL;
    this->right = NULL;
    this->num = NULL;
    this->id = "";
}

ExprTreeNode::ExprTreeNode(string t, int v)
{
    type = t;
    num = v;
}

ExprTreeNode::~ExprTreeNode()
{
    this->type = "UnDef";
    this->left = NULL;
    this->right = NULL;
    this->num = NULL;
    this->id = "";
}
