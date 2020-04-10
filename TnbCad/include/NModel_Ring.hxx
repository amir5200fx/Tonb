#pragma once
#ifndef _NModel_Ring_Header
#define _NModel_Ring_Header

#include <NModel_Edge.hxx>

namespace tnbLib
{

	class NModel_Ring
		: public NModel_Edge
	{

		/*Private Data*/

	public:

		NModel_Ring
		(
			const std::shared_ptr<NModel_Vertex>& theVtx,
			const std::shared_ptr<NModel_Curve>& theCurve,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		NModel_Ring
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<NModel_Vertex>& theVtx,
			const std::shared_ptr<NModel_Curve>& theCurve,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		NModel_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<NModel_Vertex>& theVtx,
			const std::shared_ptr<NModel_Curve>& theCurve,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		NModel_Ring
		(
			const std::shared_ptr<NModel_Curve>& theCurve,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		NModel_Ring
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<NModel_Curve>& theCurve,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		NModel_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<NModel_Curve>& theCurve,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);


		//- override functions and operators

		Standard_Boolean IsRing() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_NModel_Ring_Header