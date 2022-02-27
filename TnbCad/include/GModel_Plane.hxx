#pragma once
#ifndef _GModel_Plane_Header
#define _GModel_Plane_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Cad_Module.hxx>
#include <OFstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class GModel_ParaWire;

	class GModel_Plane
		: public Global_Indexed
		, public Global_Named
	{

	public:

		typedef std::vector<std::shared_ptr<GModel_ParaWire>> wireList;
		typedef std::shared_ptr<GModel_ParaWire> outer;
		typedef std::shared_ptr<wireList> inner;

	private:

		/*Private Data*/

		outer theOuter_;
		inner theInner_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);


		//- default constructor

		GModel_Plane()
		{}

	public:


		//- constructors

		TnbCad_EXPORT GModel_Plane
		(
			const outer& theOuter, 
			const inner& theInner = nullptr
		);

		GModel_Plane
		(
			outer&& theOuter,
			inner&& theInner
		);

		TnbCad_EXPORT GModel_Plane
		(
			const Standard_Integer theIndex, 
			const outer& theOuter, 
			const inner& theInner = nullptr
		);

		TnbCad_EXPORT GModel_Plane
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const outer& theOuter, 
			const inner& theInner = nullptr
		);


		//- public functions and operators

		TnbCad_EXPORT Standard_Boolean HasHole() const;

		TnbCad_EXPORT Standard_Integer NbHoles() const;

		const auto& Inner() const
		{
			return theInner_;
		}

		const auto& Outer() const
		{
			return theOuter_;
		}


		//- Io functions and operators

		void ExportToPlt(OFstream& File) const;
	};
}

#endif // !_GModel_Plane_Header
