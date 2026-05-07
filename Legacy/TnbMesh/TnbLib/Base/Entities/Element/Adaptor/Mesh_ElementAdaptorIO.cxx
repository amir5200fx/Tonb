#include <Mesh_ElementAdaptorTypes.hxx>

#include <Mesh3d_Node.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_Facet.hxx>
#include <Mesh2d_Node.hxx>
#include <Mesh2d_Element.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_ElementAdaptor)
{
	//ar & theNeighbors_;
	/*std::vector<Standard_Integer> neighbors;
	neighbors.reserve(4);
	if (auto x = theNeighbors_[0].lock())
	{
		neighbors.push_back(x->Index());
	}
	else
	{
		neighbors.push_back(0);
	}

	if (auto x = theNeighbors_[1].lock())
	{
		neighbors.push_back(x->Index());
	}
	else
	{
		neighbors.push_back(0);
	}

	if (auto x = theNeighbors_[2].lock())
	{
		neighbors.push_back(x->Index());
	}
	else
	{
		neighbors.push_back(0);
	}

	if (auto x = theNeighbors_[3].lock())
	{
		neighbors.push_back(x->Index());
	}
	else
	{
		neighbors.push_back(0);
	}
	ar << neighbors;*/
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_ElementAdaptor)
{
	//ar & theNeighbors_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh2d_ElementAdaptor)
{
	//ar & theNeighbors_;
	/*std::vector<Standard_Integer> neighbors;
	neighbors.reserve(3);
	if (auto x = theNeighbors_[0].lock())
	{
		neighbors.push_back(x->Index());
	}
	else
	{
		neighbors.push_back(0);
	}

	if (auto x = theNeighbors_[1].lock())
	{
		neighbors.push_back(x->Index());
	}
	else
	{
		neighbors.push_back(0);
	}

	if (auto x = theNeighbors_[2].lock())
	{
		neighbors.push_back(x->Index());
	}
	else
	{
		neighbors.push_back(0);
	}
	ar << neighbors;*/
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh2d_ElementAdaptor)
{
	//ar & theNeighbors_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_FacetElementAdaptor)
{
	/*ar & theLeftElement_;
	ar & theRightElement_;

	if (auto x = theLeftElement_.lock())
	{
		ar << x->Index();
	}
	else
	{
		ar << (Standard_Integer)0;
	}

	if (auto x = theRightElement_.lock())
	{
		ar << x->Index();
	}
	else
	{
		ar << (Standard_Integer)0;
	}*/
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_FacetElementAdaptor)
{
	//ar & theLeftElement_;
	//ar & theRightElement_;
}