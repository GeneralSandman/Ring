#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <unordered_map>

using namespace std;

typedef struct {
    string label;
    string dire;
    string arg;
} code;


char                          comment_mark = ';';
vector<code>                  code_list;
stack<int>                 run_stack;
unordered_map<string, int>    variable_table;
unordered_map<string, string> label_table;
unordered_map<string, string> function_table;
unsigned int                  eip = 0;
vector<string>                printout;
bool                          debug = false;


#define LOG_COLOR_RED "\033[4;31m"

#define LOG_COLOR_CLEAR "\033[0m"

#ifdef DEBUG
// 编译错误
#define debug_log_with_red_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_RED, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)

#else
#define debug_log_with_red_coloar(format, ...)

#endif

bool is_number(const string& str)
{
    for (auto ch : str) {
        if (std::isdigit(ch) == 0) return false;
    }
    return true;
}

vector<string>  split(const string& str,const string& delim) {
	vector<string> res;
	if("" == str) return  res;
	
	string strs = str + delim;
	size_t pos;
	size_t size = strs.size();
 
	for (int i = 0; i < size; ++i) {
		pos = strs.find(delim, i); 
		if( pos < size) {
			string s = strs.substr(i, pos - i);
			res.push_back(s);
			i = pos + delim.size() - 1;
		}
		
	}
	return res;	
}

bool is_valid_identifier(string &identifier) {
    if(identifier.empty() || isdigit(identifier[0])) {
        return false;
    }

    for (int i = 0; i < identifier.size();i++) {
        if(!(isalpha(identifier[i]) 
            || isdigit(identifier[i]) 
            || identifier[i] == '_')) {
            return false;
        }
    }

    return true;
}

bool check_label(string &label) {
    if(label.empty()) {
        return false;
    }

    return true;
}


void do_var(string &arg) {
    // printf("[deubg] do_var arg:%s\n", arg.c_str());
    if (arg.empty()) {
        return;
    }

    vector<string> identifiers = split(arg, ",");
    for(auto identifier:identifiers) {
        debug_log_with_red_coloar("[deubg] identifier:%s\n", identifier.c_str());
        auto iter = variable_table.find(identifier);
        if (!is_valid_identifier(identifier) ||iter != variable_table.end()) {
            printf("error var error\n");
            exit(1);
        }

        variable_table[identifier] = 0;
        // variable_table[run_stack.size()] = identifier;
        // run_stack.push_back(identifier);

        // run_stack.push("/");
    }
}

void do_push(string &arg) {
    debug_log_with_red_coloar("[debug] do_push\n");

    if(arg.empty()) {
        return;
    }

    int arg_value;

    if(is_number(arg)) {
        arg_value = atoi(arg.c_str());
    } else {
        // TODO:
        arg_value = variable_table[arg];
        // int index = variable_table[arg];
        // arg       = variable_table[arg];
    }

    debug_log_with_red_coloar("[debug] do_push arg %s\n", arg.c_str());
    run_stack.push(arg_value);
}

void do_pop(string &arg) {
    debug_log_with_red_coloar("[debug] do_pop arg:%s\n", arg.c_str());

    int top = run_stack.top();
    run_stack.pop();

    debug_log_with_red_coloar("[debug] stack top value:%d\n", top);


    if(arg.empty()) {
        return;
    }

    variable_table[arg] = top;

}


void do_exit(string &arg) {
    int exit_code = atoi(arg.c_str());

    exit(exit_code);
}

void do_arith(string &arg, char oper) {
    int second = run_stack.top();
    run_stack.pop();
    int first = run_stack.top();
    run_stack.pop();

    debug_log_with_red_coloar("first:%d, second:%d", first, second);

    int result_value = 0;
    switch(oper) {
        case '+' : result_value = first + second; break;
        case '-' : result_value = first - second; break;
        case '*' : result_value = first * second; break;
        case '/' : result_value = first / second; break;
        case '%' : result_value = first % second; break;
    }
    run_stack.push(result_value);
}

void do_add(string &arg){do_arith(arg, '+');};
void do_sub(string &arg){do_arith(arg, '-');};
void do_mul(string &arg){do_arith(arg, '*');};
void do_div(string &arg){do_arith(arg, '/');};
void do_mod(string &arg){do_arith(arg, '%');};

void do_and(string &arg) {}
void do_or(string &arg) {}
void do_not(string &arg) {}

void do_cmp(string &arg, string oper) {
    // string first = run_stack.top();
    // run_stack.pop();
    // string second = run_stack.top();
    // run_stack.pop();

    // int result_value = 0;
    // if(oper == "==") {
    //     result_value = int(atoi(first.c_str()) == atoi(second.c_str()));
    // } else if(oper == "!=") {
    //     result_value = int(atoi(first.c_str()) != atoi(second.c_str()));
    // } else if(oper == "==") {
    //     result_value = int(atoi(first.c_str()) == atoi(second.c_str()));
    // }else if(oper == ">") {
    //     result_value = int(atoi(first.c_str()) > atoi(second.c_str()));
    // }else if(oper == ">=") {
    //     result_value = int(atoi(first.c_str()) >= atoi(second.c_str()));
    // }else if(oper == "<") {
    //     result_value = int(atoi(first.c_str()) < atoi(second.c_str()));
    // }else if(oper == "<=") {
    //     result_value = int(atoi(first.c_str()) <= atoi(second.c_str()));
    // } 
    // run_stack.push(to_string(result_value));
}

void do_cmpeq(string &arg) {do_cmp(arg, string("=="));}
void do_cmpne(string &arg) {do_cmp(arg, string("!="));}
void do_cmpgt(string &arg) {do_cmp(arg, string(">"));}
void do_cmpge(string &arg) {do_cmp(arg, string(">="));}
void do_cmplt(string &arg) {do_cmp(arg, string("<"));}
void do_cmple(string &arg) {do_cmp(arg, string("<="));}

void do_println(string &fmt) {
    debug_log_with_red_coloar("[debug] do_println fmt:%s\n", fmt.c_str());
    int top = run_stack.top();
    run_stack.pop();

    debug_log_with_red_coloar("[debug] do_println top:%d\n", top);


    printf(fmt.c_str(), top);
    printf("\n");
}

void do_jmp(string &label) {

}

void do_jz(string &label) {

}

void call(string &func_name) {

}

void do_ret(string &arg) {

}

void do_func(string &oper, string &arg) {
    if(oper == "push") {
        do_push(arg);
    } else if (oper == "pop") {
        do_pop(arg);
    } else if (oper == "add") {
        do_add(arg);
    } else if (oper == "sub") {
        do_sub(arg);
    } else if (oper == "mul") {
        do_mul(arg);
    } else if (oper == "div") {
        do_div(arg);
    } else if (oper == "mod") {
        do_mod(arg);
    } else if (oper == "println") {
        do_println(arg);
    } else if (oper == "exit") {
        do_exit(arg);
    } else if (oper == "var") {
        do_var(arg);
    }
}

void vm_assemb(string &file_name) {
    ifstream input_file(file_name);
    string   line;
    while (getline(input_file, line)) {
        if(line.empty() || line[0] == comment_mark) {
            continue;
        }

        vector<string> words = split(line, " ");

        code tmp;
        // tmp.label = words[0];
        tmp.dire  = words[0];
        tmp.arg   = words[1];
        code_list.push_back(tmp);
    }
}

void vm_run() {
    eip = 0;

    while(true) {
        if(debug) {
            
        }
        code code = code_list[eip];
        // printf("label=%s,\toper=%s,\targ=%s\n", code.label.c_str(), code.dire.c_str(), code.arg.c_str());

        do_func(code.dire, code.arg);

        eip++;
        if(eip >= code_list.size()) {
            break;
        }
    }
}

void vm_debug() {
    for (auto iter = variable_table.begin(); iter != variable_table.end(); iter++) {
        debug_log_with_red_coloar("[debug] identifier:%s,value:%d\n", iter->first.c_str(), iter->second);
    }

    while(run_stack.size()) {
        auto tmp = run_stack.top();
        run_stack.pop();
        debug_log_with_red_coloar("run_stack top:%d\n", tmp);
    }
}

int main() {
    string file_name = "./test-000.asm";
    vm_assemb(file_name);
    vm_run();
    vm_debug();
    return 0;
}