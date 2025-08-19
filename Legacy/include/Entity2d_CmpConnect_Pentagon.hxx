#pragma once
#ifndef _Entity2d_CmpConnect_Pentagon_Header
#define _Entity2d_CmpConnect_Pentagon_Header

#include <Entity2d_CmpConnect.hxx>
#include <Entity_Connectivity.hxx>

namespace tnbLib
{
	class Entity2d_CmpConnect_Pentagon
		: public Entity2d_CmpConnect
	{
	public:
		enum
		{
			nbCmpts = 5
		};
		typedef std::array<Standard_Integer, nbCmpts> Array5;
	private:
		/*Private Data*/
		Array5 theCmpts_;

		// Private functions and operators
		friend  class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_vesion)
		{
			ar& boost::serialization::base_object<Entity2d_CmpConnect>(*this);
			ar& theCmpts_;
		}
	public:
		// default constructor
		Entity2d_CmpConnect_Pentagon(): theCmpts_{ 0,0,0,0,0 } {}
		// constructors
		Entity2d_CmpConnect_Pentagon(const Array5& theCmpts)
			: theCmpts_{ theCmpts }
		{}
		TnbGeo_EXPORT Entity2d_CmpConnect_Pentagon(const connectivity::quintuple& theQ);

		// Public functions and operators
		TnbGeo_EXPORT Standard_Boolean IsPentagon() const override;

		const auto& Array() const { return theCmpts_; }

		auto Value(const Standard_Integer theIndex) const { return theCmpts_.at(theIndex); }
		auto& Value(const Standard_Integer theIndex) { return theCmpts_.at(theIndex); }

		TnbGeo_EXPORT Standard_Integer NbCmpts() const override;
		TnbGeo_EXPORT ElmType ElementType() const override;

		TnbGeo_EXPORT std::vector<Standard_Integer> Components() const override;
		TnbGeo_EXPORT std::vector<Pnt3d> RetrievePolygon(const std::vector<Pnt3d>&) const override;
		TnbGeo_EXPORT std::vector<Pnt2d> RetrievePolygon(const std::vector<Pnt2d>&) const override;

		TnbGeo_EXPORT std::shared_ptr<Entity2d_CmpConnect> Copy() const override;

		TnbGeo_EXPORT void Reverse() override;
		TnbGeo_EXPORT void Update(const std::vector<Standard_Integer>&) override;
		TnbGeo_EXPORT void Update(const std::map<Standard_Integer, Standard_Integer>&) override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Entity2d_CmpConnect_Pentagon);

#endif