//#pragma once
//#ifndef _SectPx_OffsetCloud_Header
//#define _SectPx_OffsetCloud_Header
//
//#include <SectPx_Cloud.hxx>
//
//namespace tnbLib
//{
//
//	class SectPx_OffsetCloud
//		: public SectPx_Cloud
//	{
//
//		/*Private Data*/
//
//		std::vector<Pnt2d> theCoords_;
//
//	public:
//
//		SectPx_OffsetCloud()
//		{}
//
//		SectPx_OffsetCloud
//		(
//			const Standard_Integer theIndex,
//			const word& theName
//		);
//
//		SectPx_OffsetCloud
//		(
//			const std::vector<Pnt2d>& theCoords
//		);
//
//		SectPx_OffsetCloud
//		(
//			const Standard_Integer theIndex,
//			const word& theName,
//			const std::vector<Pnt2d>& theCoords
//		);
//
//		SectPx_OffsetCloud
//		(
//			std::vector<Pnt2d>&& theCoords
//		);
//
//		SectPx_OffsetCloud
//		(
//			const Standard_Integer theIndex, 
//			const word& theName,
//			std::vector<Pnt2d>&& theCoords
//		);
//
//		auto NbCoords() const
//		{
//			return (Standard_Integer)theCoords_.size();
//		}
//
//		const auto& CoordsRef() const
//		{
//			return theCoords_;
//		}
//
//		std::vector<Pnt2d> GetCoords() const override;
//
//		void Import(const Pnt2d& theCoord);
//	};
//}
//
//#endif // !_SectPx_OffsetCloud_Header
