#pragma once
#include "../../FLCoreDefs.hpp"

class IStateGraph;
namespace pub
{
    namespace StateGraph
    {
        enum Type
        {
            TYPE_STANDARD = 0
        };

        IMPORT int get_state_graph(int, Type);
        IMPORT int get_state_graph(const char*, Type);
        IMPORT const IStateGraph* get_state_graph_internal(int);
        IMPORT void refresh_state_graph();
    };
}