#include <PtdModel_BladeSections.hxx>

#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<PtdModel_BladeSections> mySections;


}