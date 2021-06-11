#pragma once
#ifndef _PtdModel_AirfoilSectionQ_Header
#define _PtdModel_AirfoilSectionQ_Header

#include <PtdModel_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Pnt3d;

	template<class Point>
	class PtdModel_AirfoilSectionQ
		: public PtdModel_Entity
	{

	public:

		struct faceQ
		{
			std::vector<Point> Points;

			//- default constructor
			faceQ()
			{}

			//- constructors
			faceQ(std::vector<Point>&& pts)
				: Points(std::move(pts))
			{}

			faceQ(const std::vector<Point>& pts)
				: Points(pts)
			{}

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & Points;
			}
		};

		struct backQ
		{
			std::vector<Point> Points;

			//- default constructor
			backQ()
			{}

			//- constructors
			backQ(std::vector<Point>&& pts)
				: Points(std::move(pts))
			{}

			backQ(const std::vector<Point>& pts)
				: Points(pts)
			{}

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & Points;
			}
		};

	private:

		/*Private Data*/

		faceQ theFace_;
		backQ theBack_;

		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<PtdModel_Entity>(*this);
			ar & theFace_;
			ar & theBack_;
		}

	protected:


		//- default constructor
		PtdModel_AirfoilSectionQ()
		{}


		//- constructors

		PtdModel_AirfoilSectionQ(const faceQ&, const backQ&);

		PtdModel_AirfoilSectionQ(faceQ&&, backQ&&);

	public:

		virtual ~PtdModel_AirfoilSectionQ()
		{}

		//- public functions and operators

		const auto& FaceQ() const
		{
			return theFace_;
		}

		const auto& BackQ() const
		{
			return theBack_;
		}

		void SetQ(const faceQ&);
		void SetQ(const backQ&);
		void SetQ(faceQ&&);
		void SetQ(backQ&&);

	};
}

#include <PtdModel_AirfoilSectionQI.hxx>

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_AirfoilSectionQ<Pnt2d>);
BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_AirfoilSectionQ<Pnt3d>);

#endif // !_PtdModel_AirfoilSectionQ_Header
