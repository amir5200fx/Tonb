#include <GeoIO_Loader_STL.hxx>

#include <Entity3d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

//#include <CGAL/Simple_cartesian.h>
//#include <CGAL/Surface_mesh.h>
//#include <CGAL/IO/STL/STL_reader.h>
//#include <iostream>
//#include <fstream>
//
//typedef CGAL::Simple_cartesian<double> Kernel;
//typedef Kernel::Point_3 Point;
//typedef CGAL::Surface_mesh<Point> GMesh;
//
//void tnbLib::ioLib::Loader_STL::PerformBinary(const std::string& file_name)
//{
//	GMesh mesh;
//	// Open the STL file
//	std::ifstream input(file_name, std::ios::binary);
//	if (!input)
//	{
//		FatalErrorIn(FunctionSIG) << endl
//			<< " Cannot open file: " << file_name << endl
//			<< abort(FatalError);
//	}
//	// Read the STL file
//	if (!CGAL::IO::read_STL(input, mesh))
//	{
//		FatalErrorIn(FunctionSIG) << endl
//			<< " Invalid STL file" << endl
//			<< abort(FatalError);
//	}
//	std::vector<Pnt3d> coords;
//	for (GMesh::Vertex_index v: mesh.vertices())
//	{
//		const auto& p = mesh.point(v);
//		coords.emplace_back(p.x(), p.y(), p.z());
//	}
//	std::vector<connectivity::triple> elements;
//	for (GMesh::face_index f: mesh.faces())
//	{
//		connectivity::triple t;
//		Standard_Integer k = 0;
//		for (GMesh::vertex_index v: CGAL::vertices_around_face(mesh.halfedge(f), mesh))
//		{
//			if (k > 2)
//			{
//				FatalErrorIn(FunctionSIG) << endl
//					<< " Unsupported type of element has been detected." << endl
//					<< abort(FatalError);
//			}
//			t.Value(k++) = static_cast<Standard_Integer>(v.idx()) + 1;
//		}
//		elements.emplace_back(std::move(t));
//	}
//	theMesh_ = std::make_shared<Entity3d_Triangulation>(std::move(coords), std::move(elements));
//	Change_IsDone() = Standard_True;
//}
//
//void tnbLib::ioLib::Loader_STL::PerformASCII(const std::string& file_name)
//{
//	GMesh mesh;
//	// Open the STL file
//	std::ifstream input(file_name);
//	if (!input)
//	{
//		FatalErrorIn(FunctionSIG) << endl
//			<< " Cannot open file: " << file_name << endl
//			<< abort(FatalError);
//	}
//	// Read the STL file
//	if (!CGAL::IO::read_STL(input, mesh))
//	{
//		/*FatalErrorIn(FunctionSIG) << endl
//			<< " Invalid STL file" << endl
//			<< abort(FatalError);*/
//	}
//	std::vector<Pnt3d> coords;
//	for (GMesh::Vertex_index v : mesh.vertices())
//	{
//		const auto& p = mesh.point(v);
//		coords.emplace_back(p.x(), p.y(), p.z());
//	}
//	std::vector<connectivity::triple> elements;
//	for (GMesh::face_index f : mesh.faces())
//	{
//		connectivity::triple t;
//		Standard_Integer k = 0;
//		for (GMesh::vertex_index v : CGAL::vertices_around_face(mesh.halfedge(f), mesh))
//		{
//			if (k > 2)
//			{
//				FatalErrorIn(FunctionSIG) << endl
//					<< " Unsupported type of element has been detected." << endl
//					<< abort(FatalError);
//			}
//			t.Value(k++) = static_cast<Standard_Integer>(v.idx() + 1);
//		}
//		elements.emplace_back(std::move(t));
//	}
//	theMesh_ = std::make_shared<Entity3d_Triangulation>(std::move(coords), std::move(elements));
//	Change_IsDone() = Standard_True;
//}
