#pragma once
#ifndef _Marine_SailModeler_Header
#define _Marine_SailModeler_Header

#include <Cad2d_Modeler.hxx>

namespace tnbLib
{

	class Marine_SailModeler
		: public Cad2d_Modeler
	{

		/*Private Data*/

		TnbCad2d_EXPORT void CheckCurveType(const std::shared_ptr<Pln_Edge>& theEdge, const char* name) const override;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Cad2d_Modeler>(*this);
		}

	public:

		Marine_SailModeler()
		{}


		//- public functions and operators


	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_SailModeler);

#endif // !_Marine_SailModeler_Header
