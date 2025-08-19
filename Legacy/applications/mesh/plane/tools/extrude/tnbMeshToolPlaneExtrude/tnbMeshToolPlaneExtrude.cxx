#include <MeshIO3d_FEA.hxx>
#include <MeshIO2d_FEA.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_FILENAME_OBJ;
	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;
	
	static const std::string model_directory = "mesh";

	TNB_SET_VERBOSE_FUN;

	static std::shared_ptr<MeshIO2d_FEA> myMesh2d;
	static std::shared_ptr<MeshIO3d_FEA> myMesh3d;

	TNB_STANDARD_LOAD_SAVE_POINTER_OBJECT(myMesh2d, model_directory, myMesh3d);

	void execute()
	{

	}

}