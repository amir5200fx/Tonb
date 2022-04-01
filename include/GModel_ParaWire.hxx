#pragma once
#ifndef _GModel_ParaWire_Header
#define _GModel_ParaWire_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Cad_Module.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <OFstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class GModel_ParaCurve;

	class GModel_ParaWire
		: public Global_Indexed
		, public Global_Named
	{

		typedef std::vector<std::shared_ptr<GModel_ParaCurve>> curveList;

		/*Private Data*/

		std::shared_ptr<curveList> theCurves_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

		//- default constructor

		GModel_ParaWire()
		{}

	public:


		//- constructors

		TnbCad_EXPORT GModel_ParaWire
		(
			const std::shared_ptr<curveList>& theCurves
		);

		TnbCad_EXPORT GModel_ParaWire
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const std::shared_ptr<curveList>& theCurves
		);

		TnbCad_EXPORT GModel_ParaWire
		(
			std::shared_ptr<curveList>&& theCurves
		);

		TnbCad_EXPORT GModel_ParaWire
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<curveList>&& theCurves
		);


		//- public functions and operators

		TnbCad_EXPORT Standard_Integer NbCurves() const;

		const auto& Curves() const
		{
			return *theCurves_;
		}

		//- IO functions and operators

		void ExportToPlt(OFstream& File) const;
	};
}

#endif // !_GModel_ParaWire_Header
