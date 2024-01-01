/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
// Write your code below this line
void swap(HeapNode *a, HeapNode *b)
{
    int temp = a->val;
    a->val = b->val;
    b->val = temp;
}
void Heapify_Up(HeapNode *a)
{
    if (a->par)
    {
        if (a->par->val > a->val)
        {
            swap(a, a->par);
        }
        Heapify_Up(a->par);
    }
}
void Heapify_Down(HeapNode *p)
{
    if (p->right && p->left)
    {
        if (p->val > p->left->val || p->val > p->right->val)
        {
            if (p->left->val < p->right->val)
            {
                swap(p, p->left);
                Heapify_Down(p->left);
            }
            else
            {
                swap(p, p->right);
                Heapify_Down(p->right);
            }
        }
    }
    else if (p->left)
    {
        if (p->left->val < p->val)
        {
            swap(p->left, p);
            return;
        }
    }
    else
    {
        return;
    }
}

HeapNode *End(HeapNode *rt, int sz)
{
    HeapNode *res = rt;
    int div = 1;
    int r = sz;
    while (r > 1)
    {
        div *= 2;
        r /= 2;
    }
    r = sz;
    div /= 2;
    while (div != 0)
    {
        if ((r / div) % 2 == 0)
        {

            if (res->left == NULL)
            {
                res->left = new HeapNode();
                res->left->par = res;
            }
            res = res->left;
        }
        else
        {
            if (res->right == NULL)
            {
                res->right = new HeapNode();
                res->right->par = res;
            }
            res = res->right;
        }
        div /= 2;
    }
    return res;
}

void Destructor(HeapNode *rt)
{
    if (rt)
    {
        Destructor(rt->left);
        Destructor(rt->right);
        delete rt;
        rt = NULL;
    }
}

MinHeap::MinHeap()
{
    this->size = 0;
    this->root = NULL;
}

void MinHeap::push_heap(int num)
{
    if (size == 0)
    {
        this->root = new HeapNode(num);
        size++;
        return;
    }
    HeapNode *last = End(this->root, size + 1);
    last->val = num;
    size++;
    Heapify_Up(last);
}

int MinHeap::get_min()
{
    if (root)
    {
        return root->val;
    }
    else
    {
        return -1;
    }
}

void MinHeap::pop()
{
    if (size > 1)
    {
        HeapNode *last = End(root, size);
        this->root->val = last->val;
        if (last->par->left->val == last->val)
        {
            last->par->left = NULL;
            delete last;
        }
        else
        {
            last->par->right = NULL;
            delete last;
        }
        size--;
        Heapify_Down(root);
    }
    else
    {
        delete root;
        this->root = NULL;
        size--;
    }
}

MinHeap::~MinHeap()
{
    this->size = 0;
    Destructor(root);
}