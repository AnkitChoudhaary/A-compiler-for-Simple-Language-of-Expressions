/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

// Write your code below this line

ExprTreeNode *parse_Helper(vector<string> cd)
{
    ExprTreeNode *res = new ExprTreeNode();
    vector<ExprTreeNode *> n;
    ExprTreeNode *temp = res;
    for (long i = 0; i < cd.size() - 1; i++)
    {
        if (cd[i] == "(")
        {
            n.push_back(temp);
            temp->left = new ExprTreeNode();
            temp = temp->left; // v := (13 + (2 / 51))
        }
        else if (cd[i] == ")")
        {
            if (n.size() > 0)
            {
                temp = n[n.size() - 1];
                n.pop_back();
            }
            else
            {
                printf("ERROR IN CODE\n");
            }
        }

        else if (cd[i] == "+")
        {
            temp->type = "ADD";
            temp->right = new ExprTreeNode();
            n.push_back(temp);
            temp = temp->right;
        }
        else if (cd[i] == "-")
        {
            temp->type = "SUB";
            temp->right = new ExprTreeNode();
            n.push_back(temp);
            temp = temp->right;
        }
        else if (cd[i] == "*")
        {
            temp->type = "MUL";
            temp->right = new ExprTreeNode();
            n.push_back(temp);
            temp = temp->right;
        }
        else if (cd[i] == "/")
        {
            temp->type = "DIV";
            temp->right = new ExprTreeNode();
            n.push_back(temp);
            temp = temp->right;
        }
        else if ((cd[i][0] <= 57 && cd[i][0] >= 48) || cd[i][0] == '-' || cd[i][0] == '+')
        {
            temp->type = "VAL";
            temp->num = stoi(cd[i]);
            temp = n[n.size() - 1];
            n.pop_back();
        }
        else
        {
            temp->type = "VAR";
            temp->id = cd[i];

            temp = n[n.size() - 1];
            n.pop_back();
        }
    }
    return res;
}
void Destructor(ExprTreeNode *rt)
{
    if (rt)
    {
        // printf("Destructor Called\n");
        Destructor(rt->left);
        Destructor(rt->right);
        delete rt;
    }
    return;
}
Parser::Parser()
{
    this->symtable = new SymbolTable();
    this->last_deleted = -1;
}

void Parser::parse(vector<string> expression)
{
    ExprTreeNode *root = new ExprTreeNode();
    root->left = new ExprTreeNode();
    if (expression[0] == "ret")
    {
        root->left->type = "RET";
        root->type = "ASSIGN";
        vector<string> a;
        a.assign(expression.begin() + 2, expression.end());
        if (a.size() == 1)
        {
            if ((a[0][0] <= 57 && a[0][0] >= 48) || a[0][0] == '-' || a[0][0] == '+')
            {
                root->right = new ExprTreeNode();
                root->right->type = "VAL";
                root->right->num = stoi(a[0]);
            }
            else
            {
                root->right = new ExprTreeNode();
                root->right->type = "VAR";
                root->right->id = a[0];
            }
        }
        else
        {
            root->right = parse_Helper(a);
        }
        this->expr_trees.push_back(root);
        return;
    }
    else if (expression[0] == "del")
    {
        root->left->type = "DEL";
        root->type = "ASSIGN";
        root->right = new ExprTreeNode();
        root->right->type = "VAR";
        root->right->id = expression[2];
        last_deleted = symtable->search(expression[2]);
        symtable->remove(expression[2]);
        this->expr_trees.push_back(root);
        return;
    }
    root->left->type = "VAR";
    root->left->id = expression[0];
    this->symtable->insert(expression[0]);
    root->type = "ASSIGN";
    vector<string> a;
    a.assign(expression.begin() + 2, expression.end());
    if (a.size() == 1)
    {
        if ((a[0][0] <= 57 && a[0][0] >= 48) || a[0][0] == '-' || a[0][0] == '+')
        {
            root->right = new ExprTreeNode();
            root->right->type = "VAL";
            root->right->num = stoi(a[0]);
        }
        else
        {
            root->right = new ExprTreeNode();
            root->right->type = "VAR";
            root->right->id = a[0];
        }
    }
    else
    {
        root->right = parse_Helper(a);
    }
    this->expr_trees.push_back(root);
    return;
}

Parser::~Parser()
{
    for (int i = 0; i < expr_trees.size(); i++)
    {
        Destructor(expr_trees[i]);
    }
    expr_trees.clear();
    delete symtable;
}