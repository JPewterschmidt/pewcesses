#include <sys/wait.h>
//#include "pewcesses/proc.h"
#include "pewcesses/pewcesses.h"
#include "toolpex/errret_thrower.h"

using namespace pewcesses;

void proc::kill(int sig)
{
    toolpex::errret_thrower{}(::kill(pid(), sig));
}

void proc::wait()
{
    toolpex::errret_thrower{}(::waitpid(pid(), &m_status, 0));
}
