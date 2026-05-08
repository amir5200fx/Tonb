add_library(TonbFoundation)
add_library(Tonb::Foundation ALIAS TonbFoundation)

target_sources(TonbFoundation
        PRIVATE
        src/util/env.cxx
        src/config/app_config.cxx
        src/workspace/workspace.cxx
        src/workspace/workspace_default.cxx
        src/workspace/workspace_lifecycle.cxx
        src/workspace/workspace_persist.cxx
        src/export/atomic_bundle_writer.cxx
        src/export/bundle_integrity.cxx
        src/export/bundle_naming.cxx
        src/export/export_bundle.cxx
        src/export/export_path_policy.cxx
        src/export/export_profile.cxx
        src/export/sha256.cxx
        src/failure/failure_artefact_matrix.cxx
        src/failure/failure_bundle.cxx
        src/failure/failure_bundle_writer.cxx
        src/failure/failure_capture.cxx
        src/failure/failure_code.cxx
        src/failure/failure_event.cxx
        src/failure/failure_exception.cxx
        src/failure/failure_kind.cxx
        src/failure/failure_policy.cxx
        src/failure/failure_run_context.cxx
        src/failure/failure_severity.cxx
        src/logger/logger.cxx
        src/logger/log_context.cxx
        src/logger/log_formatter.cxx
        src/logger/sinks/log_buffer_sink.cxx
        src/logger/sinks/log_console_sink.cxx
        src/logger/sinks/log_ndjson_file_sink.cxx
        src/logger/sinks/log_text_file_sink.cxx
        src/cli/command_path.cxx
        src/cli/command_registry.cxx
        src/cli/command_spec.cxx
        src/cli/help_renderer.cxx
        src/cli/parse_utils.cxx
        src/cli/text_table.cxx
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES
        include/tonb/foundation/module.hxx
        include/tonb/foundation/module.hxx
        include/tonb/foundation/util/env.hxx
        include/tonb/foundation/config/app_config.hxx
        include/tonb/foundation/config/app_identity.hxx
        include/tonb/foundation/workspace/workspace.hxx
        include/tonb/foundation/workspace/workspace_default.hxx
        include/tonb/foundation/workspace/workspace_lifecycle.hxx
        include/tonb/foundation/workspace/workspace_persist.hxx
        include/tonb/foundation/export/atomic_bundle_writer.hxx
        include/tonb/foundation/export/bundle_integrity.hxx
        include/tonb/foundation/export/bundle_naming.hxx
        include/tonb/foundation/export/export_bundle.hxx
        include/tonb/foundation/export/export_path_policy.hxx
        include/tonb/foundation/export/export_profile.hxx
        include/tonb/foundation/export/sha256.hxx
        include/tonb/foundation/failure/failure_artefact_matrix.hxx
        include/tonb/foundation/failure/failure_bundle.hxx
        include/tonb/foundation/failure/failure_bundle_writer.hxx
        include/tonb/foundation/failure/failure_capture.hxx
        include/tonb/foundation/failure/failure_cause.hxx
        include/tonb/foundation/failure/failure_code.hxx
        include/tonb/foundation/failure/failure_context.hxx
        include/tonb/foundation/failure/failure_diagnostic.hxx
        include/tonb/foundation/failure/failure_event.hxx
        include/tonb/foundation/failure/failure_exception.hxx
        include/tonb/foundation/failure/failure_kind.hxx
        include/tonb/foundation/failure/failure_policy.hxx
        include/tonb/foundation/failure/failure_run_context.hxx
        include/tonb/foundation/failure/failure_severity.hxx
        include/tonb/foundation/logger/log_level.hxx
        include/tonb/foundation/logger/log_context.hxx
        include/tonb/foundation/logger/log_field.hxx
        include/tonb/foundation/logger/log_formatter.hxx
        include/tonb/foundation/logger/log_macros.hxx
        include/tonb/foundation/logger/log_record.hxx
        include/tonb/foundation/logger/log_sink.hxx
        include/tonb/foundation/logger/logger.hxx
        include/tonb/foundation/logger/sinks/log_buffer_sink.hxx
        include/tonb/foundation/logger/sinks/log_console_sink.hxx
        include/tonb/foundation/logger/sinks/log_ndjson_file_sink.hxx
        include/tonb/foundation/logger/sinks/log_text_file_sink.hxx
        include/tonb/foundation/cli/command_path.hxx
        include/tonb/foundation/cli/command_registry.hxx
        include/tonb/foundation/cli/command_spec.hxx
        include/tonb/foundation/cli/help_renderer.hxx
        include/tonb/foundation/cli/parse_utils.hxx
        include/tonb/foundation/cli/text_table.hxx
)

target_include_directories(TonbFoundation PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(TonbFoundation
        PUBLIC Tonb::System
)

set_target_properties(TonbFoundation PROPERTIES
        CXX_VISIBILITY_PRESET default
        VISIBILITY_INLINES_HIDDEN NO
)

target_compile_definitions(TonbFoundation PRIVATE TNBFOUND_EXPORTS)

if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(TonbFoundation PUBLIC TNBFOUND_STATIC_MODULE)
endif ()