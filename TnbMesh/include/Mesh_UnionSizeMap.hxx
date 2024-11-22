#pragma once
#ifndef _Mesh_UnionSizeMap_Header
#define _Mesh_UnionSizeMap_Header

#include <Mesh_UnionSizeMap_Traits.hxx>
#include <Mesh_Module.hxx>
#include <Entity_Box.hxx>
#include <Global_Done.hxx>
#include <Global_TypeDef.hxx>

#include <memory>
#include <list>

namespace tnbLib
{

	template<class BackMeshData>
	class Mesh_UnionSizeMap
		: public Global_Done
	{

		typedef typename Mesh_UnionSizeMap_Traits<BackMeshData>::Point Point;

		class TreeObject
		{

			/*Private Data*/

			Standard_Real theTolerance_;

			const std::list<std::shared_ptr<BackMeshData>>& theSizeMaps_;

		public:

			//- default constructor


			//- constructors

			TreeObject(const std::list<std::shared_ptr<BackMeshData>>& theSizeMaps, const Standard_Real theTol)
				: theSizeMaps_(theSizeMaps)
				, theTolerance_(theTol)
			{}

			
			//- public functions and operators

			auto Tolerance() const
			{
				return theTolerance_;
			}

			const auto& SizeMaps() const
			{
				return theSizeMaps_;
			}


			Standard_Real ElementSize(const Point&) const;
			Standard_Boolean Subdivide(const Entity_Box<Point>&) const;


			//- static functions and operators

			static TnbMesh_EXPORT Standard_Boolean Subdivider(const Entity_Box<Point>&, const TreeObject*);
		};

		/*Private Data*/

		std::list<std::shared_ptr<BackMeshData>> theSizeMaps_;

		Standard_Real theTolerance_;

		Standard_Integer theMinSubdivision_;
		Standard_Integer theMaxSubdivision_;


		std::shared_ptr<BackMeshData> theBackMesh_;

	public:

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MIN_SUBDIVISION;
		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_SUBDIVISION;

		static TnbMesh_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		//- default constructor

		Mesh_UnionSizeMap();

		//- constructors


		//- public functions and operators

		const auto& SizeMaps() const
		{
			return theSizeMaps_;
		}

		const auto& BackMesh() const
		{
			return theBackMesh_;
		}

		auto Tolerance() const
		{
			return theTolerance_;
		}

		auto MinSubdivision() const
		{
			return theMinSubdivision_;
		}

		auto MaxSubdivision() const
		{
			return theMaxSubdivision_;
		}

		void AddSizeMap(const std::shared_ptr<BackMeshData>&);

		void Perform();

		void SetTolerance(const Standard_Real);

		void SetMinSubdivision(const Standard_Integer);
		void SetMaxSubdivision(const Standard_Integer);


		//- static functions and operators

		static Entity_Box<Point> CalcBoundingBox(const std::list<std::shared_ptr<BackMeshData>>&);
	};
}

#include <Mesh_UnionSizeMapI.hxx>

#endif // !_Mesh_UnionSizeMap_Header
