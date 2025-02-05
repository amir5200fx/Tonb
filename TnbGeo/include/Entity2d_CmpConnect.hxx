#pragma once
#ifndef _Entity2d_CmpConnect_Header
#define _Entity2d_CmpConnect_Header

#include <Global_TypeDef.hxx>
#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <vector>
#include <map>
#include <array>

namespace tnbLib
{

	// Forward Declarations
	class Pnt3d;
	class Pnt2d;

	class Entity2d_CmpConnect
		: public std::enable_shared_from_this<Entity2d_CmpConnect>
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			// empty body
		}

	protected:

		// default constructor

		Entity2d_CmpConnect()
		{}

	public:
		virtual ~Entity2d_CmpConnect() = default;

		enum class ElmType
		{
			triangle,
			quadrilateral,
			pentagon,
			polygon
		};


		// Public functions and operators

		virtual Standard_Boolean IsTriangle() const { return Standard_False; }
		virtual Standard_Boolean IsQuadrilateral() const { return Standard_False; }
		virtual Standard_Boolean IsPentagon() const { return Standard_False; }
		virtual Standard_Boolean IsPolygon() const { return Standard_False; }

		virtual Standard_Integer NbCmpts() const = 0;
		virtual ElmType ElementType() const = 0;

		virtual std::vector<Standard_Integer> Components() const = 0;
		virtual std::vector<Pnt3d> RetrievePolygon(const std::vector<Pnt3d>&) const = 0;
		virtual std::vector<Pnt2d> RetrievePolygon(const std::vector<Pnt2d>&) const = 0;

		virtual std::shared_ptr<Entity2d_CmpConnect> Copy() const = 0;
		TnbGeo_EXPORT std::shared_ptr<Entity2d_CmpConnect> Reversed() const;

		virtual void Reverse() = 0;
		virtual void Update(const std::vector<Standard_Integer>&) = 0;
		virtual void Update(const std::map<Standard_Integer, Standard_Integer>&) = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Entity2d_CmpConnect);

#endif
