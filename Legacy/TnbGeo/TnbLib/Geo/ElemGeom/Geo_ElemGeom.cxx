#include <Geo_ElemGeom.hxx>

#include <Entity_Connectivity.hxx>
#include <Entity3d_CmpConnect_Brick.hxx>
#include <Entity3d_CmpConnect_Prism.hxx>
#include <Entity3d_CmpConnect_Pyramid.hxx>
#include <Entity3d_CmpConnect_Tetrahedron.hxx>
#include <Entity2d_CmpConnect_Quad.hxx>
#include <Entity2d_CmpConnect_Triangle.hxx>

std::shared_ptr<tnbLib::Entity2d_CmpConnect>
tnbLib::Geo_ElemGeom::Convert2d(const Geo_ElemGeom& theElm)
{
	auto ids = theElm.IndexList();
	if (theElm.Dim() < dim::three)
	{
		switch (ids.size())
		{
		case static_cast<size_t>(Entity2d_CmpConnect_Quad::nbCmpts):
		{
			connectivity::quadruple q;
			for (size_t i = 0; i < connectivity::quadruple::nbCmpts; i++)
			{
				q.Value(i) = ids.at(i);
			}
			return std::make_shared<Entity2d_CmpConnect_Quad>(std::move(q));
		}
		case static_cast<size_t>(Entity2d_CmpConnect_Triangle::nbCmpts):
		{
			connectivity::triple q;
			for (size_t i = 0; i < connectivity::triple::nbCmpts; i++)
			{
				q.Value(i) = ids.at(i);
			}
			return std::make_shared<Entity2d_CmpConnect_Triangle>(std::move(q));
		}
		default:
			FatalErrorIn(FunctionSIG)
				<< "Unspecified type of element has been detected." << endl
				<< abort(FatalError);
		}
	}
	return nullptr;
}

std::shared_ptr<tnbLib::Entity3d_CmpConnect>
tnbLib::Geo_ElemGeom::Convert3d(const Geo_ElemGeom& theElm)
{
	auto ids = theElm.IndexList();
	switch (ids.size())
	{
		case static_cast<size_t>(Entity3d_CmpConnect_Brick::nbCmpts):
			{
			connectivity::octuple q;
			for (size_t i = 0; i < connectivity::octuple::nbCmpts; i++)
			{
				q.Value(i) = ids.at(i);
			}
			return std::make_shared<Entity3d_CmpConnect_Brick>(std::move(q));
			}
		case static_cast<size_t>(Entity3d_CmpConnect_Prism::nbCmpts):
		{
			connectivity::sextuple q;
			for (size_t i = 0; i < connectivity::sextuple::nbCmpts; i++)
			{
				q.Value(i) = ids.at(i);
			}
			return std::make_shared<Entity3d_CmpConnect_Prism>(std::move(q));
		}
		case static_cast<size_t>(Entity3d_CmpConnect_Pyramid::nbCmpts):
		{
			connectivity::quintuple q;
			for (size_t i = 0; i < connectivity::quintuple::nbCmpts; i++)
			{
				q.Value(i) = ids.at(i);
			}
			return std::make_shared<Entity3d_CmpConnect_Pyramid>(std::move(q));
		}
		case static_cast<size_t>(Entity3d_CmpConnect_Tetrahedron::nbCmpts):
		{
			connectivity::quadruple q;
			for (size_t i = 0; i < connectivity::quadruple::nbCmpts; i++)
			{
				q.Value(i) = ids.at(i);
			}
			return std::make_shared<Entity3d_CmpConnect_Tetrahedron>(std::move(q));
		}
		default:
			FatalErrorIn(FunctionSIG)
				<< "Unspecified type of element has been detected." << endl
				<< abort(FatalError);
	}
	return nullptr;
}
