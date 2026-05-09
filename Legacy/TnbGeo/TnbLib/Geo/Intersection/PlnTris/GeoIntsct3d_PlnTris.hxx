#pragma once
#ifndef _GeoIntsct3d_PlnTris_Header
#define _GeoIntsct3d_PlnTris_Header

#include <Entity3d_TriangulationFwd.hxx>
#include <Entity3d_TriangleFwd.hxx>
#include <Pnt3d.hxx>
#include <Global_Serialization.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

// Forward Declarations [2/3/2023 Payvand]
class gp_Pln;

namespace tnbLib
{

	class GeoIntsct3d_PlnTris
		: public Global_Done
	{

	public:

		class intsctEntity
		{

			/*Private Data*/


			// Private functions and operators [2/3/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{}

		public:

			static TnbGeo_EXPORT const std::string extension;

			// default constructor [2/3/2023 Payvand]

			intsctEntity()
			{}

			// constructors [2/3/2023 Payvand]


			// Public functions and operators [2/3/2023 Payvand]

			virtual TnbGeo_EXPORT Standard_Boolean IsPoint() const;
			virtual TnbGeo_EXPORT Standard_Boolean IsSegment() const;
			virtual TnbGeo_EXPORT Standard_Boolean IsTriangle() const;

			virtual Standard_Integer NbPoints() const = 0;
			virtual Pnt3d Point(const Standard_Integer) const = 0;

			virtual std::vector<Pnt3d> RetrievePoints() const = 0;

		};

		class pntIntsct
			: public intsctEntity
		{

			/*Private Data*/

			Pnt3d theCoord_;


			// Private functions and operators [2/3/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<intsctEntity>(*this);
				ar& theCoord_;
			}

		public:

			static TnbGeo_EXPORT const unsigned short nbPoints;

			// default constructor [2/3/2023 Payvand]

			pntIntsct()
			{}

			// constructors [2/3/2023 Payvand]

			explicit pntIntsct(const Pnt3d& theCoord)
				: theCoord_(theCoord)
			{}

			pntIntsct(Pnt3d&& theCoord)
				: theCoord_(std::move(theCoord))
			{}

			// Public functions and operators [2/3/2023 Payvand]

			const auto& Coord() const
			{
				return theCoord_;
			}

			TnbGeo_EXPORT Standard_Boolean IsPoint() const override;

			TnbGeo_EXPORT Standard_Integer NbPoints() const override;
			TnbGeo_EXPORT Pnt3d Point(const Standard_Integer) const override;

			TnbGeo_EXPORT std::vector<Pnt3d> RetrievePoints() const override;

			TnbGeo_EXPORT void SetCoord(const Pnt3d&);
			TnbGeo_EXPORT void SetCoord(Pnt3d&&);

		};

		class segIntsct
			: public intsctEntity
		{

			/*Private Data*/

			std::array<Pnt3d, 2> theCoords_;

			// Private functions and operators [2/3/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<intsctEntity>(*this);
				ar& theCoords_;
			}

		public:

			static TnbGeo_EXPORT const unsigned short nbPoints;


			// default constructor [2/3/2023 Payvand]

			segIntsct()
			{}

			// constructors [2/3/2023 Payvand]

			segIntsct(const std::array<Pnt3d, 2>& theCoords)
				: theCoords_(theCoords)
			{}

			segIntsct(std::array<Pnt3d, 2>&& theCoords)
				: theCoords_(std::move(theCoords))
			{}


			// Public functions and operators [2/3/2023 Payvand]

			const auto& Coords() const
			{
				return theCoords_;
			}

			const auto& P0() const
			{
				return std::get<0>(Coords());
			}

			const auto& P1() const
			{
				return std::get<1>(Coords());
			}

			TnbGeo_EXPORT Standard_Boolean IsSegment() const override;

			TnbGeo_EXPORT Standard_Integer NbPoints() const override;
			TnbGeo_EXPORT Pnt3d Point(const Standard_Integer) const override;

			TnbGeo_EXPORT std::vector<Pnt3d> RetrievePoints() const override;

			TnbGeo_EXPORT void SetP0(const Pnt3d&);
			TnbGeo_EXPORT void SetP0(Pnt3d&&);
			TnbGeo_EXPORT void SetP1(const Pnt3d&);
			TnbGeo_EXPORT void SetP1(Pnt3d&&);

		};

		class triIntsct
			: public intsctEntity
		{

			/*Private Data*/

			std::array<Pnt3d, 3> theCoords_;

			// Private functions and operators [2/3/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<intsctEntity>(*this);
				ar& theCoords_;
			}

		public:

			static TnbGeo_EXPORT const unsigned short nbPoints;

			// default constructor [2/3/2023 Payvand]

			triIntsct()
			{}

			// constructors [2/3/2023 Payvand]

			triIntsct(const std::array<Pnt3d, 3>& theCoords)
				: theCoords_(theCoords)
			{}

			triIntsct(std::array<Pnt3d, 3>&& theCoords)
				: theCoords_(std::move(theCoords))
			{}

			// Public functions and operators [2/3/2023 Payvand]

			const auto& Coords() const
			{
				return theCoords_;
			}

			const auto& P0() const
			{
				return std::get<0>(Coords());
			}

			const auto& P1() const
			{
				return std::get<1>(Coords());
			}

			const auto& P2() const
			{
				return std::get<2>(Coords());
			}

			TnbGeo_EXPORT Standard_Boolean IsTriangle() const override;

			TnbGeo_EXPORT Standard_Integer NbPoints() const override;
			TnbGeo_EXPORT Pnt3d Point(const Standard_Integer) const override;

			TnbGeo_EXPORT std::vector<Pnt3d> RetrievePoints() const override;

			TnbGeo_EXPORT void SetP0(const Pnt3d&);
			TnbGeo_EXPORT void SetP0(Pnt3d&&);
			TnbGeo_EXPORT void SetP1(const Pnt3d&);
			TnbGeo_EXPORT void SetP1(Pnt3d&&);
			TnbGeo_EXPORT void SetP2(const Pnt3d&);
			TnbGeo_EXPORT void SetP2(Pnt3d&&);
		};

	private:

		/*Private Data*/

		std::shared_ptr<gp_Pln> thePlane_;

		std::shared_ptr<Entity3d_Triangulation> theMesh_;

		// results [2/3/2023 Payvand]

		std::vector<std::shared_ptr<intsctEntity>> theEntities_;


		// Private functions and operators [2/4/2023 Payvand]

		//static std::shared_ptr<intsctEntity> CalcIntersection(const gp_Pln& thePlane, const Entity_Triangle<const Pnt3d&>& thetri);

		static TnbGeo_EXPORT std::vector<std::shared_ptr<intsctEntity>> 
			CalcIntersections
			(
				const gp_Pln& thePlane,
				const Entity3d_Triangulation& theTris
			);

	public:

		// default constructor [2/3/2023 Payvand]

		GeoIntsct3d_PlnTris()
		{}


		// constructors [2/3/2023 Payvand]


		// Public functions and operators [2/3/2023 Payvand]

		const auto& Plane() const
		{
			return thePlane_;
		}

		const auto& Mesh() const
		{
			return theMesh_;
		}

		TnbGeo_EXPORT const std::vector<std::shared_ptr<intsctEntity>>& Entities() const;

		TnbGeo_EXPORT void Perform();

		TnbGeo_EXPORT void SetPlane(const std::shared_ptr<gp_Pln>&);
		TnbGeo_EXPORT void SetMesh(const std::shared_ptr<Entity3d_Triangulation>&);

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::GeoIntsct3d_PlnTris::intsctEntity);

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoIntsct3d_PlnTris::pntIntsct);
BOOST_CLASS_EXPORT_KEY(tnbLib::GeoIntsct3d_PlnTris::segIntsct);
BOOST_CLASS_EXPORT_KEY(tnbLib::GeoIntsct3d_PlnTris::triIntsct);

#endif // !_GeoIntsct3d_PlnTris_Header
