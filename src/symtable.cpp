/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

// Write your code below this line
void Destructor(SymNode *rt)
{
    if (rt)
    {
        Destructor(rt->left);
        Destructor(rt->right);
        delete rt;
        rt = NULL;
    }
}

SymNode *Successor(SymNode *rt)
{
    if (rt == NULL)
    {
        return NULL;
    }
    SymNode *a = rt->right;
    while (a->left)
    {
        a = a->left;
    }
    return a;
}

SymNode *Balance_AVL(SymNode *rt)
{
    if (rt->right && rt->left)
    {
        if ((rt->right->height - rt->left->height) > 1)
        {
            if (rt->right->left && rt->right->right)
            {
                if (rt->right->left->height > rt->right->right->height)
                {
                    return rt->LeftRightRotation();
                }
                else
                {
                    return rt->LeftLeftRotation();
                }
            }
            else if (rt->right->left)
            {
                return rt->LeftRightRotation();
            }
            else
            {
                return rt->LeftLeftRotation();
            }
        }
        else if ((rt->left->height - rt->right->height) > 1)
        {
            if (rt->left->left && rt->left->right)
            {
                if (rt->left->right->height > rt->left->left->height)
                {
                    return rt->RightLeftRotation();
                }
                else
                {
                    return rt->RightRightRotation();
                }
            }
            else if (rt->left->right)
            {
                return rt->RightLeftRotation();
            }
            else
            {
                return rt->RightRightRotation();
            }
        }
        else
        {
            return rt;
        }
    }
    else if ((rt->left))
    {
        if (rt->left->height >= 1)
        {
            if (rt->left->right)
            {
                return rt->RightLeftRotation();
            }
            return rt->RightRightRotation();
        }
        else
        {
            return rt;
        }
    }
    else if ((rt->right))
    {
        if (rt->right->height >= 1)
        {
            if (rt->right->left)
            {
                return rt->LeftRightRotation();
            }
            return rt->LeftLeftRotation();
        }
        else
        {
            return rt;
        }
    }
    else
    {
        return rt;
    }
}

SymNode *Insert_Helper(SymNode *rt, string k)
{
    if (rt)
    {
        if (rt->key < k)
        {
            rt->right = Insert_Helper(rt->right, k);
            rt->right = Balance_AVL(rt->right);
            if (rt->left)
            {
                rt->height = max(rt->left->height, rt->right->height) + 1;
            }
            else
            {
                rt->height = rt->right->height + 1;
            }
            rt->right->par = rt;
            return rt;
        }
        else if (rt->key > k)
        {
            rt->left = Insert_Helper(rt->left, k);
            rt->left = Balance_AVL(rt->left);
            if (rt->right)
            {
                rt->height = max(rt->left->height, rt->right->height) + 1;
            }
            else
            {
                rt->height = rt->left->height + 1;
            }
            rt->left->par = rt;
            return rt;
        }
        else
        {
            return rt;
        }
    }
    else
    {
        return new SymNode(k);
    }
}

SymbolTable::SymbolTable()
{
    this->size = 0;
    this->root = NULL;
}

void SymbolTable::insert(string k)
{
    if (size == 0)
    {
        this->root = new SymNode(k);
        size++;
        return;
    }
    else
    {
        if (root->key > k)
        {
            root->left = Insert_Helper(root->left, k);
            root->left = Balance_AVL(root->left);
            if (root->right)
            {
                root->height = max(root->left->height, root->right->height) + 1;
            }
            else
            {
                root->height = root->left->height + 1;
            }
            root->left->par = root;
            size++;
        }
        else if (root->key < k)
        {
            root->right = Insert_Helper(root->right, k);
            // printf("root->right->key== %s    \n", root->right->key.c_str());
            root->right = Balance_AVL(root->right);
            if (root->left)
            {
                root->height = max(root->left->height, root->right->height) + 1;
            }
            else
            {
                root->height = root->right->height + 1;
            }
            root->right->par = root;
            size++;
        }
        this->root = Balance_AVL(root);
    }
}

void Del_(SymNode *a, string k, bool &z)
{
    if (a)
    {
        if (k > a->key)
        {
            Del_(a->right, k, z);
            if (a->right)
            {
                a->right = Balance_AVL(a->right);
                if (a->left)
                {
                    a->height = max(a->left->height, a->right->height) + 1;
                }
                else
                {
                    a->height = a->right->height + 1;
                }
            }
            else
            {
                if (a->left)
                {
                    a->height = a->left->height + 1;
                }
                else
                {
                    a->height = 1;
                }
            }
        }
        else if (k < a->key)
        {
            Del_(a->left, k, z);
            if (a->left)
            {
                a->left = Balance_AVL(a->left);
                if (a->right)
                {
                    a->height = max(a->left->height, a->right->height) + 1;
                }
                else
                {
                    a->height = a->left->height + 1;
                }
            }
            else
            {
                if (a->right)
                {
                    a->height = a->right->height + 1;
                }
                else
                {
                    a->height = 1;
                }
            }
        }
        else
        {
            if (a->left == NULL && a->right == NULL)
            {
                if (a->par->left != NULL)
                {
                    if (a->par->left->key == k)
                    {
                        a->par->left = NULL;
                        a->par->height = 0;
                        delete a;
                        return;
                    }
                }
                a->par->right = NULL;
                a->par->height = 0;
                delete a;
                return;
            }
            else if (a->left == NULL)
            {
                if (a->par->left->key == a->key)
                {
                    a->par->left = a->right;
                    a->right->par = a->par;
                    a->par->height = max(a->par->left->height, a->par->right->height) + 1;
                    delete a;
                }
                else
                {
                    a->par->right = a->right;
                    a->right->par = a->par;
                    a->par->height = max(a->par->left->height, a->par->right->height) + 1;
                    delete a;
                }
            }
            else if (a->right == NULL)
            {
                if (a->par->left->key == a->key)
                {
                    a->par->left = a->left;
                    a->left->par = a->par;
                    a->par->height = max(a->par->left->height, a->par->right->height) + 1;
                    delete a;
                }
                else
                {
                    a->par->right = a->left;
                    a->left->par = a->par;
                    a->par->height = max(a->par->left->height, a->par->right->height) + 1;
                    delete a;
                }
            }
            else
            {
                SymNode *temp = Successor(a);
                a->key = temp->key;
                a->address = temp->address;
                temp->key = k;
                Del_(a->right, k, z);
                if (a->right)
                {
                    a->right = Balance_AVL(a->right);
                    if (a->left)
                    {
                        a->height = max(a->left->height, a->right->height) + 1;
                    }
                    else
                    {
                        a->height = a->right->height + 1;
                    }
                }
            }
        }
    }
    else
    {
        z = false;
        return;
    }
}

void SymbolTable::remove(string k)
{
    if (!root)
    {
        return;
    }
    // This should be recurcive with Output symnode//   Corrected the issue for deleting root.
    // Del_(root, k);
    SymNode *rt = root;
    if (rt->key == k)
    {
        if (size == 1)
        {
            size--;
            delete rt;
            this->root = NULL;
        }
        else if (rt->left == NULL)
        {
            size--;
            this->root = Balance_AVL(this->root->right);
            this->root->par = NULL;
            delete rt;
        }
        else if (rt->right == NULL)
        {
            size--;
            this->root = rt->left;
            this->root = Balance_AVL(this->root->left);
            this->root->par = NULL;
            delete rt;
        }
        else
        {
            size--;
            bool z = true;
            Del_(rt, k, z);
            this->root = Balance_AVL(this->root);
            return;
        }
    }
    else
    {
        bool z = true;
        Del_(rt, k, z);
        this->root = Balance_AVL(this->root);
        if (z)
            size--;
        return;
    }
}

int SymbolTable::search(string k)
{
    SymNode *tp = this->root;
    while (tp)
    {
        if (tp->key < k)
        {
            tp = tp->right;
        }
        else if (tp->key > k)
        {
            tp = tp->left;
        }
        else
        {
            break;
        }
    }
    if (tp)
    {
        return tp->address;
    }
    else
    {
        return -2;
    }
}

void SymbolTable::assign_address(string k, int idx)
{
    SymNode *tp = this->root;
    while (tp)
    {
        if (tp->key < k)
        {
            tp = tp->right;
        }
        else if (tp->key > k)
        {
            tp = tp->left;
        }
        else
        {
            break;
        }
    }
    if (tp)
    {
        tp->address = idx;
    }
    else
    {
        this->insert(k);
        this->assign_address(k, idx);
    }
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}

SymbolTable::~SymbolTable()
{
    this->size = 0;
    Destructor(root);
}