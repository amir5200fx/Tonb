#pragma once
#ifndef _Marine_DisplacerModeler_Header
#define _Marine_DisplacerModeler_Header

#include <Cad2d_Modeler.hxx>

namespace tnbLib
{

	class Marine_DisplacerModeler
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

		Marine_DisplacerModeler()
		{}

		//- public functions and operators


	};
}


BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_DisplacerModeler);

#endif // !_Marine_DisplacerModeler_Header
