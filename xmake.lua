add_rules(
    "mode.tsan", "mode.ubsan", "mode.asan", 
    "mode.debug", "mode.release"
)

set_languages("c++2b", "c17")

add_requires(
    "fmt", 
    "gtest", 
    "concurrentqueue master",
    "benchmark"
)

target("pewcesses")
    set_kind("shared")
    --set_warnings("all", "error")
    add_files("src/*.cc")
    add_packages(
        "fmt"
    )
    add_includedirs(
        "include", 
        "toolpex/include"
    )

target("example")
    set_kind("binary")
    add_deps("pewcesses")
    add_files("example/*.cc")
    add_packages(
        "fmt"
    )
    add_includedirs(
        "include", 
        "toolpex/include"
    )

target("test")
    set_kind("binary")
    add_deps("pewcesses")
    --set_warnings("all", "error")
    add_files("test/*.cc")
    add_packages(
        "gtest", "fmt"
    )
    add_includedirs(
        "include", 
        "toolpex/include"
    )
    after_build(function (target)
        os.exec(target:targetfile())
        print("xmake: unittest complete.")
    end)
    on_run(function (target)
        --nothing
    end)
