add_library(TonbCAD2dShell)
add_library(Tonb::CAD2dShell ALIAS TonbCAD2dShell)

target_sources(TonbCAD2dShell
        PRIVATE
        src/shell_app.cxx
        src/shell_session.cxx
        src/shell_tokenise.cxx
        src/command/command_registry.cxx
        src/command/command_node.cxx
        src/help/help_renderer.cxx
        src/help/help_registry.cxx
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES
        include/tonb/cad2d/shell/module.hxx
        include/tonb/cad2d/shell/shell_app.hxx
        include/tonb/cad2d/shell/shell_session.hxx
        include/tonb/cad2d/shell/shell_tokenise.hxx
        include/tonb/cad2d/shell/command/command_registry.hxx
        include/tonb/cad2d/shell/command/command_args.hxx
        include/tonb/cad2d/shell/command/command_context.hxx
        include/tonb/cad2d/shell/command/command_node.hxx
        include/tonb/cad2d/shell/help/command_spec.hxx
        include/tonb/cad2d/shell/help/help_registry.hxx
        include/tonb/cad2d/shell/help/help_renderer.hxx
)

target_include_directories(TonbCAD2dShell PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(TonbCAD2dShell
        PUBLIC Tonb::CAD2d
        PUBLIC Tonb::System
)

target_link_libraries(TonbCAD2dShell
        PUBLIC Tonb::CAD2d
        PUBLIC Tonb::System
        PUBLIC Tonb::Foundation
)

set_target_properties(TonbCAD2dShell PROPERTIES
        CXX_VISIBILITY_PRESET default
        VISIBILITY_INLINES_HIDDEN NO
)

target_compile_definitions(TonbCAD2dShell PRIVATE TNBCAD2DSHELL_EXPORTS)

if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(TonbCAD2dShell PUBLIC TNBCAD2DSHELL_STATIC_MODULE)
endif ()