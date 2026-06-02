# ui/cmake/output/output.cmake

set(
    PROJECT_OUTPUT_DIR
    "${PROJECT_BINARY_DIR}"
    CACHE PATH 
    "Project output directory"
)

function(set_output_dir target module_dir)
    set_target_properties(${target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
        "${PROJECT_OUTPUT_DIR}/$<LOWER_CASE:$<CONFIG>>/bin/${module_dir}"
        LIBRARY_OUTPUT_DIRECTORY
        "${PROJECT_OUTPUT_DIR}/$<LOWER_CASE:$<CONFIG>>/lib/${module_dir}"
        ARCHIVE_OUTPUT_DIRECTORY
        "${PROJECT_OUTPUT_DIR}/$<LOWER_CASE:$<CONFIG>>/lib/${module_dir}"
    )
endfunction()

