#pragma once
#ifndef _TModel_Plane_Header
#define _TModel_Plane_Header

#include <TModel_Entity.hxx>
#include <OFstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class TModel_ParaWire;
	class TModel_Surface;
	class Cad_Tools;

	class TModel_Plane
		: public TModel_Entity
	{

		typedef std::vector<std::shared_ptr<TModel_ParaWire>> wireList;
		typedef std::shared_ptr<wireList> inner;
		typedef std::shared_ptr<TModel_ParaWire> outer;

		friend Cad_Tools;

		/*Private Data*/

		outer theOuter_;
		inner theInner_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:


		// default constructor [1/5/2022 Amir]

		TModel_Plane()
		{}


		// constructors [1/5/2022 Amir]

		TnbCad_EXPORT TModel_Plane
		(
			const outer& theOuter,
			const inner& theInner = nullptr
		);

		TnbCad_EXPORT TModel_Plane
		(
			const Standard_Integer theIndex,
			const outer& theOuter,
			const inner& theInner = nullptr
		);

		TnbCad_EXPORT TModel_Plane
		(
			const Standard_Integer theIndex,
			const word& theName,
			const outer& theOuter,
			const inner& theInner = nullptr
		);

	public:


		//- public functions and operators

		auto HasOuter() const
		{
			return (Standard_Boolean)theOuter_;
		}

		auto HasHole() const
		{
			return (Standard_Boolean)theInner_;
		}

		TnbCad_EXPORT Standard_Integer NbHoles() const;

		const auto& Outer() const
		{
			return theOuter_;
		}

		const auto& Holes() const
		{
			return theInner_;
		}

		TnbCad_EXPORT wireList RetrieveWires() const;

		TnbCad_EXPORT void RetrieveWiresTo(wireList& theWires) const;

		//- IO functions and operators

		TnbCad_EXPORT void ExportToPlt(OFstream& File) const;

		//- Static functions and operators

		static TnbCad_EXPORT std::shared_ptr<TModel_Plane>
			MakePlane(const TModel_Surface& theSurface);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_Plane);

#endif // !_TModel_Plane_Header
