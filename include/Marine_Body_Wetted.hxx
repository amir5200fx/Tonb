#pragma once
#ifndef _Marine_Body_Wetted_Header
#define _Marine_Body_Wetted_Header

#include <Marine_HullBody.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_MidSection;
	class Marine_CmpSection;

	namespace marineLib
	{

		// Forward Declarations
		class Body_Displacer;

		class Body_Wetted
			: public Marine_HullBody
		{

			friend class Marine_DisctLib;
			friend class Marine_MidSection;

			/*Private Data*/

			
			std::shared_ptr<Marine_CmpSection> theMid_;
			std::shared_ptr<Body_Displacer> theDisplacer_;


			//- private functions and operators


			TNB_SERIALIZATION(TnbMarine_EXPORT);

			auto & ChangeMid()
			{
				return theMid_;
			}

			void SetMid(const std::shared_ptr<Marine_CmpSection>& theMid)
			{
				theMid_ = theMid;
			}

			void SetMid(const std::shared_ptr<Marine_CmpSection>&& theMid)
			{
				theMid_ = std::move(theMid);
			}

		protected:

			template<class... _Types>
			Body_Wetted(_Types&&... _Args)
				: Marine_HullBody(_Args...)
			{}

		public:

			virtual Standard_Boolean ShapeType() const
			{
				return Standard_False;
			}

			Standard_Boolean IsWetted() const override
			{
				return Standard_True;
			}

			Marine_BodyType Type() const override
			{
				return Marine_BodyType::wetted;
			}	

			const auto& Mid() const
			{
				return theMid_;
			}

			const auto& Displacer() const
			{
				return theDisplacer_;
			}

			TnbMarine_EXPORT std::shared_ptr<Marine_Body> Copy() const override;

			void SetDisplacer
			(
				const std::shared_ptr<Body_Displacer>& theDisplacer
			)
			{
				theDisplacer_ = theDisplacer;
			}

		};
	}
}

#include <Marine_BodyConstructor.hxx>

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::marineLib::Body_Wetted);

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::BodyConstructor_noShape<tnbLib::marineLib::Body_Wetted>);

namespace tnbLib
{
	namespace marineLib
	{

		template<>
		class BodyConstructor_Shape<Body_Wetted>
			: public Body_Wetted
		{

			/*Private Data*/

			std::shared_ptr<Marine_Shape> theShape_;

			std::shared_ptr<Marine_CmpSection> theWater_;

			//- private functions and operators

			TNB_SERIALIZATION(TnbMarine_EXPORT);

			auto& ChangeShape()
			{
				return theShape_;
			}

			auto& ChangeWL()
			{
				return theWater_;
			}

			

		public:

			template<class... _Types>
			BodyConstructor_Shape(_Types&&... _Args)
				: Body_Wetted(_Args...)
			{}

			Standard_Boolean ShapeType() const override
			{
				return Standard_True;
			}

			const std::shared_ptr<Marine_Shape>& Shape() const
			{
				return theShape_;
			}

			void SetWL(const std::shared_ptr<Marine_CmpSection>& theWater)
			{
				theWater_ = theWater;
			}

			void SetWL(std::shared_ptr<Marine_CmpSection>&& theWater)
			{
				theWater_ = std::move(theWater);
			}

			void SetShape(const std::shared_ptr<Marine_Shape>& theShape)
			{
				theShape_ = theShape;
			}

			void SetShape(std::shared_ptr<Marine_Shape>&& theShape)
			{
				theShape_ = theShape;
			}

			const std::shared_ptr<Marine_CmpSection>& WL() const
			{
				return theWater_;
			}
		};

		typedef BodyConstructor_Shape<Body_Wetted> shapedWettedBody;
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::BodyConstructor_Shape<tnbLib::marineLib::Body_Wetted>);

#endif // !_Marine_Body_Wetted_Header
