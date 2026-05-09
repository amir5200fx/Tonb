#include <CadIO_IGES.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>
#include <Global_Timer.hxx>
#include <Global_Message.hxx>
#include <Pnt3d.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo


#include <opencascade/IGESControl_Reader.hxx>
#include <opencascade/Bnd_Box.hxx>
#include <opencascade/BRepBndLib.hxx>
#include <Cad_Tools.hxx>

unsigned short tnbLib::CadIO_IGES::verbose(0);

void tnbLib::CadIO_IGES::ReadFile
(
	const fileName & theName
)
{
	{// timer scope
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_s);

		IGESControl_Reader Reader;

		Reader.ReadFile(theName.c_str());
		
		Handle(TColStd_HSequenceOfTransient) myList = Reader.GiveList("iges-faces");
		
		SetNbFaces(myList->Length());
		Reader.TransferList(myList);
		
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