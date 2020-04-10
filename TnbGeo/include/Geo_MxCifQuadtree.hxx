#pragma once
#ifndef _Geo_MxCifQuadtree_Header
#define _Geo_MxCifQuadtree_Header

#include <Geo_MxCifQuadtree_Node.hxx>
#include <Geo_MxCifQuadtree_Quadrant.hxx>
#include <Global_AccessMethod.hxx>

namespace tnbLib
{

	class Geo_MxCifQuadtree_Base
	{

		/*Private Data*/

		Standard_Integer theMaxDivide_;

		Standard_Real theDmin_;

		Entity2d_Box theDomain_;

	protected:

		Geo_MxCifQuadtree_Base(const Entity2d_Box& theBox);

	public:

		static const Standard_Integer DEFAULT_MAX_DIVIDE;

		auto Dmin() const
		{
			return theDmin_;
		}

		const auto& Domain() const
		{
			return theDomain_;
		}

		enum class TreeCompare
		{
			LEFT,
			RIGHT,
			BOTH
		};

		enum class QuadCompare
		{
			NW,
			NE,
			SW,
			SE
		};

		enum class Axis
		{
			X,
			Y
		};

		static Axis OTHERAXIS(const Axis);

		static QuadCompare CQUAD(const QuadCompare);
		static QuadCompare CCQUAD(const QuadCompare);
		static QuadCompare OPQUAD(const QuadCompare);

		static Standard_Integer GetIndex(const Axis);

		static TreeCompare 
			BinCompare
			(
				const Entity2d_Box& theBox,
				const Standard_Real theX,
				const Axis theAxis
			);

		static TreeCompare OPDIRECTION(const TreeCompare);

		static QuadCompare 
			CIFCompare
			(
				const Entity2d_Box& theBox,
				const Pnt2d& theCx
			);

		static Standard_Real VF(const TreeCompare);
		static Standard_Real XF(const QuadCompare);
		static Standard_Real YF(const QuadCompare);

		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, MaxDivide)
	};

	template<class T>
	class Geo_MxCifQuadtree
		: public Geo_MxCifQuadtree_Base
	{

		typedef Geo_MxCifQuadtree_Node<T> node;
		typedef Geo_MxCifQuadtree_Quadrant<T> quad;

		/*Private Data*/


		const Entity2d_Box& (*GetBox_)(const std::shared_ptr<T>& theItem);
		Entity2d_Box(*GetModifiedBox_)(const std::shared_ptr<T>& theItem);

		Standard_Integer(*GetIndex_)(const std::shared_ptr<T>& theItem);

		std::shared_ptr<quad> theRoot_;

		

		static const std::shared_ptr<node>& BIN(const std::shared_ptr<quad>& t, const Axis);
		static std::shared_ptr<node>& ChangeBIN(const std::shared_ptr<quad>& t, const Axis);

		static const std::shared_ptr<node>& SON(const std::shared_ptr<node>& t, const TreeCompare);
		static std::shared_ptr<node>& ChangeSON(const std::shared_ptr<node>& t, const TreeCompare);

		static const std::shared_ptr<quad>& SON(const std::shared_ptr<quad>& t, const QuadCompare);
		static std::shared_ptr<quad>& ChangeSON(const std::shared_ptr<quad>& t, const QuadCompare);

		static Standard_Boolean 
			Intersection
			(
				const Entity2d_Box& theB,
				const Pnt2d& theCx,
				const Pnt2d& theLx
			);

		void InsertAxis
		(
			const std::shared_ptr<T>& theItem, 
			const std::shared_ptr<quad>& theCurrent, 
			const Standard_Real theCx, 
			const Standard_Real theLx, 
			const Axis ax
		);

		void Insert
		(
			const std::shared_ptr<T>& theItem,
			const std::shared_ptr<quad>& theRoot,
			const Pnt2d& theCx,
			const Pnt2d& theLx
		);

		void Remove
		(
			const std::shared_ptr<T>& theItem,
			std::shared_ptr<quad>& theRoot,
			const Pnt2d& theCx, 
			const Pnt2d& theLx
		);

		void Search
		(
			const Entity2d_Box& theArea, 
			const std::shared_ptr<quad>& theRoot, 
			const Pnt2d& theCx, 
			const Pnt2d& theLx, 
			std::vector<std::shared_ptr<T>>& theList
		) const;

		void CrossAxis
		(
			const Entity2d_Box& theArea,
			const std::shared_ptr<node>& theRoot,
			const Standard_Real theCx,
			const Standard_Real theLx, 
			const Axis theAxis,
			std::vector<std::shared_ptr<T>>& theList
		) const;

	public:

		

		Geo_MxCifQuadtree();

		void LoadBoundingBoxFunction(const Entity2d_Box& (*GetBoxFun)(const std::shared_ptr<T>&))
		{
			GetBox_ = GetBoxFun;
		}

		void LoadModifiedBoundingBoxFunction(Entity2d_Box(*GetModifiedBoxFun)(const std::shared_ptr<T>&))
		{
			GetModifiedBox_ = GetModifiedBoxFun;
		}

		void LoadGetIndexFunction(Standard_Integer(*GetIndexFun)(const std::shared_ptr<T>&))
		{
			GetIndex_ = GetIndexFun;
		}

		void Insert(const std::shared_ptr<T>& theItem);

		void Remove(const std::shared_ptr<T>& theItem);

		void Search(const Entity2d_Box& theArea, std::vector<std::shared_ptr<T>>& theQ) const;

		std::vector<std::shared_ptr<T>> Search(const Entity2d_Box& theArea) const;
	};
}


#include <Geo_MxCifQuadtreeI.hxx>

#endif // !_Geo_MxCifQuadtree_Header
