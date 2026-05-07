#include <Cad_API.hxx>

#include <Cad_Shape.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <opencascade/TopoDS_Shape.hxx>
#include <opencascade/STEPControl_Reader.hxx>
#include <opencascade/Bnd_Box.hxx>
#include <opencascade/BRepBndLib.hxx>

tnbLib::api::cad::Shape tnbLib::api::cad::load_step(const std::string& file_name, unsigned short verbose)
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

		STEPControl_Reader reader;
		Standard_Integer status = reader.ReadFile(fn.c_str());

		if (status == IFSelect_RetDone) {
			// Transfer the content of the STEP file to a TopoDS_Shape
			Handle(TColStd_HSequenceOfTransient) myList = reader.GiveList("step-faces");
			reader.TransferList(myList);
			reader.TransferRoot();
		}
		else {
			std::cerr << "Error: Unable to read the STEP file." << std::endl;
		}
		shape = std::make_shared<Cad_Shape>(0, file_name, reader.OneShape());
	}
	if (verbose)
	{
		Info << "\n"
			<< " - The STEP file has been successfully loaded in " << global_time_duration << " seconds.\n";
	}
	return { std::move(shape) };
}