#pragma once
#ifndef _VoyageMesh_Node_Header
#define _VoyageMesh_Node_Header

#include <VoyageMesh_Entity.hxx>
#include <VoyageMesh_NodeBase.hxx>

namespace tnbLib
{

	
	class VoyageMesh_Node
		: public VoyageMesh_NodeBase
	{

	public:

		//typedef VoyageMesh_Entity<Aft2d_NodeSurface> baseType;

	private:

		/*Private Data*/

		Standard_Integer theRegion_;

	public:

		//- default constructor

		VoyageMesh_Node()
			: theRegion_(0)
		{}

		//- constructors

		VoyageMesh_Node(const Standard_Integer theIndex, const Pnt2d& theCoord)
			: VoyageMesh_NodeBase(theIndex, theCoord)
			, theRegion_(0)
		{}

		VoyageMesh_Node(const Standard_Integer theIndex, Pnt2d&& theCoord)
			: VoyageMesh_NodeBase(theIndex, std::move(theCoord))
			, theRegion_(0)
		{}

	public:

		//- Public functions and operators

		auto Region() const { return theRegion_; }

		virtual Standard_Boolean IsReference() const { return Standard_False; }

		void SetRegion(const Standard_Integer theValue) { theRegion_ = theValue; }
	};

	//class VoyageMesh_Node
	//	: public VoyageMesh_Entity<Aft2d_NodeSurface>
	//{

	//public:

	//	typedef VoyageMesh_Entity<Aft2d_NodeSurface> baseType;

	//private:

	//	/*Private Data*/

	//	Standard_Integer theRegion_;

	//protected:

	//	//- default constructor

	//	VoyageMesh_Node()
	//		: theRegion_(0)
	//	{}

	//	//- constructors

	//	VoyageMesh_Node(const Standard_Integer theIndex, const Pnt2d& theCoord)
	//		: baseType(theIndex, theCoord)
	//		, theRegion_(0)
	//	{}

	//	VoyageMesh_Node(const Standard_Integer theIndex, Pnt2d&& theCoord)
	//		: baseType(theIndex, std::move(theCoord))
	//		, theRegion_(0)
	//	{}

	//public:

	//	//- Public functions and operators

	//	auto Region() const { return theRegion_; }

	//	void SetRegion(const Standard_Integer theValue) { theRegion_ = theValue; }
	//};

}

#endif // !_VoyageMesh_Node_Header
