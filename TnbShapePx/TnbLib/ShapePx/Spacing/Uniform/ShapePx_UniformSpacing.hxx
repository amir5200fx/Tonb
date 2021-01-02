#pragma once
#ifndef _ShapePx_UniformSpacing_Header
#define _ShapePx_UniformSpacing_Header

#include <ShapePx_Spacing.hxx>

namespace tnbLib
{

	class ShapePx_UniformSpacing
		: public ShapePx_Spacing
	{

		/*Private Data*/

		Standard_Integer theNbSections_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<ShapePx_Spacing>(*this);
			ar & theNbSections_;
		}

	protected:


		//- default constructors

		ShapePx_UniformSpacing()
		{}

	public:

		//- constructors

		ShapePx_UniformSpacing
		(
			const std::shared_ptr<SectPx_Limits>& theLimits
		);

		ShapePx_UniformSpacing
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<SectPx_Limits>& theLimits
		);


		//- public functions and operators

		Standard_Integer NbSections() const override
		{
			return theNbSections_;
		}

		std::vector<Standard_Real> Sections() const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::ShapePx_UniformSpacing);

#endif // !_ShapePx_UniformSpacing_Header
