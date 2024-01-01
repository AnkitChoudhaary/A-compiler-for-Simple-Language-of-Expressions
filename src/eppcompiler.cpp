/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

// Write your code below this line
void help_com(ExprTreeNode *a, SymbolTable *st, vector<string> &res, MinHeap &hp)
{
    if (a->type == "ASSIGN")
    {
        if (a->left->type == "DEL")
        {
            string str = "DEL = mem[";
            int idx = st->search(a->right->id);
            if (idx >= 0)
            {
                str += to_string(idx);
                str += "]";
                res.push_back(str);
                hp.push_heap(idx);

                st->remove(a->right->id);
            }
            else
            {
                return;
            }
        }
        else if (a->left->type == "RET")
        {
            help_com(a->right, st, res, hp);
            string str = "RET = POP";
            res.push_back(str);
        }
        else if (a->left->type == "VAR")
        {
            help_com(a->right, st, res, hp);
            string str = "mem[";
            int ii = st->search(a->left->id);
            if (ii == -1)
            {
                int idx = hp.get_min();
                str += to_string(idx);
                str += "] = POP";
                res.push_back(str);
                hp.pop();
                st->assign_address(a->left->id, idx);
            }
            else if (ii == -2)
            {
                st->insert(a->left->id);
                int idx = hp.get_min();
                str += to_string(idx);
                str += "] = POP";
                res.push_back(str);
                hp.pop();
                st->assign_address(a->left->id, idx);
            }
            else
            {
                str += to_string(ii);
                str += "] = POP";
                res.push_back(str);
            }
        }
        else
        {
            printf("ERR in Exp or prase LN:38 EPPCompiler\n");
        }
    }
    else if (a->type == "VAL")
    {
        string str = "PUSH ";
        str += to_string(a->num);
        res.push_back(str);
    }
    else if (a->type == "VAR")
    {
        string str = "PUSH mem[";
        str += to_string(st->search(a->id));
        str += "]";
        res.push_back(str);
    }
    else if (a->type == "ADD")
    {
        help_com(a->right, st, res, hp);
        help_com(a->left, st, res, hp);
        string str = "ADD";
        res.push_back(str);
    }
    else if (a->type == "SUB")
    {
        help_com(a->right, st, res, hp);
        help_com(a->left, st, res, hp);
        string str = "SUB";
        res.push_back(str);
    }
    else if (a->type == "MUL")
    {
        help_com(a->right, st, res, hp);
        help_com(a->left, st, res, hp);
        string str = "MUL";
        res.push_back(str);
    }
    else if (a->type == "DIV")
    {
        help_com(a->right, st, res, hp);
        help_com(a->left, st, res, hp);

        string str = "DIV";
        res.push_back(str);
    }
    else
    {
        printf("Undefined Exp_Node :ERR_ON_Ln_79 E++_Comp\n");
    }
}
EPPCompiler::EPPCompiler()
{
    this->memory_size = 0;
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
    this->output_file = out_file;
    ofstream of(output_file.c_str());
    this->memory_size = mem_limit;
    for (int i = 0; i <= memory_size; i++)
    {
        least_mem_loc.push_heap(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code)
{
    ofstream of(output_file.c_str());
    for (int i = 0; i < code.size(); i++)
    {
        vector<string> cd = code[i];
        targ.parse(cd);
        if (targ.expr_trees.back()->left->type == "DEL")
        {
            ofstream of;
            of.open(output_file, ios::app);
            if (targ.last_deleted >= 0)
            {
                of << "DEL = mem[";
                of << to_string(targ.last_deleted);
                of << "]";
                of << "\n";
                least_mem_loc.push_heap(targ.last_deleted);
                targ.last_deleted = -1;
                continue;
            }
            continue;
        }

        vector<string> out_str = generate_targ_commands();
        write_to_file(out_str);
    }
}

vector<string> EPPCompiler::generate_targ_commands()
{

    vector<string> a;
    help_com(targ.expr_trees[targ.expr_trees.size() - 1], targ.symtable, a, least_mem_loc);
    return a;
}

void EPPCompiler::write_to_file(vector<string> commands)
{
    ofstream of;
    of.open(output_file, ios::app);
    if (of.is_open())
    {
        for (int i = 0; i < commands.size(); i++)
        {
            of << commands[i];
            of << "\n";
        }
        of.close();
    }
    else
    {
        printf("File isn't open\n");
    }
}

EPPCompiler::~EPPCompiler()
{
    this->mem_loc.clear();
}