#pragma once
#ifndef _Aft2d_CorrFactorOptNodeSurface_Header
#define _Aft2d_CorrFactorOptNodeSurface_Header

#include <Aft2d_StdOptNodeSurface.hxx>

namespace tnbLib
{

	// Forward Declarations [2/24/2022 Amir]
	class Aft2d_StdOptNodeSurface_Info;

	class Aft2d_CorrFactorOptNodeSurface
		: public Aft2d_StdOptNodeSurface
	{

		/*Private Data*/


		// private functions and operators [2/24/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Aft2d_StdOptNodeSurface>(*this);
		}

	protected:

		// default constructor [2/24/2022 Amir]

		Aft2d_CorrFactorOptNodeSurface()
		{}

		// constructors [2/24/2022 Amir]

		explicit Aft2d_CorrFactorOptNodeSurface
		(
			const std::shared_ptr<Aft2d_StdOptNodeSurface_Info>& theInfo
		)
			: Aft2d_StdOptNodeSurface(theInfo)
		{}

	public:


		// override functions and operators [2/24/2022 Amir]


		// public functions and operators [2/24/2022 Amir]
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Aft2d_CorrFactorOptNodeSurface);

#endif // !_Aft2d_CorrFactorOptNodeSurface_Header
