#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>
#include "toolpex/errret_thrower.h"
#include "pewcesses/pewcesses.h"

namespace pewcesses
{
    bool g_is_child{};
    ::std::vector<proc> g_childs;
    ::std::move_only_function<void()> g_child_at_exit;

    proc& fork(::std::move_only_function<void()> child_call)
    {
        ::pid_t child_pid{};
        switch (child_pid = ::fork())
        {
            case -1:    toolpex::errret_thrower{}(errno);
                        break;

            case 0:     // Child
                        g_is_child = true;
                        ::std::atexit(+[] noexcept { if (g_child_at_exit) g_child_at_exit(); });
                        if (child_call) child_call();
                        exit(0);
                        break;

            default:    // Parent
                        proc& result = g_childs.emplace_back(proc{ child_pid });
                        return result;
        }
    }

    void set_atexit_child(::std::move_only_function<void()> cb)
    {
        g_child_at_exit.swap(cb);
    }

    const ::std::vector<proc>& childs()
    {
        return g_childs;
    }

    void kill_all_child()
    {
        toolpex::not_implemented();
    }

    void kill_all_descendents()
    {
        toolpex::not_implemented();
    }
}
