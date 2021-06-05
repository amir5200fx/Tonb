#pragma once
#ifndef _PtdModel_BladeFace_Header
#define _PtdModel_BladeFace_Header

#include <Standard_Handle.hxx>
#include <PtdModel_PropEntity.hxx>

class Geom_Surface;

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pnt3d;

	class PtdModel_BladeFace
		: public PtdModel_PropEntity
	{

		/*Private Data*/

		Handle(Geom_Surface) theSurface_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);


	public:

		//- default constructor

		inline PtdModel_BladeFace();


		//- constructors

		inline PtdModel_BladeFace(const Handle(Geom_Surface)&);

		inline PtdModel_BladeFace(Handle(Geom_Surface) && );


		//- public functions and operators

		const auto& Surface() const
		{
			return theSurface_;
		}

		inline void SetSurface(const Handle(Geom_Surface)&);
		inline void SetSurface(Handle(Geom_Surface) && );


		//- static functions and operators

		static TnbPtdModel_EXPORT std::shared_ptr<PtdModel_BladeFace> 
			CreateFace
			(
				std::vector<std::vector<Pnt3d>>&
			);
	};
}

#include <PtdModel_BladeFaceI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_BladeFace);

#endif // !_PtdModel_BladeFace_Header
