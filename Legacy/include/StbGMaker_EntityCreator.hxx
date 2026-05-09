#pragma once
#ifndef _StbGMaker_EntityCreator_Header
#define _StbGMaker_EntityCreator_Header

#include <StbGMaker_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Model;

	class StbGMaker_EntityCreator
		: public StbGMaker_Entity
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<StbGMaker_Entity>(*this);
		}

	protected:

		template<class... _Types>
		StbGMaker_EntityCreator(_Types&&... _Args)
			: StbGMaker_Entity(_Args...)
		{}

	public:

		TnbStbGMaker_EXPORT std::shared_ptr<Marine_Model> ExportModel() const;

		virtual void ExportAs(std::shared_ptr<Marine_Model>& theModel) const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::StbGMaker_EntityCreator);

#endif // !_StbGMaker_EntityCreator_Header
