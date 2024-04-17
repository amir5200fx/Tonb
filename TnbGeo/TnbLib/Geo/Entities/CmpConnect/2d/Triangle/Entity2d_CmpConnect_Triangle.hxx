#pragma once
#ifndef _Entity2d_CmpConnect_Triangle_Header
#define _Entity2d_CmpConnect_Triangle_Header

#include <Entity2d_CmpConnect.hxx>
#include <Entity_Connectivity.hxx>

namespace tnbLib
{

	class Entity2d_CmpConnect_Triangle
		: public Entity2d_CmpConnect
	{

	public:
		
		enum
		{
			nbCmpts = 3
		};

		typedef std::array<Standard_Integer, nbCmpts> Array3;

	private:

		/*Private Data*/

		Array3 theCmpts_;


		// Private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Entity2d_CmpConnect>(*this);
			ar& theCmpts_;
		}

	public:

		// default constructor

		Entity2d_CmpConnect_Triangle(): theCmpts_({0,0,0}) {}

		// constructors

		Entity2d_CmpConnect_Triangle(const Array3& theCmpts)
			: theCmpts_(theCmpts)
		{}

		Entity2d_CmpConnect_Triangle(Array3&& theCmpts)
			: theCmpts_(std::move(theCmpts))
		{}

		TnbGeo_EXPORT Entity2d_CmpConnect_Triangle(const connectivity::triple&);

		// Public functions and operators

		TnbGeo_EXPORT Standard_Boolean IsTriangle() const override;

		const auto& Array() const { return theCmpts_; }

		auto Value(const Standard_Integer theIndex) const { return theCmpts_.at(theIndex); }
		auto& Value(const Standard_Integer theIndex) { return theCmpts_.at(theIndex); }
		
		TnbGeo_EXPORT Standard_Integer NbCmpts() const override;
		TnbGeo_EXPORT ElmType ElementType() const override;

		TnbGeo_EXPORT std::vector<Standard_Integer> Components() const override;
		TnbGeo_EXPORT std::vector<Pnt3d> RetrievePolygon(const std::vector<Pnt3d>&) const override;
		TnbGeo_EXPORT std::vector<Pnt2d> RetrievePolygon(const std::vector<Pnt2d>&) const override;

		TnbGeo_EXPORT std::shared_ptr<Entity2d_CmpConnect> Copy() const override;
		
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Entity2d_CmpConnect_Triangle);

#endif
