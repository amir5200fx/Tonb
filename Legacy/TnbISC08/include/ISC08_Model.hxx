#pragma once
#ifndef _ISC08_Model_Header
#define _ISC08_Model_Header

#include <Global_Serialization.hxx>
#include <ISC08_Parameter.hxx>
#include <ISC08_Factor.hxx>
#include <Marine_VesselParams.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{
		class rArmCurve_Eff;
	}

	class ISC08_Model
	{

	public:

		class VesselParams
		{

			/*Private Data*/

			marineLib::B theB_;
			marineLib::TM theTm_;
			marineLib::CB theCb_;
			marineLib::LWL theLwl_;
			marineLib::KG theKg_;
			marineLib::DISPM theDisplm_;
			marineLib::GM theGm_;


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & theB_;
				ar & theTm_;
				ar & theCb_;
				ar & theLwl_;
				ar & theKg_;
				ar & theDisplm_;
				ar & theGm_;
			}

		public:

			VesselParams()
			{}

			const auto& B() const
			{
				return theB_;
			}

			auto& B()
			{
				return theB_;
			}

			const auto& TM() const
			{
				return theTm_;
			}

			auto& TM()
			{
				return theTm_;
			}

			const auto& CB() const
			{
				return theCb_;
			}

			auto& CB()
			{
				return theCb_;
			}

			const auto& LWL() const
			{
				return theLwl_;
			}

			auto& LWL()
			{
				return theLwl_;
			}

			const auto& KG() const
			{
				return theKg_;
			}

			auto& KG()
			{
				return theKg_;
			}

			const auto& Displacement() const
			{
				return theDisplm_;
			}

			auto& Displacement()
			{
				return theDisplm_;
			}

			const auto& GM() const
			{
				return theGm_;
			}

			auto& GM()
			{
				return theGm_;
			}
		};


		class Props
		{

			/*Private Data*/

			isc08Lib::A theLateral_;
			isc08Lib::Z theVerticalDist_;
			isc08Lib::Ak theAk_;
			isc08Lib::T theT_;

			isc08Lib::BilgeBarCondition theBilgeCondition_;


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar & theLateral_;
				ar & theVerticalDist_;
				ar & theAk_;
				ar & theT_;

				ar & theBilgeCondition_;
			}

		public:

			Props()
			{}

			const auto& LateralArea() const
			{
				return theLateral_;
			}

			auto& LateralArea()
			{
				return theLateral_;
			}

			const auto& VerticalDistance() const
			{
				return theVerticalDist_;
			}

			auto& VerticalDistance()
			{
				return theVerticalDist_;
			}

			const auto& Ak() const
			{
				return theAk_;
			}

			auto& Ak()
			{
				return theAk_;
			}

			const auto& T() const
			{
				return theT_;
			}

			auto& T()
			{
				return theT_;
			}

			const auto& BilgeBarCondition() const
			{
				return theBilgeCondition_;
			}

			auto& BilgeBarCondition()
			{
				return theBilgeCondition_;
			}
		};

	private:

		/*Private Data*/


		VesselParams theVesselParameters_;

		Props theProperties_;

		std::shared_ptr<hydStcLib::rArmCurve_Eff> theEff_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbISC08_EXPORT);

	public:


		//- default constructor

		ISC08_Model()
		{}

		//- constructors

		TnbISC08_EXPORT ISC08_Model
		(
			VesselParams&& theParameters,
			Props&& theProperties, 
			const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theGz
		);

		TnbISC08_EXPORT ISC08_Model
		(
			VesselParams&& theParameters,
			Props&& theProperties,
			std::shared_ptr<hydStcLib::rArmCurve_Eff>&& theGz
		);


		//- public functions and operators

		const auto& VesselParameters() const
		{
			return theVesselParameters_;
		}

		auto& VesselParameters()
		{
			return theVesselParameters_;
		}

		const auto& Properties() const
		{
			return theProperties_;
		}

		auto& Properties()
		{
			return theProperties_;
		}

		const auto& GZeff() const
		{
			return theEff_;
		}

		auto& GZeff() 
		{
			return theEff_;
		}

		TnbISC08_EXPORT void SetParameters(const VesselParams&);
		TnbISC08_EXPORT void SetParameters(VesselParams&&);

		TnbISC08_EXPORT void SetProperties(const Props&);
		TnbISC08_EXPORT void SetProperties(Props&&);

		TnbISC08_EXPORT void SetGZeff(const std::shared_ptr<hydStcLib::rArmCurve_Eff>&);
		TnbISC08_EXPORT void SetGZeff(std::shared_ptr<hydStcLib::rArmCurve_Eff>&&);
	};
}

#endif // !_ISC08_Model_Header
