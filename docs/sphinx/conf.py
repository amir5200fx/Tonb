# docs/sphinx/conf.py
import os, pathlib

project = "Tonb"
release = "0.19.0"
root_doc = "index"

extensions = ["breathe", "myst_parser"]
html_theme = "furo"
myst_enable_extensions = ["colon_fence"]

here = pathlib.Path(__file__).resolve().parent

# 1) Prefer CMake-provided env var
xml_dir = os.environ.get("DOXYGEN_XML_DIR")

# 2) Otherwise, try common fallbacks relative to this file
if not xml_dir:
    candidates = [
        here.parent / "doxygen" / "xml",                  # in-source doxygen run
        here.parent.parent / "build" / "docs" / "doxygen" / "xml",  # rare in-source build/
    ]
    for c in candidates:
        if c.exists():
            xml_dir = str(c)
            break

if not xml_dir or not os.path.exists(xml_dir):
    raise RuntimeError(f"Cannot find Doxygen XML (set DOXYGEN_XML_DIR). Tried: {xml_dir}")

breathe_projects = {"Tonb": xml_dir}
breathe_default_project = "Tonb"

# Make these macros harmless in signatures
cpp_id_attributes = ['TNBSYSTEM_EXPORT',
                     'TNB_NODISCARD',
                     'TNBSYSTEM_ND_EXPORT',
                     'TNBBASE_ND_EXPORT',
                     'TNBBASE_EXPORT',
                     'TNBGEOM_ND_EXPORT',
                     'TNBGEOM_EXPORT',
                     'TNBCAD_ND_EXPORT',
                     'TNBCAD_EXPORT',
                     'Handle']
c_id_attributes = ['TNBSYSTEM_EXPORT']



