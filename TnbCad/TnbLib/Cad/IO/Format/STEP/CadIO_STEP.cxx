#include <CadIO_STEP.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>
#include <Global_Timer.hxx>
#include <Global_Message.hxx>
#include <Pnt3d.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo


#include <opencascade/STEPControl_Reader.hxx>
#include <opencascade/Bnd_Box.hxx>
#include <opencascade/BRepBndLib.hxx>
#include <Cad_Tools.hxx>

unsigned short tnbLib::CadIO_STEP::verbose(0);

void tnbLib::CadIO_STEP::ReadFile
(
	const fileName & theName
)
{
	{// timer scope
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_s);

		STEPControl_Reader Reader;
		Standard_Integer status = Reader.ReadFile(theName.c_str());

		if (status == IFSelect_RetDone)
		{
			Handle(TColStd_HSequenceOfTransient) myList = Reader.GiveList("step-faces");
			Reader.TransferList(myList);
			Reader.TransferRoot();

			SetNbFaces(myList->Length());
		}
		else
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " Unable to read the STEP file." << endl
				<< abort(FatalError);
		}

		//Handle(TColStd_HSequenceOfTransient) myList = Reader.GiveList("iges-faces");
		SetShape(Reader.OneShape());
		SetFileName(theName);

		Bnd_Box box;
		BRepBndLib::AddOptimal(Shape(), box, Standard_False, Standard_False);

		SetBoundingBox(Cad_Tools::BoundingBox(box));

		if (verbose)
		{
			GET_MESSAGE << "IGES File Imported Successfully in "
				<< global_time_duration << " seconds.";
			SEND_INFO;

			GET_MESSAGE << "File Name: " << FileName();
			SEND_INFO;

			GET_MESSAGE << "Model Name: " << Name();
			SEND_INFO;
		}
	}
}