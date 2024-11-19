#include <Cad_API.hxx>

#include <Cad_Shape.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <opencascade/TopoDS_Shape.hxx>
#include <opencascade/IGESControl_Reader.hxx>
#include <opencascade/Bnd_Box.hxx>
#include <opencascade/BRepBndLib.hxx>

tnbLib::api::cad::Shape tnbLib::api::cad::load_iges(const std::string& file_name, unsigned short verbose)
{
	fileName fn(file_name);
	if (verbose)
	{
		Info << "\n"
			<< " - Loading the file from, " << fn << ".\n\n";
	}
	std::shared_ptr<Cad_Shape> shape;
	{// timer scope
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_s);

		IGESControl_Reader Reader;
		Reader.ReadFile(fn.c_str());

		Handle(TColStd_HSequenceOfTransient) myList = Reader.GiveList("iges-faces");
		Reader.TransferList(myList);
		shape = std::make_shared<Cad_Shape>(0, file_name, Reader.OneShape());
	}
	if (verbose)
	{
		Info << " - The IGES file has been successfully loaded in " << global_time_duration << " seconds.\n\n";
	}
	return { std::move(shape) };
}