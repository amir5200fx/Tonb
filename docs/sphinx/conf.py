# docs/sphinx/conf.py
import os
import pathlib

project = "Tonb"
release = "0.19.0"
root_doc = "index"

extensions = ["breathe", "myst_parser"]
html_theme = "furo"
myst_enable_extensions = ["colon_fence"]

here = pathlib.Path(__file__).resolve().parent
repo_root = here.parent  # docs/
# If your repo layout is <repo>/docs/sphinx/conf.py, .parent is docs/
# build dir default: <repo>/build/docs/doxygen/xml
default_xml = repo_root.parent / "build" / "docs" / "doxygen" / "xml"

# 1) Prefer CMake-provided env var
xml_dir = os.environ.get("DOXYGEN_XML_DIR")
if not xml_dir:
    # 2) Fall back to the default build path
    xml_dir = str(default_xml)

xml_dir_path = pathlib.Path(xml_dir)
if not (xml_dir_path / "index.xml").exists():
    raise RuntimeError(f"Cannot find Doxygen XML (set DOXYGEN_XML_DIR). Tried: {xml_dir_path}")

breathe_projects = {"Tonb": str(xml_dir_path)}
breathe_default_project = "Tonb"

# Optional: attribute names to ignore in C/C++ signatures so Breathe doesn't choke
cpp_id_attributes = [
    'TNBSYSTEM_EXPORT', 'TNB_NODISCARD', 'TNBSYSTEM_ND_EXPORT',
    'TNBBASE_ND_EXPORT', 'TNBBASE_EXPORT',
    'TNBGEOM_ND_EXPORT', 'TNBGEOM_EXPORT',
    'TNBCAD_ND_EXPORT', 'TNBCAD_EXPORT',
    'TNBIO_EXPORT', 'Handle'
]
c_id_attributes = ['TNBSYSTEM_EXPORT']
