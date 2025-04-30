#include "ring.hpp"
#include <ctime>
#include <set>
#include <string>
#include <tuple>
#include <vector>

static std::set<std::tuple<std::string, std::string, std::string>> edges; // node node edgeName
static std::set<std::pair<std::string, std::string>>               nodes;
static std::string                                                 output_filename;

//
void debug_generate_closure_dot_file(RVM_Closure* closure) {
    // 找到所有的closure
    // closure找到所有的free——value
    // 生成一个点图

    //
    if (true) {
        // 随机名字
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        struct tm* t    = localtime(&ts.tv_sec);
        output_filename = sprintf_string("tmp/%04d%02d%02d_%02d%02d%02d_%09ld.d2",
                                         t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                                         t->tm_hour, t->tm_min, t->tm_sec, ts.tv_nsec);
    } else {
        // 固定名字
        output_filename = "tmp/trace_closure_free_value.output.d2";
    }


    FILE* file = fopen(output_filename.c_str(), "w");
    if (file == NULL) {
        ring_error_report("open file failed:%s, filename:%s", strerror(errno), output_filename.c_str());
        exit(1);
    }

    //
    //
    std::string command_help_message = R"(
direction: right
classes: {
    func_style: {
        style: {
          fill: "#f4a261"
          stroke: "#F69E03"
        }
    }

    closure_style: {
        width: 400
        height: 100
        style: {
          stroke-width: 0
          fill: "#44C7B1"
          shadow: true
          border-radius: 5
        }
    }

    free_value_style: {
        style: {
          fill: "#FE7070"
          stroke: "#F69E03"
        }
    }
}
    )";
    fprintf(file, "%s", command_help_message.c_str());


    // closure 的名称为
    // Closure(0x12) Func(identifier, 0x12, 12,12)

    // freevalue 的名称为
    // FreeValue(0x23, identifier)
    //
    std::string   node1     = "";
    std::string   node2     = "";
    std::string   prev_node = "";

    RVM_Function* func      = closure->anonymous_func;
    {
        node1 = sprintf_string("Func(%p, (%s, %u, %u))",
                               func,
                               func->identifier, func->start_line_number, func->end_line_number);
        node2 = sprintf_string("Closure(%p, (%s, %u, %u))",
                               closure,
                               func->identifier, func->start_line_number, func->end_line_number);
        // nodes.insert(std::make_pair(node1, "func_style"));
        // nodes.insert(std::make_pair(node2, "closure_style"));
        // edges.push_back({node1, node2, ""});

        prev_node = node2;
    }


    //
    for (unsigned int i = 0; closure->fvb != nullptr && i < closure->fvb->size; i++) {
        RVM_FreeValue* value                 = &(closure->fvb->list[i]);


        const char*    free_value_identifier = func->free_value_list[i].identifier;

        //
        node1 = prev_node;
        node2 = sprintf_string("FreeValue(%p, %s)",
                               value, free_value_identifier);
        nodes.insert(std::make_pair(node1, "closure_style"));
        nodes.insert(std::make_pair(node2, "free_value_style"));
        edges.insert({node1, node2, ""});

        std::string prev_node = node2;

        if (value->is_recur) {
            node1 = prev_node;
            node2 = sprintf_string("FreeValue(%p, %s)",
                                   value->u.recur, free_value_identifier);
            nodes.insert(std::make_pair(node1, ""));
            nodes.insert(std::make_pair(node2, ""));
            edges.insert({node1, node2, "recur"});
        } else {
            if (value->is_open) {
                node1 = prev_node;
                node2 = sprintf_string("Open(%p)", value->u.p);
                nodes.insert(std::make_pair(node1, ""));
                nodes.insert(std::make_pair(node2, ""));
                edges.insert({node1, node2, ""});
            } else {
                node1 = prev_node;
                node2 = prev_node;
                nodes.insert(std::make_pair(node1, ""));
                nodes.insert(std::make_pair(node2, ""));
                edges.insert({node1, node2, "close"});
            }
        }
    }


    for (auto edge : edges) {
        std::string tmp = sprintf_string("%s -> %s", std::get<0>(edge).c_str(), std::get<1>(edge).c_str());
        if (std::get<2>(edge).size()) {
            tmp = sprintf_string("%s:%s", tmp.c_str(), std::get<2>(edge).c_str());
        }

        fprintf(file, "\n\n%s\n\n", tmp.c_str());
    }
    for (auto node : nodes) {
        std::string tmp = node.first;
        if (node.second.size()) {
            tmp += sprintf_string(".class: %s ", node.second.c_str());
        }
        fprintf(file, "\n\n%s\n\n", tmp.c_str());
    }


    //
    fclose(file);
    printf("==================Generate Closure Free Value Trace File=============\n");
    printf("File: %s\n", output_filename.c_str());
    printf("Shell Command: d2 --watch %s \n", output_filename.c_str());
}