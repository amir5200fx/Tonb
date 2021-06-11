#pragma once
#ifndef _PtdModel_WingFace_Header
#define _PtdModel_WingFace_Header

#include <Standard_Handle.hxx>
#include <PtdModel_WingEntity.hxx>

class Geom_Surface;

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pnt3d;

	class PtdModel_WingFace
		: public PtdModel_WingEntity
	{

		/*Private Data*/

		Handle(Geom_Surface) theSurface_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		inline PtdModel_WingFace();

		//- constructors

		inline PtdModel_WingFace(const Handle(Geom_Surface)&);
		inline PtdModel_WingFace(Handle(Geom_Surface) && );

		//- public functions and operators

		const auto& Surface() const
		{
			return theSurface_;
		}

		inline void SetSurface(const Handle(Geom_Surface)&);
		inline void SetSurface(Handle(Geom_Surface) && );


		//- static functions and operators

		static TnbPtdModel_EXPORT std::shared_ptr<PtdModel_WingFace>
			CreateFace
			(
				std::vector<std::vector<Pnt3d>>&
			);
	};
}

#include <PtdModel_WingFaceI.hxx>

#endif // !_PtdModel_WingFace_Header
