#pragma once
#ifndef _TModel_SingularEdge_Header
#define _TModel_SingularEdge_Header

#include <TModel_Edge.hxx>

namespace tnbLib
{

	class TModel_SingularEdge
		: public TModel_Edge
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<TModel_Edge>(*this);
		}


	protected:


		//- default constructor

		TModel_SingularEdge()
		{}

	public:

		TnbCad_EXPORT TModel_SingularEdge
		(
			const std::shared_ptr<TModel_Vertex>& theVtx,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve
		);

		TnbCad_EXPORT TModel_SingularEdge
		(
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve
		);

		TnbCad_EXPORT TModel_SingularEdge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<TModel_Vertex>& theVtx,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve
		);

		TnbCad_EXPORT TModel_SingularEdge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve
		);

		TnbCad_EXPORT TModel_SingularEdge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<TModel_Vertex>& theVtx,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve
		);

		TnbCad_EXPORT TModel_SingularEdge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve
		);


		//- override functions and operators

		Standard_Boolean IsDegenerated() const override
		{
			return Standard_True;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_SingularEdge);

#endif // !_TModel_SingularEdge_Header
