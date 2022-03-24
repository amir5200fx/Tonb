#pragma once
#ifndef _Cad2d_IntsctEntity_Adaptor_Header
#define _Cad2d_IntsctEntity_Adaptor_Header

#include <Standard_TypeDef.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_IntsctEntity;

	class Cad2d_IntsctEntity_Adaptor
	{

		/*Private Data*/

		std::weak_ptr<Cad2d_IntsctEntity> thePair_;


		// private functions and operators [3/22/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			// empty body [3/22/2022 Amir]
		}

	protected:

		Cad2d_IntsctEntity_Adaptor()
		{}

	public:

		const auto& Pair() const
		{
			return thePair_;
		}

		void SetPair
		(
			const std::weak_ptr<Cad2d_IntsctEntity>& thePair
		)
		{
			thePair_ = thePair;
		}
	};
}

#endif // !_Cad2d_IntsctEntity_Adaptor_Header
