#pragma once
#ifndef _ShapePx_ContinProfile_Linear_Header
#define _ShapePx_ContinProfile_Linear_Header

#include <ShapePx_ContinProfile.hxx>

namespace tnbLib
{

	namespace shapePxLib
	{

		class ContinProfile_Linear
			: public ShapePx_ContinProfile
		{

			/*Private Data*/

			offsetPoint theQ0_;
			offsetPoint theQ1_;


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<ShapePx_ContinProfile>(*this);

				ar & theQ0_;
				ar & theQ1_;
			}

		public:

			ContinProfile_Linear()
			{}

			ContinProfile_Linear
			(
				const offsetPoint& theQ0,
				const offsetPoint& theQ1
			)
				: theQ0_(theQ0)
				, theQ1_(theQ1)
			{}

			ContinProfile_Linear
			(
				const Standard_Integer theIndex,
				const word& theName,
				const offsetPoint& theQ0,
				const offsetPoint& theQ1
			)
				: ShapePx_ContinProfile(theIndex)
				, theQ0_(theQ0)
				, theQ1_(theQ1)
			{}

			ContinProfile_Linear
			(
				offsetPoint&& theQ0,
				offsetPoint&& theQ1
			)
				: theQ0_(std::move(theQ0))
				, theQ1_(std::move(theQ1))
			{}

			ContinProfile_Linear
			(
				const Standard_Integer theIndex,
				const word& theName,
				offsetPoint&& theQ0,
				offsetPoint&& theQ1
			)
				: ShapePx_ContinProfile(theIndex, theName)
				, theQ0_(std::move(theQ0))
				, theQ1_(std::move(theQ1))
			{}

			const auto& Q0() const
			{
				return theQ0_;
			}

			const auto& Q1() const
			{
				return theQ1_;
			}

			auto X0() const
			{
				return theQ0_.x;
			}

			auto X1() const
			{
				return theQ1_.x;
			}

			auto Value0() const
			{
				return theQ0_.y;
			}

			auto Value1() const
			{
				return theQ1_.y;
			}

			Standard_Real Lower() const override
			{
				return X0();
			}

			Standard_Real Upper() const override
			{
				return X1();
			}

			Standard_Real LowerValue() const override
			{
				return Value0();
			}

			Standard_Real UpperValue() const override
			{
				return Value1();
			}

			TnbShapePx_EXPORT Standard_Real Value(const Standard_Real x) const override;

			TnbShapePx_EXPORT std::vector<offsetPoint> RetrieveOffsets() const override;

			TnbShapePx_EXPORT std::vector<Standard_Real> X() const override;

			void SetQ0(const offsetPoint& q0)
			{
				theQ0_ = q0;
			}

			void SetQ1(const offsetPoint& q1)
			{
				theQ1_ = q1;
			}

			void SetQ0(offsetPoint&& q0)
			{
				theQ0_ = std::move(q0);
			}

			void SetQ1(offsetPoint&& q1)
			{
				theQ1_ = std::move(q1);
			}

			TnbShapePx_EXPORT void Update() override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::shapePxLib::ContinProfile_Linear);

#endif // !_ShapePx_ContinProfile_Linear_Header
