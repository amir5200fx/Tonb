#pragma once
#ifndef _NModel_ParaWire_Header
#define _NModel_ParaWire_Header

#include <NModel_Entity.hxx>
#include <Entity2d_BoxFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class NModel_CmpParaCurve;

	class NModel_ParaWire
		: public NModel_Entity
	{

		/*Private Data*/

		std::shared_ptr<NModel_CmpParaCurve> theCurve_;

	public:

		NModel_ParaWire
		(
			const std::shared_ptr<NModel_CmpParaCurve>& theCurve
		);

		NModel_ParaWire
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<NModel_CmpParaCurve>& theCurve
		);

		NModel_ParaWire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<NModel_CmpParaCurve>& theCurve
		);
	};
}

#endif // !_NModel_ParaWire_Header
