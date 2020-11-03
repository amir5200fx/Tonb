#pragma once
#ifndef _Marine_Domain_Header
#define _Marine_Domain_Header

#include <Global_Done.hxx>
#include <Global_Serialization.hxx>
#include <Marine_CoordinatedEntity.hxx>
#include <Entity3d_Box.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;

	class Marine_Domain
		: public Marine_CoordinatedEntity
		, public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Entity3d_Box> theDomain_;

		auto& ChangeDim()
		{
			return theDomain_;
		}


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
			ar & boost::serialization::base_object<Global_Done>(*this);

			ar & theDomain_;
		}

	public:

		static const Standard_Real DEFAULT_EXPAND_COEFF;

		Marine_Domain();

		Marine_Domain
		(
			const Standard_Integer theIndex
		);

		Marine_Domain
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

		auto ExpandCoeff() const
		{
			return DEFAULT_EXPAND_COEFF;
		}

		const auto& Dim() const
		{
			return theDomain_;
		}

		void Perform
		(
			const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel
		);

		void Perform(const Entity3d_Box& theModel);
	};
}

#endif // !_Marine_Domain_Header
