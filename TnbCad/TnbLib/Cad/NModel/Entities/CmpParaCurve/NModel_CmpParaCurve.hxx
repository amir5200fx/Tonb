#pragma once
#ifndef _NModel_CmpParaCurve_Header
#define _NModel_CmpParaCurve_Header

#include <NModel_Entity.hxx>
#include <Entity2d_BoxFwd.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class NModel_ParaCurve;
	class NModel_ParaWire;
	class Cad_Tools;

	class NModel_CmpParaCurve
		: public NModel_Entity
	{

		typedef std::vector<std::shared_ptr<NModel_ParaCurve>> curveList;

		friend NModel_ParaWire;
		friend Cad_Tools;

		/*Private Data*/

		curveList theCurves_;

	protected:

		void Insert(const std::shared_ptr<NModel_ParaCurve>& theCurve)
		{
			theCurves_.push_back(theCurve);
		}

	public:

		NModel_CmpParaCurve()
		{}

		NModel_CmpParaCurve
		(
			const Standard_Integer theIndex
		)
			: NModel_Entity(theIndex)
		{}

		NModel_CmpParaCurve
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: NModel_Entity(theIndex, theName)
		{}

		auto NbCurves() const
		{
			return (Standard_Integer)theCurves_.size();
		}

		const auto& Curves() const
		{
			return theCurves_;
		}

		Entity2d_Box CalcBoundingBox() const;
	};
}

#endif // !_NModel_CmpParaCurve_Header
