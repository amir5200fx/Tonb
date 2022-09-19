#pragma once
#ifndef _TopoMesh_Surface_Header
#define _TopoMesh_Surface_Header

#include <Aft2d_ElementSurfaceFwd.hxx>
#include <Aft2d_NodeSurfaceFwd.hxx>
#include <Global_Done.hxx>

#include <vector>
#include <memory>
#include <map>

namespace tnbLib
{

	class TopoMesh_Surface
		: public Global_Done
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<Aft2d_ElementSurface>> theElements_;


		// private functions and operators [6/9/2022 Amir]

		

	public:

		// default constructor [6/9/2022 Amir]

		TopoMesh_Surface()
		{}


		// constructors [6/9/2022 Amir]


		// public functions and operators [6/9/2022 Amir]

		const auto& Elements() const
		{
			return theElements_;
		}


		void Insert(const Standard_Integer theIndex, const std::shared_ptr<Aft2d_ElementSurface>& theElement);
		void Insert(const Standard_Integer theIndex, std::shared_ptr<Aft2d_ElementSurface>&& theElement);

		void Insert(const std::vector<std::shared_ptr<Aft2d_ElementSurface>>&);

		void RemoveElement(const Standard_Integer);

		void RemoveNode(const std::shared_ptr<Aft2d_NodeSurface>&);
	};
}

#endif // !_TopoMesh_Surface_Header
