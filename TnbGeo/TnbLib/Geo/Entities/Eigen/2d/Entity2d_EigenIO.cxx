//#include <Entity2d_Eigen.hxx>
//
//#include <TecPlot_Opencascade.hxx>
//
//#include <Geom2d_Ellipse.hxx>
//#include <gp_Ax22d.hxx>
//
//void tnbLib::Entity2d_Eigen::ExportToPlt
//(
//	const Pnt2d & Centre,
//	OFstream & File
//) const
//{
//	const auto h1 = H1();
//	const auto h2 = H2();
//
//	const auto& e1 = E1();
//	//const auto& e2 = E2();
//
//	gp_Dir2d xDir(e1.X(), e1.Y());
//	gp_Ax22d ax(Centre, xDir);
//
//	Geom2d_Ellipse ellipse(ax, h1, h2);
//
//	Io::ExportCurve
//	(
//		ellipse,
//		ellipse.FirstParameter(),
//		ellipse.LastParameter(), 30, File);
//}