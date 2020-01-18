//#include <Entity2d_Box.hxx>
//
//#include <TecPlot.hxx>
//
//namespace tnbLib
//{
//
//	template<>
//	void Entity2d_Box::ExportToPlt
//	(
//		OFstream& theFile
//	) const
//	{
//		Io::WriteVariables("X Y", theFile);
//
//		Io::WriteFeTriangleZone(4, 4, theFile);
//
//		Corner(Box2d_PickAlgorithm_SW).AddToPlt(theFile);
//		theFile << endl;
//		Corner(Box2d_PickAlgorithm_SE).AddToPlt(theFile);
//		theFile << endl;
//		Corner(Box2d_PickAlgorithm_NE).AddToPlt(theFile);
//		theFile << endl;
//		Corner(Box2d_PickAlgorithm_NW).AddToPlt(theFile);
//		theFile << endl;
//
//		theFile << "1 2 1" << endl;
//		theFile << "2 3 2" << endl;
//		theFile << "3 4 3" << endl;
//		theFile << "4 1 4" << endl;
//	}
//}