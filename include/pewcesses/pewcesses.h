#ifndef PEWCESSES_PEWSESSES_H
#define PEWCESSES_PEWSESSES_H

#include <vector>
#include <functional>
#include <cerrno>
#include <signal.h>

namespace pewcesses
{
    class proc
    {
    public:
        constexpr proc() noexcept = default;
        explicit proc(::pid_t pid) noexcept
            : m_pid{ pid }
        {
        }

    public:
        void kill(int sig = SIGKILL);
        void wait();
        ::pid_t pid() const noexcept { return m_pid; }
        int status() const noexcept { return m_status; }

    private:
        ::pid_t m_pid{};
        int m_status{};
    };

    proc& fork(::std::move_only_function<void()> child = nullptr);
    [[noreturn]] inline void exit(int status) { ::exit(status); }
    inline void wait(proc& p) { p.wait(); }
    inline void kill(proc& p) { p.kill(); }
    void kill_all_child();
    void kill_all_descendents();

    template<typename CallBack>
    requires (::std::is_nothrow_invocable_v<CallBack>)
    void set_atexit_child(CallBack cb)
    {
        set_atexit_child_impl(::std::move(cb));
    }

    void set_atexit_child_impl(::std::move_only_function<void()> cb);
    const ::std::vector<proc>& childs();
}

#endif 
