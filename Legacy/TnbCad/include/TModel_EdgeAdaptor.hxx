#pragma once
#ifndef _TModel_EdgeAdaptor_Header
#define _TModel_EdgeAdaptor_Header

#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <Cad_Module.hxx>

#include <memory>

namespace tnbLib
{

	//- Forward Declarations
	class TModel_Surface;
	class TModel_Paired;
	class TModel_Wire;
	class TModel_Edge;

	class TModel_EdgeAdaptor
	{

		/*Private Data*/

		std::weak_ptr<TModel_Surface> theSurface_;
		std::weak_ptr<TModel_Wire> theWire_;

		//TopoDS_Edge theTEdge_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		// default constructor [1/5/2022 Amir]

		TModel_EdgeAdaptor()
		{}

		// constructors [1/5/2022 Amir]

	public:

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::weak_ptr<TModel_Surface>, Surface)
			GLOBAL_ACCESS_SINGLE(std::weak_ptr<TModel_Wire>, Wire)

	};
}

#endif // !_TModel_EdgeAdaptor_Header
