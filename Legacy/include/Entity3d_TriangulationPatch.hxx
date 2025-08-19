#pragma once
#ifndef _Entity3d_TriangulationPatch_Header
#define _Entity3d_TriangulationPatch_Header

#include <Entity3d_Triangulation.hxx>

namespace tnbLib
{

	class Entity3d_TriangulationPatch
		: public Entity3d_Triangulation
	{

	public:

		typedef std::vector<connectivity::dual> wireType;

		using Entity3d_Triangulation::connectList;

	private:

		/*Private Data*/

		std::shared_ptr<wireType> theOuter_;
		std::shared_ptr<std::vector<std::shared_ptr<wireType>>> theInners_;


		// Private functions and operators [2/17/2023 Payvand]

		TnbGeo_EXPORT void Check();


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Entity3d_Triangulation>(*this);
			ar& theOuter_;
			ar& theInners_;
		}


	protected:

		// default constructor [2/17/2023 Payvand]

		Entity3d_TriangulationPatch()
		{}

	public:

		static TnbGeo_EXPORT const std::string extension;

		// constructors [2/17/2023 Payvand]

		Entity3d_TriangulationPatch
		(
			const std::vector<Pnt3d>& thePnts,
			const connectList& theElements,
			const std::shared_ptr<wireType>& theOuter,
			const std::shared_ptr<std::vector<std::shared_ptr<wireType>>>& theInners
		)
			: Entity3d_Triangulation(thePnts, theElements)
			, theOuter_(theOuter)
			, theInners_(theInners)
		{
			Check();
		}

		Entity3d_TriangulationPatch
		(
			std::vector<Pnt3d>&& thePnts,
			connectList&& theElements,
			std::shared_ptr<wireType>&& theOuter,
			std::shared_ptr<std::vector<std::shared_ptr<wireType>>>&& theInners
		)
			: Entity3d_Triangulation(std::move(thePnts), std::move(theElements))
			, theOuter_(std::move(theOuter))
			, theInners_(std::move(theInners))
		{
			Check();
		}


		// Public functions and operators [2/17/2023 Payvand]

		const auto& Outer() const
		{
			return theOuter_;
		}

		const auto& Inners() const
		{
			return theInners_;
		}
		
	};
}

#endif // !_Entity3d_TriangulationPatch_Header
