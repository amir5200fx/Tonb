#pragma once
#ifndef _Aft2d_CorrFactorOptNodeSurface_TwoLevIter_Header
#define _Aft2d_CorrFactorOptNodeSurface_TwoLevIter_Header

#include <Aft2d_CorrFactorOptNodeSurface.hxx>

namespace tnbLib
{

	class Aft2d_CorrFactorOptNodeSurface_TwoLevIter
		: public Aft2d_CorrFactorOptNodeSurface
	{

		/*Private Data*/


		// private functions and operators [2/24/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Aft2d_CorrFactorOptNodeSurface>(*this);
		}

	protected:

		// default constructor [2/24/2022 Amir]

		Aft2d_CorrFactorOptNodeSurface_TwoLevIter()
		{}

	public:

		// default constructor [2/24/2022 Amir]

		

		// constructors [2/24/2022 Amir]

		explicit Aft2d_CorrFactorOptNodeSurface_TwoLevIter
		(
			const std::shared_ptr<Aft2d_StdOptNodeSurface_Info>& theInfo
		)
			: Aft2d_CorrFactorOptNodeSurface(theInfo)
		{}

		// override functions and operators [2/24/2022 Amir]

		// WARNING! the function makes a side effect (set correction factor in adaptive surface metric processor) [2/24/2022 Amir]
		TnbMesh_EXPORT void Perform() override;

		// public functions and operators [2/24/2022 Amir]

		TnbMesh_EXPORT std::pair<Pnt2d, Standard_Real> CalcCoord() const;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_CorrFactorOptNodeSurface);

#endif // !_Aft2d_CorrFactorOptNodeSurface_TwoLevIter_Header
