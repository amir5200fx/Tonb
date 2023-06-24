#include <GeoSizeFun2d_Background.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad_Tools.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	static unsigned short verbose = 0;
	static bool exeTag = false;
	static bool loadTag = false;

}