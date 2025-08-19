#pragma once
#ifndef _TModel_Ring_Header
#define _TModel_Ring_Header

#include <TModel_Edge.hxx>

namespace tnbLib
{

	class TModel_Ring
		: public TModel_Edge
	{

		/*Private Data*/


		//- private functions and operators


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<TModel_Edge>(*this);
		}

	protected:

		TModel_Ring()
		{}

	public:

		TnbCad_EXPORT TModel_Ring
		(
			const std::shared_ptr<TModel_Vertex>& theVtx,
			const std::shared_ptr<TModel_Curve>& theCurve, 
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve, 
			const Standard_Boolean theSense = Standard_True
		);

		TnbCad_EXPORT TModel_Ring
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<TModel_Vertex>& theVtx,
			const std::shared_ptr<TModel_Curve>& theCurve,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		TnbCad_EXPORT TModel_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<TModel_Vertex>& theVtx,
			const std::shared_ptr<TModel_Curve>& theCurve,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		TnbCad_EXPORT TModel_Ring
		(
			const std::shared_ptr<TModel_Curve>& theCurve,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		TnbCad_EXPORT TModel_Ring
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<TModel_Curve>& theCurve,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);

		TnbCad_EXPORT TModel_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<TModel_Curve>& theCurve,
			const std::shared_ptr<TModel_ParaCurve>& theParaCurve,
			const Standard_Boolean theSense = Standard_True
		);


		//- override functions and operators

		Standard_Boolean IsRing() const override
		{
			return Standard_True;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_Ring);

#endif // !_TModel_Ring_Header
