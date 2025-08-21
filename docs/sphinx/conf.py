import os

project = "Tonb"
release = "0.19.0"

root_doc = "index"
master_doc = root_doc

extensions = ["breathe", "myst_parser"]
html_theme = "furo"
myst_enable_extensions = ["colon_fence"]

# Get Doxygen XML dir from env; fall back to a reasonable default
xml_dir = os.environ.get(
    "DOXYGEN_XML_DIR",
    os.path.abspath(os.path.join("..", "..", "build", "docs", "doxygen", "xml")),
)
breathe_projects = {"tonb": xml_dir}
breathe_default_project = "tonb"

# Treat these as harmless attributes in C/C++ declarations
cpp_id_attributes = ['TNBSYSTEM_EXPORT', 'TNB_NODISCARD', 'TNBSYSTEM_ND_EXPORT']
c_id_attributes = ['TNBSYSTEM_EXPORT']  # if you also document C code


