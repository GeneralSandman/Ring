#include "ring.hpp"


Ring_Buildin_Func Ring_Buildin_Funcs[] = {
    {
        .identifier   = "len",
        .param_size   = 1,
        .param_types  = std::vector<TypeSpecifier*>{},
        .return_size  = 1,
        .return_types = std::vector<TypeSpecifier*>{},
    },
    {
        .identifier   = "capacity",
        .param_size   = 1,
        .param_types  = std::vector<TypeSpecifier*>{},
        .return_size  = 1,
        .return_types = std::vector<TypeSpecifier*>{},
    },
    {
        .identifier   = "push",
        .param_size   = 2,
        .param_types  = std::vector<TypeSpecifier*>{},
        .return_size  = 0,
        .return_types = std::vector<TypeSpecifier*>{},
    },
    {
        .identifier   = "pop",
        .param_size   = 1,
        .param_types  = std::vector<TypeSpecifier*>{},
        .return_types = std::vector<TypeSpecifier*>{},
    },
    {
        .identifier   = "to_string",
        .param_size   = 1,
        .param_types  = std::vector<TypeSpecifier*>{},
        .return_size  = 1,
        .return_types = std::vector<TypeSpecifier*>{},
    },
};