#pragma once
#ifndef _NModel_SingularEdge_Header
#define _NModel_SingularEdge_Header

#include <NModel_Edge.hxx>

namespace tnbLib
{

	class NModel_SingularEdge
		: public NModel_Edge
	{

		/*Private Data*/

	public:

		TnbCad_EXPORT NModel_SingularEdge
		(
			const std::shared_ptr<NModel_Vertex>& theVtx,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve
		);

		TnbCad_EXPORT NModel_SingularEdge
		(
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve
		);

		TnbCad_EXPORT NModel_SingularEdge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<NModel_Vertex>& theVtx,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve
		);

		TnbCad_EXPORT NModel_SingularEdge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve
		);

		TnbCad_EXPORT NModel_SingularEdge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<NModel_Vertex>& theVtx,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve
		);

		TnbCad_EXPORT NModel_SingularEdge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<NModel_ParaCurve>& theParaCurve
		);


		//- override functions and operators

		Standard_Boolean IsDegenerated() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_NModel_SingularEdge_Header