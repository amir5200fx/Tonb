#pragma once
#ifndef _NModel_Plane_Header
#define _NModel_Plane_Header

#include <NModel_Entity.hxx>
#include <OFstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class NModel_ParaWire;
	class NModel_Surface;
	class NModel_ParaCurve;
	class Cad_Tools;

	class NModel_Plane
		: public NModel_Entity
	{

		typedef std::vector<std::shared_ptr<NModel_ParaWire>> wireList;
		typedef std::vector<std::shared_ptr<NModel_ParaCurve>> curveList;
		typedef std::shared_ptr<wireList> inner;
		typedef std::shared_ptr<NModel_ParaWire> outer;

		friend Cad_Tools;

		/*Private Data*/

		std::shared_ptr<curveList> theCurves_;

		outer theOutter_;
		inner theInner_;

	protected:

		TnbCad_EXPORT NModel_Plane
		(
			const outer& theOuter,
			const inner& theInner = nullptr,
			const std::shared_ptr<curveList>& theCurves = nullptr
		);

		TnbCad_EXPORT NModel_Plane
		(
			const Standard_Integer theIndex,
			const outer& theOuter,
			const inner& theInner = nullptr,
			const std::shared_ptr<curveList>& theCurves = nullptr
		);

		TnbCad_EXPORT NModel_Plane
		(
			const Standard_Integer theIndex,
			const word& theName,
			const outer& theOuter,
			const inner& theInner = nullptr,
			const std::shared_ptr<curveList>& theCurves = nullptr
		);

	public:

		auto HasOuter() const
		{
			return (Standard_Boolean)theOutter_;
		}

		auto HasHole() const
		{
			return (Standard_Boolean)theInner_;
		}

		auto NbCurvesOnPlane() const
		{
			return (Standard_Integer)theCurves_->size();
		}

		TnbCad_EXPORT Standard_Integer NbHoles() const;

		const auto& Outer() const
		{
			return theOutter_;
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

		static TnbCad_EXPORT std::shared_ptr<NModel_Plane>
			MakePlane(const NModel_Surface& theSurface);
	};
}

#endif // !_NModel_Plane_Header
