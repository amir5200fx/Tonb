#pragma once
#ifndef _PtdModel_Face_Header
#define _PtdModel_Face_Header

#include <Standard_Handle.hxx>
#include <PtdModel_Entity.hxx>

class Geom_Surface;

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pnt3d;

	class PtdModel_Face
		: public PtdModel_Entity
	{

		/*Private Data*/

		Handle(Geom_Surface) theSurface_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);


	public:

		//- default constructor

		inline PtdModel_Face();


		//- constructors

		inline PtdModel_Face(const Handle(Geom_Surface)&);

		inline PtdModel_Face(Handle(Geom_Surface) && );


		//- public functions and operators

		const auto& Surface() const
		{
			return theSurface_;
		}

		inline void SetSurface(const Handle(Geom_Surface)&);
		inline void SetSurface(Handle(Geom_Surface) && );


		//- static functions and operators

		static TnbPtdModel_EXPORT std::shared_ptr<PtdModel_Face>
			CreateFace
			(
				std::vector<std::vector<Pnt3d>>&
			);
	};
}

#include <PtdModel_FaceI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_Face);

#endif // !_PtdModel_Face_Header
